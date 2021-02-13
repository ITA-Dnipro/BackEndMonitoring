#include "stdafx.h"
#include "CDateTimePathConstructor.h"
#include "Utils.h"

CDateTimePathConstructor::CDateTimePathConstructor(
    const std::string& general_folder) : m_general_folder(general_folder),
    m_is_created_general_folder(false)
{ }

bool CDateTimePathConstructor::UpdatePathToFile(std::string& path)
{
    if (!IsCreatedGeneralFolder())
    {
        if (!Utils::TryCreateDirectory(m_general_folder))
        {
            // to logger
            return false;
        }
        m_is_created_general_folder = true;
    }
    char symbol_for_sect = Utils::DetermineSectDividingSymbol(path);

    m_updated_path = path;
    std::size_t posistion_last_founded = m_updated_path.find_last_of(
        '.');
    if (std::string::npos != posistion_last_founded )
    {
        m_extension = m_updated_path.substr(m_updated_path.find_last_of('.'));
        m_updated_path.erase(m_updated_path.find_last_of('.'));
    }
    posistion_last_founded = m_updated_path.find_last_of(symbol_for_sect);

    if (std::string::npos != posistion_last_founded)
    {
        m_hour =
            m_updated_path.substr(m_updated_path.find_last_of(
                symbol_for_sect) + 1,
                m_length_of_part);
        m_updated_path.erase(m_updated_path.find_last_of(symbol_for_sect));
    }
    if (Utils::IsHourPassed(m_hour))
    {
        //write to logger about new file
    }
    posistion_last_founded = m_updated_path.find_last_of(symbol_for_sect);
    if (std::string::npos != posistion_last_founded)
    {
        m_day =
            m_updated_path.substr(m_updated_path.find_last_of(symbol_for_sect));
        m_updated_path.erase(m_updated_path.find_last_of(symbol_for_sect));
        if (m_day.length() > m_length_of_part)
        {
            m_day = m_day.substr(0, m_length_of_part);
        }
    }

    if (Utils::IsDayPassed(m_day))
    {
        //write to logger about new file
    }
    m_updated_path = m_general_folder + symbol_for_sect + m_day;
    if (!Utils::TryCreateDirectory(m_updated_path))
    {
        // write to log failed to create directory
        return false;
    }
    path = m_updated_path + symbol_for_sect + m_hour + m_extension;

    return true;
}

bool CDateTimePathConstructor::IsCreatedGeneralFolder() const
{
    return m_is_created_general_folder;
}
