#pragma once

enum class EMemoryConvertType;

class CHardwareStatusSpecification
{
public:
	CHardwareStatusSpecification() = delete;
	explicit CHardwareStatusSpecification(
		std::chrono::duration<int> pause_duration,
		EMemoryConvertType count_type);
	explicit CHardwareStatusSpecification(
		const CHardwareStatusSpecification& orig);
	CHardwareStatusSpecification(const CHardwareStatusSpecification&&) 
		noexcept = delete;

	[[nodiscard]] std::chrono::duration<int> GetPauseDuration() const;
	[[nodiscard]] EMemoryConvertType GetCountType() const;

	[[nodiscard]] bool CloneObject(const CHardwareStatusSpecification& orig);

protected:
	// duration is used as seconds
	std::chrono::duration<int> m_pause_duration{};
	// Bytes - Megabytes - Gigabytes
	EMemoryConvertType m_count_type;
};

