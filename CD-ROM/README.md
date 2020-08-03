# Chapter example Workspaces from CD-ROM updated to VS2019 Solutions

Opened each 'Workspace' in VS2019 (16.6.5 at time of writing) and upgraded to 'Solution'. Summary of additional changes made before build.

To help understand the changes made for this *revisited* code (as described by [README.MD](../README.MD) and the [Errata](../Errata/Programming%20Windows%2C%205th%20Edition%2C%20Errata%20Addendum%20-%20Jason%20Doucette.html)) open one instance of VS2019 using the CMakeLists.txt file and compare to a second instance of VS2019 with the appropriate solution opened from the CD-ROM sub-folder.

---

## Microsoft Documentation Windows

[Windows / Apps / Win32 / Build desktop Windows apps using the Win32 API](https://docs.microsoft.com/en-us/windows/win32/)

[.  / Get Started / Using the Windows Headers / Windows Data Types
](https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types)

---

## Chap01

- HelloMsg
  - Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)
  - Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)

## Chap02
