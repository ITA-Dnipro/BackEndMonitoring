#include "stdafx.h"
#include "CXMLParser.h"


bool CXMLParser::Initialize(const std::string& path_to_configuration_file)
{
    p_docfile = std::move(std::make_unique<pugi::xml_document>());
    return p_docfile->load_file(path_to_configuration_file.c_str());
}

bool CXMLParser::TryToGetConfiguration(const std::string& data_path,
    bool& return_data) const
{
    std::string tmp_answer;
    if (TryToGetStringDataFromFile(data_path, tmp_answer))
    {
        return_data = tmp_answer == "enable";
        if (!return_data && tmp_answer != "disable")
        {
            std::cerr << "Failed to convert data to bool! with data path: "
                + data_path << std::endl;
            return false;
        }

        return true;
    }

    return false;
}

bool CXMLParser::TryToGetConfiguration(const std::string& data_path,
    int& return_data) const
{
    try
    {
        std::string tmp_answer;
        if (TryToGetStringDataFromFile(data_path, tmp_answer))
        {
            size_t pos;
            return_data = std::stoi(tmp_answer, &pos);
            if (tmp_answer.size() != pos)
            {
                throw std::invalid_argument("Failed to convert data to integer with this path: " 
                                                + data_path);
            }
            return true;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return false;
}


bool CXMLParser::TryToGetConfiguration(const std::string& data_path,
    std::string& return_data) const
{
    return TryToGetStringDataFromFile(data_path, return_data);
}

bool CXMLParser::TryToGetStringDataFromFile(const std::string& data_path,
    std::string& return_data) const
{
    try
    {
        if (!p_docfile)
            throw std::invalid_argument("xml file pointer is empty!!!");

        const auto point = p_docfile->select_node(data_path.c_str());
        return_data = point.node().child_value();

        if ("" == return_data)
            throw std::invalid_argument("Empty string. Failed to find data!! with this path: " + data_path);

        FormConfigurationString(return_data);
        return true;
    }
    catch (const std::exception& e)
    {

        std::cerr << e.what() << std::endl;
    }

    return false;
}

void CXMLParser::FormConfigurationString(std::string& return_data)
{
    return_data = return_data.substr((return_data.find_first_of("\"") + 1),
                                        (return_data.find_last_of("\"") - 2));
}