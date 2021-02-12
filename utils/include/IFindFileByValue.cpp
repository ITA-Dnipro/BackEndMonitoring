#include "stdafx.h"

#include "Utils.h"

#include "IFindFileByValue.h"

bool IFindFileByValue::TryFindFileByValueInFolder(const std::string& value,
    const std::string& path_to_general_folder, std::string& path_to_file)
{
    char sect_divide_symbol = Utils::DetermineSectDividingSymbol(
        path_to_general_folder);
    path_to_file = path_to_general_folder + sect_divide_symbol;
    for (const auto& folder : std::filesystem::directory_iterator(
        path_to_general_folder))
    {
        if (std::string::npos != folder.path().filename().string().find(value))
        {
            path_to_file += folder.path().filename().string();
            return true;
        }
    }

    return false;
}
