@echo off

if NOT EXIST *.lib goto NO_LIB
 del *.lib                          >nul
:NO_LIB

arj e -y -u archive

IF "%1"=="DEBUG" GOTO DEBUG
IF "%2"=="DEBUG" GOTO DEBUG
IF "%3"=="DEBUG" GOTO DEBUG
IF "%1"=="debug" GOTO DEBUG
IF "%2"=="debug" GOTO DEBUG
IF "%3"=="debug" GOTO DEBUG
 bcc -ml -c  *.cpp *.asm  >to_obj
 tdstrip *.obj
 GOTO NODEBUG
:DEBUG
 bcc -ml -c -v -y  *.cpp *.asm  >to_obj
:NODEBUG

..\makelib.exe mm.lib        >>TO_OBJ
call lib.bat
del *.obj
del *.bak

if "%1"=="NO" goto NOVIEW
if "%2"=="NO" goto NOVIEW
if "%3"=="NO" goto NOVIEW
if "%1"=="no" goto NOVIEW
if "%2"=="no" goto NOVIEW
if "%3"=="no" goto NOVIEW
 wpview to_obj
:NOVIEW

del to_obj
del lib.bat

IF "%1"=="DEBUG" GOTO ARC
IF "%2"=="DEBUG" GOTO ARC
IF "%3"=="DEBUG" GOTO ARC
IF "%1"=="debug" GOTO ARC
IF "%2"=="debug" GOTO ARC
IF "%3"=="debug" GOTO ARC
arj m -jm -f archive
GOTO NO_ARC
:ARC
arj a -jm -f archive
:NO_ARC

if "%1"=="NOCOPY" goto NOCOPY
if "%2"=="NOCOPY" goto NOCOPY
if "%3"=="NOCOPY" goto NOCOPY
if "%1"=="nocopy" goto NOCOPY
if "%2"=="nocopy" goto NOCOPY
if "%3"=="nocopy" goto NOCOPY
 copy mm.lib ..\..\OBJ\mm.LIB
 del mm.lib
:NOCOPY
