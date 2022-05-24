#ifndef __PROTOCOLTYPE_H__
#define __PROTOCOLTYPE_H__

#pragma once

#include <map>
#include <string>

namespace MicroServices{

typedef enum ProtocolType_Enumerated {
    IPC,
    INPROC,
    TCP,
    UDP,
    HTTP
} ProtocolType;

static std::map<ProtocolType,std::string> ProtocolTypeToString = {
    {IPC,"ipc"},
    {INPROC,"inproc"},
    {TCP,"tcp"},
    {UDP,"udp"},
    {HTTP,"http"}
};
static std::map<std::string,ProtocolType> ProtocolTypeFromString = {
    {"ipc",IPC},
    {"inproc",INPROC},
    {"tcp",TCP},
    {"udp",UDP},
    {"http",HTTP}
};

}



#endif // __PROTOCOLTYPE_H__