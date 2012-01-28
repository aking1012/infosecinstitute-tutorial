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

int XORIT(int start, int len, int funcid){
	unsigned int daeip;
	unsigned int end;
	if (funcid == 1){
		daeip = start + 0x24;
		end = start + len - 0xB;
	}
	while (daeip < end){
		asm(
			"XORL $0x11111111, (%[ASMEIP]);"
			:/**/
			:[ASMEIP] "r" (daeip)
			:/**/ "eax"
			);
		daeip += 4;
	};
};

EXPORT void hello(void) {
	 DWORD oldprotect = NULL;
	 int vpretval;
	 int lensec;
	 int startadd;
	 typedef void (*pfunc)();
	 HANDLE hdll;
	 pfunc vprotectaddy;
	 hdll = LoadLibrary("kernel32.dll");
	 vprotectaddy = (pfunc)GetProcAddress(hdll, "VirtualProtect");
	// DWORD oldprotect = NULL;
	 int oldprot = &oldprotect;
	/**		Things we need to at least sort of do in ASM
			DWORD baseaddress - we need to save eip
			DWORD endaddress - we need to force eip to the end of the function and save eip
			unsigned int memlen - we need to do a little math
			DWORD newprotect = 0x40; - we need to set
			DWORD oldprotect = NULL;  - we need to pass in the pointer
			int vpretval = VirtualProtect(  baseaddress,  memlen,  newprotect,  &oldprotect);
	**/

	__asm__(
	"jmp Label_passed_start;"
	/*Little ASM to get current EIP  */
	"Label_eip:"
	"mov (%%esp), %%eax;"
	"ret;"
	"Label_passed_start:"

	/*Push in reverse order*/
	"push %[old];"
	/*pointer to old protection variable*/
	"push $0x40;"
	/*new protection option*/
	"call Label_getend;"
	"push %%eax;"
	"subl %%eax, %%edx;"
	"pop %%eax;"
	/*we need to get base and end before we know length so...*/
	"push %%edx;"
	/*len*/
	"push %%eax;"
	/*base address*/
	/*"addl $0x10, %%esp;"*/
	"call %[vprotect];"
	"movl %%eax, %[vpret];"
	:/*Output */[vpret] "=r" (vpretval)
	:/*Input */[vprotect] "r" (vprotectaddy), [old] "r" (oldprot)
	:/*Clobbered */ "eax", "edx"
	);
	//end vprotect start getting eips
	asm(
			"call Label_getendenc;"
			"push %%eax;"
			"subl %%eax, %%edx;"
			"pop %%eax;"
			"movl %%edx, %[len];"
			"movl %%eax, %[start];"
			:/*Output */[len] "=r" (lensec), [start] "=r" (startadd)
			:/*Input */
			:/*Clobbered */ "eax", "edx"
		);
	//do the xor-ing
	XORIT(startadd, lensec, 1);
	//save eip structures and a little nop padding in case we miss by one  also useful for the egg-hunting approach
	//note, you would have to start searching at function entry b/c there's almost always NOPs in sequences of 4 or more
	asm(
			"jmp Label_passed_encst;"
			/*Little ASM to get current EIP  */
			"Label_eipst:"
			"mov (%esp), %eax;"
			"ret;"
			"Label_passed_encst:"
	);

	asm(
			"NOP;"
			"NOP;"
			"NOP;"
			"NOP;"
	);

	//payload
	printf("Hello\n");

	asm(
			"NOP;"
			"NOP;"
			"NOP;"
			"NOP;"
	);

	asm(
			"jmp Label_passed_endenc;"
			/*Little ASM to springboard to geteip so we actually get end */
			"Label_getendenc:"
			"call Label_eipst;"
			"movl %eax, %edx;"
			"mov (%esp), %eax;"
			"ret;"
			"Label_passed_endenc:"
	);
	//do the xor-ing
	XORIT(startadd, lensec, 1);
	__asm__(
	"jmp Label_passed_end;"
	/*Little ASM to springboard to geteip so we actually get end */
	"Label_getend:"
	"call Label_eip;"
	"movl %eax, %edx;"
	"mov (%esp), %eax;"
	"ret;"
	"Label_passed_end:"
	);
}
