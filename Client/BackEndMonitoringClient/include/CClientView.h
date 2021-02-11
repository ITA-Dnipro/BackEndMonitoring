#pragma once

enum class ERequestType;

class CClientView
{
public:
	CClientView(std::ostream& out, std::istream& in);
	CClientView(const CClientView&) = delete;
	CClientView(CClientView&&) = delete;
	~CClientView() noexcept = default;

	void PrintMenu() const;
	ERequestType GetRequest() const;
	void PrintMessage(const std::string& result) const;
	void PrintError() const;

private:
	std::ostream& m_output_stream;
	std::istream& m_input_stream;
};
