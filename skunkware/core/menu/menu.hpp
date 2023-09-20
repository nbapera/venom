#pragma once
#include "../../dependencies/interfaces/interfaces.hpp"
#include "../../hooks.hpp"
#include "font/font.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"

enum text_alignment { k_left, k_center, k_right };

inline IDirect3DStateBlock9* state_block;


struct mouse_info
{
	bool _click = false;
	bool _dragging = false;
	int drag_x = 0;
	int drag_y = 0;

	POINT pos;

};

inline mouse_info g_mouse;

class c_menu {
public:

	float main_color[3] = { 222.f, 52.f, 255.f };

	void render(IDirect3DDevice9* device);
	void unload();


	bool is_open = true;

	int menu_x = 500;
	int menu_y = 500;

	int width = 800;
	int height = 650;

	int tab_combat = 0;
};

inline c_menu menu;