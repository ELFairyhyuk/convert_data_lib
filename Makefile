convert_main: convert_main.o carInsurance.o spatialNetwork.o
	g++ convert_main.o carInsurance.o spatialNetwork.o -o convert_main
convert_mian.o: conert_main.cpp carInsurance.h spatialNetwork.h convertData.h
	g++ -c convert_main.cpp carInsurance.h spatialNetwork.h convertData.h 
carInsurance.o: carInsurance.cpp carInsurance.h convertData.h
	g++ -c carInsurance.cpp carInsurance.h convertData.h 
spatialNetwork.o: spatialNetwork.cpp spatialNetwork.h convertData.h 
	g++ -c spatialNetwork.cpp spatialNetwork.h convertData.h 
.PHONY:clean
clean:
	rm convert_main *.txt *.o *.gch

