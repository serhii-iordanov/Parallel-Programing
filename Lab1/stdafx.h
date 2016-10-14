// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define FILETIMETOUINT64(ft) \
((((unsigned __int64)ft.dwHighDateTime) << 32) | (ft.dwLowDateTime))


// TODO: reference additional headers your program requires here
