#pragma once
#include "IRequestExc.h"
class CRequestExcProcessData :
    public IRequestExc
{
public:
    CRequestExcProcessData() = delete;
    CRequestExcProcessData(const std::string& request);
    CRequestExcProcessData(CRequestExcProcessData&& orig);

    virtual bool Execute(std::string& answer) override;

};

