#include "stdafx.h"
#include "CXMLDataReader.h"
#include "CLogger/include/Log.h"

CXMLDataReader::CXMLDataReader() : 
	m_is_file_loaded_(false), m_p_file_(nullptr)
{
}

bool CXMLDataReader::Initialize(const std::string& file_path)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_file_ = std::move(std::make_unique<pugi::xml_document>());
	m_is_file_loaded_ = m_p_file_->load_file(file_path.c_str());
	if(!m_is_file_loaded_) 
		CLOG_ERROR_WITH_PARAMS("Failed to load file with this path", file_path);
	CLOG_DEBUG_END_FUNCTION();
	return m_is_file_loaded_;
}

bool CXMLDataReader::IsFileInitialized() const
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == m_p_file_ || !m_is_file_loaded_)
	{
		m_p_file_ ? CLOG_ERROR("Pointer to file is nullptr") : CLOG_ERROR("File is not loaded");
		return false;
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CXMLDataReader::TryToGetStringData(const std::string& data_path, std::string& return_data) const
{
	CLOG_DEBUG_START_FUNCTION();
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
	CLOG_DEBUG_END_FUNCTION();
	return false;
}


bool CXMLDataReader::TryToSearchNode(const std::string& data_path, pugi::xpath_node& node) const
{
	CLOG_DEBUG_START_FUNCTION();
	node = m_p_file_->select_node(data_path.c_str());
	if (nullptr == node)
	{
		CLOG_ERROR_WITH_PARAMS("Failed to find Node with this path", data_path);
		return false;
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

void CXMLDataReader::FormConfigurationString(std::string& data_to_form)
{
	CLOG_DEBUG_START_FUNCTION();
	size_t first = data_to_form.find_first_of("\""), last = data_to_form.find_last_of("\"");
	CLOG_TRACE_VAR_CREATION(first);
	data_to_form = data_to_form.substr(first + 1, last - (first + 1));
	CLOG_DEBUG_END_FUNCTION();
}

