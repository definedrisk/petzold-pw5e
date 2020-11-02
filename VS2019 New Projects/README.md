# VS2019 New Solutions

This directory stores the closest equivalent "New Solution" or "New Project" from within VS2019 and can be compared against  *revisited* code (as described by [README.MD](../README.MD) and the [Errata](../Errata/Programming%20Windows%2C%205th%20Edition%2C%20Errata%20Addendum%20-%20Jason%20Doucette.html)) and older code contained in the CD-ROM subfolder.

---

## Chap01 HelloMsg

- HelloMsg-VS2019-WinDesktopApp

  Created with File -> New Project -> Windows Desktop Application (place solution and project in same directory).
  
  This does not actually display the "Hello World!" message. This is to demonstrate what a new project now contains by default.

---

## Chap21 Dynamic-Link Libraries

A new solution was created containing a DLL project titled EDRLIB.  The use of pre-compiled headers was switched off for the imported .c source file. EDRLIB.dll is created (in both Debug and Release configurations) along with the .lib file necessary for linking into a project during compilation. A second Win32 Application project EDRTEST was then added to the solution.  The solution is configured such that EDRTEST is dependent upon EDRLIB. The DLL projects header file is included in the source code of EDRTEST. Linker options are edited to add EDRLIB.lib (residing in the appropriate Debug and Release directories).

---

*Work in progress* ... further solutions will be added if and when appropriate as I progress through the book.