#pragma once
#include "unobj.h"

class __declspec(dllexport) UField : public UObject
{
public:
	class UField* Next();
};

class __declspec(dllexport) UStruct : public UField
{
public:
	class UField* SuperField();
	class UField* Children();
	uint32_t PropertySize();
public:
	static UStruct* find_struct(const std::string& name);
};

class __declspec(dllexport) UProperty : public UField
{
public:
	uint32_t ElementSize();
	int64_t	PropertyFlags();
	uint32_t Offset();
};

class __declspec(dllexport) UClass : public UStruct
{
public:
	static UClass* find_class(const std::string& name);
};

class __declspec(dllexport) UFunction : public UStruct
{
public:
	uintptr_t Func();
public:
	static UFunction* find_function(const std::string& name);
};