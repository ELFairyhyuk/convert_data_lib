convert_main: convert_main.o carInsurance.o spatialNetwork.o criteo.o common.o
	g++ convert_main.o carInsurance.o spatialNetwork.o criteo.o common.o -o convert_main
convert_mian.o: conert_main.cpp carInsurance.h spatialNetwork.h convertData.h
	g++ -c convert_main.cpp
carInsurance.o: carInsurance.cpp carInsurance.h convertData.h
	g++ -c carInsurance.cpp
spatialNetwork.o: spatialNetwork.cpp spatialNetwork.h convertData.h 
	g++ -c spatialNetwork.cpp
criteo.o: criteo.h criteo.cpp convertData.h common.h 
	g++ -std=c++11 -c criteo.cpp
common.o:common.h common.cpp
	g++ -c common.cpp

.PHONY:clean
clean:
	rm convert_main *.txt *.bin *.o *.gch

