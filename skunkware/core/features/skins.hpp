#pragma once
#include "../../source-sdk/classes/entities.hpp"

namespace skins {
	bool apply_knife_model(attributable_item_t* weapon, const char* model) noexcept;
	bool apply_knife_skin(attributable_item_t* weapon, int item_definition_index, int paint_kit, int model_index, int entity_quality, float fallback_wear) noexcept;
	void run() noexcept;
}