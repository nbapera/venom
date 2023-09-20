#include "hooks.hpp"
#include "dependencies/utilities/csgo.hpp"

#include "core/menu/menu.hpp"

#include "core/menu/imgui/imgui.h"
#include "core/menu/imgui/imgui_impl_dx9.h"
#include "core/menu/imgui/imgui_internal.h"
#include "core/menu/imgui/imgui_impl_win32.h"

#include "core/features/visuals/chams.hpp"
#include "core/features/skins.hpp"
#include "core/config/config.hpp"
#include "core/features/visuals/esp.hpp"
#include "core/features/visuals/glow.hpp"
#include "core/features/legit.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


hooks::create_move::fn create_move_original = nullptr;
hooks::draw_model_execute::fn draw_model_execute_original = nullptr;
hooks::end_scene::fn end_scene_original = nullptr;
hooks::frame_stage_notify::fn frame_stage_notify_original = nullptr;
hooks::do_post_screen_effects::fn do_post_screen_effects_original = nullptr;
hooks::override_view::fn override_view_original = nullptr;
/*
hooks::game_events::fn fire_game_event_original = nullptr;*/
hooks::lock_cursor::fn lock_cursor_original = nullptr;
hooks::get_screen_aspect_ratio::fn get_screen_aspect_ratio_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;
hooks::get_view_model_fov::fn get_view_model_fov_original = nullptr;


bool hooks::initialize() {
	auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 24));
	auto draw_model_execute_target = reinterpret_cast<void*>(get_virtual(interfaces::model_render, 21));
	auto end_scene_target = reinterpret_cast<void*>(get_virtual(interfaces::directx, 42)); 
	auto lock_cursor_target = reinterpret_cast<void*>(get_virtual(interfaces::surface, 67));
	auto get_screen_aspect_ratio_target = reinterpret_cast<void*>(get_virtual(interfaces::engine, 101));
	auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));
	auto frame_stage_notify_target = reinterpret_cast<void*>(get_virtual(interfaces::client, 37));
	auto do_post_screen_effects_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 44));
	auto get_view_model_fov_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 35));
	auto override_view_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 18));

	/*auto fire_game_events = reinterpret_cast<void*>(get_virtual(interfaces::event_manager, 9));*/

	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize MH_Initialize.");

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");

	if (MH_CreateHook(draw_model_execute_target, &draw_model_execute::hook, reinterpret_cast<void**>(&draw_model_execute_original)) != MH_OK)
		throw std::runtime_error("failed to initialize dme. (outdated index?)");

	if (MH_CreateHook(end_scene_target, &end_scene::hook, reinterpret_cast<void**>(&end_scene_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize present. (outdated index?)");
	}

	if (MH_CreateHook(frame_stage_notify_target, &frame_stage_notify::hook, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK)
		throw std::runtime_error("failed to initialize frame_stage_notify. (outdated index?)");

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");
	}

	if (MH_CreateHook(do_post_screen_effects_target, &do_post_screen_effects::hook, reinterpret_cast<void**>(&do_post_screen_effects_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize do_post_screen_effects. (outdated index?)");
	}

	if (MH_CreateHook(get_screen_aspect_ratio_target, &get_screen_aspect_ratio::hook, reinterpret_cast<void**>(&get_screen_aspect_ratio_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize present. (outdated index?)");
	}

	if (MH_CreateHook(get_view_model_fov_target, &get_view_model_fov::hook, reinterpret_cast<void**>(&get_view_model_fov_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize present. (outdated index?)");
	}

	if (MH_CreateHook(override_view_target, &override_view::hook, reinterpret_cast<void**>(&override_view_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize present. (outdated index?)");
	}

	/*
	if (MH_CreateHook(fire_game_events, &game_events::hook, reinterpret_cast<void**>(&fire_game_event_original)) != MH_OK) {
		throw std::runtime_error("failed fire_game_events");
	}*/

	if (MH_CreateHook(lock_cursor_target, &lock_cursor::hook, reinterpret_cast<void**>(&lock_cursor_original)) != MH_OK)
		throw std::runtime_error("failed to initialize lock_cursor. (outdated index?)");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("failed to enable hooks.");



	return true;
}

void hooks::release() {
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

bool __stdcall hooks::create_move::hook(float input_sample_frametime, c_usercmd* cmd) {

	create_move_original(input_sample_frametime, cmd);

	if (!local_player) {
		return false;
	}

	if (!(local_player->flags(interfaces::i_client_class) & fl_onground) && config::bhop) {
		cmd->buttons &= ~in_jump;
	}

	legit::run(cmd);

	return false;
}

void __stdcall hooks::draw_model_execute::hook(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* bone_to_world) {
	chams::run(ctx, state, info, bone_to_world, draw_model_execute_original);
}

LRESULT __stdcall hooks::wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	static bool pressed = false;

	if (!pressed && GetAsyncKeyState(VK_INSERT)) {
		pressed = true;
	}
	else if (pressed && !GetAsyncKeyState(VK_INSERT)) {
		pressed = false;

		menu.is_open = !menu.is_open;
	}

	if (menu.is_open) {
		interfaces::inputsystem->enable_input(false);

	}
	else if (!menu.is_open) {
		interfaces::inputsystem->enable_input(true);
	}

	if (menu.is_open && ImGui_ImplWin32_WndProcHandler(hwnd, message, wparam, lparam))
		return true;

	return CallWindowProcA(wndproc_original, hwnd, message, wparam, lparam);
}

long __stdcall hooks::end_scene::hook(IDirect3DDevice9* device) {

	menu.render(device);
	return end_scene_original(device);
}

void __stdcall hooks::lock_cursor::hook() {

	if (menu.is_open) {
		interfaces::surface->unlock_cursor();
		return;
	}

	lock_cursor_original(interfaces::surface);
}

float __fastcall hooks::get_screen_aspect_ratio::hook(void* edx, void* edb, int32_t height, int32_t width) {
	return config::esp::aspect_ratio;
}

void __stdcall hooks::frame_stage_notify::hook(int frame_stage) {

	if (frame_stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && interfaces::engine->is_in_game()) {
		skins::run();
	}

	frame_stage_notify_original(interfaces::client, frame_stage);
}

float __fastcall hooks::get_view_model_fov::hook(int edx) {

	if (!interfaces::engine->is_in_game() || interfaces::engine->is_taking_screenshot())
		return get_view_model_fov_original(interfaces::clientmode, edx);

	if (local_player)
		return get_view_model_fov_original(interfaces::clientmode, edx) + config::esp::viewmodel_fov;

	return get_view_model_fov_original(interfaces::clientmode, edx);
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {

	if (!interfaces::engine->is_in_game())
		return paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);

	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));

	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):
		esp::run();
		break;

	case fnv::hash("FocusOverlayPanel"):
		break;
	}

	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}

int __stdcall hooks::do_post_screen_effects::hook(int value) {

	//misc::disable_post_processing();
	glow::run();
	//esp::aspect_ratio();
	//visuals::nightmode::run();
	esp::nightmode();
	return do_post_screen_effects_original(interfaces::clientmode, value);
}

bool __fastcall hooks::override_view::hook(uintptr_t ecx, uintptr_t edx, view_setup_t* setup) {

	setup->fov = config::esp::override_fov;

	return override_view_original(ecx, edx, setup);
}

/*bool __stdcall hooks::game_events::hook(i_game_event* event) {

	return fire_game_event_original(interfaces::event_manager, event);
}



*/