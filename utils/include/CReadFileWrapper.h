#pragma once

class CReadFileWrapper {
  public:
    CReadFileWrapper(const std::filesystem::path& path);
    CReadFileWrapper(const CReadFileWrapper&) = delete;
    CReadFileWrapper(CReadFileWrapper&&) = delete;
    ~CReadFileWrapper() noexcept;

    bool Initialize();
    bool ReadLine(std::string& buffer);
    bool ReadSym(char& buffer);
  private:
    const std::filesystem::path& m_path;
    std::unique_ptr<std::ifstream> m_p_file;
    bool m_is_initialized;
};

