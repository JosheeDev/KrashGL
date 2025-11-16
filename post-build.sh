#!/bin/bash

echo "Compiling shaders..."

echo "assets/shaders/material/Builtin.MaterialShader.vert.glsl -> assets/shaders/material/Builtin.MaterialShader.vert.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=vert assets/shaders/material/Builtin.MaterialShader.vert.glsl -o assets/shaders/material/Builtin.MaterialShader.vert.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "assets/shaders/material/Builtin.MaterialShader.frag.glsl -> assets/shaders/material/Builtin.MaterialShader.frag.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=frag assets/shaders/material/Builtin.MaterialShader.frag.glsl -o assets/shaders/material/Builtin.MaterialShader.frag.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "Done."