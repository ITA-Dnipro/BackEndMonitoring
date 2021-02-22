#include "stdafx.h"

#include "CLinuxService.h"

#ifdef __linux__

CLinuxService* CLinuxService::m_p_instance = nullptr;

CLinuxService::CLinuxService()
{
    signal(SIGTERM, CLinuxService::HandleSignal);
}

bool CLinuxService::Run()
{
    m_p_instance = this;
    RunServer();
    return true;
}

void CLinuxService::HandleSignal(int signal)
{
    if (signal == SIGTERM)
    {
        m_p_instance->m_stop_event.Set();
        CLOG_DEBUG("Stop event setted");
        m_p_instance->m_p_acceptor_socket->ShutDown();
        CLOG_DEBUG("Close acception");
        return;
    }
}

#endif
