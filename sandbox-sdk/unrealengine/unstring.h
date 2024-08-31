#pragma once
#include "unname.h"

class __declspec(dllexport) FString : public TArray<wchar_t>
{
public:
	bool is_valid();
	int32_t length() const;
	int32_t size() const;
	std::string to_string();

	FString operator=(wchar_t* string);
	bool operator==(const FString& string);
	bool operator!=(const FString& string);
};