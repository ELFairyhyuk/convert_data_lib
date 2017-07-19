convert_main: convert_main.o carInsurance.o spatialNetwork.o day_0.o common.o
	g++ convert_main.o carInsurance.o spatialNetwork.o day_0.o common.o -o convert_main
convert_mian.o: conert_main.cpp carInsurance.h spatialNetwork.h convertData.h
	g++ -c convert_main.cpp 
carInsurance.o: carInsurance.cpp carInsurance.h convertData.h
	g++ -c carInsurance.cpp 
spatialNetwork.o: spatialNetwork.cpp spatialNetwork.h convertData.h 
	g++ -c spatialNetwork.cpp
day_0.o:day_0.h day_0.cpp convertData.h common.h 
	g++ -c day_0.cpp
common.o:common.h common.cpp
	g++ -c common.cpp

.PHONY:clean
clean:
	rm convert_main *.txt *.bin *.o *.gch

