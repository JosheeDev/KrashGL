/**
 * @file (mesh.h)
 * @author JosheeDev
 * @copyright KrashGL Game Library (c) JosheeDev
 */

#pragma once

#include "resources/types/resource_types.h"

b8 mesh_load_from_resource(const char* resource_name, mesh* out_mesh);

void mesh_unload(mesh* m);
