#pragma once
#include "unclass.h"

class __declspec(dllexport) UnParams
{
public:
	std::vector<void*> m_params;
public:
	UnParams(std::vector<void*> params) : m_params(params) {}
};

class __declspec(dllexport) UnRet
{
public:
	void* m_data;
	uint32_t m_offset;
public:
	UnRet() : m_data(nullptr), m_offset(0) {}
	UnRet(void* data, uint32_t offset) : m_data(data), m_offset(offset) {}
};