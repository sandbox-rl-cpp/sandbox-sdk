#include "unstring.h"

bool FString::is_valid()
{
	return data();
}

int32_t FString::length() const
{
	return size();
}

int32_t FString::size() const
{
	return capacity();
}

std::string FString::to_string()
{
	if (is_valid())
	{
		std::wstring wstring(data());
		return std::string(wstring.begin(), wstring.end());
	}

	return "None";
}

FString FString::operator=(wchar_t* string)
{
	if (m_data != string)
	{
		m_max = m_num = *string ? (wcslen(string) + 1) : 0;

		if (m_num > 0)
		{
			m_data = string;
		}
	}

	return *this;
}

bool FString::operator==(const FString& string)
{
	return !wcscmp(data(), string.data());
}

bool FString::operator!=(const FString& string)
{
	return wcscmp(data(), string.data());
}