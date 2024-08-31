#include "unname.h"

#include <Windows.h>

std::string FNameEntry::get_name()
{
	std::wstring wstring(m_name);
	return std::string(wstring.begin(), wstring.end());
}

TArray<FNameEntry*>* FName::names()
{
	if (!g_names)
	{
		g_names = (TArray<FNameEntry*>*)(reinterpret_cast<uintptr_t>(GetModuleHandleW(0)) + 0x24BF490);
	}

	return g_names;
}

bool FName::is_valid()
{
	return m_index >= 0 && m_index < names()->size();
}

FNameEntry FName::get_entry()
{
	return *names()->at(m_index);
}

std::string FName::to_string()
{
	if (is_valid())
	{
		return get_entry().get_name();
	}

	return "None";
}

bool FName::operator==(const FName& name)
{
	return m_index == name.m_index;
}

bool FName::operator!=(const FName& name)
{
	return m_index != name.m_index;
}