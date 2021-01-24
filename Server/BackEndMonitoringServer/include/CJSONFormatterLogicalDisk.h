#pragma once

#include "CJSONFormatter.h"

class CLogicalDiskInfo;

class CJSONFormatterLogicalDisk :
    public CJSONFormatter
{
public:
    CJSONFormatterLogicalDisk();
    bool TryAddLogicalDiskData(const CLogicalDiskInfo& data_to_json,
                               unsigned short disk_number);
};