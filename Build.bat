:: Batch file for building Data Structures with VS2017 Command Prompt
:: By Tristan Hilbert
:: 06/17/2018

@echo off
SETLOCAL
::Prepare for Operations
set EXE=prog
set DEXE=d_prog
set FLAGS=/pedantic /ansi
dir *.c /s /b > dir.txt

SETLOCAL
::Check operation user wishes for
set OPER=%1
if [%1]==[] CALL :ERROR
if "%OPER%"=="--debug" CALL :debug
if "%OPER%"=="-d" CALL :debug
if "%OPER%"=="--profile" CALL :profile
if "%OPER%"=="-p" CALL :profile
if "%OPER%"=="--clean" CALL :clean
if "%OPER%"=="-c" CALL :clean
ENDLOCAL
GOTO:EOF

:ERROR
echo What operation would you like to run?
echo. 
echo Build.bat [operation]
echo --debug -d
echo    builds Debug Executable
echo --profile -p
echo    builds Standard/Deployed Executable
echo --clean -c
echo    cleans binary files
CALL:end
EXIT /B %ERRORLEVEL%

::Provides a debug build of the binaries
:debug
echo DEBUG
CALL:end
EXIT /B %ERRORLEVEL%

::Provides a profile build of the binaries
:profile
for %%a in (dir.txt) do (
   CL %FLAGS% /c %%a /out:%%a:.c=.o
)
dir *.o /s /b > dir.txt
LI %FLAGS% %dir.txt% -o %EXE%
CALL:end
EXIT /B %ERRORLEVEL%

::Removes binaries from this directory
:clean
echo CLEAN
CALL:end
EXIT /B %ERRORLEVEL%
ENDLOCAL

::Cleanup
:end
del /Q dir.txt
EXIT /B %ERRORLEVEL%