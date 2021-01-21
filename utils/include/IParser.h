#pragma once

class IParser
{
public:
    IParser() = default;
    IParser(IParser&) = delete;
    IParser(IParser&&) = delete;
    virtual ~IParser() = default;

    virtual bool Initialize(const std::string&) = 0;

    virtual bool TryToGetConfiguration(const std::string&, bool&) const = 0;
    virtual bool TryToGetConfiguration(const std::string&, int&) const = 0;
    virtual bool TryToGetConfiguration(const std::string&, std::string&) const = 0;

private:
};
