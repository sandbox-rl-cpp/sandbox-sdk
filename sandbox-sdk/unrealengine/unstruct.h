#pragma once
#include "unclass.h"

class __declspec(dllexport) UnStruct
{
public:
	std::map<std::string, uint32_t> m_fields;
	void* m_data;
public:
	UnStruct(const std::string& name) { get_struct(name); }
	UnStruct(void* data, const std::string& name) : m_data(data) { get_struct(name); }

	template <typename T>
	T& get(const std::string& name)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(m_data) + m_fields[name]);
	}

	void* operator&();
private:
	void get_struct(const std::string& name);
};