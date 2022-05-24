#ifndef __SERVICECONFIGURATION_H__
#define __SERVICECONFIGURATION_H__

#pragma once

#include "ProtocolType.h"
#include <string>
#include "json.hpp"

using json = nlohmann::json;

namespace MicroServices
{

    struct ServiceConfiguration
    {
        std::string serviceName;
        ProtocolType protocol;
        std::string address;
        std::string port;
    };

    static void to_json(json &j, const ServiceConfiguration &sc)
    {
        j = json{{"service_name", sc.serviceName}, {"protocol", ProtocolTypeToString[sc.protocol]}, {"address", sc.address}, {"port", sc.port}};
    }

    static void from_json(const json &j, ServiceConfiguration &sc)
    {
        j.at("service_name").get_to(sc.serviceName);
        sc.protocol = ProtocolTypeFromString[j.at("protocol").get<std::string>()];
        j.at("address").get_to(sc.address);
        j.at("port").get_to(sc.port);
    }
}
#endif // __SERVICECONFIGURATION_H__