#pragma once

#include "CService.h"
#include "CLinuxService.h"
#include "CWindowsService.h"

#if defined(_WIN64) || defined(_WIN32)

class ServiceHandler
{
public:
	explicit ServiceHandler(std::unique_ptr<CWindowsService> service);

    ServiceHandler(const ServiceHandler& other) = delete;
    ServiceHandler& operator=(const ServiceHandler& other) = delete;

    ServiceHandler(ServiceHandler&& other) = delete;
    ServiceHandler& operator=(ServiceHandler&& other) = delete;

	[[nodiscard]] bool Install() const;
	[[nodiscard]] bool Uninstall() const;

	[[nodiscard]] bool Run() const;

private:
	[[nodiscard]] bool Start() const;
	[[nodiscard]] bool Stop() const;

private:
	std::unique_ptr<CWindowsService> m_p_service;
};

#endif
