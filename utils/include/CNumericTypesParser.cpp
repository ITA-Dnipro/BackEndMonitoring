#include "stdafx.h"

#include "StrToNumWrapper.h"

#include "CNumericTypesParser.h"

CNumericTypesParser::CNumericTypesParser(const std::string& m_value):m_value(m_value) {}

bool CNumericTypesParser::IsValidScientificNotaton(
            std::string::const_iterator scientific_part_begin,
            std::string::const_iterator scientific_part_end) const{
    if (scientific_part_begin == scientific_part_end)
    { return false;}

    if(*scientific_part_begin == '-' || *scientific_part_begin == '+'){
        ++scientific_part_begin;
    }

    for( auto sym = scientific_part_begin; sym<scientific_part_end; ++sym) {
        if(!std::isdigit( *sym )){
            return false;
        }
    }
    return true;
}

bool CNumericTypesParser::IsIntagerNumber() const {
    size_t i = 0;
    if(m_value.at(0) == '-'){
        i = static_cast<size_t>(1);
    }

    for( ; i < m_value.size(); ++i) {
        if(!std::isdigit( m_value[i] )){
            return false;
        }
    }
    return true;
}

bool CNumericTypesParser::IsFloatingPointNumber() const {
    size_t i = static_cast<size_t>(0);
    if(m_value.at(0) == '-'){
        i = static_cast<size_t>(1);
    }

    for( ; i < m_value.size(); ++i) {
        if(!std::isdigit(m_value[i]) && m_value[i] != '.') {
            bool flag = false;
            if (m_value[i] == 'e' || m_value[i] == 'E'){
                flag = IsValidScientificNotaton(m_value.begin()+i+1,
                                                m_value.end());
            }
            return flag;
        }
    }
    return true;
}

bool CNumericTypesParser::IsUnsignedIntagerNumber() const{
    for(char sym : m_value) {
            if(!std::isdigit(sym)){
                return false;
            }
        }
        return true;
}

bool CNumericTypesParser::IsUnsignedFloatingPointNumber() const{
    for(size_t i = static_cast<size_t>(0); i < m_value.size(); ++i) {
        if(!std::isdigit(m_value[i]) && m_value[i] != '.') {
            bool flag = false;
            if (m_value[i] == 'e' || m_value[i] == 'E'){
                flag = IsValidScientificNotaton(m_value.begin()+i+1,
                                                m_value.end());
            }
            return flag;
        }
    }
    return true;
}

bool CNumericTypesParser::AsNaturalNumber(unsigned int& var) const {
    bool flag = (IsUnsignedIntagerNumber() && m_value != "0");
    if(flag){
        flag = StrToNumWrapper::TryStoul(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(
        unsigned long long& var) const {
    bool flag = (IsUnsignedIntagerNumber() && m_value != "0");
    if(flag){
        flag = StrToNumWrapper::TryStoull(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(float& var) const {
    bool flag = (IsUnsignedFloatingPointNumber() && m_value != "0");
    if(flag){
        flag = StrToNumWrapper::TryStof(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(double& var) const {
    bool flag = (IsUnsignedFloatingPointNumber() && m_value != "0");
    if(flag){
        flag = StrToNumWrapper::TryStod(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(long double& var) const {
    bool flag = (IsUnsignedFloatingPointNumber() && m_value != "0");
    if(flag){
        flag = StrToNumWrapper::TryStold(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(unsigned int& var) const {
    bool flag = IsUnsignedIntagerNumber();
    if(flag){
        flag = StrToNumWrapper::TryStoul(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(unsigned long long& var) const {
    bool flag = IsUnsignedIntagerNumber();
    if(flag){
        flag = StrToNumWrapper::TryStoull(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(float& var) const {
    bool flag = IsUnsignedFloatingPointNumber();
    if(flag){
        flag = StrToNumWrapper::TryStof(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(double& var) const {
    bool flag = IsUnsignedFloatingPointNumber();
    if(flag){
        flag = StrToNumWrapper::TryStod(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(long double& var) const {
    bool flag = IsUnsignedFloatingPointNumber();
    if(flag){
        flag = StrToNumWrapper::TryStold(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNumber(int& var) const {
    bool flag = IsIntagerNumber();
    if(flag){
        flag = StrToNumWrapper::TryStoi(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNumber(long long& var) const {
    bool flag = IsIntagerNumber();
    if(flag){
        flag = StrToNumWrapper::TryStoll(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNumber(float& var) const {
    bool flag = IsFloatingPointNumber();
    if(flag){
        flag = StrToNumWrapper::TryStof(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNumber(double& var) const {
    bool flag = IsFloatingPointNumber();
    if(flag){
        flag = StrToNumWrapper::TryStod(m_value, var);
    }
    return flag;
}

bool CNumericTypesParser::AsNumber(long double& var) const{
    bool flag = IsFloatingPointNumber();
    if(flag){
        flag = StrToNumWrapper::TryStold(m_value, var);
    }
    return flag;
}
