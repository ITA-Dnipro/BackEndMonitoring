
#include "stdafx.h"

#include "CService.h"
#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
#include "Utils.h"
#include "CLogger/include/Log.h"

int main(int argc, char** argv)
{
  std::fstream stream(
	CService::GetRelativePath() + "Log.txt",
	std::ios_base::app);

	CLOG_START_CREATION();

	CLOG_SET_LOG_NAME("ServiceLogger");
	CLOG_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL);
	CLOG_SET_LOG_CONFIG(
		ELogConfig::LOG_NAME,
		ELogConfig::LOG_LEVEL,
		ELogConfig::CALL_TIME,
		ELogConfig::THREAD_ID,
		ELogConfig::FILE_NAME,
		ELogConfig::FUNCTION_NAME,
		ELogConfig::LINE_NUMBER,
		ELogConfig::MESSAGE,
		ELogConfig::PARAMS);

	CLOG_ADD_SAFE_STREAM(stream);

	CLOG_BUILD();

  CLOG_END_CREATION();

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
