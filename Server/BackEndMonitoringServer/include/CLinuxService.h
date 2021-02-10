#pragma once

#include "CService.h"

class CLinuxService : public CService
{
public:
    CLinuxService();

    bool Run();

private:
    static void HandleSignal(int signal);

private:
    static CLinuxService* m_p_instance;
};
