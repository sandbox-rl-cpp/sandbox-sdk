#pragma once

class PluginSDK
{
public:
	virtual void load() = 0;
	virtual void unload() = 0;
};

#define SANDBOX_PLUGIN(classtype) \
extern "C" __declspec(dllexport) PluginSDK* create() \
{ \
	return new classtype; \
} \