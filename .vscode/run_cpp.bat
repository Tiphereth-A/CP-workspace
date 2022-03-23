@echo off
Set _fBlack=[30m
Set _bBlack=[40m
Set _fRed=[31m
Set _bRed=[41m
Set _fGreen=[32m
Set _bGreen=[42m
Set _fYellow=[33m
Set _bYellow=[43m
Set _fBlue=[34m
Set _bBlue=[44m
Set _fMag=[35m
Set _bMag=[45m
Set _fCyan=[36m
Set _bCyan=[46m
Set _fLGray=[37m
Set _bLGray=[47m
Set _fDGray=[90m
Set _bDGray=[100m
Set _fBRed=[91m
Set _bBRed=[101m
Set _fBGreen=[92m
Set _bBGreen=[102m
Set _fBYellow=[93m
Set _bBYellow=[103m
Set _fBBlue=[94m
Set _bBBlue=[104m
Set _fBMag=[95m
Set _bBMag=[105m
Set _fBCyan=[96m
Set _bBCyan=[106m
Set _fBWhite=[97m
Set _bBWhite=[107m
Set _RESET=[0m

%CPPBIN_PATH%\c++ -fdiagnostics-color=always "%1\%2.cpp" -o "%1\%2" -DLOCAL_ -O2 -std=c++17 -I "%1\tools\lib-cpp" -I "%1\lib\testlib" -Wall -Wextra -Wconversion -Wpedantic -Wparentheses -Wno-variadic-macros || goto end

echo %_fBGreen%%_bBlack%compile finished%_RESET%

"%1\%2" < "%3\in.in" > "%3\out.out" 2> "%3\err.err"

if not %ERRORLEVEL% == 0 (
    echo %_fBMag%%_bBlack%runtime error%_RESET% with %_fBRed%%_bBlack%%ERRORLEVEL%%_RESET%
    goto end
)

echo %_fBGreen%%_bBlack%fin%_RESET%

del "%1\%2.exe"

:end
