@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if not exist build mkdir build
set /p NAME=exe name :
cd /d "%~dp0"
cl /EHsc /std:c++17 /O2 /DNDEBUG /MD Thread.cpp MultiThreading.cpp /Fe:build\%NAME%.exe /Fo:build\
build\%NAME%.exe > build\%NAME%.log 2>&1