#ifndef CXXMICROSERVICE_CURLHANDLE_H
#define CXXMICROSERVICE_CURLHANDLE_H

#include <curl/curl.h>

/**
 * @class CurlHandle
 * @brief Singleton class for managing libcurl global state and providing a single instance of the CURL* handle.
 *
 * The CurlHandle class ensures that libcurl global state is initialized only once and provides a single
 * instance of the CURL* handle that can be shared among multiple HTTPClient instances. This helps in
 * efficient resource management and avoids redundant initialization of libcurl.
 *
 * Usage:
 * To get the singleton instance of CurlHandle, use the static `instance()` method:
 *     CurlHandle& curlHandle = CurlHandle::instance();
 *
 * Note: Since this class follows the singleton design pattern, the constructor is private and cannot be
 *       accessed directly. The CurlHandle class provides a single instance that should be accessed
 *       through the `instance()` method.
 */
class CurlHandle {

public:
    /**
     * @brief Returns the singleton instance of the CurlHandle class.
     * @return Reference to the singleton instance of CurlHandle.
     */
    static CurlHandle &instance();

    CurlHandle(CurlHandle const &) = delete;
    CurlHandle(CurlHandle &&) = delete;
    CurlHandle &operator=(CurlHandle const &) = delete;
    CurlHandle &operator=(CurlHandle &&) = delete;

    /**
     * @brief Destructor for the CurlHandle class.
     * @note This destructor cleans up and closes the libcurl global state when the program exits.
     */
    ~CurlHandle();

private:
    /**
     * @brief Private constructor for the CurlHandle class.
     * @note The constructor is private to enforce the singleton design pattern.
     *       The CurlHandle instance should be accessed through the static `instance()` method.
     */
    CurlHandle();
};

#endif //CXXMICROSERVICE_CURLHANDLE_H
