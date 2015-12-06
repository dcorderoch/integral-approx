#include <stdio.h> //better precision print than std::cout
#include <math.h>
#include <iostream>
#include <deque>

#define PI 3.14

using namespace std;

// a function pointer is used instead of an abstract class
// due to C++ not compiling with an abstract class
// as the argument/parameter for a method

class Integration //abstract class
{
public:
	virtual ~Integration()
	{
	}                     //avoid memleaks
	virtual void setIntervalLength(double pIntervalLength) = 0;
	virtual void integrationInterval(double pInfLimit, double pSupLimit) = 0;
	//this function would make the program not compile
	//if used with an abstract class, so instead
	//a function pointer was used
	virtual void setFunction(double (*pIntegrand)(double)) = 0;
	virtual double exactIntegral() const= 0;
};

class simpson : public Integration
{
private:
	double _SetStart; //interval inferior limit
	double _SetEnd; //interval superior limit
	double _SetIntervalLength; //length of divisions
	double (*_Integrand)(double);
public:
	simpson()
	{
		_SetStart = 0;
		_SetEnd = 0;
		_SetIntervalLength = 0;
	}
	void setFunction(double (*pIntegrand)(double))
	{
		_Integrand = pIntegrand;
	}
	void setIntervalLength(double pIntervalLength)
	{
		_SetIntervalLength = pIntervalLength;
	}
	void integrationInterval(double pInfLimit, double pSupLimit)
	{
		_SetStart = pInfLimit;
		_SetEnd = pSupLimit;
	}

	double exactIntegral() const
	{
		double _ReturnVal = 0;
		double tmpSum = _SetStart;
		double tmpsumReturn = 0;
		while( tmpSum <= _SetEnd )
		{
			tmpsumReturn = _Integrand(tmpSum);
			tmpsumReturn += 4*_Integrand((2*tmpSum + _SetIntervalLength)/2.0);
			tmpsumReturn += _Integrand(tmpSum + _SetIntervalLength);
			//setIntervalLength is b-a
			tmpsumReturn = tmpsumReturn * _SetIntervalLength;
			tmpsumReturn = tmpsumReturn / 6.0;
			tmpSum +=_SetIntervalLength;
			_ReturnVal += tmpsumReturn;
		}
		return _ReturnVal;
	}
};

class trapezoidal : public Integration
{
private:
	double _SetStart; //interval inferior limit
	double _SetEnd; //interval superior limit
	double _SetIntervalLength; //length of divisions
	double (*_Integrand)(double);
public:
	trapezoidal()
	{
		_SetStart = 0;
		_SetEnd = 0;
		_SetIntervalLength = 0;
	}
	void setFunction(double (*pIntegrand)(double))
	{
		_Integrand = pIntegrand;
	}
	void setIntervalLength(double pIntervalLength)
	{
		_SetIntervalLength = pIntervalLength;
	}
	void integrationInterval(double pInfLimit, double pSupLimit)
	{
		_SetStart = pInfLimit;
		_SetEnd = pSupLimit;
	}
	double exactIntegral() const
	{
		double _ReturnVal = 0;
		double tmpSum = _SetStart;
		double tmpsumReturn = 0;
		while( tmpSum <= _SetEnd )
		{
			tmpsumReturn = _Integrand(tmpSum);
			tmpsumReturn += _Integrand(tmpSum + _SetIntervalLength);
			//setIntervalLength is b-a
			tmpsumReturn = tmpsumReturn * _SetIntervalLength;
			tmpsumReturn = tmpsumReturn / 2.0;
			tmpSum +=_SetIntervalLength;
			_ReturnVal += tmpsumReturn;
		}
		return _ReturnVal;
	}
};

double poli(double pXpoint)
{
	double _ReturnVal = 2 * pow(pXpoint,2) + 5;
	return _ReturnVal;
}

double sinfoo(double pXpoint)
{
	double _ReturnVal = pXpoint * sin(pXpoint) / PI;
	return _ReturnVal;
}

int main()
{
	printf("start test\n");
	Integration * test = new trapezoidal();
	Integration * test2 = new simpson();

	test->integrationInterval(-3.0,13.0);
	test->setIntervalLength(0.005);
	test->setFunction(&poli);
	printf("%f\n",test->exactIntegral());

	test2->integrationInterval(-3.0,13.0);
	test2->setIntervalLength(0.005);
	test2->setFunction(&poli);
	printf("%f\n",test2->exactIntegral());

	test->integrationInterval(0,2*PI);
	test->setIntervalLength(0.001);
	test->setFunction(&sinfoo);
	printf("%f\n",test->exactIntegral());

	test2->integrationInterval(0,2*PI);
	test2->setIntervalLength(0.001);
	test2->setFunction(&sinfoo);
	printf("%f\n",test2->exactIntegral());

	printf("end test\n");

	delete test;
	delete test2;
	return 0;
}
