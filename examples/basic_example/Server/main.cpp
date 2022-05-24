#include <zmq.hpp>
#include <json.hpp>
#include <iostream>
#include "MicroserviceLogger.h"
#include "MicroService.h"
#include "ZMQMicroServiceClient.h"
#include "ProtocolType.h"
#include <thread>
#include <unistd.h>

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
    //MicroService ms(sc);
    MicroService ms(configFilePath);
    
    std::thread ms_thread(&MicroService::run,&ms);

    sleep(10);

    ms.stop();
    
    if(ms_thread.joinable()){
        ms_thread.join();
    }
    
    return 0;
}