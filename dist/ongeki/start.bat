@echo off

pushd %~dp0

start /min inject -d -k estella.dll amdaemon.exe -f -c config_common.json config_server.json config_client.json
inject -d -k estella.dll mu3.exe -nolog
taskkill /f /im amdaemon.exe > nul 2>&1

echo.
echo Game processes have terminated
pause