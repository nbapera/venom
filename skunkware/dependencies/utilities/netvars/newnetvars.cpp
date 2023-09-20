#include "newnetvars.hpp"

#include <string.h>

// Finding Offsets
uintptr_t netvars::get_offset(recv_table* table, const char* tableName, const char* netvarName, const char* propName, int dataOffset) {
	for (int i = 0; i < table->props_count; i++) {
		recv_prop prop = table->props[i];

		// For: propName == varName
		if (!strcmp(prop.prop_name, netvarName)) {
			return prop.offset;
		}
		// For: propName != varName
		else if (!strcmp(propName, prop.prop_name)) {
			return dataOffset + prop.offset;
		}
		// If another table in the current one
		if (prop.data_table) {
			uintptr_t offset = get_offset(prop.data_table, tableName, netvarName, propName, dataOffset);

			if (offset) {
				return offset + prop.offset;
			}
		}
	}
	return 0;
}

// Looping through the linked list to call `GetOffset`
uintptr_t netvars::get_netvar_offset(const char* tableName, const char* netvarName, c_client_class* clientClass, const char* propName, int dataOffset) {
	c_client_class* currentNode = clientClass;

	for (auto currentNode = clientClass; currentNode; currentNode = currentNode->next_ptr) {
		if (strcmp(tableName, currentNode->recvtable_ptr->table_name) == 0) {
			return get_offset(currentNode->recvtable_ptr, tableName, netvarName, propName, dataOffset);
		}
	}
	return 0;
}