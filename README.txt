------------------------
Important Folders
------------------------


Projects
---------

Library/
  - C# classes that implement the actual library code

Wrapper/
  - wrappers for the C# classes so they can be used in C++
  - goal is to keep as much program logic in C# as possible;
    the wrapper should do nothing but make calls to AcsLib.NET
    C# methods, and convert data between C# and C++ 
	
        Wrapper/include/
          - interfaces for different modules in AcsLib.NET
          - ex. FoxPro.NET.h, SQLite.NET.h, etc.
        Wrapper/src/
          - implementation of wrapper modules



Other
---------

.git/
  - revision tracking

_doc/
  - documentation

_scripts/
  - automate the boring stuff

    _scripts/mkrelease_local.bat
      - create .release folder in solution directory containing 

_build/
  - compile output

--

mkrelease_local.bat
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

mkrelease_network.bat
  - same as above, output to J:\Programs\DotNet\AcsNetLib