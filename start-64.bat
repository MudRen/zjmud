@echo off
title ����
echo ���������ػ�����...
:1
tasklist /nh|find /i "tangmen.exe">nul
if ERRORLEVEL 1 (
echo ��������...
fluffos64\tangmen.exe config.ini
)
ping 127.0.0.1 -n 10>nul
goto 1
