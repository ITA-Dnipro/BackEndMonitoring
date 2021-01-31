#pragma once

#include <string>

namespace StrToNumWrapper {

	bool TryStoi(const std::string& val, int& var);
	bool TryStoul(const std::string& val, unsigned int& var);
	bool TryStoll(const std::string& val, long long int& var);
	bool TryStoull(const std::string& val, unsigned long long int& var);
	bool TryStof(const std::string& val, float& var);
	bool TryStod(const std::string& val, double& var);
	bool TryStold(const std::string& val, long double& var);

}
