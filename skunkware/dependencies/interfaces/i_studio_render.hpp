#pragma once
#include "../../source-sdk/structs/materials.hpp"
#include "../utilities/utilities.hpp"


class i_studio_render
{
public:
	enum
	{
		STUDIORENDER_DRAW_ENTIRE_MODEL = 0,
		STUDIORENDER_DRAW_OPAQUE_ONLY = 0x01,
		STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
		STUDIORENDER_DRAW_GROUP_MASK = 0x03,
		STUDIORENDER_DRAW_NO_FLEXES = 0x04,
		STUDIORENDER_DRAW_STATIC_LIGHTING = 0x08,
		STUDIORENDER_DRAW_ACCURATETIME = 0x10,
		STUDIORENDER_DRAW_NO_SHADOWS = 0x20,
		STUDIORENDER_DRAW_GET_PERF_STATS = 0x40,
		STUDIORENDER_DRAW_WIREFRAME = 0x80,
		STUDIORENDER_DRAW_ITEM_BLINK = 0x100,
		STUDIORENDER_SHADOWDEPTHTEXTURE = 0x200,
		STUDIORENDER_UNUSED = 0x400,
		STUDIORENDER_SKIP_DECALS = 0x800,
		STUDIORENDER_MODEL_IS_CACHEABLE = 0x1000,
		STUDIORENDER_SHADOWDEPTHTEXTURE_INCLUDE_TRANSLUCENT_MATERIALS = 0x2000,
		STUDIORENDER_NO_PRIMARY_DRAW = 0x4000,
		STUDIORENDER_SSAODEPTHTEXTURE = 0x8000,
	};

	enum EOverrideType : int
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_SELECTIVE,
		OVERRIDE_SSAO_DEPTH_WRITE,
	};

	void set_color_modulation(const float* color) noexcept
	{
		return utilities::call_virtual< void(__thiscall*)(decltype(this), const float*) >(this, 27)(this, color);
	}

	void set_alpha_modulation(const float alpha) noexcept
	{
		return utilities::call_virtual< void(__thiscall*)(decltype(this), const float) >(this, 28)(this, alpha);
	}

	void forced_material_override(i_material* material, const int  type = OVERRIDE_NORMAL, const int  index = -1) noexcept
	{
		return utilities::call_virtual< void(__thiscall*)(decltype(this), i_material*, const int, const int) >(this, 33)(this, material, type, index);
	}

	bool is_forced_material_override() noexcept
	{
		return utilities::call_virtual< bool(__thiscall*)(decltype(this)) >(this, 34)(this);
	}
};