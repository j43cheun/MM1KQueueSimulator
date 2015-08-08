# ECE 358 Project 1 - Queue Simulation Makefile
#
# For instructions on how to run the Queue Simulator,
# refer to README.txt in the project directory.

# Global Macros
CC=g++
EXE=./Main

# Macros for Question 1
Q1_LAMBDA=75

# Macros for Question 3
Q3_FILEPATH=./question_3_part_1_and_part_2_dataset.csv
Q3_T=20000
Q3_L=12000
Q3_C=1000000
Q3_K=-1

# Macros for Question 4
Q4_FILEPATH=./question_4_dataset.csv
Q4_T=20000
Q4_L=12000
Q4_C=1000000
Q4_K=-1

# Macros for Question 6 Part 1
Q6P1_FILEPATH=./question_6_part_1_dataset.csv
Q6P1_T=20000
Q6P1_L=12000
Q6P1_C=1000000
Q6P1_K_1=5
Q6P1_K_2=10
Q6P1_K_3=40optimized

# Macros for Question 6 Part 2
Q6P2_FILEPATH=./question_6_part_2_dataset.csv
Q6P2_T=10000
Q6P2_L=12000
Q6P2_C=1000000
Q6P2_K_1=5
Q6P2_K_2=10
Q6P2_K_3=40

all: ECE358_Project_One

ECE358_Project_One: Event.o Log.o Main.o Questions.o Random.o
	$(CC) -m64 Main.o Event.o Log.o Questions.o Random.o -o Main
	
q1:
	$(EXE) -q1 $(Q1_LAMBDA) 

q3:
	$(EXE) -q3 $(Q3_FILEPATH) $(Q3_T) $(Q3_L) $(Q3_C) $(Q3_K)

q4:
	$(EXE) -q4 $(Q4_FILEPATH) $(Q4_T) $(Q4_L) $(Q4_C) $(Q4_K)

q6p1:
	$(EXE) -q6p1 $(Q6P1_FILEPATH) $(Q6P1_T) $(Q6P1_L) $(Q6P1_C) $(Q6P1_K_1) $(Q6P1_K_2) $(Q6P1_K_3)

q6p2:
	$(EXE) -q6p2 $(Q6P2_FILEPATH) $(Q6P2_T) $(Q6P2_L) $(Q6P2_C) $(Q6P2_K_1) $(Q6P2_K_2) $(Q6P2_K_3)

Event.o: Event.cpp Event.h
	$(CC) -m64 -c Event.cpp

Log.o: Log.cpp Log.h
	$(CC) -m64 -c Log.cpp

Main.o: Main.cpp
	$(CC) -m64 -c Main.cpp

Questions.o: Questions.cpp Questions.h
	$(CC) -m64 -c Questions.cpp
	
Random.o: Random.cpp Random.h
	$(CC) -m64 -c Random.cpp
	
clean:
	rm -rf ./Main
	rm -rf *.o
	rm -rf *~
	
wipe_data:
	rm -rf *.csv
