#include "unstruct.h"

void* UnStruct::operator&()
{
	return m_data;
}

void UnStruct::get_struct(const std::string& name)
{
	UStruct* u_struct = UStruct::find_struct(name);

	if (u_struct)
	{
		for (UProperty* u_property = (UProperty*)u_struct->Children(); u_property; u_property = (UProperty*)u_property->Next())
		{
			if (u_property->ElementSize() > 0)
			{
				m_fields[u_property->get_name()] = u_property->Offset();
			}
		}

		if (!m_data)
		{
			m_data = malloc(u_struct->PropertySize());
		}
	}
}