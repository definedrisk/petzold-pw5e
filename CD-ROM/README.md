# Example Workspaces for each chapter from CD-ROM updated to VS2019 Solutions

Opened each 'Workspace' in VS2019 (16.6.5 at time of writing) and upgraded to 'Solution'. Summary of additional changes made before build.

To help understand the changes made for the *revisited* code at the top level of this repo (as described by the main [README.MD](../README.MD) and the [Errata](../Errata/Programming%20Windows%2C%205th%20Edition%2C%20Errata%20Addendum%20-%20Jason%20Doucette.html)) open one instance of VS2019 using the [CMakeLists.txt](../CMakeLists.txt) file and compare to a second instance of VS2019 with the appropriate solution opened from this CD-ROM sub-folder. These Visual Studio Solutions provide the minimum change to "get-it-working" from the CD-ROM directly in VS2019. By comparing the two versions of the code and reading the associated notes below, the scope of changes to bring it to the *revisited* standard can be seen.

(The seperate [VS2019 New Projects](../VS2019%20New%20Projects) folder contains just a few projects created from scratch - see the folders associated [README.MD](../VS2019%20New%20Projects/README.MD) for details)

The "Helpful web links" below are what I consider to be the up-to-date Microsoft references for the main points of relevance in each example (clearly over time these links may become invalid or change).

---

## Useful Microsoft Documentation for Windows

