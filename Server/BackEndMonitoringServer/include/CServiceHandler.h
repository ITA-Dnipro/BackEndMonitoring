#pragma once

#include "CService.h"

#ifdef _WIN64
class ServiceHandler
{
public:
	explicit ServiceHandler(std::unique_ptr<CService> service);

    ServiceHandler(const ServiceHandler& other) = delete;
    ServiceHandler& operator=(const ServiceHandler& other) = delete;

    ServiceHandler(ServiceHandler&& other) = delete;
    ServiceHandler& operator=(ServiceHandler&& other) = delete;

	bool Install() const;
	bool Uninstall() const;

	bool Run() const;

private:
	bool Start() const;
	bool Stop() const;

private:
	std::unique_ptr<CService> m_p_service;
};
#endif
