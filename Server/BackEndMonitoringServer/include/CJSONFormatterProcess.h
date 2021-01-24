#pragma once

#include "CJSONFormatter.h"

class CProcessInfo;

class CJSONFormatterProcess :
    public CJSONFormatter
{
public:
    CJSONFormatterProcess();
    CJSONFormatterProcess(const CJSONFormatterProcess&) = delete;
    CJSONFormatterProcess(CJSONFormatterProcess&&) = delete;

    bool TryAddProcessData(const CProcessInfo& data_to_json);
};