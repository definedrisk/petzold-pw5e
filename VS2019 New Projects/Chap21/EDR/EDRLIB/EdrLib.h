/*----------------------
   EDRLIB.H header file
  ----------------------*/
#pragma once

#ifdef EDRLIB_EXPORTS
  #ifdef __cplusplus
    #define EXPORT extern "C" __declspec (dllexport)
  #else
    #define EXPORT __declspec (dllexport)
  #endif
#else
  #ifdef __cplusplus
    #define EXPORT extern "C" __declspec (dllimport)
  #else
    #define EXPORT __declspec (dllimport)
  #endif
#endif

EXPORT BOOL CALLBACK EdrCenterTextA (HDC, PRECT, PCSTR) ;
EXPORT BOOL CALLBACK EdrCenterTextW (HDC, PRECT, PCWSTR) ;

#ifdef UNICODE
#define EdrCenterText EdrCenterTextW
#else
#define EdrCenterText EdrCenterTextA
#endif