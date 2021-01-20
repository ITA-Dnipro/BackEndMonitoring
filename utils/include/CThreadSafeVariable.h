#pragma once

template <typename T>
class CThreadSafeVariable
{
public:
	CThreadSafeVariable() = default;
	explicit CThreadSafeVariable(T&& value)
		: m_value(value)
	{}
	CThreadSafeVariable(const CThreadSafeVariable&) = delete;
	CThreadSafeVariable(CThreadSafeVariable&&) = delete;
	~CThreadSafeVariable() noexcept = default;

	struct SAccess
	{
		T& ref_to_value;
		std::unique_lock<std::mutex> guard;
	};

	SAccess GetAccess()
	{ return { m_value, std::unique_lock(m_lock) }; }

private:
	T m_value;
	std::mutex m_lock;
};

