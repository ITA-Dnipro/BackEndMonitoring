#pragma once

class CStringCleaner {
public:
    CStringCleaner(const std::string& value);
    std::string GetTrimedString() const;
    std::string GetLowercaseString() const;
    std::string GetOriginalString() const;
    std::string GetTrimmedLowercaseString() const;
  private:
    std::string m_original_string;
};
