#include "glow.hpp"
#include "../../dependencies/interfaces/interfaces.hpp"
#include "../../source-sdk/classes/entities.hpp"
#include "../../config/config.hpp"
#include "../../dependencies/utilities/csgo.hpp"


void glow::run() {
	if (!config::esp::glow || !local_player)
		return;

	for (size_t i = 0; i < interfaces::glow_manager->size; ++i) {
		glow_object_definition_t& glow = interfaces::glow_manager->objects[i];

		player_t* entity = glow.entity;

		if (glow.unused() || !entity || !entity->alive() || entity->team() == local_player->team())
			continue;

		switch (entity->client_class()->class_id) {
		case class_ids::ccsplayer:
			if (config::esp::player_glow)
				glow.set(config::esp::player_glow_clr[0], config::esp::player_glow_clr[1], config::esp::player_glow_clr[2], config::esp::player_glow_clr[3] + 1);
			break;

		case 35:
			if (config::esp::weapon_glow)
				glow.set(config::esp::weapon_glow_clr[0], config::esp::weapon_glow_clr[1], config::esp::weapon_glow_clr[2], config::esp::weapon_glow_clr[3] + 3);
			break;

		}


	}
}