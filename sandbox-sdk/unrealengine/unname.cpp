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
	if (!g_names)
	{
		uintptr_t image_base = reinterpret_cast<uintptr_t>(GetModuleHandleW(0));
		uintptr_t image_size = reinterpret_cast<IMAGE_NT_HEADERS*>(image_base + reinterpret_cast<IMAGE_DOS_HEADER*>(image_base)->e_lfanew)->OptionalHeader.SizeOfImage;
		
		std::vector<uint8_t> signature = { 'B', '.', 'y', '.', 't', '.', 'e', '.', 'P', '.', 'r', '.', 'o', '.', 'p', '.', 'e', '.', 'r', '.', 't', '.', 'y' };
		uintptr_t signature_address = 0;
		int32_t pos = 0;

		for (uintptr_t address = image_base; address < image_base + image_size; address++)
		{
			if (address && *reinterpret_cast<uint8_t*>(address) == signature[pos] || signature[pos] == '.')
			{
				if (pos == signature.size())
				{
					signature_address = address - signature.size(); break;
				}

				pos++;
			}
			else
			{
				pos = 0;
			}
		}
		
		if (signature_address)
		{
			for (uintptr_t address = image_base; address < image_base + image_size; address++)
			{
				if (address)
				{
					auto find_address = address + *reinterpret_cast<uint32_t*>(address + 3) + 7;

					if (signature_address == find_address)
					{
						auto offset = address - 0xB;
						
						g_names = (TArray<FNameEntry*>*)(offset + *reinterpret_cast<uint32_t*>(offset + 3) - 9);

						break;
					}
				}
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