#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include "exception.h"

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define EGNAPI __declspec(dllexport)
#else
    #define EGNAPI __declspec(dllimport)
#endif




#endif // __MAIN_H__
