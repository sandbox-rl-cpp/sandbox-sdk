#pragma once
#include "../unrealengine/unclass.h"

#include <functional>

class __declspec(dllexport) Hooking
{
private:
	static inline std::map<uint32_t, std::vector<std::function<void(UObject*, UFunction*, void*)>>> g_hooks[3];
	static inline std::map<uint32_t, std::vector<std::function<void(UObject*, UFunction*, void*)>>> g_post_hooks[3];
public:
	enum HookType
	{
		PE,
		PI,
		CF
	};

	static void hook_function(const std::string& name, HookType type, std::function<void(UObject*, UFunction*, void*)> hook);
	static void hook_function_post(const std::string& name, HookType type, std::function<void(UObject*, UFunction*, void*)> hook);

	static void call_hooks(int32_t index, HookType type, UObject* caller, UFunction* function, void* params);
	static void call_post_hooks(int32_t index, HookType type, UObject* caller, UFunction* function, void* params);
};