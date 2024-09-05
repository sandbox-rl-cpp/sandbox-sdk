#include "unname.h"

#include <Windows.h>
#include <Psapi.h>

std::string FNameEntry::get_name()
{
	std::wstring wstring(m_name);
	return std::string(wstring.begin(), wstring.end());
}

TArray<FNameEntry*>* FName::names()
{
	while (!g_names)
	{
		uintptr_t image_base = reinterpret_cast<uintptr_t>(GetModuleHandleW(0));
		uintptr_t image_size = reinterpret_cast<IMAGE_NT_HEADERS*>(image_base + reinterpret_cast<IMAGE_DOS_HEADER*>(image_base)->e_lfanew)->OptionalHeader.SizeOfImage;
		
		std::vector<uint8_t> signature = { 0x48, 0x8B, 0x05, '?', '?', '?', '?', 0x4C, 0x89, 0x3C, 0xC8 };
		int32_t pos = 0;

		for (uintptr_t address = image_base; address < image_base + image_size; address++)
		{
			if (address && *reinterpret_cast<uint8_t*>(address) == signature[pos] || signature[pos] == '?')
			{
				if (pos == signature.size() - 1)
				{
					auto offset = address - signature.size() + 1;
					g_names = (TArray<FNameEntry*>*)(offset + *reinterpret_cast<uint32_t*>(offset + 3) + 7);
					break;
				}

				pos++;
			}
			else
			{
				pos = 0;
			}
		}
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