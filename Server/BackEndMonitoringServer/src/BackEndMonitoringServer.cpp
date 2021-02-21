
#include "stdafx.h"

#include "CService.h"
#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
#include "Utils.h"
#include "CLogger/include/Log.h"
#include "ERequestType.h"
#include "ERequestRangeSpecification.h"
#include "CRequestHandler.h"
#include "CRequestFrame.h"
#include "CResponseHandler.h"

int main(int argc, char** argv)
{
	std::string answer = "{ \"id\": \"2\", \"error\": 0, \"data\": 0}";
	
	nlohmann::json request = nlohmann::json::parse(answer);
	request["data"] = nlohmann::json::parse(answer);
	auto i = request.count("data");

	answer = request.dump();

	CResponseHandler g;
	nlohmann::json h;
	g.HandleResponse("2", answer, h);

	std::cout << h.dump(4) << std::endl;
  std::fstream stream(
	CService::GetRelativePath() + "Log.txt",
	std::ios_base::app);

	CLOG_CREATION_START();

	CLOG_CREATION_SET_LOG_NAME("ServiceLogger");
	CLOG_CREATION_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL);
	CLOG_CREATION_SET_LOG_CONFIG(
		ELogConfig::LOG_NAME,
		ELogConfig::LOG_LEVEL,
		ELogConfig::CALL_TIME,
		ELogConfig::THREAD_ID,
		ELogConfig::FILE_NAME,
		ELogConfig::FUNCTION_NAME,
		ELogConfig::LINE_NUMBER,
		ELogConfig::MESSAGE,
		ELogConfig::PARAMS);

	CLOG_CREATION_ADD_SAFE_STREAM(stream);

	CLOG_BUILD();

  CLOG_CREATION_END();

  auto parser = std::make_unique<CommandLineHandler>(argc, argv);
  bool success = parser->Parse( );

  if (!success)
  {
      Utils::DisplayMessage("Invalid parameters");
      return EXIT_FAILURE;
  }

  const int return_code = success ? 0 : 1;

  CLOG_DESTROY();

  return return_code;
};
