# Chapter example Workspaces from CD-ROM updated to VS2019 Solutions

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

### Helpful web links

1. [Windows > Apps > Win32 > Get Started  Using the Windows Headers](https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types)
1. [Docs > Microsoft C++, C, and Assembler > C++ language > C++ language reference > Built-in types](https://docs.microsoft.com/en-us/cpp/cpp/fundamental-types-cpp?view=vs-2019)

## Chap02

### ScrnSize

  1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
  1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### Comments

`_UNICODE` is defined by setting *Project Properties -> Advanced -> Character Set*, while  `UNICODE` is defined as an additional preprocessor definition at *Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions*

> ... to maintain a single source that compiles in both ASCII and Unicode, you will need to define some identifiers. The UNICODE (without the underscore) identifier is recognized by the Win32 API. The _UNICODE (with the underscore) identifier is recognized by the C run-time library. Define it if you use any C run-time functions that have strings as parameters.

Use of the formatted output functions with *security enhancements* e.g. [_vsntprintf_s](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vsnprintf-s-vsnprintf-s-vsnprintf-s-l-vsnwprintf-s-vsnwprintf-s-l?view=vs-2019) always adds a terminating `NULL` therefore *sizeOfBuffer* does not need to be reduced by 1 as terminating null is always appended and *count* should be a suitable size to accomodate the extra `NULL` *or* `_TRUNCATE` should be used otherwise invalid parameter handler is invoked. This statement is no longer relevant:

> ... does not guarantee the output is NULL terminated. This occurs when what you write to the buffer is larger than the buffer. It writes as many characters as it can before it runs out of room, without stopping one character sooner to append a NULL as the final character. Therefore ...

### Helpful web links

1. [Docs > Microsoft C++, C, and Assembler > C runtime library > UCRT reference > CRT alphabetical function reference > vsnprintf_s, _vsnprintf_s, _vsnprintf_s_l, _vsnwprintf_s, _vsnwprintf_s_l](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vsnprintf-s-vsnprintf-s-vsnprintf-s-l-vsnwprintf-s-vsnwprintf-s-l?view=vs-2019)
1. [Docs > Visual Studio > IDE > Debugging > How-to guides > Application types > C/C++ code > CRT debugging > Macros for reporting](https://docs.microsoft.com/en-us/visualstudio/debugger/macros-for-reporting?view=vs-2019)

## Chap03

### Hellowin

  1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
  1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### Comments

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

### Helpful web links

1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > WNDCLASSEX structure](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > RegisterClassEx function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > CreateWindowEx function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > GetMessage function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage)

## Chap04

... work in progress ...
