#include "Questions.h"
#include "Random.h"
#include "time.h"
#include <iostream>
#include "Event.h"
#include "Log.h"
#include <string>

void questionOne( const int lambda )
{
	const int cardinality = 1000;
	double values[cardinality];

	seed( static_cast<int>( time( NULL ) ) );
	
	for ( int idx = 0; idx < cardinality; idx++ )
	{
		values[idx] = generateExponentialRandomVariable( lambda );
	}

	std::cout << "##### Question 1 ##############################################################" << "\n";
	std::cout << "\n";
	std::cout << "Distribution          = " << "Exponential" << "\n";
	std::cout << "Lambda                = " << lambda << "\n";
	std::cout << "\n";
	std::cout << "Cardinality           = " << cardinality << "\n";
	std::cout << "\n";
	std::cout << "Ideal Expected Value  = " << exponentialIdealExpectedValue( lambda ) << "\n";
	std::cout << "Actual Expected Value = " << actualExpectedValue( values, cardinality ) << "\n";
	std::cout << "\n";
	std::cout << "Ideal Variance        = " << exponentialIdealVariance( lambda ) << "\n";
	std::cout << "Actual Variance       = " << actualVariance( values, cardinality ) << "\n";
	std::cout << "\n";
	std::cout << "###############################################################################" << "\n";
}

void questionThree( const std::string filePath, const double T, const double L, const double C, const int K )
{
	// Test Iteration Parameters.
	const double lowerBound = 0.25;
	const double upperBound = 0.95;
	const double stepSize = 0.1;
	
	// Print question header containing test parameters to console.
	std::cout << "##### Question 3 ##############################################################" << "\n";
	std::cout << "\n";
	std::cout << "Parameters:" << "\n";
	std::cout << "\n";
	std::cout << "T                         = " << T << " seconds" << "\n";
	std::cout << "L                         = " << L << " bits" << "\n";
	std::cout << "C                         = " << C << " bits per second" << "\n";
	std::cout << "K                         = " << K << " packets" << "\n";
	std::cout << "Lower bound on rho        = " << lowerBound << "\n";
	std::cout << "Upper bound on rho        = " << upperBound << "\n";
	std::cout << "Step size                 = " << stepSize << "\n";
	std::cout << "\n";
	std::cout << "Note: K = -1 implies that the buffer is unbounded." << "\n";
	std::cout << "\n";
	
	// Initialize rho.
	double rho = lowerBound;

	// Get instance of Logger singleton.
	Logger* instance = Logger::getInstance();
	instance->setFilePath( filePath );

	// Insert data title.
	std::string title[1];
	title[0] = "Question 3 Dataset (Part 1 and Part 2) for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	std::string tableHeadings[6];
	tableHeadings[0] = "Rho";
	tableHeadings[1] = "Lambda";
	tableHeadings[2] = "Alpha";
	tableHeadings[3] = "E[N]";
	tableHeadings[4] = "Pidle";
	tableHeadings[5] = "Ploss";
	instance->csvLog(tableHeadings, 6);

	// Simulate and gather test data.
	while ( rho <= upperBound )
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler( T, lambda, L, alpha, C, K );
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;
	}

	std::cout << "###############################################################################" << "\n";
	
	// Insert new line into log.
	instance->insertNewLine();
	
	// Delete memory allocated to Logger singleton instance.
	delete instance;
}

void questionFour( std::string filePath, const double T, const double L, const double C, const int K )
{
	// Define constant test parameters.
	const double rho = 1.2;
	double lambda = rho * C / L;
	double alpha = lambda * 8;
	
	// Get instance of Logger singleton.
	Logger* instance = Logger::getInstance();
	instance->setFilePath( filePath );

	// Insert data title.
	std::string title[1];
	title[0] = "Question 4 Dataset for T = " + doubleToString(T) +
	std::string(" seconds / L = ") + doubleToString(L) +
	std::string(" bits / C = ") + doubleToString(C) +
	std::string(" bps / K = ") + intToString(K) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	std::string tableHeadings[6];
	tableHeadings[0] = "Rho";
	tableHeadings[1] = "Lambda";
	tableHeadings[2] = "Alpha";
	tableHeadings[3] = "E[N]";
	tableHeadings[4] = "Pidle";
	tableHeadings[5] = "Ploss";
	instance->csvLog(tableHeadings, 6);

	// Print question header containing test parameters to console.
	std::cout << "##### Question 4 ##############################################################" << "\n";
	std::cout << "\n";
	std::cout << "Parameters:" << "\n";
	std::cout << "\n";
	std::cout << "T                         = " << T << " seconds" << "\n";
	std::cout << "L                         = " << L << " bits" << "\n";
	std::cout << "C                         = " << C << " bits per second" << "\n";
	std::cout << "K                         = " << K << " packets" << "\n";
	std::cout << "\n";
	std::cout << "Note: K = -1 implies that the buffer is unbounded." << "\n";
	std::cout << "--------------------------------------------------------------------------------" << "\n";
	std::cout << "Rho    = " << rho << "\n";
	std::cout << "Alpha  = " << alpha << "\n";
	std::cout << "Lambda = " << lambda << "\n";
	EventScheduler* eventScheduler = new EventScheduler( T, lambda, L, alpha, C, K );
	eventScheduler->simulate();
	std::cout << "\n";
	
	delete instance;
	delete eventScheduler;
}

