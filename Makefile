FLAGS := -O3
convert_main: convert_main.o carInsurance.o spatialNetwork.o criteo.o common.o
	g++ $(FLAGS) convert_main.o carInsurance.o spatialNetwork.o criteo.o common.o -o convert_main

convert_main.o: convert_main.cpp carInsurance.h spatialNetwork.h convertData.h
	g++ $(FLAGS) -c convert_main.cpp
carInsurance.o: carInsurance.cpp carInsurance.h convertData.h
	g++ $(FLAGS) -std=c++11 -c carInsurance.cpp
spatialNetwork.o: spatialNetwork.cpp spatialNetwork.h convertData.h 
	g++ $(FLAGS) -c spatialNetwork.cpp
criteo.o: criteo.h criteo.cpp convertData.h common.h 
	g++ $(FLAGS) -std=c++11 -c criteo.cpp
common.o:common.h common.cpp
	g++ $(FLAGS) -c common.cpp

.PHONY:clean
clean:
	rm convert_main *.o 

