#ifndef RANDOM_H
#define RANDOM_H

void seed( const int seedArg );

double generateExponentialRandomVariable( const double parameter );

double exponentialIdealExpectedValue( const double parameter );

double exponentialIdealVariance( const double parameter );

double actualExpectedValue( const double argv[], const int cardinality );

double actualVariance( const double argv[], const int cardinality );

#endif // RANDOM_H