#pragma once

class CRequestExcProcessData : public IRequestExc
{
public:
    CRequestExcProcessData() = delete;
    explicit CRequestExcProcessData(const std::string& request,
        std::shared_ptr<CDataProvider> data_base);
    CRequestExcProcessData(const CRequestExcProcessData&) = delete;
    CRequestExcProcessData(CRequestExcProcessData&& orig) noexcept = default;

    virtual bool Execute(std::string& answer) override;

};

