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

UnStruct UnArrayStruct::at(const std::string& name, int32_t index)
{
	return UnStruct(reinterpret_cast<void*>(m_data + (index * UStruct::find_struct(name)->PropertySize())), name);
}

void UnArrayStruct::get_array(void* data)
{
	m_data = reinterpret_cast<uintptr_t*>(data);
	m_num = *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(data) + 0x8);
	m_max = *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(data) + 0x4);
}