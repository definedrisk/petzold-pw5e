# Example Workspaces for each chapter from CD-ROM updated to VS2019 Solutions

## Summary

Opened each 'Workspace' in VS2019 (16.6.5 at time of writing) from CD-ROM accompanying the book and upgraded to 'Solution'. This document is a summary of the additional changes made before build.

To help understand the changes made for the *revisited* code at the top level of this repo (as described by the main [README.MD](../README.md) and the [Errata](../Errata/Programming%20Windows%2C%205th%20Edition%2C%20Errata%20Addendum%20-%20Jason%20Doucette.html)) open one instance of VS2019 using the [CMakeLists.txt](../CMakeLists.txt) file and compare to a second instance of VS2019 with the appropriate solution opened from **this** CD-ROM sub-folder. These Visual Studio Solutions provide the minimum change to "get-it-working" from the CD-ROM directly in VS2019. By comparing the two versions of the code and reading the associated notes below, the changes to bring the code to the *revisited* standard can be seen.

(The seperate [VS2019 **New** Projects](../VS2019%20New%20Projects) folder contains just a few projects created from scratch - see the folders associated [README.MD](../VS2019%20New%20Projects/README.MD) for details)

## Scope

In addition to the minimal required **Changes** in most cases I have added **Comments** to summarise some of the main points demonstrated by each example and **Helpful web links** which I consider to be the up-to-date Microsoft references for the main points of relevance in each example (clearly over time these links may become invalid or change). There are also some links to Raymond Chen's ['The Old New Thing'](https://devblogs.microsoft.com/oldnewthing/).

---

## Useful Microsoft Documentation Entry Point for Win32

