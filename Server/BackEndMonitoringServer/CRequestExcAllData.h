#pragma once

class CRequestExcAllData : public IRequestExc
{
public:
	CRequestExcAllData() = delete;
	CRequestExcAllData(const std::string& request);
	CRequestExcAllData(CRequestExcAllData&& orig);

	virtual bool Execute(std::string& answer) override;

};

