#include <iostream>

// Defitnition
#include "ClientDef.h"

class Client
{
public:
    bool SendEvent(const char *pTargetChannel, unsigned int iEventCode, std::string &rSrc, bool useOnline, ClientDef::ServerInfo serverInfo);
};