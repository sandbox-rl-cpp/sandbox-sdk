#pragma once
#include "array.h"

struct __declspec(dllexport) FNameEntry
{
private:
	uint8_t m_pad[0x18];
	wchar_t m_name[0x100];
public:
	std::string get_name();
};

class __declspec(dllexport) FName
{
private:
	int32_t m_index;
	int32_t m_num;
public:
	static inline TArray<FNameEntry*>* g_names;

	static TArray<FNameEntry*>* names();

	bool is_valid();
	FNameEntry get_entry();
	std::string to_string();

	bool operator==(const FName& name);
	bool operator!=(const FName& name);
};