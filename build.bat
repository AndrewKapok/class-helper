@echo off

REM 设置Qt环境变量
set QTDIR=C:\Qt\5.15.2\mingw81_64
set PATH=%QTDIR%\bin;%PATH%

REM 进入Qt项目目录
cd qt_src

REM 清理旧的构建文件
if exist Makefile del Makefile
if exist debug rd /s /q debug
if exist release rd /s /q release

REM 生成Makefile
qmake seat_allocator.pro

REM 编译项目
mingw32-make

REM 检查编译结果
if exist release\seat_allocator.exe (
    echo 编译成功！
    echo 可执行文件位置：qt_src\release\seat_allocator.exe
) else (
    echo 编译失败！
    pause
    exit /b 1
)

REM 复制必要的DLL文件
if not exist release\Qt5Core.dll copy %QTDIR%\bin\Qt5Core.dll release\
if not exist release\Qt5Gui.dll copy %QTDIR%\bin\Qt5Gui.dll release\
if not exist release\Qt5Widgets.dll copy %QTDIR%\bin\Qt5Widgets.dll release\

REM 返回上级目录
cd ..

echo 构建完成！
pause
