@echo off
setlocal

set "CMAKE=C:\Qt\Tools\CMake_64\bin\cmake.exe"
set "NINJA=C:\Qt\Tools\Ninja\ninja.exe"
set "COMPILADOR=C:\Qt\Tools\mingw1310_64\bin\g++.exe"
set "QT=C:\Qt\6.11.1\mingw_64"
set "CONFIGURACAO=%~1"

if not defined CONFIGURACAO set "CONFIGURACAO=debug"

if /I not "%CONFIGURACAO%"=="debug" if /I not "%CONFIGURACAO%"=="release" (
    echo ERRO: Configuracao invalida: %CONFIGURACAO%
    echo Uso: configurar.bat [debug^|release]
    exit /b 2
)

if not exist "%CMAKE%" (
    echo ERRO: CMake nao encontrado: %CMAKE%
    exit /b 1
)
if not exist "%NINJA%" (
    echo ERRO: Ninja nao encontrado: %NINJA%
    exit /b 1
)
if not exist "%COMPILADOR%" (
    echo ERRO: Compilador nao encontrado: %COMPILADOR%
    exit /b 1
)
if not exist "%QT%\lib\cmake\Qt6\Qt6Config.cmake" (
    echo ERRO: Kit Qt nao encontrado ou incompleto: %QT%
    exit /b 1
)

pushd "%~dp0"
"%CMAKE%" --preset "windows-%CONFIGURACAO%"
set "RESULTADO=%ERRORLEVEL%"
popd

exit /b %RESULTADO%
