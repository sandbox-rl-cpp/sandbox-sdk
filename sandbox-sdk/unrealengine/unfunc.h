#pragma once
#include "unstruct.h"
#include "unparams.h"

class __declspec(dllexport) UnFunc
{
public:
	UObject* m_caller;
	UnParams m_params;
	UnRet m_ret;
public:
	UnFunc(UObject* caller, const std::string& name, UnParams params) : m_caller(caller), m_params(params) { get_function(name); }

	template <typename T>
	const T get_ret()
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(m_ret.m_data) + m_ret.m_offset);
	}

	class UnStruct get_struct_ret(const std::string& name);
private:
	void get_function(const std::string& name);
};

class __declspec(dllexport) UnFuncParams
{
public:
	std::map<std::string, uint32_t> m_params;
	void* m_data;
public:
	UnFuncParams(UFunction* function, void* params) : m_data(params) { get_params(function); }

	template <typename T>
	T& get(const std::string& name)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(m_data) + m_params[name]);
	}

	class UnStruct get_struct(const std::string& unstruct, const std::string& name);
private:
	void get_params(UFunction* function);
};