#ifndef CXXMICROSERVICE_HTTP_H
#define CXXMICROSERVICE_HTTP_H

#include <functional>
#include <memory>
#include <curl/curl.h>
#include <utility>
#include "CurlHandle.h"
#include <zmq.hpp>

using ProgressCallback = std::function<int(void *, double, double, double, double)>;
using LogCallback = std::function<void(const std::string &)>;
using HeadersMap = std::unordered_map<std::string, std::string>;
using ByteBuffer = std::vector<char>;

/**
* @brief Class for handling HTTP requests using libcurl.
 *
 * The HTTPClient class provides methods to perform various HTTP requests such as GET, POST, PUT, DELETE, etc.
 * using libcurl library. It also supports SSL certificates, progress callbacks, and custom headers.
 */
class HTTPClient {
public:
    struct PostFormData {
        PostFormData();

        ~PostFormData();

        void AddFileData(const std::string &fieldName, const std::string &fileData);

        void AddFieldData(const std::string &fieldName, const std::string &fieldValue);

        std::unique_ptr<curl_httppost, void (*)(curl_httppost *)> m_pFormPost;
        std::unique_ptr<curl_httppost, void (*)(curl_httppost *)> m_pLastFormptr;
    };

    struct ProgressData {
        ProgressData()
                : lastRunTime(0),
                  curlHandle(nullptr, curl_easy_cleanup),
                  owner(nullptr, [](void *) {}) {}

        double lastRunTime;
        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curlHandle;
        std::unique_ptr<void, void (*)(void *)> owner;

    };

    struct HttpResponse {
        HttpResponse()
                : iCode(0) {}

        int iCode;
        HeadersMap mapHeaders;
        std::unique_ptr<std::string> strBody;
    };

    enum SettingsFlag {
        NO_FLAGS = 0x00,
        ENABLE_LOG = 0x01,
        VERIFY_PEER = 0x02,
        VERIFY_HOST = 0x04,
        ALL_FLAGS = ENABLE_LOG | VERIFY_PEER | VERIFY_HOST
    };

    /**
    * @brief Constructs an HTTPClient object.
    * @param oLogger The log callback function used to log messages.
    * @param mCurlHandle The reference to the CurlHandle instance used for HTTP requests.
    */
    explicit HTTPClient(LogCallback oLogger, CurlHandle &mCurlHandle);

    virtual ~HTTPClient();

    HTTPClient(const HTTPClient &Copy) = delete;

    HTTPClient &operator=(const HTTPClient &Copy) = delete;

    /**
     * @brief Set the callback function and owner for progress monitoring of HTTP requests.
     *
     * @param owner The owner pointer to be passed to the progress callback function.
     * @param callback The callback function that will be called during the progress of the request.
     */
    void SetProgressCallbackOwner(void *owner, const ProgressCallback &callback);

    /**
     * @brief Set the proxy address to be used for HTTP requests.
     *
     * @param proxyAddress The proxy address in the format "http://proxy.example.com:8080".
     */
    void SetProxyAddress(const std::string &proxyAddress);

    /**
     * @brief Set the timeout for HTTP requests in milliseconds.
     *
     * @param timeoutMilliseconds The timeout value in milliseconds.
     */
    void SetTimeoutMilliseconds(const int &timeoutMilliseconds);

    /**
     * @brief Set the no signal flag for HTTP requests.
     *
     * By default, libcurl uses signals to perform timeouts. Setting this flag to true will disable the use
     * of signals, and timeouts will be handled within the application code.
     *
     * @param noSignal A boolean value indicating whether to use signals or not.
     */
    void SetNoSignalFlag(const bool &noSignal);

    /**
     * @brief Enable or disable HTTPS support for HTTP requests.
     *
     * By default, HTTPS support is disabled. Setting this flag to true enables support for HTTPS.
     *
     * @param enableHTTPS A boolean value indicating whether to enable HTTPS support.
     */
    void SetHTTPSFlag(const bool &enableHTTPS);

