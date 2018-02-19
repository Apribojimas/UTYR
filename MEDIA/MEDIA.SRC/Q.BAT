@echo off
del timetest > nul
del media.dsk > nul
del *.sym > nul
del media.cfg > nul
del media.mak > nul
del *.swp > nul
del backup.msg

cd obj
del *.obj > nul
del media.exe > nul
cd ..