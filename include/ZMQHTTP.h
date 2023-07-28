#ifndef CXXMICROSERVICE_ZMQHTTP_H
#define CXXMICROSERVICE_ZMQHTTP_H

#include "HTTP.h"

/**
 * @brief The ZMQHTTP class provides methods for integrating ZeroMQ and performing HTTP requests using libcurl.
 */
class ZMQHTTP {
public:
    /**
    * @brief Constructs a ZMQHTTP object.
    * @param oLogger The log callback function used to log messages.
    * @param mCurlHandle The reference to the CurlHandle instance used for HTTP requests.
    */
    ZMQHTTP(LogCallback oLogger, CurlHandle &mCurlHandle);

    /**
     * @brief Destructor for the ZMQHTTP object.
     */
    virtual ~ZMQHTTP();

    /**
     * @brief Connects to the ZeroMQ socket with the specified address.
     * @param address The address to connect to, e.g., "tcp://127.0.0.1:5555".
     */
    void connectZMQ(const std::string &address);

    /**
     * @brief Disconnects from the ZeroMQ socket with the specified address.
     * @param address The address to disconnect from, e.g., "tcp://127.0.0.1:5555".
     */
    void disconnectZMQ(const std::string &address);

    /**
     * @brief Sends a message to the connected ZeroMQ socket.
     * @param message The message to send.
     */
    void sendZMQMessage(const std::string &message);

    /**
     * @brief Handles an HTTP GET request to the specified URL.
     * @param url The URL to send the GET request to.
     */
    void handleHttpGet(const std::string &url);

    /**
     * @brief Handles an HTTP POST request to the specified URL with the provided data.
     * @param url The URL to send the POST request to.
     * @param data The data to include in the POST request body.
     */
    void handleHttpPost(const std::string &url, const std::string &data);

    /**
     * @brief Handles an HTTP PUT request to the specified URL with the provided data.
     * @param url The URL to send the PUT request to.
     * @param data The data to include in the PUT request body.
     */
    void handleHttpPut(const std::string &url, const std::string &data);

    /**
     * @brief Handles an HTTP DELETE request to the specified URL.
     * @param url The URL to send the DELETE request to.
     */
    void handleHttpDelete(const std::string &url);

    /**
     * @brief Gets the global certificate file path used for SSL certificate verification.
     * @return The global certificate file path.
     */
    static const std::string &GetGlobalCertificateFile();

    /**
     * @brief Sets the global certificate file path used for SSL certificate verification.
     * @param filePath The path to the certificate file.
     */
    static void SetGlobalCertificateFile(const std::string &filePath);

    /**
     * @brief Sets the SSL certificate file path used for SSL certificate verification for the current HTTPClient instance.
     * @param filePath The path to the certificate file.
     */
    void SetSSLCertificateFile(const std::string &filePath);

    /**
     * @brief Gets the SSL key file path used for SSL certificate verification for the current HTTPClient instance.
     * @return The SSL key file path.
     */
    const std::string &GetSSLKeyFile() const;

    /**
     * @brief Sets the SSL key password used for SSL certificate verification for the current HTTPClient instance.
     * @param password The password for the SSL key.
     */
    void SetSSLKeyPassword(const std::string &password);

    /**
     * @brief Gets the SSL key password used for SSL certificate verification for the current HTTPClient instance.
     * @return The SSL key password.
     */
    const std::string &GetSSLKeyPassword();

    /**
     * @brief Downloads a file from the specified URL and saves it to the local file system.
     * @param localFile The path to the local file where the downloaded content will be saved.
     * @param url The URL of the file to download.
     * @param[out] httpStatusCode The variable to store the HTTP status code of the response.
     * @return True if the download was successful, false otherwise.
     */
    bool DownloadFile(const std::string &localFile, const std::string &url, long &httpStatusCode);

    /**
     * @brief Downloads a file from the specified URL and stores its content in the provided byte vector.
     * @param[out] fileData The vector to store the downloaded file's content.
     * @param url The URL of the file to download.
     * @param[out] httpStatusCode The variable to store the HTTP status code of the response.
     * @return True if the download was successful, false otherwise.
     */
    bool DownloadFile(std::vector<unsigned char> &fileData, const std::string &url, long &httpStatusCode);

    /**
     * @brief Uploads form data to the specified URL using an HTTP POST request.
     * @param url The URL where the form data will be sent.
     * @param formData The map containing form data in key-value pairs.
     * @param[out] httpStatusCode The variable to store the HTTP status code of the response.
     * @return True if the upload was successful, false otherwise.
     */
    bool UploadForm(const std::string &url, const HeadersMap &formData, long &httpStatusCode);

    /**
     * @brief Adds a custom header to the HTTP request.
     * @param header The custom header to be added in the format "Header-Name: Header-Value".
     */
    void AddHeader(const std::string &header);

    /**
     * @brief Initializes the HTTP session for making HTTP requests.
     * @param enableHTTPS Flag indicating whether to enable HTTPS (secure HTTP) support.
     * @param settingsFlags The combination of settings flags to configure the session.
     *        Default value is HTTPClient::ALL_FLAGS which enables logging, peer verification, and host verification.
     * @return True if the session initialization was successful, false otherwise.
     */
    bool InitializeSession(bool enableHTTPS = false, unsigned char settingsFlags = HTTPClient::ALL_FLAGS);

    /**
     * @brief Cleans up and closes the current HTTP session.
     * @note This function should be called before the program exits or when the HTTP session is no longer needed to free resources properly.
     * @return True if the cleanup was successful, false otherwise.
     */
    virtual bool CleanupSession();

    /**
     * @brief Retrieves the underlying libcurl session handle.
     * @return A pointer to the libcurl session handle (CURL*) used by the HTTPClient for HTTP requests.
     */
    const CURL *GetCurlSession() const;

private:
    std::unique_ptr<zmq::context_t> zmqContext;
    std::unique_ptr<zmq::socket_t> zmqSocket;

    HTTPClient httpClient;
};


#endif //CXXMICROSERVICE_ZMQHTTP_H
