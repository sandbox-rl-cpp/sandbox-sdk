#pragma once
#include "unstring.h"

class __declspec(dllexport) UObject
{
public:
	void* VTable();
	int32_t ObjectIndex();
	class UObject* Outer();
	class FName Name();
	class UObject* Class();
public:
	static inline TArray<UObject*>* g_objects;

	static TArray<UObject*>* objects();

	std::string get_name();
	std::string get_full_name();

	int32_t find_offset(const std::string& name);

	template <typename T>
	T& get_field(const std::string& name)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(this) + find_offset(name));
	}

	class UnStruct get_struct_field(const std::string& unstruct, const std::string& name);
	class UnFunc call_function(const std::string& name, class UnParams params);

	static inline void (*process_event_original)(class UObject*, class UFunction*, void*, void*);

	void process_event(class UFunction* function, void* params, void* result);
};