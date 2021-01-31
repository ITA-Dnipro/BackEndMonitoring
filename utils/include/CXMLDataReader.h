#pragma once
#include "CDataReader.h"
#include "pugixml.hpp"

class CXMLDataReader : public CDataReader
{
public:
	CXMLDataReader();
	CXMLDataReader(const CXMLDataReader&) = delete;
	CXMLDataReader(CXMLDataReader&&) = delete;
	~CXMLDataReader() override = default;

	bool Initialize(const std::string& file_path) override;
	bool IsFileInitialized() const override;
	bool TryToGetStringData(const std::string& data_path, std::string& return_data) const override;

private:
	bool TryToSearchNode(const std::string& data_path, pugi::xpath_node& node) const;
	static void FormConfigurationString(std::string& data_to_form);

private:
	bool is_file_loaded_;
	std::unique_ptr<pugi::xml_document> p_file_;

};
