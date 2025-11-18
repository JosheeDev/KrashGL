#include "game.h"

#include <core/logger/logger.h>
#include <memory/kmemory.h>

#include <core/input/input.h>
#include <core/event/event.h>

#include <math/kmath.h>

// HACK: This should not be available outside the engine.
#include <renderer/frontend/renderer_frontend.h>

void recalculate_view_matrix(game_state* state) {
    if (state->camera_view_dirty) {
        mat4 rotation = mat4_euler_xyz(state->camera_euler.x, state->camera_euler.y, state->camera_euler.z);
        mat4 translation = mat4_translation(state->camera_position);

        state->view = mat4_mul(rotation, translation);
        state->view = mat4_inverse(state->view);

        state->camera_view_dirty = false;
    }
}

void camera_yaw(game_state* state, f32 amount) {
    state->camera_euler.y += amount;
    state->camera_view_dirty = true;
}

void camera_pitch(game_state* state, f32 amount) {
    state->camera_euler.x += amount;

    // Clamp to avoid Gimball lock.
    f32 limit = deg_to_rad(89.0f);
    state->camera_euler.x = KCLAMP(state->camera_euler.x, -limit, limit);

    state->camera_view_dirty = true;
}

b8 game_initialize(game* game_inst) {
    KDEBUG("game_initialize() called!");

    game_state* state = (game_state*)game_inst->state;

    state->camera_position = (vec3){0, 0, 30.0f};
    state->camera_euler = vec3_zero();

    state->view = mat4_translation(state->camera_position);
    state->view = mat4_inverse(state->view);
    state->camera_view_dirty = true;

    return true;
}

b8 game_update(game* game_inst, f32 delta_time) {
    static u64 alloc_count = 0;
    u64 prev_alloc_count = alloc_count;
    alloc_count = get_memory_alloc_count();

    // Debug: print allocation count when M is released.
    if (input_is_key_up('M') && input_was_key_down('M')) {
        KDEBUG("Allocations: %llu (%llu this frame)", alloc_count, alloc_count - prev_alloc_count);
    }
    
    // TODO: temp
    if (input_is_key_up('T') && input_was_key_down('T')) {
        KDEBUG("Swapping texture!");
        event_context context = {};
        event_fire(EVENT_CODE_DEBUG0, game_inst, context);
    }
    // TODO: end temp

    game_state* state = (game_state*)game_inst->state;

    f32 temp_move_speed = 50.0f;
    vec3 velocity = vec3_zero();

    // Forward/backward movement.
    if (input_is_key_down('W')) {
        vec3 forward = mat4_forward(state->view);
        velocity = vec3_add(velocity, forward);
    }
    if (input_is_key_down('S')) {
        vec3 backward = mat4_backward(state->view);
        velocity = vec3_add(velocity, backward);
    }

    // Left/right strafe movement (A/D only).
    if (input_is_key_down('A')) {
        vec3 left = mat4_left(state->view);
        velocity = vec3_add(velocity, left);
    }
    if (input_is_key_down('D')) {
        vec3 right = mat4_right(state->view);
        velocity = vec3_add(velocity, right);
    }

    // Vertical movement.
    if (input_is_key_down(KEY_SPACE)) {
        velocity.y += 1.0f;
    }
    if (input_is_key_down(KEY_LSHIFT)) {
        velocity.y -= 1.0f;
    }

    // Camera rotation with arrow keys.
    if (input_is_key_down(KEY_LEFT)) {
        camera_yaw(state, 1.0f * delta_time);
    }
    if (input_is_key_down(KEY_RIGHT)) {
        camera_yaw(state, -1.0f * delta_time);
    }
    if (input_is_key_down(KEY_UP)) {
        camera_pitch(state, 1.0f * delta_time);
    }
    if (input_is_key_down(KEY_DOWN)) {
        camera_pitch(state, -1.0f * delta_time);
    }

    // Apply velocity if non-zero.
    vec3 z = vec3_zero();
    if (!vec3_compare(z, velocity, 0.0002f)) {
        // Normalize before applying speed.
        vec3_normalize(&velocity);
        state->camera_position.x += velocity.x * temp_move_speed * delta_time;
        state->camera_position.y += velocity.y * temp_move_speed * delta_time;
        state->camera_position.z += velocity.z * temp_move_speed * delta_time;
        state->camera_view_dirty = true;
    }

    recalculate_view_matrix(state);

    // HACK: This should not be available outside the engine.
    renderer_set_view(state->view, state->camera_position);

    // TODO: temp
    if (input_is_key_up('P') && input_was_key_down('P')) {
        KDEBUG(
            "Pos:[%.2f, %.2f, %.2f]",
            state->camera_position.x,
            state->camera_position.y,
            state->camera_position.z);
    }
    // TODO: end temp

    return true;
}

b8 game_render(game* game_inst, f32 delta_time) {
    return true;
}

void game_on_resize(game* game_inst, u32 width, u32 height) {
}