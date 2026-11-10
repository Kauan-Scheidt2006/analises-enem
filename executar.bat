@echo off
setlocal

set "QT_BIN=C:\Qt\6.11.1\mingw_64\bin"
set "CONFIGURACAO=%~1"
set "CAMINHO_CSV=%~2"

if not defined CONFIGURACAO set "CONFIGURACAO=debug"

if /I not "%CONFIGURACAO%"=="debug" if /I not "%CONFIGURACAO%"=="release" (
    echo ERRO: Configuracao invalida: %CONFIGURACAO%
    echo Uso: executar.bat [debug^|release] [caminho-csv]
    exit /b 2
)

set "EXECUTAVEL=%~dp0build\windows-%CONFIGURACAO%\bin\analises_enem.exe"

if not exist "%QT_BIN%\Qt6Core.dll" (
    echo ERRO: Runtime do Qt nao encontrado: %QT_BIN%
    exit /b 1
)
if not exist "%EXECUTAVEL%" (
    echo ERRO: Executavel nao encontrado: %EXECUTAVEL%
    echo Execute compilar.bat %CONFIGURACAO% primeiro.
    exit /b 1
)

set "PATH=%QT_BIN%;%PATH%"

if defined CAMINHO_CSV (
    "%EXECUTAVEL%" "%CAMINHO_CSV%"
) else (
    "%EXECUTAVEL%"
)

exit /b %ERRORLEVEL%
