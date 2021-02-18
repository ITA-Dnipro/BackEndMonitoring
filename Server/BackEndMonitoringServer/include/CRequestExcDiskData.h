#pragma once
#include "IRequestExc.h"
class CRequestExcDiskData :
    public IRequestExc
{
public:
    CRequestExcDiskData() = delete;
    explicit CRequestExcDiskData(const std::string& request,
        std::shared_ptr<CDataProvider> data_base);
    CRequestExcDiskData(CRequestExcDiskData&& orig) = default;

    virtual bool Execute(std::string& answer) override;
};

