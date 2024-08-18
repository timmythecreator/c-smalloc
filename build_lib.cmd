@echo off
REM Building malloc.dll
gcc -shared -o malloc.dll malloc.c -D_SMALLOC_EXPORTS
if %ERRORLEVEL% neq 0 (
    echo Error compiling malloc.dll
    exit /b %ERRORLEVEL%
)

REM Building arena.dll with linking to malloc.dll
gcc -shared -o arena.dll arena.c -D_ARENA_EXPORTS -L. -lmalloc
if %ERRORLEVEL% neq 0 (
    echo Error compiling arena.dll
    exit /b %ERRORLEVEL%
)

echo Libraries compiled successfully!