    /**
     * @brief Get the currently set progress callback function.
     *
     * @return The progress callback function currently set.
     */
    const ProgressCallback &GetProgressCallback() const;

    /**
     * @brief Get the owner pointer associated with the progress callback function.
     *
     * @return The owner pointer associated with the progress callback.
     */
    void *GetProgressCallbackOwner() const;

    /**
     * @brief Get the currently set proxy address.
     *
     * @return The proxy address in the format "http://proxy.example.com:8080".
     */
    const std::string &GetProxyAddress() const;

    /**
     * @brief Get the currently set timeout for HTTP requests in milliseconds.
     *
     * @return The timeout value in milliseconds.
     */
    const int &GetTimeoutMilliseconds() const;

    /**
     * @brief Get the currently set no signal flag.
     *
     * @return A boolean value indicating whether the no signal flag is enabled or not.
     */
    const bool &GetNoSignalFlag() const;

    /**
     * @brief Get the URL associated with the HTTPClient instance.
     *
     * @return The URL used for HTTP requests.
     */
    const std::string &GetURL() const;

    /**
     * @brief Get the currently set settings flags for the HTTPClient instance.
     *
     * The settings flags determine the behavior of the HTTPClient, such as enabling logs, verifying
     * the peer, verifying the host, etc.
     *
     * @return The current settings flags (a combination of HTTPClient::SettingsFlag values).
     */
    const unsigned char GetSettingsFlags() const;

    /**
     * @brief Get the currently set HTTPS flag.
     *
     * @return A boolean value indicating whether HTTPS support is enabled or not.
     */
    const bool &GetHTTPSFlag() const;


    /**
     * @brief Initialize the HTTP session for making requests.
     *
     * This method should be called before making any HTTP requests. It initializes the underlying libcurl
     * session and performs necessary setup. The optional parameters enableHTTPS and settingsFlags can be used
     * to enable HTTPS support and configure other settings, respectively.
     *
     * @param enableHTTPS A boolean value indicating whether to enable HTTPS support (default is false).
     * @param settingsFlags The settings flags to configure the behavior of the HTTPClient
     *                     (a combination of HTTPClient::SettingsFlag values). Default is ALL_FLAGS.
     * @return A boolean value indicating whether the session initialization was successful.
     */
    bool InitializeSession(bool enableHTTPS = false, unsigned char settingsFlags = ALL_FLAGS);

    /**
     * @brief Cleanup the HTTP session and release resources.
     *
     * This method should be called when the HTTPClient instance is no longer needed. It cleans up the libcurl
     * session and releases associated resources. It is essential to call this method to avoid memory leaks.
     *
     * @return A boolean value indicating whether the session cleanup was successful.
     */
    virtual bool CleanupSession();

    /**
     * @brief Get the raw libcurl session handle.
     *
     * This method allows accessing the underlying libcurl session handle if required. However, it is generally
     * not necessary to use this handle directly, as the HTTPClient class abstracts most of the functionality.
     *
     * @return The raw libcurl session handle.
     */
    const CURL *GetCurlSession() const;

/**
     * @brief Perform a GET request and retrieve the response as a string.
     *
     * This method performs a GET request to the specified URL and retrieves the response as a string in the
     * responseText parameter. The HTTP status code of the response is returned in the httpStatusCode parameter.
     *
     * @param url The URL to perform the GET request.
     * @param responseText The string to store the response data.
     * @param httpStatusCode The variable to store the HTTP status code of the response.
     * @return A boolean value indicating whether the request was successful.
     */
    bool GetText(const std::string &url, std::string &responseText, long &httpStatusCode);

    /**
     * @brief Download a file from the specified URL and save it to a local file.
     *
     * This method performs a GET request to the specified URL and downloads the file to the localFilePath.
     * The HTTP status code of the response is returned in the httpStatusCode parameter.
     *
     * @param localFilePath The local file path where the downloaded file will be saved.
     * @param url The URL from which the file will be downloaded.
     * @param httpStatusCode The variable to store the HTTP status code of the response.
     * @return A boolean value indicating whether the download was successful.
     */
    bool DownloadFile(const std::string &localFilePath, const std::string &url, long &httpStatusCode);

