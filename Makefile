convert_main:convert_main.cpp data2lib.cpp data2lib.h
	g++  convert_main.cpp data2lib.cpp data2lib.h -o convert_main
.PHONY:clean
clean:
	rm -f convet_main *.txt
