#pragma once

struct ISettings
{
	ISettings() = default;
	ISettings(const ISettings&) = delete;
	ISettings(ISettings&&) = delete;
	virtual ~ISettings() = default;

	virtual void ReadConfigurationFromFile() = 0;
}; 
