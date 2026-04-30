@echo off
if not defined VSCMD_VER (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
)
if not exist build mkdir build
set /p NAME=exe name :
cd /d "%~dp0"
nvcc -O2 -std=c++17 -Xcompiler "/wd4819" DeviceQuery.cu -o build\%NAME%.exe > build\%NAME%.log 2>&1
if errorlevel 1 (
    echo Build failed. See build\%NAME%.log
    exit /b 1
)
build\%NAME%.exe >> build\%NAME%.log 2>&1