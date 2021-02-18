#pragma once
#include "IRequestExc.h"
class CRequestExcProcessData :
    public IRequestExc
{
public:
    CRequestExcProcessData() = delete;
    explicit CRequestExcProcessData(const std::string& request,
        std::shared_ptr<CDataProvider> data_base);
    CRequestExcProcessData(CRequestExcProcessData&& orig) = default;

    virtual bool Execute(std::string& answer) override;

};

