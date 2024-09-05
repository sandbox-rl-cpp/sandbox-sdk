#include "unfunc.h"

UnStruct UnFunc::get_struct_ret(const std::string& name)
{
	return UnStruct(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(m_ret.m_data) + m_ret.m_offset), name);
}

void UnFunc::get_function(const std::string& name)
{
	UFunction* u_function = UFunction::find_function(name);

	if (u_function && m_caller)
	{
		void* params = malloc(u_function->PropertySize());
		int param = 0;

		for (UProperty* u_property = (UProperty*)u_function->Children(); u_property; u_property = (UProperty*)u_property->Next(), param++)
		{
			if (params && u_property->ElementSize() > 0)
			{
				if (u_property->PropertyFlags() & 128)
				{
					if (u_property->PropertyFlags() & 256)
					{
						m_ret = UnRet(params, u_property->Offset());
					}
					else
					{
						memcpy(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(params) + u_property->Offset()), m_params.m_params.at(param), u_property->ElementSize());
					}
				}
			}
		}

		m_caller->process_event(u_function, params, nullptr);
	}
}

UnStruct UnFuncParams::get_struct(const std::string& unstruct, const std::string& name)
{
	return UnStruct(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(m_data) + m_params[name]), unstruct);
}

void UnFuncParams::get_params(UFunction* function)
{
	for (UProperty* u_property = (UProperty*)function->Children(); u_property; u_property = (UProperty*)u_property->Next())
	{
		if (u_property->ElementSize() > 0)
		{
			if (u_property->PropertyFlags() & 128)
			{
				m_params[u_property->get_name()] = u_property->Offset();
			}
		}
	}
}