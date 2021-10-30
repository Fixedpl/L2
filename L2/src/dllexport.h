#pragma once

#ifdef LE_EXPORTS
#define LE_API __declspec(dllexport)
#else
#define LE_API __declspec(dllimport)
#endif
