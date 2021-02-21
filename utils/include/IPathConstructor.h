#pragma once

class IPathConstructor
{
public:
	virtual bool UpdatePathToFile(std::string& path) = 0;
};

