#pragma once

#include "IFindFileByValue.h"

class CFindFileByDateTime : public IFindFileByValue
{
public:
	virtual bool TryFindFileByValue(const std::string& date_time,
		const std::string& path_to_general_folder, std::string& path_to_file) 
		override;
	
private:
	std::size_t m_position;
	std::string m_date;
	std::string m_hour;
};

