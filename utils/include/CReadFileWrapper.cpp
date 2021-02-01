#include "stdafx.h"

#include "CLogger/include/Log.h"

#include "CReadFileWrapper.h"

CReadFileWrapper::CReadFileWrapper(const std::filesystem::path& path)
        :m_is_initialized(false), m_path(path), m_p_file(nullptr)
{ }

bool CReadFileWrapper::Initialize()
{
    bool success = false;
    CLOG_DEBUG_START_FUNCTION();
    success = std::filesystem::exists(m_path);
    CLOG_TRACE_VAR_CREATION(success);
    if(m_is_initialized)
    { return false;}

    std::string temp = m_path.string();
    CLOG_TRACE_VAR_CREATION(temp);
    if(!success)
    { return success;}

    m_p_file = std::make_unique<std::ifstream>(std::ifstream(m_path, std::ios::in));
    success = m_p_file->is_open();

    m_is_initialized = success;
    CLOG_DEBUG_END_FUNCTION();
    return success;
}

bool CReadFileWrapper::ReadLine(std::string& buffer) 
{
    CLOG_DEBUG_START_FUNCTION();
    if(m_is_initialized)
    {
        return std::getline(*m_p_file, buffer).good();
    }
    CLOG_DEBUG_END_FUNCTION();
    return false;
}

bool CReadFileWrapper::ReadSym(char& buffer) 
{
    CLOG_DEBUG_START_FUNCTION();
    if(m_is_initialized)
    {
        return m_p_file->get(buffer).good();
    }
    CLOG_DEBUG_END_FUNCTION();
    return false;
}

CReadFileWrapper::~CReadFileWrapper() 
{
    CLOG_DEBUG_START_FUNCTION();
    if(m_is_initialized)
    {     m_p_file->close();}
    CLOG_DEBUG_END_FUNCTION();
}
