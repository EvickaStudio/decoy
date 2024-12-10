@echo off

if exist "dummy.obj" del "dummy.obj"
if exist "dummy.exe" del "dummy.exe"
if exist "dummy.res" del "dummy.res"

\masm32\bin\ml /c /coff "dummy.asm"
if errorlevel 1 goto errasm

\masm32\bin\rc /v dummy.rc
if errorlevel 1 goto errres

\masm32\bin\PoLink /SUBSYSTEM:CONSOLE "dummy.obj" "dummy.res"
if errorlevel 1 goto errlink

dir "dummy.*"
goto TheEnd

:errlink
echo _
echo Link error
goto TheEnd

:errasm
echo _
echo Assembly Error
goto TheEnd

:errres
echo _
echo Resource Compilation Error
goto TheEnd

:TheEnd

pause
