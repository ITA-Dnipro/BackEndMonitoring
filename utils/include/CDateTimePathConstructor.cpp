#include "stdafx.h"

#include "Log.h"
#include "Utils.h"

#include "CDateTimePathConstructor.h"


CDateTimePathConstructor::CDateTimePathConstructor(
    const std::string& general_folder) : m_general_folder(general_folder),
    m_is_created_general_folder(false)
{ 
    CLOG_DEBUG_START_FUNCTION( );
    CLOG_DEBUG_END_FUNCTION( );
}

bool CDateTimePathConstructor::UpdatePathToFile(std::string& path)
{
    CLOG_DEBUG_START_FUNCTION( );
    if (!IsCreatedGeneralFolder())
    {
        CLOG_DEBUG("Trying to create general folder");
        if (!Utils::TryCreateDirectory(m_general_folder))
        {
            CLOG_ERROR("Can't create general folder");
            return false;
        }
        m_is_created_general_folder = true;
    }
    char symbol_for_sect = Utils::DetermineSectDividingSymbol(path);
    CLOG_TRACE_VAR_CREATION(symbol_for_sect);

    m_updated_path = path;
    std::size_t posistion_last_founded = m_updated_path.find_last_of('.');
    CLOG_TRACE_VAR_CREATION(posistion_last_founded);

    if (std::string::npos != posistion_last_founded )
    {
        m_extension = m_updated_path.substr(posistion_last_founded);
        m_updated_path.erase(posistion_last_founded);
    }
    else
    {
        CLOG_WARNING("Can't find dividing symbol for extesion");
    }
    posistion_last_founded = m_updated_path.find_last_of(symbol_for_sect);

    if (std::string::npos != posistion_last_founded)
    {
        m_hour = m_updated_path.substr(posistion_last_founded + 1,
                                       m_length_of_part);
        m_updated_path.erase(posistion_last_founded);
    }
    else
    {
        CLOG_WARNING("Can't find symbol for section in path");
    }
    if (Utils::IsHourPassed(m_hour))
    {
        CLOG_DEBUG("Hour passed, trying to create new dir");
    }
    posistion_last_founded = m_updated_path.find_last_of(symbol_for_sect);
    if (std::string::npos != posistion_last_founded)
    {
        m_day = m_updated_path.substr(posistion_last_founded);
        m_updated_path.erase(posistion_last_founded);
        if (m_day.length() > m_length_of_part)
        {
            m_day = m_day.substr(0, m_length_of_part);
        }
    }

    if (Utils::IsDayPassed(m_day))
    {
        CLOG_DEBUG("Day passed, trying to create new dir");
    }
    m_updated_path = m_general_folder + symbol_for_sect + m_day;
    if (!Utils::TryCreateDirectory(m_updated_path))
    {
        CLOG_ERROR("can't create directory");
        return false;
    }
    path = m_updated_path + symbol_for_sect + m_hour + m_extension;
    CLOG_DEBUG_END_FUNCTION( );
    return true;
}

bool CDateTimePathConstructor::IsCreatedGeneralFolder() const
{
    CLOG_DEBUG_START_FUNCTION( );
    CLOG_DEBUG_END_FUNCTION( );
    return m_is_created_general_folder;
}
