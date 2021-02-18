#pragma once

class CRequestExcAllData : public IRequestExc
{
public:
	CRequestExcAllData() = delete;
	explicit CRequestExcAllData(const std::string& request, 
		std::shared_ptr<CDataProvider> data_base);
	CRequestExcAllData(CRequestExcAllData&& orig) = default;

	virtual bool Execute(std::string& answer) override;

};

