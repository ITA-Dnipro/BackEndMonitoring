#include "stdafx.h"

#include "StrToNumWrapper.h"
#include "CLogger/include/Log.h"

#include "CNumericTypesParser.h"

CNumericTypesParser::CNumericTypesParser(const std::string& m_value) :
    m_value(m_value)
{ };

bool CNumericTypesParser::IsValidScientificNotaton(
            std::string::const_iterator scientific_part_begin,
            std::string::const_iterator scientific_part_end) const
{
    CLOG_TRACE_START_FUNCTION();
    if (scientific_part_begin == scientific_part_end)
    { return false;}

    if(*scientific_part_begin == '-' || *scientific_part_begin == '+')
    {
        ++scientific_part_begin;
    }

    for( auto sym = scientific_part_begin; sym<scientific_part_end; ++sym) 
    {
        if(!std::isdigit( *sym ))
        {
            return false;
        }
    }
    CLOG_TRACE_END_FUNCTION();
    return true;
}

bool CNumericTypesParser::IsIntagerNumber() const 
{
    CLOG_TRACE_START_FUNCTION();
    size_t i = 0;
    CLOG_TRACE_VAR_CREATION(i);
    if(m_value.at(0) == '-')
    {
        i = static_cast<size_t>(1);
    }

    for( ; i < m_value.size(); ++i) 
    {
        if(!std::isdigit( m_value[i] ))
        {
            return false;
        }
    }
    CLOG_TRACE_END_FUNCTION();
    return true;
}

bool CNumericTypesParser::IsFloatingPointNumber() const 
{
    CLOG_TRACE_START_FUNCTION();
    size_t i = static_cast<size_t>(0);
    CLOG_TRACE_VAR_CREATION(i);
    if(m_value.at(0) == '-')
    {
        i = static_cast<size_t>(1);
    }

    for( ; i < m_value.size(); ++i) 
    {
        if(!std::isdigit(m_value[i]) && m_value[i] != '.') 
        {
            bool flag = false;
            CLOG_TRACE_VAR_CREATION(flag);
            if (m_value[i] == 'e' || m_value[i] == 'E')
            {
                flag = IsValidScientificNotaton(m_value.begin()+i+1,
                                                m_value.end());
            }
            return flag;
        }
    }
    CLOG_TRACE_END_FUNCTION();
    return true;
}

bool CNumericTypesParser::IsUnsignedIntagerNumber() const
{
    CLOG_TRACE_START_FUNCTION();    
    for(char sym : m_value)
    {
            if(!std::isdigit(sym))
            {
                return false;
            }
    }
    CLOG_TRACE_END_FUNCTION();
    return true;
}

bool CNumericTypesParser::IsUnsignedFloatingPointNumber() const
{
    CLOG_TRACE_START_FUNCTION();
    for(size_t i = static_cast<size_t>(0); i < m_value.size(); ++i) 
    {
        if(!std::isdigit(m_value[i]) && m_value[i] != '.') 
        {
            bool flag = false;
            if (m_value[i] == 'e' || m_value[i] == 'E')
            {
                flag = IsValidScientificNotaton(m_value.begin()+i+1,
                                                m_value.end());
            }
            return flag;
        }
    }
    CLOG_TRACE_END_FUNCTION();
    return true;
}

bool CNumericTypesParser::AsNaturalNumber(unsigned int& var) const 
{
    
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    CLOG_TRACE_VAR_CREATION(flag);
    flag = (IsUnsignedIntagerNumber() && m_value != "0");
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStoul(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(
        unsigned long long& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = (IsUnsignedIntagerNumber() && m_value != "0");
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStoull(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(float& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = (IsUnsignedFloatingPointNumber() && m_value != "0");
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStof(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(double& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = (IsUnsignedFloatingPointNumber() && m_value != "0");
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStod(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNaturalNumber(long double& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = (IsUnsignedFloatingPointNumber() && m_value != "0");
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStold(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(unsigned int& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsUnsignedIntagerNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStoul(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(unsigned long long& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsUnsignedIntagerNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStoull(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(float& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsUnsignedFloatingPointNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStof(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(double& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsUnsignedFloatingPointNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStod(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsUnsignedNumber(long double& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsUnsignedFloatingPointNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStold(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNumber(int& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsIntagerNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStoi(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNumber(long long& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsIntagerNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStoll(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNumber(float& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsFloatingPointNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStof(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNumber(double& var) const 
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsFloatingPointNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStod(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}

bool CNumericTypesParser::AsNumber(long double& var) const
{
    bool flag = false; 
    CLOG_TRACE_START_FUNCTION();
    flag = IsFloatingPointNumber();
    CLOG_TRACE_VAR_CREATION(flag);
    if(flag)
    {
        flag = StrToNumWrapper::TryStold(m_value, var);
    }
    CLOG_TRACE_END_FUNCTION();
    return flag;
}
