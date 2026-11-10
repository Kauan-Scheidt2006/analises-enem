@echo off
setlocal

set "CMAKE=C:\Qt\Tools\CMake_64\bin\cmake.exe"
set "CONFIGURACAO=%~1"

if not defined CONFIGURACAO set "CONFIGURACAO=debug"

call "%~dp0configurar.bat" "%CONFIGURACAO%"
if errorlevel 1 exit /b %ERRORLEVEL%

pushd "%~dp0"
"%CMAKE%" --build --preset "windows-%CONFIGURACAO%"
set "RESULTADO=%ERRORLEVEL%"
popd

exit /b %RESULTADO%
