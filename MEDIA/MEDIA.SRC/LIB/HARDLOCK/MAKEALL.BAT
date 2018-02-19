@echo off

if NOT EXIST *.obj goto NO_OBJ
 attrib -R *.obj                    >nul
:NO_OBJ
if NOT EXIST *.lib goto NO_LIB
 del *.lib                          >nul
:NO_LIB

arj e -y -u ARCHIVE.ARJ                   >nul

REM ----------------- TIKRINAM AR REIKIA HARDLOCK'O
bcc -ml hlyn.c                      >nul
del *.obj                           >nul
hlyn.exe
if ERRORLEVEL 1 goto LIB

REM ----------------- ISTRAUKIAM HARDLOK'O *.OBJ
:YRA
arcview hardlock.arj                >nul
if NOT EXIST *.obj goto YRA
for %%f IN (*.obj) DO call tmp.bat %%f
:LIB

REM _________________ DAROM LIB'A
IF "%1"=="DEBUG" GOTO DEBUG
IF "%2"=="DEBUG" GOTO DEBUG
IF "%3"=="DEBUG" GOTO DEBUG
IF "%1"=="debug" GOTO DEBUG
IF "%2"=="debug" GOTO DEBUG
IF "%3"=="debug" GOTO DEBUG
 bcc -ml -c -3 -I..\..\HPP *.cpp       >to_obj
 tdstrip hardlock.obj                  >nul
 GOTO NODEBUG
:DEBUG
 bcc -ml -c -v -y -3 -I..\..\HPP *.cpp >to_obj
:NODEBUG

..\makelib hardlock.lib               >>TO_OBJ
call lib.bat

if "%1"=="NO" goto NOVIEW
if "%2"=="NO" goto NOVIEW
if "%3"=="NO" goto NOVIEW
if "%1"=="no" goto NOVIEW
if "%2"=="no" goto NOVIEW
if "%3"=="no" goto NOVIEW
 wpview to_obj
:NOVIEW

del *.bak                              >nul
del to_obj                             >nul
del lib.bat                            >nul
attrib -R *.obj                        >nul

REM ____________________ DAROME TYRXXXX.EXE ir FCDXXXXX.EXE
hlyn.exe
if ERRORLEVEL 1 goto TYR
bcc -ml -I..\..\HPP -P tyrxxxx.c hardlock.lib  >nul
bcc -ml -I..\..\HPP -P fcode.c hardlock.lib  >nul
call tyrxxxx.bat
del TYRXXXX.*
del FCODE.*
:TYR

del hlyn.exe
del *.obj

arj m -jm -f archive                   >nul

if "%1"=="NOCOPY" goto NOCOPY
if "%2"=="NOCOPY" goto NOCOPY
if "%3"=="NOCOPY" goto NOCOPY
if "%1"=="nocopy" goto NOCOPY
if "%2"=="nocopy" goto NOCOPY
if "%3"=="nocopy" goto NOCOPY
 copy hardlock.lib ..\..\OBJ\hardlock.lib
 del hardlock.lib
:NOCOPY

