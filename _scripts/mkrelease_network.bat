set dest=J:\Programs\DotNet\AcsNetLib

cd ..
rmdir /S %dest%
mkdir %dest% %dest%\include %dest%\lib
copy _build\lib\*.dll %dest%
copy _build\lib\*.lib %dest%\lib
copy Wrapper\include\*.h %dest%\include

pause