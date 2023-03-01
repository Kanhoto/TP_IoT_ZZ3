# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
LFLAGS = -lmosquitto
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: mqttClient.o
	$(CC) $(CFLAGS) -o main mqttClient.o $(LFLAGS)
	rm *.o
 
# The main.o target can be written more simply
mqttClient.o: mqttClient.cpp
	$(CC) $(CFLAGS) -c mqttClient.cpp

AesCyphering.o: AesCyphering.cpp
	$(CC) $(CFLAGS) -c AesCyphering.cpp