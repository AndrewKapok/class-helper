# 设置Qt环境变量
$QTDIR = "C:\Qt\5.15.2\mingw81_64"
$env:PATH = "$QTDIR\bin;$env:PATH"

# 进入Qt项目目录
Set-Location qt_src

# 清理旧的构建文件
if (Test-Path Makefile) {
    Remove-Item Makefile -Force
}
if (Test-Path debug) {
    Remove-Item debug -Recurse -Force
}
if (Test-Path release) {
    Remove-Item release -Recurse -Force
}

# 生成Makefile
Write-Host "生成Makefile..."
qmake seat_allocator.pro

# 编译项目
Write-Host "编译项目..."
mingw32-make

# 检查编译结果
if (Test-Path release\seat_allocator.exe) {
    Write-Host "编译成功！"
    Write-Host "可执行文件位置：qt_src\release\seat_allocator.exe"
} else {
    Write-Host "编译失败！"
    Read-Host "按Enter键继续..."
    exit 1
}

# 复制必要的DLL文件
Write-Host "复制必要的DLL文件..."
if (!(Test-Path release\Qt5Core.dll)) {
    Copy-Item "$QTDIR\bin\Qt5Core.dll" release\
}
if (!(Test-Path release\Qt5Gui.dll)) {
    Copy-Item "$QTDIR\bin\Qt5Gui.dll" release\
}
if (!(Test-Path release\Qt5Widgets.dll)) {
    Copy-Item "$QTDIR\bin\Qt5Widgets.dll" release\
}

# 返回上级目录
Set-Location ..

Write-Host "构建完成！"
Read-Host "按Enter键继续..."
