#include "stdafx.h"

#include "CReadFileWrapper.h"

CReadFileWrapper::CReadFileWrapper(const std::filesystem::path& path)
        :m_is_initialized(false), m_path(path), m_p_file(nullptr)
{ }

bool CReadFileWrapper::Initialize()
{
    if(m_is_initialized)
    { return false;}

    std::string temp = m_path.string();
    bool success = std::filesystem::exists(m_path);
    if(!success)
    { return success;}

    m_p_file = std::make_unique<std::ifstream>(std::ifstream(m_path, std::ios::in));
    success = m_p_file->is_open();

    m_is_initialized = success;
    return success;
}

bool CReadFileWrapper::ReadLine(std::string& buffer) {
    if(m_is_initialized)
    {
        return std::getline(*m_p_file, buffer).good();
    }
    return false;
}

bool CReadFileWrapper::ReadSym(char& buffer) {
    if(m_is_initialized)
    {
        return m_p_file->get(buffer).good();
    }
    return false;
}

CReadFileWrapper::~CReadFileWrapper() {
    if(m_is_initialized)
    {     m_p_file->close();}
}
