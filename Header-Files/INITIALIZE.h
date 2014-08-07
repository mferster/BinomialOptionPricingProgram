//Mathieu Ferster
//Initialize.h
//07/11/07
#include<math.h>

class Initialize
{
public:
	Initialize();
	int gtimestep();
	double gstockvalue();
	double grate();
	double gstrike();
	double gvolatility();
	double gdivyield();
	double gexpire();
	double gcash();
	////////////////////////////calculations
	double gsteplength() {steplength=expire/timestep;	return steplength;}
	double gv() {v=volatility*sqrt(steplength);			return v;}
	double ga() {a=exp((rate-divyield)*steplength);		return a;}
	double gp() {return (a-exp(-v))/(exp(v)-exp(-v));}
	double gb() {return exp(-rate*steplength);}

private:
	int timestep;
	double stockvalue, rate, strike, volatility, divyield, expire, cash;
	/////////////////////////////calculations
	double steplength, v, a, p, b;
	
};
