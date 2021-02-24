#include "stdafx.h"

#include "CReadFileWrapper.h"

CReadFileWrapper::CReadFileWrapper(const std::filesystem::path& path)
        :m_is_initialized(false), m_path(path), m_p_file(nullptr)
{ }

bool CReadFileWrapper::Initialize()
{
    bool success = false;
    success = std::filesystem::exists(m_path);
    if(m_is_initialized)
    { return false;}

    std::string temp = m_path.string();
    if(!success)
    { return success;}

    m_p_file = std::make_unique<std::ifstream>(std::ifstream(m_path, 
                                               std::ios::in | std::ios::binary));
    success = m_p_file->is_open();

    m_is_initialized = success;
    return success;
}

bool CReadFileWrapper::ReadWholeFile(std::string& buffer)
{
    if (m_is_initialized)
    {
        buffer.clear( );
        m_p_file->seekg(0, std::ios::end);        
        buffer.resize(m_p_file->tellg( ));
        m_p_file->seekg(0, std::ios::beg);
        m_p_file->read(buffer.data(), buffer.size( ));
    }
    return m_p_file->good( );
}

bool CReadFileWrapper::Read(std::string& buffer, std::streamsize count)
{
    if (m_is_initialized)
    {
        buffer.clear( );
        buffer.resize(count);
        return m_p_file->read(buffer.data( ), count).good( );
    }
    return false;
}

bool CReadFileWrapper::ReadLine(std::string& buffer) 
{
    if(m_is_initialized)
    {
        return std::getline(*m_p_file, buffer).good();
    }
    return false;
}

bool CReadFileWrapper::ReadPrevLine(std::string& buffer)
{
    buffer.clear( );
    char sym;
    
    
    while (ReadPrevSym(sym))
    {
        if(sym == '\n')
        { return true;}
        buffer.insert(0, 1, sym);
    }

    return false;
}

bool CReadFileWrapper::ReadSym(char& buffer) 
{
    if(m_is_initialized)
    {
        return m_p_file->get(buffer).good();
    }
    return false;
}

bool CReadFileWrapper::ReadPrevSym(char& buffer)
{
    if (m_is_initialized)
    {
        std::streampos cur_pos = 0;
        if(!GetPosition(cur_pos))
        { return false;}
        
        cur_pos -= 2;
        if(!MoveCursorTo(cur_pos))
        { return false;}

        return m_p_file->get(buffer).good( );
    }
    return false;
}

bool CReadFileWrapper::GetPosition(std::streampos& pos)
{
    pos = m_p_file->tellg( );
    return m_p_file->good( );
}

bool CReadFileWrapper::MoveCursorTo(std::streampos pos)
{
    m_p_file->clear();
    m_p_file->seekg(pos);
    return m_p_file->good();
}

CReadFileWrapper::~CReadFileWrapper() 
{
    if(m_is_initialized)
    {     m_p_file->close();}
}
