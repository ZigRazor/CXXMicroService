#ifndef ZMQMICROSERVICECLIENT_H
#define ZMQMICROSERVICECLIENT_H

#pragma once

#include <zmq.hpp>
#include "MicroserviceLogger.h"
#include "ProtocolType.h"
#include "ServiceConfiguration.h"

namespace MicroServices
{

    class ZMQMicroServiceClient
    {
    public:
        ZMQMicroServiceClient(const ServiceConfiguration &serviceConfiguration);
        ZMQMicroServiceClient(const std::string& configFilePath);
        ~ZMQMicroServiceClient();

        void run();
        void stop();

    private:
        ServiceConfiguration serviceConfiguration;

        zmq::context_t ctx;
        zmq::socket_t *socket;

        MICROSERVICE_LOG_LOGGER logger;
    };

}

#endif