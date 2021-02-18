#pragma once
#include "IRequestExc.h"
class CRequestExcDiskData :
    public IRequestExc
{
public:
    CRequestExcDiskData() = delete;
    CRequestExcDiskData(const std::string& request);
    CRequestExcDiskData(CRequestExcDiskData&& orig);

    virtual bool Execute(std::string& answer) override;
};

