@echo off
set PROGRAM="%~1"

rem Simple convertation
%PROGRAM% 10 16 127 > %TEMP%\test01.txt
if ERRORLEVEL 1 goto err
fc test01.txt %TEMP%\test01.txt
if ERRORLEVEL 1 goto err

rem Simple convertation negative
%PROGRAM% 10 16 -127 > %TEMP%\test02.txt
if ERRORLEVEL 1 goto err
fc test02.txt %TEMP%\test02.txt
if ERRORLEVEL 1 goto err

rem Max positive value
%PROGRAM% 10 16 2147483647 > %TEMP%\test03.txt
if ERRORLEVEL 1 goto err
fc test03.txt %TEMP%\test03.txt
if ERRORLEVEL 1 goto err

rem Max negative value
%PROGRAM% 10 16 -2147483648 > %TEMP%\test04.txt
if ERRORLEVEL 1 goto err
fc test04.txt %TEMP%\test04.txt
if ERRORLEVEL 1 goto err

rem Max positive value +1
%PROGRAM% 10 16 2147483648 > %TEMP%\test05.txt
if NOT ERRORLEVEL 1 goto err
fc test05.txt %TEMP%\test05.txt
if ERRORLEVEL 1 goto err

rem Max negative value -1
%PROGRAM% 10 16 -2147483649 > %TEMP%\test06.txt
if NOT ERRORLEVEL 1 goto err
fc test06.txt %TEMP%\test06.txt
if ERRORLEVEL 1 goto err

rem Invalid radix value
%PROGRAM% 1 16 1 > %TEMP%\test07.txt
if NOT ERRORLEVEL 1 goto err
fc test07.txt %TEMP%\test07.txt
if ERRORLEVEL 1 goto err

rem from 36 to 10 radix
%PROGRAM% 36 10 ABCDEF > %TEMP%\test08.txt
if ERRORLEVEL 1 goto err
fc test08.txt %TEMP%\test08.txt
if ERRORLEVEL 1 goto err

rem from 36 to 2 radix
%PROGRAM% 36 2 HIJKLM > %TEMP%\test09.txt
if ERRORLEVEL 1 goto err
fc test09.txt %TEMP%\test09.txt
if ERRORLEVEL 1 goto err

rem from 2 to 10 radix
%PROGRAM% 2 10 111111001000000010010100001010 > %TEMP%\test10.txt
if ERRORLEVEL 1 goto err
fc test10.txt %TEMP%\test10.txt
if ERRORLEVEL 1 goto err

rem Too many zeros
%PROGRAM% 10 27 0000000637654 > %TEMP%\test11.txt
if ERRORLEVEL 1 goto err
fc test11.txt %TEMP%\test11.txt
if ERRORLEVEL 1 goto err

rem Invalid charachter in number
%PROGRAM% 10 16 10F > %TEMP%\test12.txt
if NOT ERRORLEVEL 1 goto err
fc test12.txt %TEMP%\test12.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1