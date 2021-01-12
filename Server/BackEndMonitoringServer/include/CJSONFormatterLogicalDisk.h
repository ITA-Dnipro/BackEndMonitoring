#pragma once

#include "CJSONFormatter.h"
#include "CLogicalDiskStatus.h"

class CJSONFormatterLogicalDisk :
    public CJSONFormatter
{
public:
    CJSONFormatterLogicalDisk() : CJSONFormatter()
    { };

    bool TryAddLogicalDiskData(
        const CLogicalDiskStatus& data_to_json,
        unsigned short disk_number);
};