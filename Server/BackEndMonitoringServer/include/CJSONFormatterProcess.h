#pragma once

#include "CJSONFormatter.h"
#include "CProcess.h"

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