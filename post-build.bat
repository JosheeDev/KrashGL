@echo off

REM Run from root directory!
if not exist "%cd%\bin\assets\shaders\" mkdir "%cd%\bin\assets\shaders"

if not exist "%cd%\bin\assets\shaders\material" mkdir "%cd%\bin\assets\shaders\material"

echo "Compiling shaders..."

echo "assets/shaders/material/Builtin.MaterialShader.vert.glsl -> bin/assets/shaders/material/Builtin.MaterialShader.vert.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/material/Builtin.MaterialShader.vert.glsl -o bin/assets/shaders/material/Builtin.MaterialShader.vert.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "assets/shaders/material/Builtin.MaterialShader.frag.glsl -> bin/assets/shaders/material/Builtin.MaterialShader.frag.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/material/Builtin.MaterialShader.frag.glsl -o bin/assets/shaders/material/Builtin.MaterialShader.frag.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "Copying assets..."
echo xcopy "assets" "bin\assets" /h /i /c /k /e /r /y
xcopy "assets" "bin\assets" /h /i /c /k /e /r /y

echo "Done."