1. [Windows / Apps / Win32 / Build desktop Windows apps using the Win32 API](https://docs.microsoft.com/en-us/windows/win32/)
1. [Docs > Visual Studio > IDE > Debugging > How-to guides > Application types > C/C++ code > CRT debugging > CRT debugging techniques](https://docs.microsoft.com/en-us/visualstudio/debugger/crt-debugging-techniques?view=vs-2019)

---

## Chap01

### HelloMsg

  1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
  1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Get Started  Using the Windows Headers : Setting WINVER or _WIN32_WINNT](https://docs.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers#setting-winver-or-_win32_winnt)
1. [Windows > Apps > Win32 > Get Started  Using the Windows Headers : Windows Data Types](https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types)
1. [Docs > Microsoft C++, C, and Assembler > C++ language > C++ language reference > Built-in types](https://docs.microsoft.com/en-us/cpp/cpp/fundamental-types-cpp?view=vs-2019)

## Chap02

### ScrnSize

  1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
  1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Comments

`_UNICODE` is defined by setting *Project Properties -> Advanced -> Character Set*, while  `UNICODE` is defined as an additional preprocessor definition at *Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions*

> ... to maintain a single source that compiles in both ASCII and Unicode, you will need to define some identifiers. The UNICODE (without the underscore) identifier is recognized by the Win32 API. The _UNICODE (with the underscore) identifier is recognized by the C run-time library. Define it if you use any C run-time functions that have strings as parameters.

Use of the formatted output functions with *security enhancements* e.g. [_vsntprintf_s](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vsnprintf-s-vsnprintf-s-vsnprintf-s-l-vsnwprintf-s-vsnwprintf-s-l?view=vs-2019) always adds a terminating `NULL` therefore *sizeOfBuffer* does not need to be reduced by 1 as terminating null is always appended and *count* should be a suitable size to accomodate the extra `NULL` *or* `_TRUNCATE` should be used otherwise invalid parameter handler is invoked. This statement is no longer relevant:

> ... does not guarantee the output is NULL terminated. This occurs when what you write to the buffer is larger than the buffer. It writes as many characters as it can before it runs out of room, without stopping one character sooner to append a NULL as the final character. Therefore ...

#### Useful Microsoft Documentation

1. [Docs > Visual Studio > IDE > Debugging > How-to guides > Application types > C/C++ code > CRT debugging > Macros for reporting](https://docs.microsoft.com/en-us/visualstudio/debugger/macros-for-reporting?view=vs-2019)

## Chap03

### Hellowin

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Comments

*RegisterClassEx* function and *WNDCLASSEX* structure are now used giving some extra functionality. The *GetLastError* function is used establish a reason for failure if *RegisterClass* return value is zero. Note that:

> All window classes that an application registers are unregistered when it terminates.
>
>No window classes registered by a DLL are unregistered when the DLL is unloaded. A DLL must explicitly unregister its classes when it is unloaded.

The return value `HWND` of *CreateWindow* should be checked for `NULL` in which case use *GetLastError* for extended information.

`WM_QUIT` causes *GetMessage* to return zero, otherwise it is always nonzero, however *GetMessage* can return -1 if an error occurs so it should be checked using an if-else construct:

    while ( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    {
      if (bRet == -1)
      {
        // handle the error and possibly exit
      }
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > WNDCLASSEX structure](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > RegisterClassEx function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > CreateWindowEx function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > GetMessage function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage)

## Chap04

### For each project

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Comments

Erratum 3 states

> All programs whose WM_PAINT message handler redraws the entire client area (that is, in all cases of repainting, without using ROPs (raster operations) that merge with the background), do not require a background brush.
>
> Windows automatically fills the client area with the background brush selected when a window is resized. It does so by sending a WM_ERASEBKGND Notification to the window, and the default processing of this message, via the DefWindowProc() Function, is that the background is 'erased' by using the class background brush specified by the hbrBackground member of the WNDCLASS structure. If this is NULL, the background is not erased (although the application could process the WM_ERASEBKGND Notification and erase it manually, it would typically process this message simply returning zero to signify that no change to background has occured). Thus, for programs that are going to fill the client area themselves in their WM_PAINT handler, erasing the background by painting with the background brush will result in a slower application that flickers needlessly. The flicker occurs because the application fills the client area completely immediately after Windows has just finished filling it in with the background brush.
>
>To remove the background brush in any of these programs in the text book, change:

    WinMain():
      //wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
      wndclass.hbrBackground = NULL ;

There is disagreement with Erratum 7 as this [stackoverflow answer](https://stackoverflow.com/questions/23001890/winapi-getupdaterect-with-brepaint-true-inside-wm-paint-doesnt-clear-the-pai/23005852#23005852) explains. Either check the *rcPaint* field of *PAINTSTRUCT* to determine what needs painting and if this is empty end early OR call *InvalidateRect* (before *BeginPaint*) to invalidate the whole (or appropriate part) of the client area. Once *BeginPaint* is called then *fErase* flag would usually be FALSE indicating that `WM_ERASEBKGND` (called by *BeginPaint*) has completed with a nonzero return value, otherwise *fErase* would be TRUE indicating that the background should still be dealt with (often the case when the background brush is NULL).

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows GDI > Winuser.h > BeginPaint function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-beginpaint)
1. [Windows > Apps > Win32 > API > Windows GDI > Winuser.h > PAINTSTRUCT structure](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-paintstruct)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > GetSystemMetrics function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics)

### SysMets1, SysMets2 & SysMets3

1. Line 6: comment out

#### Comments

Windows places a `WM_PAINT` message in the message queue when part of the client area is invalid. Unless you call *BeginPaint* (and therefore *EndPaint*) or *ValidateRect* upon receiving the message then windows will continuously call `WM_PAINT`. Only one `WM_PAINT` is placed in the queue but this will be there as long as part of the client area is invalid. The *DefWindowProc* is simply:

    case WM_PAINT:
      BeginPaint (hwnd, &ps) ;
      EndPaint (hwnd, &ps) ;
      return 0 ;

Default mapping of logical to physical coordinates is `MM_TEXT` (logical units are the same as physical pixels with the origin at the top left and positive values increasing to the right and down. This is the same system used to define the invalid rectangle.

There is certainly no point using the SM_SLOWMACHINE metric of *GetSystemMetrics* anymore: ["What is a SM_SLOWMACHINE", Raymond Chen, March 12 2007](https://devblogs.microsoft.com/oldnewthing/20070312-00/?p=27653) 

## Chap05

### For each project

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### DevCaps1

#### Comments

Introduction to display resolution, pixel and physcial size, and font dimensions and color. See links below for key functions introduced. Also *CreateCompatibleDC*, *CreateMetaFile*,

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows GDI > Winuser.h > GetDC function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdc)
1. [Windows > Apps > Win32 > API > Windows GDI > Winuser.h > GetWindowDC function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowdc)
1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > CreateDC function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createdca)
1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > CreateIC function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createica)
1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > GetDeviceCaps function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getdevicecaps)

### SineWave

1. Line 85: insert: `EndPaint (hwnd, &ps) ;` 

#### Comments

Introduced `CS_OWNDC` but not recommended to use. See ["What does the CS_OWNDC class style do?", Raymond Chen, June 1 2006](https://devblogs.microsoft.com/oldnewthing/20060601-06/?p=31003).

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > SaveDC function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-savedc)

### LineDemo

#### Comments

Various filled shapes demonstrated.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Graphics and Gaming > Windows GDI > Filled Shapes](https://docs.microsoft.com/en-us/windows/win32/gdi/filled-shapes)

... work in progress ...
