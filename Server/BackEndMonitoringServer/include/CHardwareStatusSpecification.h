#pragma once

enum class EMemoryConvertType;

class CHardwareStatusSpecification
{
public:
	CHardwareStatusSpecification() = delete;
	explicit CHardwareStatusSpecification(
		std::chrono::duration<int>
		pause_duration, const std::string& path_to_file,
		EMemoryConvertType count_type);
	explicit CHardwareStatusSpecification(
		const CHardwareStatusSpecification& orig);
	CHardwareStatusSpecification(const CHardwareStatusSpecification&&) 
		noexcept = delete;

	[[nodiscard]] std::chrono::duration<int> GetPauseDuration() const;
	[[nodiscard]] EMemoryConvertType GetCountType() const;
	[[nodiscard]] std::string* GetPathToSaveFile();

protected:
	// duration is used as seconds
	std::chrono::duration<int> m_pause_duration{};
	// path to file where status of hardware will be storaged
	std::string m_path_to_file;
	// Bytes - Megabytes - Gigabytes
	EMemoryConvertType m_count_type;
};

