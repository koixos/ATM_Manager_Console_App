objects = src/main.o src/system.o src/auth.o

atm : $(objects)
	cc -o atm $(objects)

main.o : src/Header.h
kbd.o : src/Header.h
command.o : src/Header.h
display.o : src/Header.h
insert.o : src/Header.h
search.o : src/Header.h
files.o : src/Header.h
utils.o : src/Header.h

clean :
	rm -f $(objects)
