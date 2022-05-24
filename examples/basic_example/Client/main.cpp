#include <zmq.hpp>
#include <json.hpp>
#include <iostream>
#include "MicroserviceLogger.h"
#include "MicroService.h"
#include "ZMQMicroServiceClient.h"
#include "ProtocolType.h"
#include <thread>

using namespace MicroServices;

int main(){    
    /*
    ServiceConfiguration sc = {
        "service_name",
        ProtocolType::IPC,
        "127.0.0.1",
        "5555"
    };
    */
    std::string configFilePath = "../examples/config/service_config.json";
    //ZMQMicroServiceClient ms_client(sc);
    ZMQMicroServiceClient ms_client(configFilePath);
    std::thread ms_client_thread(&ZMQMicroServiceClient::run,&ms_client);
    if(ms_client_thread.joinable()){
        ms_client_thread.join();
    }
    
    return 0;
}