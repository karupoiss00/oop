@echo off
set PROGRAM="%~1"

rem Regular inversion
%PROGRAM% matrix01.txt > %TEMP%\invert01.txt
if ERRORLEVEL 1 goto err
fc invert01.txt %TEMP%\invert01.txt
if ERRORLEVEL 1 goto err

rem Regular inversion with precision
%PROGRAM% matrix02.txt > %TEMP%\invert02.txt
if ERRORLEVEL 1 goto err
fc invert02.txt %TEMP%\invert02.txt
if ERRORLEVEL 1 goto err

rem If determinant of matrix is null
%PROGRAM% matrix03.txt > %TEMP%\invert03.txt
if NOT ERRORLEVEL 1 goto err
fc invert03.txt %TEMP%\invert03.txt
if ERRORLEVEL 1 goto err

rem Failed matrix (enough lines)
%PROGRAM% matrix04.txt > %TEMP%\invert04.txt
if NOT ERRORLEVEL 1 goto err
fc invert04.txt %TEMP%\invert04.txt
if ERRORLEVEL 1 goto err

rem Failed matrix (cells is missing)
%PROGRAM% matrix05.txt > %TEMP%\invert05.txt
if NOT ERRORLEVEL 1 goto err
fc invert05.txt %TEMP%\invert05.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1