1. [Windows / Apps / Win32 / Build desktop Windows apps using the Win32 API](https://docs.microsoft.com/en-us/windows/win32/)
1. [Docs > Visual Studio > IDE > Debugging > How-to guides > Application types > C/C++ code > CRT debugging > CRT debugging techniques](https://docs.microsoft.com/en-us/visualstudio/debugger/crt-debugging-techniques?view=vs-2019)

---

## Chap01

### HelloMsg

#### Changes

  1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
  1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Get Started  Using the Windows Headers : Setting WINVER or _WIN32_WINNT](https://docs.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers#setting-winver-or-_win32_winnt)
1. [Windows > Apps > Win32 > Get Started  Using the Windows Headers : Windows Data Types](https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types)
1. [Docs > Microsoft C++, C, and Assembler > C++ language > C++ language reference > Built-in types](https://docs.microsoft.com/en-us/cpp/cpp/fundamental-types-cpp?view=vs-2019)

---

## Chap02 An Introduction to UNICODE

### ScrnSize

#### Changes

  1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
  1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Comments

`_UNICODE` is defined by setting *Project Properties -> Advanced -> Character Set*, while  `UNICODE` is defined as an additional preprocessor definition at *Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions*

From Errata:

> ... to maintain a single source that compiles in both ASCII and Unicode, you will need to define some identifiers. The UNICODE (without the underscore) identifier is recognized by the Win32 API. The _UNICODE (with the underscore) identifier is recognized by the C run-time library. Define it if you use any C run-time functions that have strings as parameters.

Use of the formatted output functions with *security enhancements* e.g. [_vsntprintf_s](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vsnprintf-s-vsnprintf-s-vsnprintf-s-l-vsnwprintf-s-vsnwprintf-s-l?view=vs-2019) always adds a terminating `NULL` therefore *sizeOfBuffer* does not need to be reduced by 1 as terminating null is always appended and *count* should be a suitable size to accomodate the extra `NULL` *or* `_TRUNCATE` should be used otherwise the invalid parameter handler is invoked.

Therefore this statement from Errata is no **longer relevant**:

> ... does not guarantee the output is NULL terminated. This occurs when what you write to the buffer is larger than the buffer. It writes as many characters as it can before it runs out of room, without stopping one character sooner to append a NULL as the final character. Therefore ...

#### Useful Microsoft Documentation

1. [Docs > Visual Studio > IDE > Debugging > How-to guides > Application types > C/C++ code > CRT debugging > Macros for reporting](https://docs.microsoft.com/en-us/visualstudio/debugger/macros-for-reporting?view=vs-2019)

---

## Chap03 Windows and Messages

### Hellowin

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Comments

*RegisterClassEx* function and *WNDCLASSEX* structure are now used giving some extra functionality. The *GetLastError* function is used establish a reason for failure if *RegisterClass* return value is zero.

Note from Microsoft Documentation of *RegisterClass* that:

> All window classes that an application registers are unregistered when it terminates.
>
>No window classes registered by a DLL are unregistered when the DLL is unloaded. A DLL must explicitly unregister its classes when it is unloaded.

The return value `HWND` of *CreateWindow* should be checked for `NULL` in which case use *GetLastError* for extended information.

`WM_QUIT` causes *GetMessage* to return zero, otherwise it is always nonzero, however *GetMessage* can return -1 if an error occurs so it should be checked using an if-else construct:

    while ( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    {
      if (bRet == -1)
      {
        // handle the error using GetLastError() and possibly exit 
      }
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows and Messages](https://docs.microsoft.com/en-us/windows/win32/winmsg/messages-and-message-queues)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > WNDCLASSEX structure](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > RegisterClassEx function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > CreateWindowEx function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > GetMessage function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage)

---

## Chap04 An Exercise in Text Output

### For each project

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Comments

Erratum 3 states

>All programs whose WM_PAINT message handler redraws the entire client area (that is, in all cases of repainting, without using ROPs (raster operations) that merge with the background), do not require a background brush.
>
>Windows automatically fills the client area with the background brush selected when a window is resized. It does so by sending a WM_ERASEBKGND Notification to the window, and the default processing of this message, via the DefWindowProc() Function, is that the background is 'erased' by using the class background brush specified by the hbrBackground member of the WNDCLASS structure. If this is NULL, the background is not erased (although the application could process the WM_ERASEBKGND Notification and erase it manually).
>
>Thus, for programs that are going to fill the client area themselves in their WM_PAINT handler, this will result in a slower application that flickers needlessly. The flicker occurs because the application fills the client area completely immediately after Windows has just finished filling it in with the background brush.
>
>To remove the background brush in any of these programs in the text book, change the WinMain() line:

      //wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
      wndclass.hbrBackground = NULL ;

There is disagreement with Erratum 7 as this [stackoverflow answer](https://stackoverflow.com/questions/23001890/winapi-getupdaterect-with-brepaint-true-inside-wm-paint-doesnt-clear-the-pai/23005852#23005852) explains. Either check the *rcPaint* field of *PAINTSTRUCT* to determine what needs painting and if this is empty end early OR call *InvalidateRect* (before *BeginPaint*) to invalidate the whole (or appropriate part) of the client area. Once *BeginPaint* is called then *fErase* flag would usually be FALSE indicating that `WM_ERASEBKGND` (called by *BeginPaint*) has completed with a nonzero return value, otherwise *fErase* would be TRUE indicating that the background should still be dealt with (often the case when the background brush is NULL).

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows GDI > Winuser.h > BeginPaint function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-beginpaint)
1. [Windows > Apps > Win32 > API > Windows GDI > Winuser.h > PAINTSTRUCT structure](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-paintstruct)
1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > GetSystemMetrics function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics)

### SysMets1, SysMets2 & SysMets3

#### Changes

1. Line 6: comment out

#### Comments

Windows places a `WM_PAINT` message in the message queue when part of the client area is invalid. Unless you call *BeginPaint* (and therefore *EndPaint*) or *ValidateRect* upon receiving the message then windows will continuously call `WM_PAINT`. Only one `WM_PAINT` is placed in the queue but this will be there as long as part of the client area is invalid. The *DefWindowProc* is simply:

    case WM_PAINT:
      BeginPaint (hwnd, &ps) ;
      EndPaint (hwnd, &ps) ;
      return 0 ;

Default mapping of logical to physical coordinates is `MM_TEXT` (logical units are the same as physical pixels with the origin at the top left and positive values increasing to the right and down). This is the same system used to define the invalid rectangle.

There is no point using the SM_SLOWMACHINE metric of *GetSystemMetrics* anymore: ["What is a SM_SLOWMACHINE", Raymond Chen, March 12 2007](https://devblogs.microsoft.com/oldnewthing/20070312-00/?p=27653)

---

## Chap05 Basic Drawing

### For each project

#### Changes

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

#### Changes

From Errata:

1. Line 85: insert: `EndPaint (hwnd, &ps) ;`

#### Comments

Introduced `CS_OWNDC` but not recommended to use. See ["What does the CS_OWNDC class style do?", Raymond Chen, June 1 2006](https://devblogs.microsoft.com/oldnewthing/20060601-06/?p=31003).

#### Useful Microsoft Documentation

1. [Windows  Apps  Win32  Desktop Technologies  Graphics and Gaming  Windows GDI > Display Device Context Defaults](https://docs.microsoft.com/en-us/windows/win32/gdi/display-device-context-defaults)
1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > SaveDC function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-savedc)

### LineDemo

#### Comments

Various filled shapes demonstrated.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Graphics and Gaming > Windows GDI > Filled Shapes](https://docs.microsoft.com/en-us/windows/win32/gdi/filled-shapes)

### Bezier

#### Comments

> When you draw a series of connected Bezier splines, the point of connection will be smooth only if the second control point of the first Bezier, the end point of the first Bezier (which is also the start point of the second Bezier), and the first control point of the second Bezier are colinear; that is, they lie on the same straight line.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > PolyBezier function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-polybezier)

### AltWind

#### Comments

Generally for all GDI objects:

- You should eventually delete all GDI objects that you create.
- Dont delete GDI objects while they are selected into a valid Device Context.
- Dont delete stock objects.

Creating, Selecting and Deleting Pens. Use of *CreatePen* and *CreatePenIndirect* using a `LOGPEN` structure. Raster Operation (ROP) is a bitwise boolean operation with pixels. Binary Raster Operation (ROP2) when just two pixel patterns involved (the pen and destination). Demonstrate `ALTERNATE` and `WINDING` parameters for the *Polygon Fill Mode* (Device Context Attribute).

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows GDI > Wingdi.h > SetPolyFillMode function](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpolyfillmode)

### WhatSize

#### Comments

Metric mapping modes (see pp.184-185 for details):

- *Window origin* default (0,0) can be changed.
- *Viewport origin* default (0,0) can be changed.
- *Window extent* default set by mapping mode and resolution of device cannot be changed.
- *Viewport extent* default set by mapping mode and resolution of device cannot be changed.
- The extents *Window extent* and *Viewport extent* aren't important by themselves but take on meaning when expressed as ratios of each other.

(An)Isotropic mapping modes (see pp.188-192 for details):

- Let you change the viewport and window extents.

### RandRect

#### Comments

Demonstrate use of *PeekMessage* function instead of *GetMessage* to create an alternative style message loop:

     while (TRUE)
     {
          if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
          {
               if (msg.message == WM_QUIT)
                    break ;
               
               TranslateMessage (&msg) ;
               DispatchMessage (&msg) ;
          }
          else
               DrawRectangle (hwnd) ;
     }

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > PeekMessageA function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea)

### Clover

#### Comments

Demonstrate creation, combination and use of Region (GDI) objects for clipping the device context during paint. They should be deleted as with other GDI objects after use. A `COMPLEXREGION` is a combination of `SIMPLEREGION` objects.

---

## Chap06 The Keyboard

### For each project

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### SysMets4

#### Changes

1. Line 6: comment out

#### Comments

Using the `WM_KEYDOWN` messages to send a subsequent message direct to the window thereby using the exisiting code logic (in this case scroll bar messages as would be sent using mouse clicks in the scroll bars which can now also be controlled using key presses).

### KeyView1 & KeyView2

#### Comments

For a window procedure used with two window classes, one registred with *RegisterClassW* and one with *RegisterClassA* then it is necessary to establish which version (8-bit ANSI or 16-bit UNICODE) the functions dealing with characters and strings should be using.  Within the procedure use:

    fUnicode = IsWindowUnicode (hwnd) ;

Line 114: Added *return* as WM_SIZE is called afterwards.

This demonstrates some more techniques for drawing including displaying text on top of existing text to create an underline (using transparent background). Also the *ScrollWindow* function is used (which updates the scrolled region immediately) but does not update the "exposed" region until the application retrieves WM_PAINT (or a call to *UpdateWindow* is made). In this case it is still necessary to "draw" all the window in WM_PAINT to cope with the situation when the window is resized (whole window is invalid).

### StokFont

#### Changes

1. Ensure that UNICODE is removed from *Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions*

#### Comments

Demonstrate various "standard" system fonts and character sets.

### Typer

#### Comments

Concept of a single caret being a single object shared by system queue (and therefore multiple windows).  Use `WM_SETFOCUS` and `WM_KILLFOCUS` (always occur in pairs) to call *CreateCaret* and *DestroyCaret*.  Use *ShowCaret* and *HideCaret* during drawing (other than during WM_PAINT).

---

## Chap07 The Mouse

### For each project

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### Connect

#### Comments

Demonstrate use of `WM_LBUTTONDOWN`, `WM_MOUSEMOVE` and `WM_LBUTTONUP`to process some simple mouse actions.

### Checker1

#### Comments

Basic mouse click hit testing. Note that whole window is repainted. Instead it would be possible to add some extra logic to draw only the invalid area by using *IntersectRect* function along with the *ps.rcPaint* (updated during call to *BeginPaint*).

### Checker 2

#### Comments

Keyboard interface added. Uses *SendMessage* to send `WM_LBUTTONDOWN` to itself. I have edited the code to display the last known values of x and y (during the keyboard operation).  Therefore when clicking on further boxes the x and y values are not updated. This also demonstrates the necessary code to display *dynmamic* text i.e. formulating the text in a temporary buffer and passing that to the approproate Text output function.

### Checker 3

#### Comments

Demonstrate use of Child Windows.

### Checker 4

#### Comments

Add keyboard processing with Child Windows. Note that child windows do not automatically get focus.

### BlokOut1 & BlokOut2

#### Changes

1. Use *GET_X_LPARAM* and *GET_Y_LPARAM* macros instead of *LOWORD (lParam)* and *HIWORD (lParam)* respectively in both `WM_MOUSEMOVE` and `WM_LBUTTONUP` message processing.

#### Comments

Demonstrate capture of mouse.  To avoid problems only capture when mouse button is pressed.  Even if captured, if no buttons are pressed and the cursor is moved over another window then `WM_MOUSEMOVE` messages will be sent to the other window.

> Do not use the LOWORD or HIWORD macros to extract the x- and y- coordinates of the cursor position because these macros return incorrect results on systems with multiple monitors. Systems with multiple monitors can have negative x- and y- coordinates, and LOWORD and HIWORD treat the coordinates as unsigned quantities.

Use *GET_X_LPARAM* and *GET_Y_LPARAM* macros.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > User Interaction > Legacy Features > Keyboard and Mouse Input](https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove)

### SysMets

#### Comments

Demonstrate use of mouse wheel and scrolling.  This program requires `WIN_VER` and `_WIN32_WINNT` setting (the errata are superceeded by the link below).  There is a difference in scrollbar processing to demonstrate `SB_THUMBTRACK` vs `SB_THUMBPOSITION` when handling `WM_VSCROLL` and `WM_HSCROLL` respectively.

#### Useful Microsoft Documentation

1. [Docs > Microsoft C++, C, and Assembler > Porting and upgrading > Upgrade projects from earlier versions > Update WINVER and _WIN32_WINNT](https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt?view=vs-2019)

---

## Chap08 The Timer

### For each project

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### Beeper1 & Beeper2

#### Comments

Responding to `WM_TIMER` directly in the window procedure or via a callback funcion.  It is considered good practice to call *KillTimer* on any active timers during `WM_DESTROY`.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows and Messages > WM_TIMER message](https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-timer)
2. [Windows > Apps > Win32 > API > Windows and Messages > Winuser.h > TIMERPROC callback function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-timerproc)

### DigClock

#### Comments

Note that multiple functions are used to implement different parts of drawing functionality on the same Device Context (i.e. typedef struct HDC__ *HDC defines a HDC as a pointer to a structure object) which includes modifying the window origin.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Internationalization > Locale Information Constants](https://docs.microsoft.com/en-us/windows/win32/intl/locale-information-constants)

### Clock

#### Comments

Line 166 requires TRUE to draw all hands because the removal of previous second hand slowly erases parts of the minute and hour hands.

### WhatClr

#### Comments

To demonstrate that drawing is possible (although no advised) anywhere on the screen I have added the following line to `WM_TIMER` message handler:

    SetPixel(hdcScreen, pt.x, pt.y, 0);

This writes a black pixel at the location of the cursor after reporting the colour.  Eventually these pixles are updated when their associated window refreshes.

## Chap09 Child Window Controls

### For each project

From the errata:

> "Message numbers in the second range (WM_USER through 0x7FFF) can be defined and used by an application to send messages within a private window class. These values cannot be used to define messages that are meaningful throughout an application, because some predefined window classes already define values in this range. For example, predefined control classes such as BUTTON, EDIT, LISTBOX, and COMBOBOX may use these values. Messages in this range should not be sent to other applications unless the applications have been designed to exchange messages and to attach the same meaning to the message numbers.

> Message numbers in the third range (WM_APP through 0xBFFF) are available for application to use as private messages. Message in this range do not conflict with system messages."

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows Controls](https://docs.microsoft.com/en-us/windows/win32/controls/window-controls)
1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows Controls > Control Library](https://docs.microsoft.com/en-us/windows/win32/controls/individual-control-info)
1. [The Old New Thing: Which message numbers belong to whom?](https://devblogs.microsoft.com/oldnewthing/20031202-00/?p=41653)

### BtnLook

#### Comments

Demonstrates use of *GetDialogBaseUnits* to obatin width and height of characters in default font.  This returns roughly the same values as the *GetTextMetrics* function but ensures greater consistency with controls in dialog boxes.  Also discusses three ways to obtain hInstance:

    hInst = ((LPCREATESTRUCT) lPAram) -> hInstance; // get the hInstance member as held in the "creation structure"
    hInst = hInstance; // Use a global variable and set it form WinMain
    hInst = GetWindowLong(hWnd, GWL_HINSTANCE)

From errata:

> On page 368, Chapter 9, Check Boxes, the book explains what you must pass in the wParam parameter in a SendMessage() call when sending a BM_SETCHECK Message to a check box control to set or remove the check mark:

> "The wParam parameter is set to 1 to create a check mark and to 0 to remove it."

> While this statement is correct, the BM_SETCHECK Message has identifiers already created that hold these values, so you need not remember them. They are:
BST_CHECKED is defined as 1, which sets the button state to checked.
BST_UNCHECKED is defined as 0, which sets the button state to cleared.
BST_INDETERMINATE is defined as 2, which sets the button state to grayed, indicating an indeterminate state. (This is only used for buttons with the BS_3STATE or BS_AUTO3STATE style).

When using Windows `COLOR_` constants within the `wndclass.hbrBackground` member of the WNDCLASS structure it is required to add +1 e.g.

    wndclass.hbrBackground = (HBRUSH) (COLR_BTNFACE + 1) ;

Windows understands that when then value is low it acutally refers to a system color rather than an actaul handle but ...
>... doing so has no profound purpose other than to prevent the value from being NULL.

### OwnDraw

#### Comments

Demonstrate `BS_OWNERDRAW` button style. The button sends its parent a `WM_DRAWITEM` message whenever it need painting e.g. when pressed, released, when it gains or looses focus and whenever else it needs painting. *lParam* is a pointer to `DRAWITEMSTRUCT`.  This struct contains a Device Context for the button. Any GDI objects selected into the device must be unselected. Also care not to draw outside the rectangle defining boundaries of the button.

### Colors1

#### Comments

Demonstrate 'subclassing' to add functionality to a control's `GWL_WNDPROC`. Store the old value and ensure that it is called in the default case.  From the errata notes 

Demonstrate methods to color child windows, implement scroll bar controls and adjust static controls. Also shows method to maintain keyboard focus (using the subclassing to add 'tab' key functionality while passing remainder of keypresses through to default procedure).

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > API > The Windows Shell > Commctrl.h > SetWindowSubclass function](https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-setwindowsubclass)
1. [Homework assignment about window subclassing, Raymond Chen, November 10 2003](https://devblogs.microsoft.com/oldnewthing/20031110-00/?p=41893)
1. ["Safer subclassing", Raymond Chen, November 11 2003](https://devblogs.microsoft.com/oldnewthing/20031111-00/?p=41883)

### PopPad1

#### Comments

Demonstrate use of Edit Control.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows Controls > Edit Control](https://docs.microsoft.com/en-us/windows/win32/controls/edit-controls)

### Environ

#### Comments

Demonstrate use of List Box control. Incorporate the fix from errata whereby the pointer to memory is modified and then same pointer is used during call to free; a copy of the ptr should be saved instead.

Added code to resize/move List Box control to utilise minimum of available space in window and required size for contents.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows Controls > List Box](https://docs.microsoft.com/en-us/windows/win32/controls/list-boxes)
1. [Windows > Apps > Win32 > API > Processenv.h > GetEnvironmentStrings function](https://docs.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getenvironmentstrings)

### Head

#### Comments

Demonstrates `LB_DIR` message. Also gives example of problems that may be faced mixing files with and without `UNICODE` specified. Trialled with UTF8 and UTF16 test files.

#### Useful Microsoft Documentation

1. [Windows > Apps > Win32 > Desktop Technologies > Desktop App User Interface > Windows Controls > LB_DIR message](https://docs.microsoft.com/en-us/windows/win32/controls/lb-dir)

## Chap10 Menus and Other Resources

### For each project

#### Changes

1. *Project Properties -> C/C++ -> Code Generation -> Enable Minimal Rebuild = No (/Gm-)*
1. *Project Properties -> C/C++ -> General -> Debug Information Format = Program Database (/Zi)*

### PoePoem

Cannot directly modify text in resource by retrieved pointer, instead see this [Stack Overflow question: Embed Text File in a Resource in a native Windows Application](https://stackoverflow.com/questions/2933295/embed-text-file-in-a-resource-in-a-native-windows-application)

The implementation is changed quite substanitally based on the Stack Overflow article.

### MenuDemo, PopMenu and NoPopups

Demonstrate basic menu creation and use including controlling the system menu. Popup menu can be obtained from a submenu.

[Stack Overflow: How to use main menu handle in TrackPopupMenu()](https://stackoverflow.com/questions/20926773/how-to-use-main-menu-handle-in-trackpopupmenu)

#### Useful Microsoft Documentation

[Windows > Apps > Win32 > API > Menus and Other Resources > Winuser.h > TrackPopupMenu function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-trackpopupmenu)

### PopPad2



... *work in progress* ...