    /**
     * @brief Download a file from the specified URL and store it in a vector of unsigned chars.
     *
     * This method performs a GET request to the specified URL and downloads the file. The downloaded file
     * data is stored in the fileData vector, and the HTTP status code of the response is returned in the
     * httpStatusCode parameter.
     *
     * @param fileData The vector to store the downloaded file data as unsigned chars.
     * @param url The URL from which the file will be downloaded.
     * @param httpStatusCode The variable to store the HTTP status code of the response.
     * @return A boolean value indicating whether the download was successful.
     */
    bool DownloadFile(std::vector<unsigned char> &fileData, const std::string &url, long &httpStatusCode);

    /**
     * @brief Upload form data to the specified URL using a POST request.
     *
     * This method performs a POST request to the specified URL and uploads the form data as specified
     * in the formData parameter. The HTTP status code of the response is returned in the httpStatusCode parameter.
     *
     * @param url The URL to which the form data will be uploaded.
     * @param formData The map containing the form data in key-value pairs.
     * @param httpStatusCode The variable to store the HTTP status code of the response.
     * @return A boolean value indicating whether the upload was successful.
     */
    bool UploadForm(const std::string &url, const HeadersMap &formData, long &httpStatusCode);

    /**
     * @brief Add a custom header to be included in all subsequent HTTP requests.
     *
     * This method adds a custom header to the list of headers that will be included in all subsequent HTTP
     * requests made with the HTTPClient instance.
     *
     * @param header The custom header string to add (e.g., "Authorization: Bearer xxxxxxxxx").
     */
    void AddHeader(const std::string &header);

    /**
     * @brief Perform a HEAD request to the specified URL.
     *
     * This method performs a HEAD request to the specified URL and retrieves the response information in the
     * HttpResponse parameter.
     *
     * @param url The URL to perform the HEAD request.
     * @param headers The map containing custom headers to include in the request.
     * @param response The HttpResponse object to store the response information.
     * @return A boolean value indicating whether the request was successful.
     */
    bool head(const std::string &url, const HeadersMap &headers, HttpResponse &response);

    /**
     * @brief Perform a GET request to the specified URL.
     *
     * This method performs a GET request to the specified URL and retrieves the response in the HttpResponse
     * parameter.
     *
     * @param url The URL to perform the GET request.
     * @param headers The map containing custom headers to include in the request.
     * @param response The HttpResponse object to store the response.
     * @return A boolean value indicating whether the request was successful.
     */
    bool get(const std::string &url, const HeadersMap &headers, HttpResponse &response);

    /**
     * @brief Perform a DELETE request to the specified URL.
     *
     * This method performs a DELETE request to the specified URL and retrieves the response in the HttpResponse
     * parameter.
     *
     * @param url The URL to perform the DELETE request.
     * @param headers The map containing custom headers to include in the request.
     * @param response The HttpResponse object to store the response.
     * @return A boolean value indicating whether the request was successful.
     */
    bool destroy(const std::string &url, const HeadersMap &headers, HttpResponse &response);

    /**
     * @brief Perform a POST request to the specified URL.
     *
     * This method performs a POST request to the specified URL with the provided postData and retrieves the
     * response in the HttpResponse parameter. Custom headers can also be included in the request using the
     * headers parameter.
     *
     * @param url The URL to perform the POST request.
     * @param headers The map containing custom headers to include in the request.
     * @param postData The data to be included in the POST request body.
     * @param response The HttpResponse object to store the response.
     * @return A boolean value indicating whether the request was successful.
     */
    bool post(const std::string &url, const HeadersMap &headers,
              const std::string &postData, HttpResponse &response);

