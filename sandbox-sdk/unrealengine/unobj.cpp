#include "unclass.h"
#include "unstruct.h"
#include "unfunc.h"

void* UObject::VTable()
{
	return *reinterpret_cast<void**>(this);
}

int32_t UObject::ObjectIndex()
{
	return *reinterpret_cast<int32_t*>(this + 0x38);
}

UObject* UObject::Outer()
{
	return *reinterpret_cast<UObject**>(this + 0x40);
}

FName UObject::Name()
{
	return *reinterpret_cast<FName*>(this + 0x48);
}

UObject* UObject::Class()
{
	return *reinterpret_cast<UObject**>(this + 0x50);
}

TArray<UObject*>* UObject::objects()
{
	if (!g_objects)
	{
		g_objects = (TArray<UObject*>*)(reinterpret_cast<uintptr_t>(FName::names()) + 0x48);
	}

	return g_objects;
}

std::string UObject::get_name()
{
	return this->Name().to_string();
}

std::string UObject::get_full_name()
{
	UObject* u_class = this->Class();

	if (u_class)
	{
		std::string outer_name;

		for (UObject* u_outer = this->Outer(); u_outer; u_outer = u_outer->Outer())
		{
			outer_name = std::format("{}.{}", u_outer->get_name(), outer_name);
		}

		return std::format("{} {}{}", u_class->get_name(), outer_name, this->get_name());
	}

	return "None";
}

int32_t UObject::find_offset(const std::string& name)
{
	static std::map<std::string, int32_t> s_offsets;

	if (s_offsets.contains(name))
	{
		return s_offsets[name];
	}

	for (UClass* u_class = (UClass*)this->Class(); u_class; u_class = (UClass*)u_class->SuperField())
	{
		for (UProperty* u_property = (UProperty*)u_class->Children(); u_property; u_property = (UProperty*)u_property->Next())
		{
			if (u_property->ElementSize() > 0)
			{
				if (name == u_property->get_name())
				{
					s_offsets[name] = u_property->Offset();
					return s_offsets[name];
				}
			}
		}
	}

	return 0;
}

UnStruct UObject::get_struct_field(const std::string& unstruct, const std::string& name)
{
	return UnStruct(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(this) + find_offset(name)), unstruct);
}

UnFunc UObject::call_function(const std::string& name, UnParams params)
{
	return UnFunc(this, std::format("Function {}", name), params);
}

void UObject::process_event(UFunction* function, void* params, void* result)
{
	if (!process_event_original)
	{
		process_event_original = decltype(process_event_original)(reinterpret_cast<void**>(UClass::find_class("Class Core.Object")->VTable())[67]);
	}
	
	process_event_original(this, function, params, result);
}