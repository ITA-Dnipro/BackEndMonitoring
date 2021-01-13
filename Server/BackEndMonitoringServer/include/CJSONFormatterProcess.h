#pragma once

#include "CJSONFormatter.h"
#include "CProcess.h"

class CJSONFormatterProcess :
    public CJSONFormatter
{
public:
    CJSONFormatterProcess() : CJSONFormatter()
    {};

    bool TryAddProcessData(const CProcess& data_to_json);
};