@echo off

REM 进入Qt项目的release目录
cd qt_src\release

REM 运行应用程序
seat_allocator.exe

REM 返回上级目录
cd ..\..
