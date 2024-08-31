#include "hooking.h"

void Hooking::hook_function(const std::string& name, HookType type, std::function<void(UObject*, UFunction*, void*)> hook)
{
	UFunction* u_function = UFunction::find_function(name);

	if (u_function)
	{
		int32_t index = u_function->ObjectIndex();
		
		switch (type)
		{
			case HookType::PE:
			{
				g_hooks[HookType::PE][index].push_back(hook);
				break;
			}
			case HookType::PI:
			{
				g_hooks[HookType::PI][index].push_back(hook);
				break;
			}
			case HookType::CF:
			{
				g_hooks[HookType::CF][index].push_back(hook);
				break;
			}
		}
	}
}

void Hooking::hook_function_post(const std::string& name, HookType type, std::function<void(UObject*, UFunction*, void*)> hook)
{
	UFunction* u_function = UFunction::find_function(name);

	if (u_function)
	{
		int32_t index = u_function->ObjectIndex();

		switch (type)
		{
			case HookType::PE:
			{
				g_post_hooks[HookType::PE][index].push_back(hook);
				break;
			}
			case HookType::PI:
			{
				g_post_hooks[HookType::PI][index].push_back(hook);
				break;
			}
			case HookType::CF:
			{
				g_post_hooks[HookType::CF][index].push_back(hook);
				break;
			}
		}
	}
}

void Hooking::call_hooks(int32_t index, HookType type, UObject* caller, UFunction* function, void* params)
{
	auto hook = g_hooks[type].find(index);

	if (hook != g_hooks[type].end())
	{
		for (const auto& func : hook->second)
		{
			func(caller, function, params);
		}
	}
}

void Hooking::call_post_hooks(int32_t index, HookType type, UObject* caller, UFunction* function, void* params)
{
	auto hook = g_post_hooks[type].find(index);
	
	if (hook != g_post_hooks[type].end())
	{
		for (const auto& func : hook->second)
		{
			func(caller, function, params);
		}
	}
}