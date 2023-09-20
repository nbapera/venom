#pragma once
#include "../../../dependencies/utilities/csgo.hpp"
#include "../../../hooks.hpp"

namespace chams {
	void run(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* bone_to_world, hooks::draw_model_execute::fn original);
}