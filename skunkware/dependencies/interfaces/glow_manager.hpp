#pragma once
#include "../../source-sdk/math/vector3d.hpp"

/*class glow_object_definition_t {
public:
	void set(float r, float g, float b, float a) {
		color = vec3_t(r, g, b);
		alpha = a;
		render_when_occluded = true;
		render_when_unoccluded = false;
		bloom_amount = 1.0f;
	}
	bool unused() {
		return next_free_slot != -2;
	}

	void* entity;
	vec3_t color;
	float alpha;
	char unknown0[8];
	float bloom_amount;
	char unknown1[4];
	bool render_when_occluded;
	bool render_when_unoccluded;
	bool full_bloom_render;
	char unknown2[13];
	int next_free_slot;
};*/

class glow_object_definition_t
{
public:
    int nextFreeSlot;
    player_t* entity;

    struct
    {
        float r;
        float g;
        float b;
        float a;
    }color;

    bool glowAlphaCappedByRenderAlpha;
    float glowAlphaFunctionOfMaxVelocity;
    float glowAlphaMax;
    float glowPulseOverdrive;

    bool renderWhenOccluded;
    bool renderWhenUnoccluded;

    bool fullBloomRender;
    int fullBloomStencilTestValue;
    int glowStyle;
    int splitScreenSlot;

    static constexpr int END_OF_FREE_LIST = -1;
    static constexpr int ENTRY_IN_USE = -2;

    constexpr bool unused() const noexcept
    {
        return nextFreeSlot != ENTRY_IN_USE;
    }

    // helper function to set the glow color
    constexpr void set(float r, float g, float b, float a = 1.f) noexcept
    {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;

        renderWhenOccluded = true;
        renderWhenUnoccluded = false;
    }
};

class glow_manager_t {
public:
	glow_object_definition_t* objects;
	char pad[8];
	int size;
};
