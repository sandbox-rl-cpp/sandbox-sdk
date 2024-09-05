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

class __declspec(dllexport) UnArrayStruct
{
public:
	uintptr_t* m_data;
	int32_t m_num;
	int32_t m_max;
public:
	UnArrayStruct(void* data) { get_array(data); }

	class UnStruct at(const std::string& name, int32_t index);

	int32_t size() const
	{
		return m_num;
	}
private:
	void get_array(void* data);
};