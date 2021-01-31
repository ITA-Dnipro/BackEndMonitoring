#include "stdafx.h"
#include "CXMLDataReader.h"
#include "CLogger/include/Log.h"

CXMLDataReader::CXMLDataReader() : 
	m_is_file_loaded_(false), m_p_file_(nullptr)
{
}

bool CXMLDataReader::Initialize(const std::string& file_path)
{
	m_p_file_ = std::move(std::make_unique<pugi::xml_document>());
	m_is_file_loaded_ = m_p_file_->load_file(file_path.c_str());
	if(!m_is_file_loaded_) 
		CLOG_ERROR_WITH_PARAMS("Failed to load file with this path", file_path);
	return m_is_file_loaded_;
}

bool CXMLDataReader::IsFileInitialized() const
{
	if (nullptr == m_p_file_ || !m_is_file_loaded_)
	{
		m_p_file_ ? CLOG_ERROR("Pointer to file is nullptr") : CLOG_ERROR("File is not loaded");
		return false;
	}

	return true;
}

bool CXMLDataReader::TryToGetStringData(const std::string& data_path, std::string& return_data) const
{
	if (IsFileInitialized())
	{
		pugi::xpath_node point;
		if (TryToSearchNode(data_path, point))
		{
			return_data = point.node().child_value();
			FormConfigurationString(return_data);
			if ("" == return_data)
				CLOG_ERROR_WITH_PARAMS("Empty data with this path", data_path);
			return true;
		}
	}

	return false;
}


bool CXMLDataReader::TryToSearchNode(const std::string& data_path, pugi::xpath_node& node) const
{
	node = m_p_file_->select_node(data_path.c_str());
	if (nullptr == node)
	{
		CLOG_ERROR_WITH_PARAMS("Failed to find Node with this path", data_path);
		return false;
	}
	return true;
}

void CXMLDataReader::FormConfigurationString(std::string& data_to_form)
{
	size_t first = data_to_form.find_first_of("\""), last = data_to_form.find_last_of("\"");
	data_to_form = data_to_form.substr(first + 1, last - (first + 1));
}

