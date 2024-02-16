#ifndef HELPERFUNC_H
#define HELPERFUNC_H

struct Time ConvertTime(int time)
{
	struct Time rtrn;
	int temp;

	temp = time % 60;
	rtrn.minute = temp;
	time = time - (temp);
	temp = time;
	rtrn.hour = (temp / 60) % 24;
	temp = time / 1440;
	rtrn.days = temp;

	return rtrn;
}

/*Function that returns a functional value between 1 and 5 for arguments between 0 and 1, with a plateu at 2,*/
double distribFunc(double rand)
{

	double func;

	func = pow((rand - 0.4), 3.0) * 16.0 + 2.0;

	return func;
}

double distribFunc2(double rand)
{

	double func;

	func = pow((rand - 0.5), 3.0) * 16.0 + 3;

	return func;
}

/*Yup, math.h has no rounding function SMH*/
double round(double x)
{

	double remainder;

	remainder = x - floor(x);

	if (remainder >= 0.5)
	{

		x = ceil(x);
	}
	else
	{

		x = floor(x);
	}

	return x;
}

#endif
