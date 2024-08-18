@echo off
REM Building test.exe using malloc.dll and arena.dll
gcc -o test.exe test.c -L. -larena -lmalloc
if %ERRORLEVEL% neq 0 (
    echo Error compiling test.exe
    exit /b %ERRORLEVEL%
)

echo Test program compiled successfully!