void questionSixPartTwo( const std::string filePath , const double T, const double L, const double C, const int K_1, const int K_2, const int K_3 )
{
	// Test iteration parameters.
	const double lowerBound = 0.4;
	const double intermediateBound1 = 2;
	const double intermediateBound2 = 5;
	const double upperBound = 10;
	const double stepSize1 = 0.1;
	const double stepSize2 = 0.2;
	const double stepSize3 = 0.4;
	
	
	std::cout << "##### Question 6 Part 2 #######################################################" << "\n";
	std::cout << "\n";
	std::cout << "Parameters:" << "\n";
	std::cout << "\n";
	std::cout << "T                           = " << T << " seconds" << "\n";
	std::cout << "L                           = " << L << " bits" << "\n";
	std::cout << "C                           = " << C << " bits per second" << "\n";
	std::cout << "Lower bound on rho          = " << lowerBound << "\n";
	std::cout << "Step size 1                 = " << stepSize1 << "\n";
	std::cout << "Intermediate bound 1 on rho = " << intermediateBound1 << "\n";
	std::cout << "Step size 2                 = " << stepSize2 << "\n";
	std::cout << "Intermediate bound 2 on rho = " << intermediateBound2 << "\n";
	std::cout << "Step size 3                 = " << stepSize3 << "\n";
	std::cout << "Upper bound on rho          = " << upperBound << "\n";
	std::cout << "\n";

	std::cout << "***** K = " + intToString( K_1 ) + " packets ***********************************************************" << "\n";
	
	double rho = lowerBound;

	Logger* instance = Logger::getInstance();
	instance->setFilePath(filePath);

	// Insert data table 1 data.
	std::string title[1];
	title[0] = "Question 6 Part 2 Dataset for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K_1) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	std::string tableHeadings[6];
	tableHeadings[0] = "Rho";
	tableHeadings[1] = "Lambda";
	tableHeadings[2] = "Alpha";
	tableHeadings[3] = "E[N]";
	tableHeadings[4] = "Pidle";
	tableHeadings[5] = "Ploss";
	instance->csvLog(tableHeadings, 6);

	// Initialize step size.
	double stepSize = stepSize1;
	
	// Simulate and gather data.
	while ( static_cast<int>(rho * 10.0) <= static_cast<int>(upperBound * 10.0) )
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler(T, lambda, L, alpha, C, K_1);
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;

		if (static_cast<int>(rho * 10.0) >= static_cast<int>(intermediateBound1 * 10.0) && static_cast<int>(rho * 10.0) < static_cast<int>(intermediateBound2 * 10.0))
		{
			stepSize = stepSize2;
		}
		else if (static_cast<int>(rho * 10.0) >= static_cast<int>(intermediateBound2 * 10.0))
		{
			stepSize = stepSize3;
		}
	}

	// Insert new line in log.
	instance->insertNewLine();

	// Reset rho to lowerbound.
	rho = lowerBound;
	
	std::cout << "***** K = " + intToString(K_2) + " packets ***********************************************************" << "\n";

	// Insert data table 2 data.
	title[0] = "Question 6 Part 2 Dataset for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K_2) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	instance->csvLog(tableHeadings, 6);

	// Reset step size to step size 1.
	stepSize = stepSize1;
	
	// Simulate and gather data.
	while (static_cast<int>(rho * 10.0) <= static_cast<int>(upperBound * 10.0))
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler(T, lambda, L, alpha, C, K_2);
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;

		if (static_cast<int>(rho * 10.0) >= static_cast<int>(intermediateBound1 * 10.0) && static_cast<int>(rho * 10.0) < static_cast<int>(intermediateBound2 * 10.0))
		{
			stepSize = stepSize2;
		}
		else if (static_cast<int>(rho * 10.0) >= static_cast<int>(intermediateBound2 * 10.0))
		{
			stepSize = stepSize3;
		}
	}

	// Insert new line in log.
	instance->insertNewLine();

	// Reset rho to lowerbound.
	rho = lowerBound;

	std::cout << "***** K = " + intToString(K_3) + " packets ***********************************************************" << "\n";

	// Insert data table 2 data.
	title[0] = "Question 6 Part 2 Dataset for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K_3) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	instance->csvLog(tableHeadings, 6);

	// Reset step size to step size 1.
	stepSize = stepSize1;
	
	// Simulate and gather data.
	while (static_cast<int>(rho * 10.0) <= static_cast<int>(upperBound * 10.0))
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler(T, lambda, L, alpha, C, K_3);
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;

		if (static_cast<int>(rho * 10.0) >= static_cast<int>(intermediateBound1 * 10.0) && static_cast<int>(rho * 10.0) < static_cast<int>(intermediateBound2 * 10.0))
		{
			stepSize = stepSize2;
		}
		else if (static_cast<int>(rho * 10.0) >= static_cast<int>(intermediateBound2 * 10.0))
		{
			stepSize = stepSize3;
		}
	}

	// Insert new line in log.
	instance->insertNewLine();
	
	std::cout << "###############################################################################" << "\n";

	// Delete memory allocated to Logger singleton instance.
	delete instance;
}

