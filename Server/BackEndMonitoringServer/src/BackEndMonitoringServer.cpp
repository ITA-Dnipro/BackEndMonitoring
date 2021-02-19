
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


int main(int argc, char** argv)
{
	std::string answer = "{ \"id\": 2, \"request_type\": 1, \"special\": 0, \"duration\": \"\" : 12.02.2020 12:32:12, \"\" : 12.03.2020 12:32:12 }";
	//nlohmann::json request = nlohmann::json::parse(answer);
	
	CRequestFrame g;
	
	g.TryFormateRequest(answer, ERequestType::DISKS_DATA, 
		ERequestRangeSpecification::ALL_DATA, "12.02.2020 12:32:12", "12.03.2020 12:32:12");

	//ERequestType b = ERequestType(request["id"]);
	//std::cout << typeid(request["id"]).name();

	CRequestHandler b(answer);
	std::string kill;

	b.HandleRequest(kill);

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
