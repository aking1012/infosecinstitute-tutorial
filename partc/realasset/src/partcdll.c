#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include "partcdll.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

    switch (fdwReason) {
	case DLL_PROCESS_ATTACH: {
             break;
		}

        case DLL_PROCESS_DETACH: {
            break;
		}

        case DLL_THREAD_ATTACH: {
            break;
		}

        case DLL_THREAD_DETACH: {
            break;
		}
    }

	return TRUE;
}

EXPORT void hello(void) {
	printf("Hello\n");
}