    /**
     * @brief Perform a PUT request to the specified URL.
     *
     * This method performs a PUT request to the specified URL with the provided putData and retrieves the
     * response in the HttpResponse parameter. Custom headers can also be included in the request using the
     * headers parameter.
     *
     * @param url The URL to perform the PUT request.
     * @param headers The map containing custom headers to include in the request.
     * @param putData The data to be included in the PUT request body.
     * @param response The HttpResponse object to store the response.
     * @return A boolean value indicating whether the request was successful.
     */
    bool put(const std::string &url, const HeadersMap &headers,
             const std::string &putData, HttpResponse &response);

    /**
     * @brief Perform a PATCH request to the specified URL.
     *
     * This method performs a PATCH request to the specified URL with the provided data and retrieves the
     * response in the HttpResponse parameter. Custom headers can also be included in the request using the
     * headers parameter.
     *
     * @param url The URL to perform the PATCH request.
     * @param headers The map containing custom headers to include in the request.
     * @param data The data to be included in the PATCH request body.
     * @param response The HttpResponse object to store the response.
     * @return A boolean value indicating whether the request was successful.
     */
    bool patch(const std::string &url, const HeadersMap &headers,
               const ByteBuffer &data, HttpResponse &response);

    /**
     * @brief Get the path to the global SSL certificate file.
     *
     * This static method returns the path to the global SSL certificate file used by all instances of HTTPClient.
     *
     * @return The path to the global SSL certificate file.
     */
    static const std::string &GetGlobalCertificateFile();

    /**
     * @brief Set the path to the global SSL certificate file.
     *
     * This static method sets the path to the global SSL certificate file to be used by all instances of HTTPClient.
     *
     * @param filePath The path to the global SSL certificate file.
     */
    static void SetGlobalCertificateFile(const std::string &filePath);

    /**
 * @brief Set the SSL certificate file for the current HTTPClient instance.
 *
 * This method sets the SSL certificate file to be used for the current HTTPClient instance.
 *
 * @param filePath The path to the SSL certificate file.
 */
    void SetSSLCertificateFile(const std::string &filePath);

    /**
     * @brief Get the path to the SSL certificate file used by the current HTTPClient instance.
     *
     * This method returns the path to the SSL certificate file used by the current HTTPClient instance.
     *
     * @return The path to the SSL certificate file.
     */
    const std::string &GetSSLCertificateFile() const;

    /**
     * @brief Set the SSL key file for the current HTTPClient instance.
     *
     * This method sets the SSL key file to be used for the current HTTPClient instance.
     *
     * @param filePath The path to the SSL key file.
     */
    void SetSSLKeyFile(const std::string &filePath);

    /**
     * @brief Get the path to the SSL key file used by the current HTTPClient instance.
     *
     * This method returns the path to the SSL key file used by the current HTTPClient instance.
     *
     * @return The path to the SSL key file.
     */
    const std::string &GetSSLKeyFile() const;

    /**
     * @brief Set the password for the SSL key file of the current HTTPClient instance.
     *
     * This method sets the password for the SSL key file used by the current HTTPClient instance.
     *
     * @param password The password for the SSL key file.
     */
    void SetSSLKeyPassword(const std::string &password);

    /**
     * @brief Get the password for the SSL key file used by the current HTTPClient instance.
     *
     * This method returns the password for the SSL key file used by the current HTTPClient instance.
     *
     * @return The password for the SSL key file.
     */
    const std::string &GetSSLKeyPassword() const;


#ifdef DEBUG_CURL
    static void SetCurlTraceLogDirectory(const std::string& strPath);
#endif

#ifdef WINDOWS
    static std::string AnsiToUtf8(const std::string& ansiStr);
   static std::wstring Utf8ToUtf16(const std::string& str);
#endif

protected:
    // Struct for payload to upload on POST requests.
    struct UploadObject {
        UploadObject() : pszData(nullptr), usLength(0) {}

        const char *pszData; // Data to upload
        size_t usLength; // Length of the data to upload
    };

    // Common operations are performed here
    const CURLcode Perform();

    void UpdateURL(const std::string &strURL);

    const bool InitRestRequest(const std::string &strUrl, const HeadersMap &Headers, HttpResponse &Response);

