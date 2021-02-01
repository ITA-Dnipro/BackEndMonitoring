#include "stdafx.h"

#include <cctype>

#include "CStringCleaner.h"

CStringCleaner::CStringCleaner(const std::string& value):m_original_string(value) {}

std::string CStringCleaner::GetTrimedString() const {
    size_t StartPos = m_original_string.find_first_not_of(" \t\n");
    if ( StartPos == std::string::npos )
        return "";
    size_t EndPos = m_original_string.find_last_not_of(" \t");

    return m_original_string.substr(StartPos, EndPos - StartPos + 1);
}

std::string CStringCleaner::GetLowercaseString() const {
    std::string temp_lowercase_copy;
    for(char sym : m_original_string) {
        temp_lowercase_copy.push_back( tolower(sym) );
    }
    return temp_lowercase_copy;
}

std::string CStringCleaner::GetOriginalString() const {
    return m_original_string;
}

std::string CStringCleaner::GetTrimmedLowercaseString() const {
    CStringCleaner temp_trimmed_string(GetTrimedString());
    return temp_trimmed_string.GetLowercaseString();
}
