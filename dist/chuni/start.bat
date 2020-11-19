@echo off

pushd %~dp0

start /min inject -d -k estella.dll aimeReaderHost.exe -p 12
inject -d -k estella.dll chuniApp.exe
taskkill /f /im aimeReaderHost.exe > nul 2>&1

echo.
echo Game processes have terminated
pause