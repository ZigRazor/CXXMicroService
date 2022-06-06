#include "ZMQMicroServiceClient.h"
#include <fstream>

namespace MicroServices
{

    ZMQMicroServiceClient::ZMQMicroServiceClient(const ServiceConfiguration &serviceConfiguration) : ctx()
    {
        MICROSERVICE_LOG_INIT("../config/LoggerConfig.xml");
        MICROSERVICE_LOG_GET_LOGGER(logger, "MicroService");
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Created ZMQMicroServiceClient " << serviceConfiguration.serviceName);

        this->serviceConfiguration = serviceConfiguration;

        socket = new zmq::socket_t(ctx, zmq::socket_type::client);
    }

    ZMQMicroServiceClient::ZMQMicroServiceClient(const std::string& configFilePath){
        MICROSERVICE_LOG_INIT("../config/LoggerConfig.xml");
        MICROSERVICE_LOG_GET_LOGGER(logger, "MicroService");
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Reading Configuration File at " << configFilePath);

        std::ifstream i(configFilePath);
        json j;
        i >> j;

        from_json(j, serviceConfiguration);

        this->serviceConfiguration = serviceConfiguration;

        socket = new zmq::socket_t(ctx, zmq::socket_type::client);

        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Created ZMQMicroServiceClient " << serviceConfiguration.serviceName);
    }

    ZMQMicroServiceClient::~ZMQMicroServiceClient()
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Destructed ZMQMicroServiceClient " << serviceConfiguration.serviceName);
        if (socket != nullptr)
        {
            delete socket;
        }
    }

    void ZMQMicroServiceClient::run()
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Run ZMQMicroServiceClient");
        std::string endpoint = ProtocolTypeToString[serviceConfiguration.protocol] + "://" + serviceConfiguration.address + ":" + serviceConfiguration.port;
        socket->connect(endpoint);
        zmq::message_t msg("hello world!", 12);
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Sending Message: " << msg.str());
        auto res = socket->send(msg, zmq::send_flags::dontwait);
        return;
    }

    void ZMQMicroServiceClient::stop()
    {
        MICROSERVICE_LOG(MICROSERVICE_LOG_DEBUG, logger, "Stop ZMQMicroServiceClient " << serviceConfiguration.serviceName);
        socket->close();
        return;
    }

}
