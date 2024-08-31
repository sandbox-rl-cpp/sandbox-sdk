#pragma once
#include <cstdint>
#include <format>
#include <string>
#include <vector>
#include <map>

template <typename T>
class __declspec(dllexport) TArray
{
public:
	T* m_data;
	int32_t m_num;
	int32_t m_max;
public:
	T& at(const int32_t index) const
	{
		return m_data[index];
	}

	int32_t size() const
	{
		return m_num;
	}

	int32_t capacity() const
	{
		return m_max;
	}

	T* data() const
	{
		return m_data;
	}
};