#include "legit.hpp"
#include "../config/config.hpp"

player_t* find_target(c_usercmd* user_cmd)
{
	if (!(user_cmd->buttons & cmd_buttons::in_attack))
		return;

	if (local_player->is_defusing())//netvar
		return;

	weapon_t* weapon = local_player->active_weapon();

	if (weapon->get_type() != WEAPONTYPE_MACHINEGUN || weapon->get_type() != WEAPONTYPE_PISTOL//switch za buducnost
	|| weapon->get_type() != WEAPONTYPE_RIFLE || weapon->get_type() != WEAPONTYPE_SHOTGUN
	|| weapon->get_type() != WEAPONTYPE_SNIPER_RIFLE || !weapon->clip1_count());
	{
		return;
	}


	if (weapon->get_type() == WEAPONTYPE_SNIPER_RIFLE && !local_player->is_scoped())
		return;


	float best_fov = FLT_MAX;
	player_t* entity = nullptr;
	float damage = 0;

	for (int i = 1; i < interfaces::globals->max_clients; i++)
	{
		player_t* current_entity = (player_t*)interfaces::entity_list->get_client_entity(i);
		if (!current_entity || !current_entity->is_alive(interfaces::i_client_class) || current_entity->dormant() || current_entity->team() == local_player->team())
			continue;

		//if (!local_player->can_see_player_pos(entity, entity->get_eye_pos()))
			//continue;


		float cdistance = local_player->get_eye_pos().distance_to(current_entity->get_eye_pos());

		math::distance_based_fov(cdistance, math::calculate_angle(local_player->get_eye_pos(), current_entity->get_bone_position(8), user_cmd->viewangles), user_cmd);

		if (config::legit::fov < best_fov) {
			best_fov = config::legit::fov;
			entity = current_entity;
		}

	}
	return entity;
}

void legit::run(c_usercmd* user_cmd)
{

	if (!config::legit::aim)
		return;

	if (!local_player->is_alive(interfaces::i_client_class))
		return;

	player_t* entity = find_target(user_cmd);
	if (!entity)
		return;

	auto angle = math::calculate_angle(local_player->get_eye_pos(), entity->get_bone_position(8), user_cmd->viewangles + local_player->aim_punch_angle());

	angle = angle.clamp();

	if (config::legit::smoothing != 0)
		angle /= (config::legit::smoothing * 5);

	angle.normalize();

	user_cmd->viewangles += angle;

	interfaces::engine->set_view_angles(user_cmd->viewangles);

}