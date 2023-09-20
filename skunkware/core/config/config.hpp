#pragma once

namespace config {

	inline bool bhop = true;
	inline bool ncc = false;
	inline bool moonwalk = false;

	inline bool preserve_kill_feed = true;
	inline bool radar = true;
	inline bool rank_reveal = false;
	inline bool disable_post_processing = false;
	inline bool sniper_crosshair = false;
	inline bool recoil_crosshair = false;

	inline bool hitsounds = true;
	inline bool hitmarker = true;

	inline bool nightmode = true;
	inline int nightmode_brightness = 40;

	namespace esp {
		inline float aspect_ratio = 1.777f;
		inline int viewmodel_fov = 0;
		inline int override_fov = 90;
		inline bool enabled = false;
		inline bool skeleton = false;
		inline bool player_box = false;
		inline bool player_weapon = false;
		inline float player_weapon_clr[3] = { 0.55, 1.0, 0.10 };
		inline float player_weapon_clr_drop[3] = { 0.53, 0.20, 0.92 };
		inline bool glow = false;

		inline bool player_glow = false;
		inline float player_glow_clr[4] = { 1.f, 0.f, 0.f, 1.f };

		inline bool weapon_glow = false;
		inline float weapon_glow_clr[4] = { 1.f, 0.f, 0.f, 1.f };
	}


	inline float clr_box[4] = { 155.f, 155.f, 155.f, 255.f };

	inline float chams_clr[3] = { 0.55, 1.0, 0.10 };
	inline float chams_clr_hidden[3] = { 0.53, 0.20, 0.92 };
	inline bool chams = true;
	inline bool bullet_tracer = true;

	inline bool backtrack = true;
	inline bool backtrack_chams = false;
	inline int backtrack_ms = 400;


	inline bool skin_changer = true;
	inline bool glove_changer = true;

	inline int glove_model = 6;
	inline int knife_model = 2;

	inline int knife_paint = 562;
	inline int glove_paint = 10061;

	namespace rage {
		inline bool enabled = false;
		inline bool aim = false;
		inline bool autowall = false;
	}

	namespace legit {
		inline bool aim = false;
		inline int fov = 10	;
		inline int smoothing = 3;
	}

	namespace trigger {
		inline bool enabled = false;
		inline bool flash_check = false;
		inline bool jump_check = false;
		inline bool smoke_checl = false;
		inline int reaction = 10;
	}

	namespace paints {
		inline int usp = 100;
		inline int p2000 = 100;
		inline int glock = 100;
		inline int p250 = 100;
		inline int fiveseven = 100;
		inline int tec = 100;
		inline int cz = 100;
		inline int duals = 100;
		inline int deagle = 100;
		inline int revolver = 100;
		inline int famas = 100;
		inline int galil = 100;
		inline int m4a4 = 100;
		inline int m4a1 = 100;
		inline int ak47 = 100;
		inline int sg553 = 100;
		inline int aug = 100;
		inline int ssg08 = 100;
		inline int awp = 100;
		inline int scar = 100;
		inline int g3sg1 = 100;
		inline int sawoff = 100;
		inline int m249 = 100;
		inline int negev = 100;
		inline int mag7 = 100;
		inline int xm1014 = 100;
		inline int nova = 100;
		inline int bizon = 100;
		inline int mp5sd = 100;
		inline int mp7 = 100;
		inline int mp9 = 100;
		inline int mac10 = 100;
		inline int p90 = 100;
		inline int ump45 = 100;
	}

}