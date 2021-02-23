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
	std::fstream stream(
		Utils::GetRelativePath() + "Log.txt",
		std::ios_base::app);

	CLOG_CREATION_START();

	CLOG_CREATION_SET_LOG_NAME("Client Logger");
	CLOG_CREATION_SET_DEBUG();
	CLOG_CREATION_SET_LOG_FLUSH(ELogFlush::FLUSH);
	CLOG_CREATION_SET_LOG_CONFIG(
		ELogConfig::THREAD_ID, ELogConfig::CALL_TIME,
		ELogConfig::LOG_LEVEL, ELogConfig::FUNCTION_NAME,
		ELogConfig::MESSAGE, ELogConfig::PARAMS);

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
