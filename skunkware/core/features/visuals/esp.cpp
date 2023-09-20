#define _CRT_SECURE_NO_WARNINGS

#include "esp.hpp"
#include "../../dependencies/interfaces/interfaces.hpp"
#include "../../dependencies/utilities/csgo.hpp"
#include "../../config/config.hpp"

void esp::player_box(player_t* entity) {
	if (!entity)
		return;

	if ((entity->dormant() && alpha[entity->index()] == 0)) // && config::player_box_dormant = true?
		return;

	player_info_t info;
	interfaces::engine->get_player_info(entity->index(), &info);

	box bbox;
	if (!get_box(entity, bbox))
		return;

	if (config::esp::player_box) {
		auto red = config::clr_box[0];
		auto green = config::clr_box[1];
		auto blue = config::clr_box[2];

		render::draw_outline(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, color(0, 0, 0, alpha[entity->index()] - 90));
		render::draw_rect(bbox.x, bbox.y, bbox.w, bbox.h, color(red, green, blue, (alpha[entity->index()] - 90)));
		render::draw_outline(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, color(0, 0, 0, alpha[entity->index()] - 90));
	}

}

void esp::skeleton(player_t* entity) {
	if (!config::esp::skeleton)
		return;

	auto p_studio_hdr = interfaces::model_info->get_studio_model(entity->model());
	if (!p_studio_hdr)
		return;

	vec3_t v_parent, v_child, s_parent, s_child;

	for (int j = 0; j < p_studio_hdr->bones_count; j++) {
		studio_bone_t* bone = p_studio_hdr->bone(j);
		if (!bone)return;

		if (bone && (bone->flags & BONE_USED_BY_HITBOX) && (bone->parent != -1)) {
			v_child = entity->get_bone_position(j);
			v_parent = entity->get_bone_position(bone->parent);

			int chest_bone = 6;  // Parameter of relevant Bone number
			//vec3_t breast_bone; // New reference Point for connecting many bones

			vec3_t upper_direction = entity->get_bone_position(chest_bone + 1) - entity->get_bone_position(chest_bone); // direction vector from chest to neck
			vec3_t breast_bone = entity->get_bone_position(chest_bone) + upper_direction / 2;

			vec3_t v_delta_child = v_child - breast_bone; // Used to determine close bones to the reference point
			vec3_t v_delta_parent = v_parent - breast_bone;

			// Eliminating / Converting all disturbing bone positions in three steps.
			if ((v_delta_parent.size() < 9 && v_delta_child.size() < 9))
				v_parent = breast_bone;

			if (j == chest_bone - 1)
				v_child = breast_bone;

			if (abs(v_delta_child.z) < 5 && (v_delta_parent.size() < 5 && v_delta_child.size() < 5) || j == chest_bone)
				continue;

			if (math::world_to_screen(v_parent, s_parent) && math::world_to_screen(v_child, s_child))
				render::draw_line(s_parent[0], s_parent[1], s_child[0], s_child[1], color(255, 255, 255));
		}
	}
}

void esp::player_weapon(player_t* entity, box bbox) {

	auto red = config::esp::player_weapon_clr[0] * 255;
	auto green = config::esp::player_weapon_clr[1] * 255;
	auto blue = config::esp::player_weapon_clr[2] * 255;

	int redz = config::esp::player_weapon_clr_drop[0] * 255;
	int greenz = config::esp::player_weapon_clr_drop[1] * 255;
	int bluez = config::esp::player_weapon_clr_drop[2] * 255;

	auto weapon = entity->active_weapon();
	if (!weapon)return;

	auto info = weapon->get_weapon_data();
	if (!info)return;

	const char* hud_name = info->m_szHudName;
	if (!hud_name)return;

	wchar_t* weapon_name = interfaces::localize->find(hud_name);
	if (!weapon_name)return;
	_wcsupr(weapon_name);

	//wchar_t icon_name[2] = { (wchar_t)visual::WeaponIcons[weapon->item_definition()], 0 };

	//	setup for drawing
	std::string ammo_s = "" + std::to_string(weapon->clip1_count());
	const auto ammo = weapon->clip1_count();
	const auto max_ammo = info->m_iMaxClip;
	auto width = bbox.w;
	width *= ammo;
	width /= max_ammo;

	if (!(info->m_iWeaponType == WEAPONTYPE_KNIFE || info->m_iWeaponType == WEAPONTYPE_GRENADE || info->m_iWeaponType == WEAPONTYPE_C4)) {
		// background
		render::draw_filled_rect(bbox.x - 1, bbox.y + bbox.h + 1, bbox.w + 2, 4, color(0, 0, 0, alpha[entity->index()] - 90));
		// ammo bar
		render::draw_filled_rect(bbox.x, bbox.y + bbox.h + 2, width, 2, color(redz, greenz, bluez, 240));
		//render::draw_text_string(bbox.x + width + 2, bbox.y + bbox.h + 2, render::fonts::watermark_font, ammo_s, true, color(255, 255, 255, 240));
	}

	int h_index = 0;
	//if (weapno text)
	render::draw_text_wchar(bbox.x + (bbox.w / 2), bbox.h + (6 * h_index) + bbox.y + 4, render::fonts::name_font, weapon_name, true, color(red, green, blue, alpha[entity->index()]));
	h_index++;

	/*if (config_system.item.player_weapon_icon) {
		render::draw_text_wchar(bbox.x + (bbox.w / 2), bbox.h + (6 * h_index) + bbox.y + 4, render::fonts::icon_font, icon_name, true, color(red, green, blue, alpha[entity->index()]));
		h_index++;
	}*/

}

void esp::run() {

	if (!config::esp::enabled) {
		return;
	}

	box bbox;

	for (int i = 1; i <= interfaces::globals->max_clients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || 
			entity == local_player || 
			entity->health() <= 0 || 
			entity->dormant() || 
			entity->team(interfaces::i_client_class) == local_player->team(interfaces::i_client_class))
			continue;



		if (!get_box(entity, bbox))
			return;

		if (config::esp::skeleton)
			skeleton(entity);

		//if (config::esp::player_box)
			//player_box(entity);

		if (config::esp::player_weapon)
			player_weapon(entity, bbox);
		

	}
}

void esp::aspect_ratio() {
	static convar* aspect = interfaces::console->get_convar("r_aspectratio");

	if (aspect) {
		aspect->callbacks.size = 0;
		aspect->set_value(config::esp::aspect_ratio);
	}

	//aspect->set_value(config::esp::aspect_ratio);
}
void esp::nightmode() {
	static convar* sv_skyname = interfaces::console->get_convar("sv_skyname");

	if (sv_skyname) {
		MessageBoxA(0, "skyname not nptr", "", 0);
	}
}