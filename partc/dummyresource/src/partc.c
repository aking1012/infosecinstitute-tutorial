/*
 ============================================================================
 Name        : partc.c
 Author      : aking1012.com@gmail.com
 Version     :
 Copyright   : None
 ============================================================================
 */
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int MapRes(unsigned int hinst, unsigned int resid){
	HRSRC hres = FindResource(hinst, MAKEINTRESOURCE(resid), MAKEINTRESOURCE("BINARY"));
	unsigned int hfileres = LoadResource(hinst, hres);
	unsigned int dwSize = SizeofResource(hinst, hres);
	return 0;
};

int main() {
	int base = GetModuleHandle(0);
	int retval = MapRes(base, 10);
	printf("Done...\n");
	return 0;
};
