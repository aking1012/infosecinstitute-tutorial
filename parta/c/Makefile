#Use mingw32-gcc 
CC=i586-mingw32msvc-gcc 
#set CFLAGS and DLLNAME 
CFLAGS=-c 
DLLNAME=hellodll

all: loader.exe 

loader.exe: hellodll.dll hello.o 
	$(CC) -o hello.exe hello.o $(DLLNAME).dll 

hellodll.dll: hellodll.o
	$(CC) -shared -o $(DLLNAME).dll hellodll.o -Wl,--out-implib,libtest.a 

hellodll.o: 
	$(CC) $(CFLAGS) -DBUILD_DLL -DWIN32 hellodll.c 

hello.o: 
	$(CC) $(CFLAGS) hello.c 

clean: 
	rm -rf *o *.exe *.dll *a

debug: dloader.exe 

dloader.exe: dhellodll.dll dhello.o 
	$(CC) -o hello.exe hello.o $(DLLNAME).dll 

dhellodll.dll: dhellodll.o 
	$(CC) -shared -o $(DLLNAME).dll hellodll.o -Wl,--out-implib,libtest.a 

dhellodll.o: 
	$(CC) $(CFLAGS) -DBUILD_DLL -DWIN32 -DDEBUG hellodll.c 

dhello.o: 
	$(CC) $(CFLAGS) hello.c 
