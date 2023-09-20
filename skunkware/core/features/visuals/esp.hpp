#pragma once
#include "../../../source-sdk/classes/entities.hpp"

namespace esp {

	static inline std::array< float, 64 > alpha;

	struct box {
		int x, y, w, h;
		box() = default;
		box(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	static inline bool get_box(entity_t* entity, box& box) {
		matrix_t& tran_frame = entity->coord_frame();


		const vec3_t min = entity->mins();
		const vec3_t max = entity->maxs();

		vec3_t screen_boxes[8];

		vec3_t points[] = {
			vec3_t(min.x, min.y, min.z),
			vec3_t(min.x, max.y, min.z),
			vec3_t(max.x, max.y, min.z),
			vec3_t(max.x, min.y, min.z),
			vec3_t(max.x, max.y, max.z),
			vec3_t(min.x, max.y, max.z),
			vec3_t(min.x, min.y, max.z),
			vec3_t(max.x, min.y, max.z)
		};

		for (int i = 0; i <= 7; i++)
			if (!math::world_to_screen(math::vector_transform(points[i], tran_frame), screen_boxes[i]))
				return false;

		vec3_t box_array[] = {
			screen_boxes[3], // fl
			screen_boxes[5], // br
			screen_boxes[0], // bl
			screen_boxes[4], // fr
			screen_boxes[2], // fr
			screen_boxes[1], // br
			screen_boxes[6], // bl
			screen_boxes[7] // fl
		};

		float left = screen_boxes[3].x, bottom = screen_boxes[3].y, right = screen_boxes[3].x, top = screen_boxes[3].y;

		for (int i = 0; i <= 7; i++) {
			if (left > box_array[i].x)
				left = box_array[i].x;

			if (bottom < box_array[i].y)
				bottom = box_array[i].y;

			if (right < box_array[i].x)
				right = box_array[i].x;

			if (top > box_array[i].y)
				top = box_array[i].y;
		}

		box.x = static_cast<int>(left);
		box.y = static_cast<int>(top);
		box.w = static_cast<int>(right) - static_cast<int>(left);
		box.h = static_cast<int>(bottom) - static_cast<int>(top);

		return true;
	}

	void aspect_ratio();
	void nightmode();

	void player_weapon(player_t* entity, box bbox);
	void skeleton(player_t* entity);
	void player_box(player_t* entity);

	void run();
}