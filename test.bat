@echo off
set PROGRAM="%~1"

rem Simple test
%PROGRAM% simpleTestInput.txt %TEMP%\simpleTestOutput.txt cat dog
if ERRORLEVEL 1 goto err
fc simpleTestOutput.txt %TEMP%\simpleTestOutput.txt || goto err

rem Loop testing
%PROGRAM% loopInput.txt %TEMP%\lookOutput.txt ma mama
if ERRORLEVEL 1 goto err
fc loopOutput.txt %TEMP%\lookOutput.txt || goto err

rem Trying to output data to an executable program file
%PROGRAM% simpleTestInput.txt %PROGRAM% cat dog
if NOT ERRORLEVEL 1 goto err

rem Trying to find an empty line
%PROGRAM% simpleTestInput.txt %TEMP%\simpleTestOutput.txt "" dog
if NOT ERRORLEVEL 1 goto err

rem Trying to find in empty file
%PROGRAM% emptyInput.txt %TEMP%\emptyOutput.txt cat dog
if ERRORLEVEL 1 goto err
fc emptyOutput.txt %TEMP%\emptyOutput.txt || goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1