void questionSixPartOne( const std::string filePath, const double T, const double L, const double C, const int K_1, const int K_2, const int K_3 )
{
	// Test iteration parameters.
	const double lowerBound = 0.5;
	const double upperBound = 1.5;
	const double stepSize = 0.1;
	
	std::cout << "##### Question 6 Part 1 #######################################################" << "\n";
	std::cout << "\n";
	std::cout << "Parameters:" << "\n";
	std::cout << "\n";
	std::cout << "T                         = " << T << " seconds" << "\n";
	std::cout << "L                         = " << L << " bits" << "\n";
	std::cout << "C                         = " << C << " bits per second" << "\n";
	std::cout << "Lower bound on rho        = " << lowerBound << "\n";
	std::cout << "Upper bound on rho        = " << upperBound << "\n";
	std::cout << "Step size                 = " << stepSize << "\n";
	std::cout << "\n";
	std::cout << "***** K = " + intToString(K_1) + " packets ***********************************************************" << "\n";

	double rho = lowerBound;

	Logger* instance = Logger::getInstance();
	instance->setFilePath(filePath);

	// Insert data table 1 data.
	std::string title[1];
	title[0] = "Question 6 Part 1 Dataset for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K_1) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	std::string tableHeadings[6];
	tableHeadings[0] = "Rho";
	tableHeadings[1] = "Lambda";
	tableHeadings[2] = "Alpha";
	tableHeadings[3] = "E[N]";
	tableHeadings[4] = "Pidle";
	tableHeadings[5] = "Ploss";
	instance->csvLog(tableHeadings, 6);

	// Simulate and gather data.
	while (rho < upperBound + stepSize)
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler(T, lambda, L, alpha, C, K_1);
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;
	}

	// Insert new line in log.
	instance->insertNewLine();
	
	// Reset rho to lowerbound.
	rho = lowerBound;

	std::cout << "***** K = " + intToString(K_2) + " packets ***********************************************************" << "\n";

	// Insert data table 2 data.
	title[0] = "Question 6 Part 1 Dataset for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K_2) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	instance->csvLog(tableHeadings, 6);

	// Simulate and gather data.
	while (rho < upperBound + stepSize)
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler(T, lambda, L, alpha, C, K_2);
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;
	}

	// Insert new line in log.
	instance->insertNewLine();

	// Reset rho to lowerbound.
	rho = lowerBound;
	
	std::cout << "***** K = " + intToString(K_3) + " packets ***********************************************************" << "\n";

	// Insert data table 2 data.
	title[0] = "Question 6 Part 1 Dataset for T = " + doubleToString(T) +
		std::string(" seconds / L = ") + doubleToString(L) +
		std::string(" bits / C = ") + doubleToString(C) +
		std::string(" bps / K = ") + intToString(K_3) + std::string(" packets");
	instance->csvLog(title, 1);

	// Insert table headers.
	instance->csvLog(tableHeadings, 6);

	// Simulate and gather data.
	while (rho < upperBound + stepSize)
	{
		double lambda = rho * C / L;
		double alpha = lambda * 8;

		std::cout << "--------------------------------------------------------------------------------" << "\n";
		std::cout << "Rho    = " << rho << "\n";
		std::cout << "Alpha  = " << alpha << "\n";
		std::cout << "Lambda = " << lambda << "\n";

		EventScheduler* eventScheduler = new EventScheduler(T, lambda, L, alpha, C, K_3);
		eventScheduler->simulate();
		delete eventScheduler;
		std::cout << "\n";
		rho += stepSize;
	}

	// Insert new line in log.
	instance->insertNewLine();

	std::cout << "###############################################################################" << "\n";

	// Delete memory allocated to Logger singleton instance.
	delete instance;
}
