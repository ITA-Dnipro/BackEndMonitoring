#pragma once

enum class ERequestType;

class CClientView
{
public:
	CClientView(std::ostream& out, std::istream& in);
	CClientView(const CClientView&) = delete;
	CClientView(CClientView&&) = delete;
	~CClientView() noexcept = default;

	void PrintMenu();
	ERequestType GetRequest();
	void PrintResult(const std::string& result);
	void PrintError();
	void PrintGoodbye();
	void PrintClientConnected();
	void PrintErrorConnection();

private:
	std::ostream& m_output_stream;
	std::istream& m_input_stream;
};

