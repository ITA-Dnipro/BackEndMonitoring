#include "stdafx.h"

#include "StrToNumWrapper.h"

namespace StrToNumWrapper{
bool TryStoi(const std::string& val, int& var){
    try{
        var = std::stoi(val);
    } catch(...) {
        return false;
    }
    return true;
}

bool TryStoul(const std::string& val, unsigned int& var){
    try{
        var = std::stoul(val);
    } catch(...) {
        return false;
    }
    return true;
}

bool TryStoll(const std::string& val, long long int& var){
    try{
        var = std::stoll(val);
    } catch(...) {
        return false;
    }
    return true;
}

bool TryStoull(const std::string& val, unsigned long long int& var){
    try{
        var = std::stoull(val);
    } catch(...) {
        return false;
    }
    return true;
}

bool TryStof(const std::string& val, float& var){
    try{
        var = std::stof(val);
    } catch(...) {
        return false;
    }
    return true;
}

bool TryStod(const std::string& val, double& var){
    try{
        var = std::stod(val);
    } catch(...) {
        return false;
    }
    return true;
}

bool TryStold(const std::string& val, long double& var){
    try{
        var = std::stold(val);
    } catch(...) {
        return false;
    }
    return true;
}

}
