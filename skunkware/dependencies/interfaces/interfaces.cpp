#include "interfaces.hpp"
#include "../utilities/csgo.hpp"
#include <effects.h>

i_base_client_dll* interfaces::client = nullptr;
c_client_class* interfaces::i_client_class = nullptr;
i_studio_render* interfaces::studio_render = nullptr;
i_input* interfaces::input = nullptr;
i_client_entity_list* interfaces::entity_list = nullptr;
iv_engine_client* interfaces::engine = nullptr;
i_client_mode* interfaces::clientmode = nullptr;
i_client_state* interfaces::clientstate = nullptr;
i_panel* interfaces::panel = nullptr;
i_surface* interfaces::surface = nullptr;
c_global_vars_base* interfaces::globals = nullptr;
i_material_system* interfaces::material_system = nullptr;
iv_model_info* interfaces::model_info = nullptr;
iv_model_render* interfaces::model_render = nullptr;
i_render_view* interfaces::render_view = nullptr;
i_console* interfaces::console = nullptr;
i_localize* interfaces::localize = nullptr;
i_game_event_manager2* interfaces::event_manager = nullptr;
i_inputsytem* interfaces::inputsystem = nullptr;
iv_debug_overlay* interfaces::debug_overlay = nullptr;
IDirect3DDevice9* interfaces::directx = nullptr;
trace* interfaces::trace_ray = nullptr;
glow_manager_t* interfaces::glow_manager = nullptr;
player_game_movement* interfaces::game_movement = nullptr;
player_prediction* interfaces::prediction = nullptr;
player_move_helper* interfaces::move_helper = nullptr;
i_weapon_system* interfaces::weapon_system = nullptr;
i_view_render_beams* interfaces::render_beams = nullptr;
iv_effects* interfaces::effects = nullptr;
i_physics_surface* interfaces::physics_surface = nullptr;
void* interfaces::file_system = nullptr;

bool interfaces::initialize() {
	client = get_interface<i_base_client_dll, interface_type::index>(CLIENT_DLL, "VClient018");
	entity_list = get_interface<i_client_entity_list, interface_type::index>(CLIENT_DLL, "VClientEntityList003");
	engine = get_interface<iv_engine_client, interface_type::index>(ENGINE_DLL, "VEngineClient014");
	i_client_class = client->get_client_classes();
	material_system = get_interface<i_material_system, interface_type::index>("materialsystem.dll", "VMaterialSystem080");
	model_info = get_interface<iv_model_info, interface_type::index>(ENGINE_DLL, "VModelInfoClient004");
	model_render = get_interface<iv_model_render, interface_type::index>(ENGINE_DLL, "VEngineModel016");
	studio_render = get_interface < i_studio_render, interface_type::index>("studiorender.dll", "VStudioRender026");
	inputsystem = get_interface<i_inputsytem, interface_type::index>("inputsystem.dll", "InputSystemVersion001");
	surface = get_interface<i_surface, interface_type::index>("vguimatsurface.dll", "VGUI_Surface031");
	panel = get_interface<i_panel, interface_type::index>("vgui2.dll", "VGUI_Panel009");
	console = get_interface<i_console, interface_type::index>("vstdlib.dll", "VEngineCvar007");
	
	/*render_view = get_interface<i_render_view, interface_type::index>(ENGINE_DLL, "VEngineRenderView014");
	
	localize = get_interface<i_localize, interface_type::index>("localize.dll", "Localize_001");
	event_manager = get_interface<i_game_event_manager2, interface_type::index>(ENGINE_DLL, "GAMEEVENTSMANAGER002");
	debug_overlay = get_interface<iv_debug_overlay, interface_type::index>(ENGINE_DLL, "VDebugOverlay004");
	trace_ray = get_interface<trace, interface_type::index>(ENGINE_DLL, "EngineTraceClient004");
	game_movement = get_interface<player_game_movement, interface_type::index>(CLIENT_DLL, "GameMovement001");
	prediction = get_interface<player_prediction, interface_type::index>(CLIENT_DLL, "VClientPrediction001");
	physics_surface = get_interface<i_physics_surface, interface_type::index>("vphysics.dll", "VPhysicsSurfaceProps001");*/

	/*custom interfaces*/
	clientmode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);
	directx = **(IDirect3DDevice9***)(utilities::pattern_scan("shaderapidx9.dll", sig_directx) + 1);
	globals = **reinterpret_cast<c_global_vars_base***>((*reinterpret_cast<uintptr_t**>(client))[0] + 0x1F);
	glow_manager = (glow_manager_t*)(*(uintptr_t*)(utilities::pattern_scan(CLIENT_DLL, sig_glow_manager) + 3));
	clientstate = **(i_client_state***)(utilities::pattern_scan(ENGINE_DLL, sig_client_state) + 1);
	input = *(i_input**)(utilities::pattern_scan(CLIENT_DLL, sig_input) + 1);
	
	/*move_helper = **(player_move_helper***)(utilities::pattern_scan(CLIENT_DLL, sig_player_move_helper) + 2);
	weapon_system = *(i_weapon_system**)(utilities::pattern_scan(CLIENT_DLL, sig_weapon_data) + 2);
	render_beams = *reinterpret_cast<i_view_render_beams**>((utilities::pattern_scan(CLIENT_DLL, sig_render_beams) + 1));

	effects = get_interface<iv_effects, interface_type::index>(ENGINE_DLL, "VEngineEffects001");
	file_system = get_interface<void, interface_type::index>("filesystem_stdio.dll", "VFileSystem017");*/
	//file_system = **(void***)(utilities::pattern_scan(ENGINE_DLL, sig_file_system) + 0x2);

	console::log("[setup] interfaces initialized!\n");

	return true;
}