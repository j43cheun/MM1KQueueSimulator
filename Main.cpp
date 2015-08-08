#include <iostream>
#include <string>
#include <cstdlib>
#include "Questions.h"


int main(int argc, char* argv[])
{	
	if ( argc > 1 )
	{
		// Possible simulation options for Project 1.
		const std::string q1_option = "-q1";
		const std::string q3_option = "-q3";
		const std::string q4_option = "-q4";
		const std::string q6_p1_option = "-q6p1";
		const std::string q6_p2_option = "-q6p2";
		
		// Get the simulation option.
		std::string q_option( argv[1] );
		
		if ( q_option.compare( q1_option ) == 0 )
		{
			// Default lambda for Question 1.
			int lambda = 75;
			
			if ( argc > 2 )
			{
				// Grab lambda from program arguments.
				lambda = atoi( argv[2] );
			}
			else
			{
				std::cout << "No lambda parameter was specified for Question 1. Default to lamba = 75." << "\n";
			}
			
			// Run Question 1.
			questionOne( lambda );
		}
		else if ( q_option.compare( q3_option ) == 0 )
		{
			// Default arguments for Question 3.
			std::string filePath = "./question_3_part_1_and_part2_dataset.csv";
			double T = 20000;
			double L = 12000;
			double C = 1000000;
			int K = -1;
			
			if ( argc == 7 )
			{
				// Convert file path argument to string.
				std::string filePathArg( argv[2] );
				
				// Assign parameters.
				filePath = filePathArg;
				T = atof( argv[3] );
				L = atof( argv[4] );
				C = atof( argv[5] );
				K = atoi( argv[6] );
			}
			else
			{
				std::cout << "The number of arguments is incorrect. Using default parameters." << "\n";
			}
			
			// Run Question 3.
			questionThree( filePath, T, L, C, K );
		}
		else if ( q_option.compare( q4_option ) == 0 )
		{
			// Default arguments for Question 4.
			std::string filePath = "./question_4_dataset.csv";
			double T = 20000;
			double L = 12000;
			double C = 1000000;
			int K = -1;
			
			if ( argc == 7 )
			{
				// Convert file path argument to string.
				std::string filePathArg( argv[2] );
				
				// Assign parameters.
				filePath = filePathArg;
				T = atof( argv[3] );
				L = atof( argv[4] );
				C = atof( argv[5] );
				K = atoi( argv[6] );
			}
			else
			{
				std::cout << "The number of arguments is incorrect. Using default parameters." << "\n";
			}
			
			// Run Question 4.
			questionFour( filePath, T, L, C, K );
		}
		else if ( q_option.compare( q6_p1_option ) == 0 )
		{
			// Default arguments for Question 6 Part 1.
			std::string filePath = "./question_6_part_1_dataset.csv";
			double T = 20000;
			double L = 12000;
			double C = 1000000;
			int K_1 = 5;
			int K_2 = 10;
			int K_3 = 40;
			
			if ( argc == 9 )
			{
				// Convert file path argument to string.
				std::string filePathArg( argv[2] );
				
				// Assign parameters.
				filePath = filePathArg;
				T = atof( argv[3] );
				L = atof( argv[4] );
				C = atof( argv[5] );
				K_1 = atoi( argv[6] );
				K_2 = atoi( argv[7] );
				K_3 = atoi( argv[8] );
			}
			else
			{
				std::cout << "The number of arguments is incorrect. Using default parameters." << "\n";
			}
			
			// Run Question 6 Part 1.
			questionSixPartOne( filePath, T, L, C, K_1, K_2, K_3 );
		}
		else if ( q_option.compare( q6_p2_option ) == 0 )
		{
			// Default arguments for Question 6 Part 2.
			std::string filePath = "./question_6_part_2_dataset.csv";
			double T = 10000;
			double L = 12000;
			double C = 1000000;
			int K_1 = 5;
			int K_2 = 10;
			int K_3 = 40;
			
			if ( argc == 9 )
			{
				// Convert file path argument to string.
				std::string filePathArg( argv[2] );
				
				// Assign parameters.
				filePath = filePathArg;
				T = atof( argv[3] );
				L = atof( argv[4] );
				C = atof( argv[5] );
				K_1 = atoi( argv[6] );
				K_2 = atoi( argv[7] );
				K_3 = atoi( argv[8] );
			}
			else
			{
				std::cout << "The number of arguments is incorrect. Using default parameters." << "\n";
			}
			
			// Run Question 6 Part 2.
			questionSixPartTwo( filePath, T, L, C, K_1, K_2, K_3 );
		}
		else
		{
			std::cout << "The specified simulation option does not exist. Exitting..." << "\n";
		}
	}
	else
	{
		std::cout << "No simulation options were specified. Exitting..." << "\n";
	}
	
	return 0;
}
