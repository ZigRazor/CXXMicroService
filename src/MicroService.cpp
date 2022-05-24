#include "MicroService.h"
#include <openssl/sha.h>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>


namespace MicroServices
{

    MicroService::MicroService(const ServiceConfiguration &serviceConfiguration) : ctx()
    {
        MICROSERVICE_LOG_INIT("../config/LoggerConfig.xml");
        MICROSERVICE_LOG_GET_LOGGER(logger, "MicroService");
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Created MicroService " << serviceConfiguration.serviceName);

        this->serviceConfiguration = serviceConfiguration;

        init();
    }

    MicroService::MicroService(const std::string &configFilePath) : ctx(){
        MICROSERVICE_LOG_INIT("../config/LoggerConfig.xml");
        MICROSERVICE_LOG_GET_LOGGER(logger, "MicroService");
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Reading Configuration File at " << configFilePath);

        std::ifstream i(configFilePath);
        json j;
        i >> j;

        from_json(j, serviceConfiguration);

        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Created MicroService " << serviceConfiguration.serviceName);

        init();
    }

    MicroService::~MicroService()
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Destructed MicroService " << serviceConfiguration.serviceName);
        if (socket != nullptr)
        {
            delete socket;
        }
    }
    void MicroService::run()
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Run MicroService");
        std::string endpoint = ProtocolTypeToString[serviceConfiguration.protocol] + "://" + serviceConfiguration.address + ":" + serviceConfiguration.port;
        socket->bind(endpoint);
        while (true)
        {
            zmq::message_t msg(1024);
            auto res = socket->recv(msg, zmq::recv_flags::none);
            MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Received " << (res.has_value() ? res.value() : 0) << " bytes");

            MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Message Received: " << msg.str());
            std::string msg_data = msg.to_string();
            std::string msg_commandType = msg_data.substr(0, msg_data.find(" "));
            if (serviceMap.find(msg_commandType) != serviceMap.end())
            {
                MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Found command " << msg_commandType);
                std::string msg_args = msg_data.substr(msg_data.find(" ") + 1);
                auto result = serviceMap.find(msg_commandType)->second(msg_args);
                if (msg_commandType == "STOP" && result == 0)
                { // stop service
                    break;
                }
            }
            else
            {
                MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Command " << msg_commandType << " not found");
            }
        }
        return;
    }

    void MicroService::stop()
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Stop ZMQMicroServiceClient " << serviceConfiguration.serviceName);

        zmq::context_t client_ctx;
        zmq::socket_t client_socket(ctx, zmq::socket_type::client);
        std::string endpoint = ProtocolTypeToString[serviceConfiguration.protocol] + "://" + serviceConfiguration.address + ":" + serviceConfiguration.port;
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Endpoint: " << endpoint);
        client_socket.connect(endpoint);
        std::stringstream msg_ss;
        msg_ss << "STOP " << digest;
        zmq::message_t msg(msg_ss.str().c_str(), msg_ss.str().size());
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Sending Message: " << msg.str());
        auto res = client_socket.send(msg, zmq::send_flags::dontwait);
        client_socket.close();

        return;
    }

    void MicroService::addService(const std::string &subServiceName, std::function<int(const std::string &)> subService)
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Add SubService " << subServiceName);
        serviceMap[subServiceName] = subService;
    }

    void MicroService::deleteService(const std::string &subServiceName)
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Delete SubService " << subServiceName);
        serviceMap.erase(subServiceName);
    }

    const std::string &MicroService::getDigest() const
    {
        return digest;
    }

    const ServiceConfiguration &MicroService::getServiceConfiguration() const
    {
        return serviceConfiguration;
    }

    void MicroService::init(){
        socket = new zmq::socket_t(ctx, zmq::socket_type::server);
        // calcutate digest
        SHA256_CTX ctx;
        unsigned char md[512];
        auto time = std::chrono::system_clock::now();
        std::stringstream ss;
        ss << serviceConfiguration.serviceName << ProtocolTypeToString[serviceConfiguration.protocol] << serviceConfiguration.address << serviceConfiguration.port << time.time_since_epoch().count();

        SHA256_Init(&ctx);
        SHA256_Update(&ctx, ss.str().c_str(), ss.str().size());
        SHA256_Final(md, &ctx);
        digest = std::string(md, md + sizeof(md) / sizeof(md[0]));

        /////////////////////

        // Add Stop Service Command
        addService("STOP", std::bind(&MicroService::stopCommand, this, std::placeholders::_1));
        ///////////////////
    }

    int MicroService::stopCommand(const std::string &digest)
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Received Digest Size: " << digest.size() << " Expected: " << digest.size());
        if (digest == this->digest)
        {
            socket->close();
            MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Exiting... " << serviceConfiguration.serviceName);
            return 0;
        }
        else
        {
            return -1;
        }
    }

}