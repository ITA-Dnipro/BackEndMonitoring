#pragma once

#include "CJSONFormatter.h"

class CProcess;

class CJSONFormatterProcess :
    public CJSONFormatter
{
public:
    CJSONFormatterProcess() : CJSONFormatter()
    {};
    CJSONFormatterProcess(const CJSONFormatterProcess&) = delete;
    CJSONFormatterProcess(CJSONFormatterProcess&&) = delete;

    bool TryAddProcessData(const CProcess& data_to_json);
};