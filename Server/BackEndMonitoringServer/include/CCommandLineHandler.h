#pragma once

enum class Task
{
	RUN,
	INSTALL,
	UNINSTALL,
	START,
	STOP,
	RESTART,
	SHOW_HELP,
};

class CommandLineHandler
{
public:
	Task GetTask();

	bool Parse(int argc, char** argv);

private:
	Task task;
};
