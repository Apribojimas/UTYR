@echo off
cd HARDLOCK
call makeall %1 %2 %3
cd ..
cd GRAPH.386
call makeall.bat %1 %2 %3
cd ..
cd MM.386
call makeall.bat %1 %2 %3
cd ..
cd FILL
call makeall.bat %1 %2 %3
cd ..
cd HBLIB
call makeall.bat %1 %2 %3
cd ..
cd EVENT
call makeall.bat %1 %2 %3
cd ..
cd BAG
call makeall.bat %1 %2 %3
cd ..
cd HD_ERROR
call makeall.bat %1 %2 %3
cd ..