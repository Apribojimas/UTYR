@echo off
arj u archive.arj obj\*.lib
arj u -r archive.arj lib\*.*
arj u archive.arj hpp\*.hpp hpp\*.h
arj u archive.arj *.cpp *.hpp *.prj *.bat
arj u archive.arj good\*.*
