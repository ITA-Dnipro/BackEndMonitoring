#pragma once

#include "stdafx.h"

class CReadFileWrapper {
  public:
    CReadFileWrapper(const std::filesystem::path& path);
    CReadFileWrapper(const CReadFileWrapper&) = delete;
    CReadFileWrapper(CReadFileWrapper&&) = delete;
    ~CReadFileWrapper() noexcept;

    bool Initialize();
    bool ReadWholeFile(std::string& buffer);
    bool Read(std::string& buffer, std::streamsize count);
    bool ReadLine(std::string& buffer);
    bool ReadPrevLine(std::string& buffer);
    bool ReadSym(char& buffer);
    bool ReadPrevSym(char& buffer);
    bool GetPosition(std::streampos& pos);
    bool MoveCursorTo(std::streampos pos);
  private:
    const std::filesystem::path m_path;
    std::unique_ptr<std::ifstream> m_p_file;
    bool m_is_initialized;
};

