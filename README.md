------------------------
Important Folders
------------------------


Projects
---------

DotNetLibrary/
  - C# classes that implement the actual library code

DotNetCppWrapper/
  - C++ wrapper for library; for use in legacy MFC programs w/ no CLR support
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

_doc/
  - documentation

_build/
  - compile output

---------

Project is small enough now (11/30/2017) for inline comments and XML documentation in code.  
Will consider more elaborate documentation if project grows.