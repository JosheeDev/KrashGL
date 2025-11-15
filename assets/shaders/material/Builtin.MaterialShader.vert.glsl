#version 450
#extension GL_ARB_separate_shader_objects : enable

// Vertex input attributes
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texcoord;

// Global uniform buffer (projection + view)
layout(set = 0, binding = 0) uniform global_uniform_object {
    mat4 projection;
    mat4 view;
} global_ubo;

// Push constants (model matrix)
layout(push_constant) uniform push_constants {
    // Only guaranteed a total of 128 bytes.
    mat4 model; // 64 bytes
} u_push_constants;

// Data Transfer Object (passed to fragment shader)
layout(location = 1) out struct dto {
    vec2 tex_coord;
} out_dto;

void main() {
    // Pass texture coordinates to fragment shader
    out_dto.tex_coord = in_texcoord;

    // Compute final clip-space position
    gl_Position = global_ubo.projection * global_ubo.view * u_push_constants.model * vec4(in_position, 1.0);
}