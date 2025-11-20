/**
 * @file (loader_utils.h)
 * @author JosheeDev
 * @copyright KrashGL Game Library (c) JosheeDev
 */

#pragma once

#include "core/defines.h"
#include "memory/kmemory.h"
#include "resources/types/resource_types.h"

struct resource_loader;

b8 resource_unload(struct resource_loader* self, resource* resource, memory_tag tag);
