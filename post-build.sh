#!/bin/bash

# Run from root directory!
mkdir -p bin/assets
mkdir -p bin/assets/shaders

mkdir -p bin/assets/shaders/material

echo "Compiling shaders..."

echo "assets/shaders/material/Builtin.MaterialShader.vert.glsl -> bin/assets/shaders/material/Builtin.MaterialShader.vert.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=vert assets/shaders/material/Builtin.MaterialShader.vert.glsl -o bin/assets/shaders/material/Builtin.MaterialShader.vert.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "assets/shaders/material/Builtin.MaterialShader.frag.glsl -> bin/assets/shaders/material/Builtin.MaterialShader.frag.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=frag assets/shaders/material/Builtin.MaterialShader.frag.glsl -o bin/assets/shaders/material/Builtin.MaterialShader.frag.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "Copying assets..."
echo cp -R "assets" "bin"
cp -R "assets" "bin"

echo "Done."