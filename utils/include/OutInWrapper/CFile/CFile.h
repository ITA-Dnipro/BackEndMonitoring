#pragma once
#include <filesystem>

#include "../../CDummyPointer.h"

class CFile
{
public:
	CFile() : CFile(nullptr) {}
	CFile(const CFile& copy) = default;
	CFile(CFile&& move) noexcept;
	explicit CFile(const std::string& path);
	explicit CFile(const std::filesystem::path& path);
	explicit CFile(FILE* file);

	CFile& operator=(const CFile& copy) = delete;
	CFile& operator=(CFile&& move) noexcept = default;

	virtual ~CFile();

	bool TryOpen(const std::string& path);
	bool TryOpen(const std::filesystem::path& path);

	bool TryCreateAndOpen(const std::string& path);
	bool TryCreateAndOpen(const std::filesystem::path& path);

	bool TryAppendAndOpen(const std::string& path);
	bool TryAppendAndOpen(const std::filesystem::path& path);

	bool TryClose();

	[[nodiscard]] bool IsOpen() const;
	[[nodiscard]] bool IsClosable() const;
	[[nodiscard]] FILE* GetFile() const;

	operator FILE* () const;
private:
	CDummyPointer<FILE> m_file;
	bool m_is_open;
	bool m_is_closable;

	bool WrapperTryOpen(const std::string& path, const std::string& mode);
};

inline CFile::CFile(CFile&& move) noexcept = default;

inline CFile::CFile(const std::string & path)
	: m_is_open(TryOpen(path)), m_is_closable(true)
{}

inline CFile::CFile(const std::filesystem::path & path) : CFile(path.string())
{}

inline CFile::CFile(FILE * file)
	: m_file(file), m_is_open(nullptr != file),
	m_is_closable(!(stdout == file || stdin == file || stderr == file))
{}

inline CFile::~CFile()
{
	TryClose();
}

inline bool CFile::TryOpen(const std::string & path)
{
	return WrapperTryOpen(path, std::string("r+"));
}

inline bool CFile::TryOpen(const std::filesystem::path & path)
{
	return TryOpen(path.string());
}

inline bool CFile::TryCreateAndOpen(const std::string & path)
{
	return WrapperTryOpen(path, std::string("w+"));
}

inline bool CFile::TryCreateAndOpen(const std::filesystem::path & path)
{
	return TryCreateAndOpen(path.string());
}

inline bool CFile::TryAppendAndOpen(const std::string & path)
{
	return WrapperTryOpen(path, std::string("a+"));
}

inline bool CFile::TryAppendAndOpen(const std::filesystem::path & path)
{
	return TryAppendAndOpen(path.string());
}

inline bool CFile::TryClose()
{
	if (!m_is_closable) {
		m_is_open = false;
		return m_is_closable;
	}
	
	if (m_is_open && m_file.GetCount() == 1u)
	{
		fclose(m_file.GetPointer());
	}
	
	m_is_open = false;
	m_is_closable = false;

	return m_is_open;
}

inline bool CFile::IsOpen() const
{
	return m_is_open;
}

inline bool CFile::IsClosable() const
{
	return m_is_closable;
}

inline FILE* CFile::GetFile() const
{
	return m_file.GetPointer();
}

inline CFile::operator FILE*() const
{
	return GetFile();
}

inline bool CFile::WrapperTryOpen(const std::string & path, const std::string & mode)
{
	if (!m_is_open)
	{
		const auto* temp = path.c_str();
		m_is_open = nullptr != (m_file = CDummyPointer<FILE>(fopen(temp, mode.c_str()))).GetPointer();
	}
	return m_is_open;
}
