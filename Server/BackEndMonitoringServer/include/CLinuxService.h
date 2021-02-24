#pragma once

#include "CService.h"

#ifdef __linux__

class CLinuxService : public CService
{
public:
    CLinuxService();

    [[nodiscard]] bool Run();

private:
    static void HandleSignal(int signal);

private:
    static CLinuxService* m_p_instance;
};

#endif
