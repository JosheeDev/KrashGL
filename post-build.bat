@echo off

echo "Compiling shaders..."

echo "assets/shaders/material/Builtin.MaterialShader.vert.glsl -> assets/shaders/material/Builtin.MaterialShader.vert.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/material/Builtin.MaterialShader.vert.glsl -o assets/shaders/material/Builtin.MaterialShader.vert.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "assets/shaders/material/Builtin.MaterialShader.frag.glsl -> assets/shaders/material/Builtin.MaterialShader.frag.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/material/Builtin.MaterialShader.frag.glsl -o assets/shaders/material/Builtin.MaterialShader.frag.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "assets/shaders/ui/Builtin.UIShader.vert.glsl -> assets/shaders/ui/Builtin.UIShader.vert.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/ui/Builtin.UIShader.vert.glsl -o assets/shaders/ui/Builtin.UIShader.vert.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "assets/shaders/ui/Builtin.UIShader.frag.glsl -> assets/shaders/ui/Builtin.UIShader.frag.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/ui/Builtin.UIShader.frag.glsl -o assets/shaders/ui/Builtin.UIShader.frag.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "Done."