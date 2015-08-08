# ECE 358 Project 1 - Queue Simulation Makefile
# 
# Name: Justin Cheung
# Program: 3B Computer Engineering
# Student ID: 20390063
# UW Email Address: j43cheun@uwaterloo.ca
# Course: ECE 358 - Computer Networks

##############################################################################
0. Introduction
##############################################################################

The instructions below explain how to do the following:
- Compiling the Queue Simulator project
- Running Question 1
- Running Question 3
- Running Question 4
- Running Question 6 Part 1
- Running Question 6 Part 2
- Clearing object files from project directory
- Clearing CSV files from project directory

With the exception of Question 1, simulations for the other questions in the
lab manual will generate an output CSV file. There is one CSV file for each
Question (except Question 1, which does not generate a CSV file). In addition
the file path and naming of each CSV file is specified in the makefile macros.
In general, the generated CSV files will also be placed into the project
directory so everything is in one place. The filename of each CSV file will
directly specify which question or which question part it came from.

###############################################################################
1. Compiling the Queue Simulator project
###############################################################################
 
Requirements:

The makefile for this Queue Simulator project as been configured to compile on
ECE Linux 4 as an x64 console application (due to memory requirements).

Compiling the Queue Simulator project:

To compile the Queue Simulator project, simply open a terminal instance and  
navigate into the project directory in which all header files and source 
files for the Queue Simulator project are contained (they are all contained 
within the same directory).Then run the following command:

	make
	
Warning:

This step must be performed first before any simulations specified below can
be run.
	
###############################################################################
2. Running Question 1
###############################################################################

Requirements:

Before running Question 1,the Queue Simulator project must be compiled at least
once such that there is an executable called "Main" in the project directory.
Before running Question 6 Part 1,the Queue Simulator project must be compiled
at least once such that there is an executable called "Main" in the project 
directory.

Running Question 1:
optimized
To run the simulation for Question 1, open a terminal instance and navigate
into the project directory. Then run the following command:

	make q1
	
The Ideal Expected Value, Ideal Variance, Actual Expected Value and Actual
Variance will be output to the console at the end of the simulation.
	
###############################################################################
2. Running Question 3
###############################################################################

Requirements:

Before running Question 3,the Queue Simulator project must be compiled at least
once such that there is an executable called "Main" in the project directory.

Running Question 3:

This simulation deals with part Question 3 parts 1 and 2 in the lab manual. To
run the simulation for Question 3, open a terminal and navigate into the project
directory. Then run the following command:

	make q3
	
During the simulation, a CSV file will be generated (see Q3_FILEPATH macro in 
makefile for the file path of this CSV file). The CSV file in question will 
contain data gathered from the simulation of Question 3 and can be used to 
verify the functions required in Question 3 of the lab manual. If the file
already exists, the data will be appended to the existing file. The data will 
also be output to the console.
	
###############################################################################
2. Running Question 4
###############################################################################

Requirements:

Before running Question 4,the Queue Simulator project must be compiled at least
once such that there is an executable called "Main" in the project directory.

Running Question 4:

To run the simulation for Question 4, open a terminal instance and navigate to
the project directory. Then run the following command:

	make q4
	
During the simulation, a CSV file will be generated (see Q4_FILEPATH macro in 
makefile for the file path of this CSV file). The CSV file in question will 
contain data gathered from the simulation of Question 4 and can be used to 
verify the functions required in Question 4 of the lab manual. If the file
already exists, the data will be appended to the existing file. The data will 
also be output to the console.

###############################################################################
3. Running Question 6 Part 1
###############################################################################

Requirements:

Before running Question 6 Part 1,the Queue Simulator project must be compiled
at least once such that there is an executable called "Main" in the project 
directory.

Running Question 6 Part 1:

To run the simulation for Question 6 Part 1, open a terminal instance and
navigate to the project directory. Then run the following command:

	make q6p1
	
During the simulation, a CSV file will be generated (see Q6P1_FILEPATH macro in 
makefile for the file path of this CSV file). The CSV file in question will 
contain data gathered from the simulation of Question 6 Part 1 and can be used to 
verify the functions required in Question 6 Part 1 of the lab manual. If the file
already exists, the data will be appended to the existing file. The data will 
also be output to the console.

###############################################################################
4. Running Question 6 Part 2
###############################################################################

Requirements:

Before running Question 6 Part 2,the Queue Simulator project must be compiled
at least once such that there is an executable called "Main" in the project 
directory.

Running Question 6 Part 2:

To run the simulation for Question 6 Part 2, open a terminal instance and
navigate to the project directory. Then run the following command:

	make q6p2
	
During the simulation, a CSV file will be generated (see Q6P2_FILEPATH macro in 
makefile for the file path of this CSV file). The CSV file in question will 
contain data gathered from the simulation of Question 6 Part 2 and can be used to 
verify the functions required in Question 6 Part 1 of the lab manual. If the file
already exists, the data will be appended to the existing file. The data will 
also be output to the console.

###############################################################################
5. Clearing object files from project directory
###############################################################################

To clear all object files from the project directory, open a terminal instance
and navigate to the project directory. Then run the following command:

	make clean
	
###############################################################################
6. Clearing CSV files from project directory
###############################################################################

To clear all CSV files from the project directory, open a terminal instance
and navigate to the project directory. Then run the following command:

	make wipe_data

