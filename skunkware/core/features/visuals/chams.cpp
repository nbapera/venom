#include "chams.hpp"
#include "../../config/config.hpp"

inline bool once = false;
inline float color[3] = { 0.55, 1.00, 0.10 };
inline float color2[3] = { 0.10, 1.00, 0.70 };
void chams::run(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* bone_to_world, hooks::draw_model_execute::fn original) {

	if (!config::chams) {
		return original(interfaces::model_render, ctx, state, info, bone_to_world);
	}

	i_material* mat = interfaces::material_system->find_material("debug/debugambientcube");

	if (local_player && info.renderable) {

		auto model_name = interfaces::model_info->get_model_name((model_t*)info.model);
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(info.entity_index));

		if (!model_name || !entity)
			return original(interfaces::model_render, ctx, state, info, bone_to_world);

		if (model_name && strstr(model_name, "models/player")) {

			if (!entity || !entity->is_alive(interfaces::i_client_class) || entity->dormant() || !interfaces::engine->is_in_game() || entity->team() == local_player->team())
				return;

			interfaces::studio_render->set_alpha_modulation(1.f);

			mat->set_material_var_flag(material_var_ignorez, true);
			mat->color_modulate(config::chams_clr_hidden[0], config::chams_clr_hidden[1], config::chams_clr_hidden[2]);
			interfaces::model_render->override_material(mat);
			original(interfaces::model_render, ctx, state, info, bone_to_world);

			mat->set_material_var_flag(material_var_ignorez, false);
			mat->color_modulate(config::chams_clr[0], config::chams_clr[1], config::chams_clr[2]);
			interfaces::model_render->override_material(mat);
			original(interfaces::model_render, ctx, state, info, bone_to_world);

			return interfaces::model_render->override_material(nullptr);


		}

	}
	original(interfaces::model_render, ctx, state, info, bone_to_world);

}