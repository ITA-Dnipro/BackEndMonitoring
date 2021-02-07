#include "stdafx.h"

#include "CLogger/include/Log.h"

#include "StrToNumWrapper.h"

namespace StrToNumWrapper
{
    bool TryStoi(const std::string& val, int& var)
    {
        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stoi(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

    bool TryStoul(const std::string& val, unsigned int& var) {
        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stoul(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

    bool TryStoll(const std::string& val, long long int& var) {
        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stoll(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

    bool TryStoull(const std::string& val, unsigned long long int& var) {
        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stoull(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

    bool TryStof(const std::string& val, float& var) {

        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stof(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

    bool TryStod(const std::string& val, double& var) {
        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stod(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

    bool TryStold(const std::string& val, long double& var) {
        bool success = false;
        CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(val, var);
        var = std::stold(val);
        success = true;
        CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
        return success;
    }

}
