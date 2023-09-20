#pragma once

#include <cstdint>

#include "../../../source-sdk/classes/recv_props.hpp"
#include "../../../source-sdk/classes/client_class.hpp"

namespace netvars {
	// Finding Offsets
	uintptr_t get_offset(recv_table* table, const char* tableName, const char* netvarName, const char* propName, int dataOffset);

	// Looping through the linked list to call `GetOffset`
	uintptr_t get_netvar_offset(const char* tableName, const char* netvarName, c_client_class*clientClass, const char* propName, int dataOffset);
}