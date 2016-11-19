__start__: obj ../libs/Interp4Fly.so ../libs/Interp4Turn.so ../libs/Interp4Rotate.so
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++11 -Iinc -I../inc
LDFLAGS=-Wall -shared




../libs/Interp4Turn.so: obj/Interp4Turn.o
	g++ ${LDFLAGS} -o ../libs/Interp4Turn.so obj/Interp4Turn.o
	@echo
	@echo "  Wtyczka dla polecenia 'Turn' zostala utworzona."
	@echo

../libs/Interp4Fly.so: obj/Interp4Fly.o
	g++ ${LDFLAGS} -o ../libs/Interp4Fly.so obj/Interp4Fly.o
	@echo
	@echo "  Wtyczka dla polecenia 'Fly' zostala utworzona."
	@echo

../libs/Interp4Rotate.so: obj/Interp4Rotate.o
	g++ ${LDFLAGS} -o ../libs/Interp4Rotate.so obj/Interp4Rotate.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo

obj/Interp4Fly.o: src/Interp4Fly.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Fly.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Fly.o src/Interp4Fly.cpp

obj/Interp4Turn.o: src/Interp4Turn.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Turn.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Turn.o src/Interp4Turn.cpp

obj/Interp4Rotate.o: src/Interp4Rotate.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Rotate.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Rotate.o src/Interp4Rotate.cpp

clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