    const bool PostRestRequest(const CURLcode ePerformCode, HttpResponse &Response);

    // Curl callbacks
    static size_t WriteInStringCallback(void *ptr, size_t size, size_t nmemb, void *data);

    static size_t WriteToFileCallback(void *ptr, size_t size, size_t nmemb, void *data);

    static size_t WriteToMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

    static size_t ReadFromFileCallback(void *ptr, size_t size, size_t nmemb, void *stream);

    static size_t ThrowAwayCallback(void *ptr, size_t size, size_t nmemb, void *data);

    static size_t RestWriteCallback(void *ptr, size_t size, size_t nmemb, void *userdata);

    static size_t RestHeaderCallback(void *ptr, size_t size, size_t nmemb, void *userdata);

    static size_t RestReadCallback(void *ptr, size_t size, size_t nmemb, void *userdata);

    // String Helpers
    static std::string StringFormat(const std::string &strFormat, ...);

    static void TrimSpaces(std::string &str);

    // Curl Debug information
#ifdef DEBUG_CURL
    static int DebugCallback(CURL* curl, curl_infotype curl_info_type, char* strace, size_t nSize, void* pFile);
    void StartCurlDebug() const;
    void EndCurlDebug() const;
#endif

    std::string m_strURL;
    std::string m_strProxy;

    bool m_bNoSignal;
    bool m_bHTTPS;
    SettingsFlag m_eSettingsFlags;

    std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)> m_pHeaderList{nullptr, curl_slist_free_all};
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> m_pCurlSession;

    // SSL
    static std::string s_strCertificationAuthorityFile;
    std::string m_strSSLCertFile;
    std::string m_strSSLKeyFile;
    std::string m_strSSLKeyPwd;


    int m_iCurlTimeout;

    // Progress function
    ProgressCallback m_fnProgressCallback;
    ProgressData m_ProgressData;
    bool m_bProgressCallbackSet;

    // Log printer callback
    LogCallback m_Logger;

private:
#ifdef DEBUG_CURL
    static std::string s_strCurlTraceLogDirectory;
    mutable std::ofstream m_ofFileCurlTrace;
#endif

    CurlHandle &m_curlHandle;


};

inline HTTPClient::SettingsFlag operator|(HTTPClient::SettingsFlag a, HTTPClient::SettingsFlag b) {
    return static_cast<HTTPClient::SettingsFlag>(static_cast<int>(a) | static_cast<int>(b));
}

// Logs messages
#define LOG_ERROR_EMPTY_HOST_MSG                "[HTTPClient][Error] Empty hostname."
#define LOG_WARNING_OBJECT_NOT_CLEANED          "[HTTPClient][Warning] Object was freed before calling " \
                                                        "CHTTPClient::CleanupSession(). The API session was cleaned though."
#define LOG_ERROR_CURL_ALREADY_INIT_MSG         "[HTTPClient][Error] Curl session is already initialized ! " \
                                                        "Use CleanupSession() to clean the present one."
#define LOG_ERROR_CURL_NOT_INIT_MSG             "[HTTPClient][Error] Curl session is not initialized ! Use InitSession() before."


#define LOG_ERROR_CURL_REQ_FAILURE_FORMAT       "[HTTPClient][Error] Unable to perform request from '%s' " \
                                                        "(Error = %d | %s) (HTTP_Status = %ld)"
#define LOG_ERROR_CURL_REST_FAILURE_FORMAT      "[HTTPClient][Error] Unable to perform a REST request from '%s' " \
                                                        "(Error = %d | %s)"
#define LOG_ERROR_CURL_DOWNLOAD_FAILURE_FORMAT  "[HTTPClient][Error] Unable to perform a request - '%s' from '%s' " \
                                                        "(Error = %d | %s) (HTTP_Status = %ld)"
#define LOG_ERROR_DOWNLOAD_FILE_FORMAT          "[HTTPClient][Error] Unable to open local file %s"


#endif //CXXMICROSERVICE_HTTP_H