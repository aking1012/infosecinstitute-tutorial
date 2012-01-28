all:
	i586-mingw32msvc-gcc -c -DBUILDING_EXAMPLE_DLL partcdll.c
	i586-mingw32msvc-gcc -shared -o partcdll.dll partcdll.o -Wl,--out-implib,libpartcdll.a
	i586-mingw32msvc-windres -i partc.rc -o partcrc.o
	i586-mingw32msvc-gcc -o partc.exe partc.c partcrc.o 
clean:
	rm *.o
	rm *.a
	rm *.exe
	rm *.dll

dll:
	rm partcdll.o
	rm libpartcdll.a
	rm partcdll.dll
	i586-mingw32msvc-gcc -c -DBUILDING_EXAMPLE_DLL partcdll.c
	i586-mingw32msvc-gcc -shared -o partcdll.dll partcdll.o -Wl,--out-implib,libpartcdll.a

exe:
	rm partcrc.o
	rm partc.exe
	i586-mingw32msvc-windres -i partc.rc -o partcrc.o
	i586-mingw32msvc-gcc -o partc.exe partc.c partcrc.o 
