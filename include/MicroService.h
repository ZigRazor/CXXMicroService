#ifndef MICROSERVICE_H
#define MICROSERVICE_H

#pragma once

#include "MicroserviceLogger.h"
#include "ProtocolType.h"
#include "ServiceConfiguration.h"
#include <zmq.hpp>
#include <map>
#include <list>

namespace MicroServices
{

    class MicroService
    {
    public:
        MicroService(const ServiceConfiguration &serviceConfiguration);
        MicroService(const std::string &configFilePath);
        ~MicroService();

        void run();
        void stop();

        void addService(const std::string &subServiceName, std::function<int(const std::string &)> subService);
        void deleteService(const std::string &subServiceName);

        const std::string &getDigest() const;

        const ServiceConfiguration &getServiceConfiguration() const;

    protected:
        MICROSERVICE_LOG_LOGGER logger;

    private:
        ServiceConfiguration serviceConfiguration;

        zmq::context_t ctx;
        zmq::socket_t *socket;

        std::string digest;

        std::map<std::string, std::function<int(const std::string &)>> serviceMap;

        void init();
        int stopCommand(const std::string &digest); //not overridable
    };

}

#endif
