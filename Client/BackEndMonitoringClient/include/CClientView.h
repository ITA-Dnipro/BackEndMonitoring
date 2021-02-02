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
	void PrintResult(const std::string& result) const;
	void PrintError() const;
	void PrintGoodbye() const;
	void PrintClientConnected() const;
	void PrintErrorConnection() const;

private:
	std::ostream& m_output_stream;
	std::istream& m_input_stream;
};

