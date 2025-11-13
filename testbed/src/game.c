#include "game.h"

#include <core/logger/logger.h>
#include <memory/kmemory.h>

#include <core/input/input.h>

b8 game_initialize(game* game_inst) {
    KDEBUG("game_initialize() called!");
    return true;
}

b8 game_update(game* game_inst, f32 delta_time) {
    static u64 alloc_count = 0;
    u64 prev_alloc_count = alloc_count;
    alloc_count = get_memory_alloc_count();
    if (input_is_key_up('O') && input_was_key_down('O')) {
        KDEBUG("Allocations: %llu (%llu this frame)", alloc_count, alloc_count - prev_alloc_count);
    }

    return true;
}

b8 game_render(game* game_inst, f32 delta_time) {
    return true;
}

void game_on_resize(game* game_inst, u32 width, u32 height) {
}