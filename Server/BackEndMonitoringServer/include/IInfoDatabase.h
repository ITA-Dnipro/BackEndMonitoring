#pragma once

class IInfoDatabase
{ 
public:
	virtual bool GetAllInfo(std::string& data) = 0;
	virtual bool GetLastInfo(std::string& data) = 0;
	virtual bool GetSelectedInfo(time_t from, time_t to, std::string& data) = 0;
};

