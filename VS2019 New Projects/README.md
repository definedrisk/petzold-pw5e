# VS2019 New Solutions

This directory stores the closest equivalent "New Solution" or "New Project" from within VS2019 and can be compared against  *revisited* code (as described by [README.MD](../README.MD) and the [Errata](../Errata/Programming%20Windows%2C%205th%20Edition%2C%20Errata%20Addendum%20-%20Jason%20Doucette.html)) and older code contained in the CD-ROM subfolder.

---

## Chap01 HelloMsg

- HelloMsg-VS2019-WinDesktopApp

  Created with File -> New Project -> Windows Desktop Application (place solution and project in same directory).
  
  This does not actually display the "Hello World!" message. This is to demonstrate what a new project now contains by default.

---

## Chap21 Dynamic-Link Libraries

A new solution *EDR* was created containing a single DLL project titled *EDRLIB*.  The use of pre-compiled headers was switched off for the *EdrLib.c* source file. EDRLIB.dll is created (in both Debug and Release configurations) along with the EDRLIB.lib file necessary for linking into a project during compilation. A second Win32 Application project *EDRTest* was then added to the solution.  The solution is configured such that *EDRTest* is dependent upon *EDRLIB*. The DLL projects header file is included in the source code of *EDRTest*. Linker options are edited to add EDRLIB.lib (residing in the appropriate Debug and Release directories).

Preprocessor statements are used to define `__declspec(dllexport)` or `__declspec(dllimport)` as required.  A conditional define statement has also been added to define `extern "C"` langauge calling convention which allows the DLL to be used with C and C++ programs.

The *EDRTest* project should have its properties updated: add *EdrLib.h* to *Additional Include Directories* (C/C++ General options), add *EDRLIB.lib* to *Additional Dependencies* and add the relevent *Debug* or *Release* folder to *Additional Library Directories* (Linker Input and General options respectively).

### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > System Services > Dynamic-Link Libraries > Using Dynamic-Link Libraries](https://docs.microsoft.com/en-us/windows/win32/dlls/using-dynamic-link-libraries)
1. [Docs > Microsoft C++, C, and Assembler > Build C/C++ projects > Building C++ DLLs in Visual Studio > Create C/C++ DLLs in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/dlls-in-visual-cpp?view=msvc-160)

---

*Work in progress* ... further solutions will be added if and when appropriate as I progress through the book.