all:
	i586-mingw32msvc-windres -i partc.rc -o partcrc.o
	i586-mingw32msvc-gcc -o partc.exe partc.c partcrc.o
clean:
	rm partcrc.o
	rm partc.exe
