#include "SendEvent.h"

bool Client::SendEvent(const char *pTargetChannel, unsigned int iEventCode, std::string &rSrc, bool useOnline, ClientDef::ServerInfo serverInfo)
{
    bool retValue = false;

    // if you want not to boolean flag, please check chnnale.
    if( false == useOnline)
    {
        // origin method
    }
    else
    {
        // REST API
    }


    return retValue;   
}