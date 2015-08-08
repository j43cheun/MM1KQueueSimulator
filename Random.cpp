#include "Random.h"
#include <stdlib.h>
#include "math.h"

void seed( const int seedArg )
{
	srand( seedArg );
}

double generateExponentialRandomVariable( const double parameter )
{
	const double pseudoRandomValue = static_cast<double>( rand() ) + 1.0;
	const double probability = pseudoRandomValue / ( static_cast<double>( RAND_MAX ) + 1.0 );
	const double pseudoExponentialRandomVariable = -log( probability ) / parameter;
	return pseudoExponentialRandomVariable;
}

double exponentialIdealExpectedValue( const double parameter )
{
	return 1.0 / parameter;
}

double exponentialIdealVariance( const double parameter )
{
	return 1.0 / pow( parameter, 2 );
}

double actualExpectedValue( const double argv[], const int cardinality )
{
	double sum = 0;
	for ( int idx = 0; idx < cardinality; idx++ )
	{
		sum += argv[idx];
	}
	const double expectedValue = sum / cardinality;
	return expectedValue;
}

double actualVariance( const double argv[], const int cardinality )
{
	double sum = 0;
	const double expectedValue = actualExpectedValue( argv, cardinality );
	for ( int idx = 0; idx < cardinality; idx++ )
	{
		sum += pow( argv[idx] - expectedValue, 2 );
	}
	const double variance = sum / cardinality;
	return variance;
}