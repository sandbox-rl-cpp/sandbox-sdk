#include "unclass.h"

UField* UField::Next()
{
	return *reinterpret_cast<UField**>(this + 0x60);
}

UField* UStruct::SuperField()
{
	return *reinterpret_cast<UField**>(this + 0x80);
}

UField* UStruct::Children()
{
	return *reinterpret_cast<UField**>(this + 0x88);
}

uint32_t UStruct::PropertySize()
{
	return *reinterpret_cast<uint32_t*>(this + 0x90);
}

UStruct* UStruct::find_struct(const std::string& name)
{
	static std::map<std::string, UStruct*> s_structs;

	if (s_structs.size() == 0)
	{
		for (int i = 0; i < UObject::objects()->size(); i++)
		{
			UObject* u_object = UObject::objects()->at(i);

			if (u_object)
			{
				UObject* u_class = u_object->Class();

				if (u_class && u_class->get_name() == "ScriptStruct")
				{
					s_structs[u_object->get_name()] = (UStruct*)u_object;
				}
			}
		}
	}

	return s_structs[name];
}

uint32_t UProperty::ElementSize()
{
	return *reinterpret_cast<uint32_t*>(this + 0x74);
}

int64_t UProperty::PropertyFlags()
{
	return *reinterpret_cast<uint32_t*>(this + 0x78);
}

uint32_t UProperty::Offset()
{
	return *reinterpret_cast<uint32_t*>(this + 0x98);
}

UClass* UClass::find_class(const std::string & name)
{
	static std::map<std::string, UClass*> s_classes;

	if (s_classes.size() == 0)
	{
		for (int i = 0; i < objects()->size(); i++)
		{
			UObject* u_object = objects()->at(i);

			if (u_object)
			{
				UObject* u_class = u_object->Class();

				if (u_class && u_class->get_name() == "Class")
				{
					s_classes[u_object->get_full_name()] = (UClass*)u_object;
				}
			}
		}
	}

	return s_classes[name];
}

uintptr_t UFunction::Func()
{
	return *reinterpret_cast<uintptr_t*>(this + 0x158);
}

UFunction* UFunction::find_function(const std::string& name)
{
	static std::map<std::string, UFunction*> s_functions;

	if (s_functions.size() == 0)
	{
		for (int i = 0; i < objects()->size(); i++)
		{
			UObject* u_object = objects()->at(i);

			if (u_object)
			{
				UObject* u_class = u_object->Class();

				if (u_class && u_class->get_name() == "Function")
				{
					s_functions[u_object->get_full_name()] = (UFunction*)u_object;
				}
			}
		}
	}

	return s_functions[name];
}