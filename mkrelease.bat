rmdir /S .release
mkdir .release .release\include .release\lib
copy lib\*.dll .release
copy lib\*.lib .release\lib
copy include\*.h .release\include
pause