@echo off
title 唐门
echo 启动唐门守护程序...
:1
tasklist /nh|find /i "tangmen.exe">nul
if ERRORLEVEL 1 (
echo 启动唐门...
fluffos64\tangmen.exe config.ini
)
ping 127.0.0.1 -n 10>nul
goto 1
