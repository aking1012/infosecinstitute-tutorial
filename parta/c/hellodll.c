#include <windows.h> 
#include <stdio.h> 
#include "hellodll.h" 
#include <winbase.h> 

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) { 

    switch (fdwReason) { 
	case DLL_PROCESS_ATTACH: { 
		DWORD thispid = GetCurrentProcessId(); 
		char modname[16]  = "hellodll.dll"; 
		DWORD baseaddress = GetModuleHandle(modname); 
		DWORD endaddress = GetProcAddress(baseaddress, "endmarker"); 
		unsigned int memlen = ((endaddress - baseaddress)); 
		DWORD newprotect = 0x40; 
		DWORD oldprotect = NULL; 
		int vpretval = VirtualProtect(  baseaddress,  memlen,  newprotect,  &oldprotect); 
#ifdef DEBUG 
		if (vpretval!=0) { 
			printf("Memory successfully set to RWX.\n"); 
			printf("PID: %d\n", thispid); 
			printf("Base address of module: 0x%8x\n", baseaddress); 
			printf("End address of meaning: 0x%8x\n", endaddress); 
			printf("Old protection:         0x%8x\n", oldprotect); 
			printf("New protection:         0x%8x\n", newprotect); 
			printf("Length in bytes:        0x%8x\n", memlen); 
			printf("Return value from VirtualProtect: %d\n", vpretval); 
		} else { 
			printf("No joy...\n"); 
			printf("PID: %d\n", thispid); 
			printf("Base address of module: 0x%8x\n", baseaddress); 
			printf("End address of meaning: 0x%8x\n", endaddress); 
			printf("Old protection:         0x%8x\n", oldprotect); 
			printf("New protection:         0x%8x\n", newprotect); 
			printf("Length in bytes:        0x%8x\n", memlen); 
			printf("Return value from VirtualProtect: %d\n", vpretval); 
		} 
		vpretval = VirtualProtect(  baseaddress,  memlen,  newprotect,  &oldprotect); 
		if (vpretval!=0) { 
			printf("\n\n#########################################################\nJust verifying that I did it right here...\nI wanted to make sure old protection actually changed.\n"); 
			printf("PID: %d\n", thispid); 
			printf("Base address of module: 0x%8x\n", baseaddress); 
			printf("Old protection:         0x%8x\n", oldprotect); 
			printf("New protection:         0x%8x\n", newprotect); 
			printf("Length in bytes:        0x%8x\n", memlen); 
			printf("Return value from VirtualProtect: %d\n", vpretval); 
		} else { 
			printf("No joy...\n"); 
		} 
#endif 
            break; 
		} 

        case DLL_PROCESS_DETACH: 
		// Code to run when the DLL is freed 
		printf ("Unload working...\n"); 
            break; 

        case DLL_THREAD_ATTACH: 
		// Code to run when a thread is created during the DLL's lifetime 
		printf ("ThreadLoad working...\n"); 
            break; 

        case DLL_THREAD_DETACH: 
		// Code to run when a thread ends normally. 
		printf ("ThreadUnload working...\n"); 
            break; 
    } 

	return TRUE; 
} 

EXPORT void hello(void) {
__asm__(
"nop;"
"nop;"
"nop;"
"nop;"
);
} 

EXPORT void endmarker(void) { 
}

