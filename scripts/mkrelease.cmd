set dest=%1

rmdir /S %dest%
mkdir %dest% %dest%\include %dest%\lib
copy lib\*.dll %dest%
copy lib\*.lib %dest%\lib
copy include\*.h %dest%\include

pause