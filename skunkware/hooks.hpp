#pragma once

#include "source-sdk/classes/c_usercmd.hpp"
#include "dependencies/utilities/csgo.hpp"

namespace hooks {

	bool initialize();
	void release();

	inline WNDPROC wndproc_original;
	inline HWND window;
	LRESULT __stdcall wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __stdcall hook(float input_sample_frametime, c_usercmd* cmd);
	};

	namespace get_screen_aspect_ratio {
		using fn = float(__fastcall*)(void*, void*, int32_t, int32_t);
		float __fastcall hook(void* edx, void* edb, int32_t width, int32_t height);
	}

	namespace draw_model_execute {
		using fn = void(__thiscall*)(iv_model_render*, i_mat_render_context*, const draw_model_state_t&, const model_render_info_t&, matrix_t*);
		static void __stdcall hook(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* bone_to_world);
	}

	namespace end_scene {
		using fn = long(__stdcall*)(IDirect3DDevice9*);
		long __stdcall hook(IDirect3DDevice9* device);
	}

	namespace lock_cursor {
		using fn = void(__thiscall*)(void*);
		void __stdcall hook();
	}

	namespace frame_stage_notify {
		using fn = void(__thiscall*)(i_base_client_dll*, int);
		void __stdcall hook(int frame_stage);
	}

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		static void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace do_post_screen_effects {
		using fn = int(__thiscall*)(void*, int);
		static int __stdcall hook(int value);
	};

	namespace get_view_model_fov {
		using fn = float(__fastcall*)(void*, int);
		static float __fastcall hook(int edx);
	}

	namespace override_view {
		using fn = bool(__fastcall*)(uintptr_t ecx, uintptr_t edx, view_setup_t* setup);
		static bool __fastcall hook(uintptr_t ecx, uintptr_t edx, view_setup_t* setup);
	}

	/*namespace game_events {
		using fn = bool(__thiscall*)(i_game_event_manager2*, i_game_event*);
		bool __stdcall hook(i_game_event* event);
	}



	*/

}