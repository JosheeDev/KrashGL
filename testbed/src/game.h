/**
 * @file (game.h)
 * @author JosheeDev
 * @copyright KrashGL Game Library (c) JosheeDev
 */

#pragma once

#include <core/defines.h>
#include <game/types/game_types.h>
#include <math/types/math_types.h>

typedef struct game_state {
    f32 delta_time;
    mat4 view;
    vec3 camera_position;
    vec3 camera_euler;
    b8 camera_view_dirty;
} game_state;

b8 game_initialize(game* game_inst);

b8 game_update(game* game_inst, f32 delta_time);

b8 game_render(game* game_inst, f32 delta_time);

void game_on_resize(game* game_inst, u32 width, u32 height);
