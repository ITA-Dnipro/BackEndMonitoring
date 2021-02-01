#include "stdafx.h"

#include "Server/BackEndMonitoringServer/include/EMemoryConvertType.h"
#include "CLogger/include/Log.h"

#include "Utils.h"

//in order to use ctime
#pragma warning(disable:4996)

std::vector<std::string> Utils::SplitIntoWords(const std::string& str,
                                               const char delimiter)
{
    std::vector<std::string> result;
    CLOG_DEBUG_START_FUNCTION();
    CLOG_TRACE_VAR_CREATION(result);
    size_t pos = 0;
    CLOG_TRACE_VAR_CREATION(pos);
    const size_t pos_end = str.npos;
    CLOG_TRACE_VAR_CREATION(pos_end);

    while (true) 
    {
        size_t space = str.find(delimiter, pos);
        CLOG_TRACE_VAR_CREATION(space);
        result.push_back(
            space == pos_end
            ? str.substr(pos)
            : str.substr(pos, space - pos));

        if (space == pos_end) {
            break;
        }
        else {
            pos = space + 1;
        }
    }
    CLOG_DEBUG_END_FUNCTION();
    return result;
}

bool Utils::TryGetCurrentDateAndTimeFormatted(std::string&
                                              date_time_var_to_save)
{
    CLOG_DEBUG_START_FUNCTION();
    //parse to format: dd.mm.yyyy hh:mm:ss
    std::time_t current_time = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now( ));
    CLOG_TRACE_VAR_CREATION(current_time);

    date_time_var_to_save = ctime(&current_time);

    date_time_var_to_save.pop_back( );
    date_time_var_to_save = date_time_var_to_save.substr(
        date_time_var_to_save.find_first_of(" ") + 1ULL);

    std::string buff_year = date_time_var_to_save.substr(
        date_time_var_to_save.find_last_of(" ") + 1ULL);
    date_time_var_to_save.erase(date_time_var_to_save.end( ) - 
                                buff_year.size( ) - 1,
                                date_time_var_to_save.end( ));
    CLOG_TRACE_VAR_CREATION(buff_year);

    std::string buff_month = date_time_var_to_save.substr(
        0, date_time_var_to_save.find_first_of(" "));
    date_time_var_to_save.erase(date_time_var_to_save.begin( ),
                                date_time_var_to_save.begin( ) + 
                                buff_month.size( ) + 1ULL);
    CLOG_TRACE_VAR_CREATION(buff_month);

    if (!TrySetMonthAsNumber(buff_month))
    {
        return false;
    }

    date_time_var_to_save.insert(date_time_var_to_save.find_first_of(" "),
                                 "." + buff_month);
    date_time_var_to_save.insert(date_time_var_to_save.find_first_of(" "),
                                 "." + buff_year + " ");

    CLOG_DEBUG_END_FUNCTION();
    return true;
}

bool Utils::TrySetMonthAsNumber(std::string& p_month)
{
    CLOG_DEBUG_START_FUNCTION();
    constexpr size_t num_of_month_in_year = 12U;
    CLOG_TRACE_VAR_CREATION(num_of_month_in_year);
    constexpr size_t num_of_letters = 4U;
    CLOG_TRACE_VAR_CREATION(num_of_letters);
    constexpr char c_name_of_all_months[][num_of_letters] = {
        {'J', 'a', 'n', '\0'},
        {'F', 'e', 'b', '\0'},
        {'M', 'a', 'r', '\0'},
        {'A', 'p', 'r', '\0'},
        {'M', 'a', 'y', '\0'},
        {'J', 'u', 'n', '\0'},
        {'J', 'u', 'l', '\0'},
        {'S', 'e', 'p', '\0'},
        {'A', 'u', 'g', '\0'},
        {'O', 'c', 't', '\0'},
        {'N', 'o', 'v', '\0'},
        {'D', 'e', 'c', '\0'} };
    CLOG_TRACE_VAR_CREATION(c_name_of_all_months);

    for (size_t month_as_num = 0; month_as_num < num_of_month_in_year;
         ++month_as_num)
    {
        if (!strcmp(p_month.c_str( ),
            c_name_of_all_months[month_as_num - 1ULL]))
        {
            p_month = std::to_string(month_as_num);
            return true;
        }
    }
    CLOG_DEBUG_END_FUNCTION();
    return false;
}

bool Utils::TryGetFormattedDiskName(std::string& name_of_disk)
{
    CLOG_DEBUG_START_FUNCTION();

    if (name_of_disk.empty( ))
    {
        return false;
    }
    name_of_disk.replace(name_of_disk.begin( ) + 1ULL, name_of_disk.end( ),
                         std::string(":/"));
    CLOG_DEBUG_END_FUNCTION();
    return true;
}

bool Utils::TryCreateFileIfNotExist(const std::string& path_to_file)
{
    CLOG_DEBUG_START_FUNCTION();
    if (!std::filesystem::exists(path_to_file))
    {
        std::ofstream created_file(path_to_file);
        CLOG_TRACE_VAR_CREATION(created_file);

        if (!created_file.is_open())
        {
            // couldn't create file
            return false;
        }
        created_file.close();
    }
    CLOG_DEBUG_END_FUNCTION();
    return true;
}

bool Utils::IsFileEmpty(std::ifstream& file)
{ return file.peek( ) == std::ifstream::traits_type::eof( ); }

bool Utils::IsFileEmpty(std::fstream& file)
{ return file.peek( ) == std::fstream::traits_type::eof( ); }

bool Utils::IsFileEmpty(std::ofstream& file)
{
    bool answer = false;
    CLOG_DEBUG_START_FUNCTION();
    file.seekp(0, file.end);
    std::streampos position = file.tellp();
    CLOG_TRACE_VAR_CREATION(position);

    if (position == 0)
    {
        answer = true;
    }
    file.seekp(file.beg);
    CLOG_DEBUG_END_FUNCTION();
    return answer;
}

#define EN_US 0x0409

void Utils::DisplayError(const std::string& message)
{
    CLOG_DEBUG_START_FUNCTION();
    // char*
    LPSTR error = NULL;
    CLOG_TRACE_VAR_CREATION(error);

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        EN_US,
        reinterpret_cast<LPSTR>(&error),
        0,
        NULL);

    std::cout << message << ". " << error;
    LocalFree(error);
    CLOG_DEBUG_END_FUNCTION();
}

void Utils::DisplayMessage(const std::string& message)
{ std::cout << message << ". " << std::endl; }


long double Utils::ConvertToCountType(
    uintmax_t const value_to_calculate, EMemoryConvertType convert_type)
{
    return static_cast<long double>(value_to_calculate)
        /
        static_cast<long double>(convert_type);
}

long double Utils::RoundToDecimal(
    long double const value_to_round)
{ return round(value_to_round * 100.0) / 100.0; }

EMemoryConvertType Utils::DefineCountType(int count_type_from_xml)
{
    switch (count_type_from_xml)
    {
    case 0:
        return EMemoryConvertType::BYTES;
        
    case 1:
        return EMemoryConvertType::KILOBYTES;

    case 2:
        return EMemoryConvertType::MEGABYTES;

    case 3:
        return EMemoryConvertType::GIGABYTES;

    default:
        //write to logger
        return EMemoryConvertType::BYTES;
    }
}
