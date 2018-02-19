@echo off
vtime >timetest
cd lib
call makeall no 
cd ..
call c.bat
vtime >>timetest
