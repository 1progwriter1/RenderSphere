CFLAGS=-fsanitize=address,alignment -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-qual \
		-Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline \
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
		-Wstrict-overflow=2 -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation \
		-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -Werror=vla
# -Wsuggest-override

SFML=-lsfml-graphics -lsfml-window -lsfml-system
INCLUDE=-I/opt/homebrew/include/ -I${PWD}/headers
LINK=-L/opt/homebrew/lib

SOURCES=$(wildcard src/*.cpp) $(wildcard src/clock/*.cpp) $(wildcard src/gui/*.cpp) $(wildcard src/sys/*.cpp) $(wildcard src/sphere/*.cpp)

COMP=g++

all:
	$(COMP) $(CFLAGS) $(SOURCES) $(SFML) $(INCLUDE) $(LINK)
	rm -r *.dSYM

%.out: %.cpp
	$(COMP) $(CFLAGS) $< $(SFML) $(INCLUDE) $(LINK) -o $@
	rm -r *.dSYM
