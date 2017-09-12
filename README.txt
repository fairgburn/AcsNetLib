------------------------
Important Files/Folders
------------------------

CSharp/
  - classes that implement the actual library code

CPP/
  -  wrappers for the C# classes so they can be used in C++

include/
  - headers for C++ wrapper classes

lib/
  - generated during compile
  - default output location for .dll and .lib files from the library/wrapper

mkrelease.bat
  - creates a folder (.release) and copies library distribution files to it:

	.release/
            |--AcsLib.NET.dll
            |--AcsCppLib.NET.dll
            |--(other dependency DLLs)
            |
            |--include/
            |       |--FoxPro.NET.h
            |       |--(other C++ wrapper headers)
            |
            |--lib/
                |--AcsCppLib.NET.lib