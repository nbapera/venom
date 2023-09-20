#include "skins.hpp"

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

bool skins::apply_knife_model(attributable_item_t* weapon, const char* model) noexcept {
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	if (!local_player)
		return false;

	auto viewmodel = reinterpret_cast<base_view_model_t*>(interfaces::entity_list->get_client_entity_handle(local_player->view_model()));

	if (!viewmodel)
		return false;

	auto h_view_model_weapon = viewmodel->m_hweapon();

	if (!h_view_model_weapon)
		return false;

	auto view_model_weapon = reinterpret_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity_handle(h_view_model_weapon));

	if (view_model_weapon != weapon)
		return false;

	viewmodel->model_index() = interfaces::model_info->get_model_index(model);

	return true;
}

bool skins::apply_knife_skin(attributable_item_t* weapon, int item_definition_index, int paint_kit, int model_index, int entity_quality, float fallback_wear) noexcept {
	weapon->item_definition() = item_definition_index;
	weapon->fallback_paint_kit() = paint_kit;
	weapon->model_index() = model_index;
	weapon->entity_quality() = entity_quality;
	weapon->fallback_wear() = fallback_wear;

	return true;
}


void skins::run() noexcept {
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
		return;

	//if (!cfg.skinchanger)
	//	return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	if (!local_player)
		return;

	auto active_weapon = local_player->active_weapon();

	if (!active_weapon)
		return;

	auto model_bayonet = "models/weapons/v_knife_bayonet.mdl";
	auto model_m9 = "models/weapons/v_knife_m9_bay.mdl";
	auto model_karambit = "models/weapons/v_knife_karam.mdl";
	auto model_bowie = "models/weapons/v_knife_survival_bowie.mdl";
	auto model_butterfly = "models/weapons/v_knife_butterfly.mdl";
	auto model_falchion = "models/weapons/v_knife_falchion_advanced.mdl";
	auto model_flip = "models/weapons/v_knife_flip.mdl";
	auto model_gut = "models/weapons/v_knife_gut.mdl";
	auto model_huntsman = "models/weapons/v_knife_tactical.mdl";
	auto model_shadow_daggers = "models/weapons/v_knife_push.mdl";
	auto model_navaja = "models/weapons/v_knife_gypsy_jackknife.mdl";
	auto model_stiletto = "models/weapons/v_knife_stiletto.mdl";
	auto model_talon = "models/weapons/v_knife_widowmaker.mdl";
	auto model_ursus = "models/weapons/v_knife_ursus.mdl";

	auto index_bayonet = interfaces::model_info->get_model_index("models/weapons/v_knife_bayonet.mdl");
	auto index_m9 = interfaces::model_info->get_model_index("models/weapons/v_knife_m9_bay.mdl");
	auto index_karambit = interfaces::model_info->get_model_index("models/weapons/v_knife_karam.mdl");
	auto index_bowie = interfaces::model_info->get_model_index("models/weapons/v_knife_survival_bowie.mdl");
	auto index_butterfly = interfaces::model_info->get_model_index("models/weapons/v_knife_butterfly.mdl");
	auto index_falchion = interfaces::model_info->get_model_index("models/weapons/v_knife_falchion_advanced.mdl");
	auto index_flip = interfaces::model_info->get_model_index("models/weapons/v_knife_flip.mdl");
	auto index_gut = interfaces::model_info->get_model_index("models/weapons/v_knife_gut.mdl");
	auto index_huntsman = interfaces::model_info->get_model_index("models/weapons/v_knife_tactical.mdl");
	auto index_shadow_daggers = interfaces::model_info->get_model_index("models/weapons/v_knife_push.mdl");
	auto index_navaja = interfaces::model_info->get_model_index("models/weapons/v_knife_gypsy_jackknife.mdl");
	auto index_stiletto = interfaces::model_info->get_model_index("models/weapons/v_knife_stiletto.mdl");
	auto index_talon = interfaces::model_info->get_model_index("models/weapons/v_knife_widowmaker.mdl");
	auto index_ursus = interfaces::model_info->get_model_index("models/weapons/v_knife_ursus.mdl");

	auto my_weapons = local_player->get_weapons();
	for (int i = 0; my_weapons[i] != INVALID_EHANDLE_INDEX; i++) {
		auto weapon = reinterpret_cast<attributable_item_t*>(interfaces::entity_list->get_client_entity_handle(my_weapons[i]));

		if (!weapon)
			return;

		float wear = 0.f;
		wear = 0.001f;

		switch (active_weapon->client_class()->class_id)
		{
		case class_ids::cknife:
			apply_knife_model(weapon, model_m9);
			//apply_knife_skin(weapon, WEAPON_KNIFE_M9_BAYONET, 618, index_bayonet, 3, wear);
			break;
		}

	}
}