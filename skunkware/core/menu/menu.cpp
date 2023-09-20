#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>

#include "menu.hpp"
#include "font/font.hpp"
#include <math.h>
#include "byte_array.hpp"
#include "etc_elements.hpp"
#include "nav_elements.hpp"

#include "../config/config.hpp"

static bool init = false;
int tab = 0;
int subtab = 0;

ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;


const char* combo_items[3] = { "Value", "Value 1", "Value 2" };
static int sliderscalar, c_combo = 0;

enum heads {
	legit, visuals, antiaim, settings, skins, configs, scripts
};

enum sub_heads {
	general, accuracy, exploits, _general, advanced
};



void c_menu::render(IDirect3DDevice9* device) {
	if (!init) {
		init = true;


		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImFontConfig font_config;
		font_config.PixelSnapH = false;
		font_config.OversampleH = 5;
		font_config.OversampleV = 5;
		font_config.RasterizerMultiply = 1.2f;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0xE000, 0xE226, // icons
			0,
		};

		font_config.GlyphRanges = ranges;

		medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 15.0f, &font_config, ranges);
		bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

		tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 15.0f, &font_config, ranges);
		logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 21.0f, &font_config, ranges);

		tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 19.0f, &font_config, ranges);
		tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

		subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

		combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

		//io.IniFilename = NULL;
		ImGui_ImplWin32_Init(hooks::window);
		ImGui_ImplDX9_Init(device);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (menu.is_open) {
		const char* tab_name = tab == legit ? "Legitbot" : tab == antiaim ? "Anti-aim" : tab == visuals ? "Visuals" : tab == settings ? "Misc" : tab == skins ? "Skins" : tab == configs ? "Configs" : tab == scripts ? "Scripts" : 0;
		const char* tab_icon = tab == legit ? "B" : tab == antiaim ? "C" : tab == visuals ? "D" : tab == settings ? "E" : tab == skins ? "F" : tab == configs ? "G" : tab == scripts ? "H" : 0;
		ImGui::SetNextWindowSize({ 730, 460 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

		ImGui::Begin("hi world", nullptr, ImGuiWindowFlags_NoDecoration); {
			auto draw = ImGui::GetWindowDrawList();

			auto pos = ImGui::GetWindowPos();
			auto size = ImGui::GetWindowSize();

			ImGuiStyle style = ImGui::GetStyle();

			draw->AddRectFilled(pos, ImVec2(pos.x + 210, pos.y + size.y), ImColor(24, 24, 26), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
			draw->AddLine(ImVec2(pos.x + 210, pos.y + 2), ImVec2(pos.x + 210, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddLine(ImVec2(pos.x + 47, pos.y + 2), ImVec2(pos.x + 47, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddLine(ImVec2(pos.x + 2, pos.y + 47), ImVec2(pos.x + 47, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddLine(ImVec2(pos.x + 63, pos.y + 47), ImVec2(pos.x + 195, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddText(logo, 21.0f, ImVec2(pos.x + 14, pos.y + 12), ImColor(158, 0, 207), "A");

			draw->AddText(tab_title_icon, 18.0f, ImVec2(pos.x + 65, pos.y + 14), ImColor(158, 0, 207), tab_icon);
			draw->AddText(tab_title, 19.0f, ImVec2(pos.x + 93, pos.y + 15), ImColor(1.0f, 1.0f, 1.0f), tab_name);

			draw->AddRect(ImVec2(pos.x + 1, pos.y + 1), ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImColor(1.0f, 1.0f, 1.0f, 0.03f), style.WindowRounding);
			ImGui::SetCursorPos({ 8, 56 });
			ImGui::BeginGroup(); {
				if (elements::tab("B", tab == legit)) { tab = legit; }
				if (elements::tab("C", tab == antiaim)) { tab = antiaim; }
				if (elements::tab("D", tab == visuals)) { tab = visuals; }
				if (elements::tab("E", tab == settings)) { tab = settings; }
				if (elements::tab("F", tab == skins)) { tab = skins; }
				if (elements::tab("G", tab == configs)) { tab = configs; }
				if (elements::tab("H", tab == scripts)) { tab = scripts; }
			} ImGui::EndGroup();

			switch (tab) {
			case legit:
				draw->AddText(subtab_title, 15.0f, ImVec2(pos.x + 72, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.4f), "MAIN");

				ImGui::SetCursorPos({ 57, 86 });
				ImGui::BeginGroup(); {
					if (elements::subtab("General", subtab == general)) { subtab = general; }
					if (elements::subtab("Accuracy", subtab == accuracy)) { subtab = accuracy; }
					if (elements::subtab("Exploits", subtab == exploits)) { subtab = exploits; }
				} ImGui::EndGroup();

				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("General", ImVec2(240, 430)); {
					ImGui::Checkbox("Legit Aim", &config::legit::aim);
					ImGui::SliderInt("Smoothing", &config::legit::smoothing, 0, 10);
					ImGui::SliderInt("FOV", &config::legit::fov, 10, 180);
				}
				e_elements::end_child();
				break;

			case antiaim:
				break;
			case visuals:

				draw->AddText(subtab_title, 15.0f, ImVec2(pos.x + 72, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.4f), "MAIN");

				ImGui::SetCursorPos({ 57, 86 });
				ImGui::BeginGroup(); {
					if (elements::subtab("ESP & Chams", subtab == general)) { subtab = general; }
					if (elements::subtab("Other", subtab == accuracy)) { subtab = accuracy; }
				} ImGui::EndGroup();

				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("ESP", ImVec2(240, 430)); {

					ImGui::Checkbox("Enabled", &config::esp::enabled);
					ImGui::Checkbox("Box", &config::esp::player_box);
					ImGui::Checkbox("Weapon ESP", &config::esp::player_weapon);
					ImGui::ColorEdit3("Weapon Color", config::esp::player_weapon_clr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB);
					ImGui::Checkbox("Draw Skeleton", &config::esp::skeleton);
					//glow
					ImGui::Checkbox("Glow", &config::esp::glow);
					ImGui::Checkbox("Player Glow", &config::esp::player_glow);
					ImGui::ColorEdit4("Player Glow Color", config::esp::player_glow_clr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB);
					ImGui::Checkbox("Weapon Glow", &config::esp::weapon_glow);
					ImGui::ColorEdit4("Weapon Glow Color", config::esp::weapon_glow_clr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB);
					//visuals
					ImGui::SliderFloat("Aspect Ratio", &config::esp::aspect_ratio, 0, 5);
					ImGui::SliderInt("Viewmodel FOV", &config::esp::viewmodel_fov, 0, 150);
					ImGui::SliderInt("Override FOV", &config::esp::override_fov, 90, 150);
					
				}
				e_elements::end_child();
				ImGui::SetCursorPos({ 476, 16 });
				e_elements::begin_child("Chams", ImVec2(240, 430)); {
					ImGui::Checkbox("Chams", &config::chams);
					ImGui::ColorEdit3("Chams Color", config::chams_clr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB);
					ImGui::ColorEdit3("Chams Color (Behind the wall)", config::chams_clr_hidden, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB);
				}
				e_elements::end_child();
				break;

			case settings:
				draw->AddText(subtab_title, 15.0f, ImVec2(pos.x + 72, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.4f), "MAIN");

				ImGui::SetCursorPos({ 57, 86 });
				ImGui::BeginGroup(); {
					if (elements::subtab("General", subtab == general)) { subtab = general; }
					if (elements::subtab("Other", subtab == accuracy)) { subtab = accuracy; }
				} ImGui::EndGroup();

				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("Misc", ImVec2(240, 430)); {

					ImGui::Checkbox("Bhop", &config::bhop);
					ImGui::Checkbox("No Crouch Cooldown (Risky)", &config::ncc);
					ImGui::Checkbox("Moonwalk", &config::moonwalk);
					ImGui::Checkbox("Rank Reveal", &config::moonwalk);
					//ImGui::Combo("Combobox", &c_combo, combo_items, IM_ARRAYSIZE(combo_items));
				}
				e_elements::end_child();
				break;

			}


		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


void c_menu::unload() {
	interfaces::inputsystem->enable_input(true);
}

/*void c_menu::render(IDirect3DDevice9* device) {

	if (!init) {
		init = true;
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		//font = io.Fonts->AddFontFromMemoryCompressedTTF(source_sans_pro_regular_compressed_data, source_sans_pro_regular_compressed_size, 16);
		topbar_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 20);
		font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 17);
		icons = io.Fonts->AddFontFromMemoryTTF(font_awesome, sizeof(font_awesome), 30);
		io.IniFilename = NULL;
		ImGui_ImplWin32_Init(hooks::window);
		ImGui_ImplDX9_Init(device);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	menu.theme();

	if (menu.is_open) {
		ImGui::SetNextWindowSize(ImVec2(menu.width, menu.height), ImGuiCond_FirstUseEver);
		ImGui::Begin("ok", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		menu.sidebar();

		switch (tab) {
		case 0:
			menu.combat_topbar();
		}

		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
}

void c_menu::theme() {
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowMinSize = ImVec2(menu.width, menu.height);

	style->WindowPadding = ImVec2(0, 0);
	style->FramePadding = ImVec2(0, 0);

	style->Colors[ImGuiCol_FrameBg] = ImColor(19, 17, 17);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(19, 17, 17);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(19, 17, 17);

	style->Colors[ImGuiCol_ChildBg] = ImColor(23, 23, 23);

	style->Colors[ImGuiCol_Button] = ImColor(255, 0, 0, 0);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(255, 0, 0, 0);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(255, 0, 0, 0);

	style->Colors[ImGuiCol_CheckMark] = ImColor(menu.main_color[0], menu.main_color[1], menu.main_color[2]);

}


void c_menu::sidebar() {
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y));
	ImGui::BeginChild("sidebar", ImVec2(100, ImGui::GetWindowSize().y));
	

	ImGui::Button("C", ImVec2(100, 70));
	ImGui::Button("V", ImVec2(100, 70));
	ImGui::Button("M", ImVec2(100, 70));
	ImGui::Button("S", ImVec2(100, 70));
	ImGui::Button("CH", ImVec2(100, 70));


	ImGui::EndChild();
}

void c_menu::combat_topbar() {

	//ImGui::PushFont(topbar_font);

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 100, ImGui::GetWindowPos().y));
	ImGui::BeginChild("topbar", ImVec2(ImGui::GetWindowSize().x - 100, 60));

	if (menu.tab_combat == 0) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ menu.main_color[0] / 255, menu.main_color[1] / 255, menu.main_color[2] / 255, 1.0f});
		ImGui::Button("Rage", ImVec2(166, 60));
		ImGui::PopStyleColor();
	}
	else
		if (ImGui::Button("Rage", ImVec2(166, 60)))
			menu.tab_combat = 0;

	ImGui::SameLine();
	if (menu.tab_combat == 1) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.87f, 0.20f, 1.00f, 1.0f });
		ImGui::Button("Legit", ImVec2(166, 60));
		ImGui::PopStyleColor();
	}
	else
		if (ImGui::Button("Legit", ImVec2(166, 60)))
			menu.tab_combat = 1;

	ImGui::SameLine();
	if (menu.tab_combat == 2) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.87f, 0.20f, 1.00f, 1.0f });
		ImGui::Button("Trigger", ImVec2(166, 60));
		ImGui::PopStyleColor();
	}
	else
		if (ImGui::Button("Trigger", ImVec2(166, 60)))
			menu.tab_combat = 2;

	ImGui::SameLine();
	if (menu.tab_combat == 3) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.87f, 0.20f, 1.00f, 1.0f });
		ImGui::Button("Anti-Aim", ImVec2(166, 60));
		ImGui::PopStyleColor();
	}
	else
		if (ImGui::Button("Anti-Aim", ImVec2(166, 60)))
			menu.tab_combat = 3;

	ImGui::EndChild();

	if (menu.tab_combat == 0) {
		menu.rage();
	}

	if (menu.tab_combat == 1) {
		menu.legit();
	}

	if (menu.tab_combat == 2) {
		menu.trigger();
	}

	if (menu.tab_combat == 3) {
		menu.antiaim();
	}

	ImGui::PopFont();

}

void c_menu::rage() {
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("rage_tab", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));

	//ImGui::PushFont(font);

	menu.checkbox("Enabled", &config::rage::enabled, ImVec2(10, 10));
	ImGui::NewLine();
	ImGui::NewLine();
	menu.checkbox("Autowall", &config::rage::autowall, ImVec2(10, 10));
	ImGui::NewLine();
	ImGui::NewLine();
	menu.checkbox("Aimbot", &config::rage::aim, ImVec2(10, 10));
	ImGui::NewLine();
	ImGui::NewLine();

	ImGui::PopFont();

	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120 + 40 + ImGui::GetWindowSize().x / 2 - 100, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("rage_tab2", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();

}

void c_menu::legit() {
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("legit_tab", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120 + 40 + ImGui::GetWindowSize().x / 2 - 100, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("legit_tab2", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();
}

void c_menu::trigger() {
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("trigger_tab", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120 + 40 + ImGui::GetWindowSize().x / 2 - 100, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("trigger_tab2", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();
}

void c_menu::antiaim() {
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("antiaim_tab", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + 120 + 40 + ImGui::GetWindowSize().x / 2 - 100, ImGui::GetWindowPos().y + 75));
	ImGui::BeginChild("antiaim_tab2", ImVec2(ImGui::GetWindowSize().x / 2 - 80, ImGui::GetWindowSize().y - 90));
	ImGui::EndChild();
}

void c_menu::checkbox(const char* label, bool* v, ImVec2 padding) {
	ImVec2 cursor = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(padding.x + cursor.x, padding.y + cursor.y));
	ImGui::Checkbox(label, v);
	ImGui::SetCursorPos(cursor);
}*/