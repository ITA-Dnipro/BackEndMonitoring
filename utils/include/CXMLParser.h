#pragma once

#include "pugixml.hpp"
#include "IParser.h"

class CXMLParser : public IParser
{
public:
    CXMLParser() = default;
    CXMLParser(CXMLParser&) = delete;
    CXMLParser(CXMLParser&&) = delete;

    ~CXMLParser() override = default;

    bool Initialize(const std::string& path_to_configuration_file) override;

    bool TryToGetConfiguration(const std::string& data_path,
        bool& return_data) const override;
    bool TryToGetConfiguration(const std::string& data_path,
        int& return_data) const override;
    bool TryToGetConfiguration(const std::string& data_path,
        std::string& return_data) const override;

private:
    bool TryToGetStringDataFromFile(const std::string& data_path,
        std::string& return_data) const;
    static void FormConfigurationString(std::string& data_to_form);

private:
    std::unique_ptr<pugi::xml_document> p_docfile;
};
