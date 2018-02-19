@echo off
ncache2 /dump >nul
if "%1" == "/r" goto clear
if "%2" == "/r" goto clear
if "%3" == "/r" goto clear
td286 -vp -vg obj\media.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end
:clear
td286 -vp -vg obj\media.exe %1 %2 %3 %4 %5 %6 %7 %8 %9 /t
:end
