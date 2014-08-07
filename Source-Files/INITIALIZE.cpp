#include<iostream>
#include"Initialize.h"


using namespace std;

Initialize::Initialize()
{
	/*
	timestep=0;
	stockvalue=0;
	rate=0;
	strike=0;
	volatility=0;
	divyield=0;
	expire=0;
	cash=0;
	
	steplength=0;
	v=0;
	a=0;
	p=0;
	b=0;
	*/
}
double Initialize::gstockvalue() 
{
	cout<<"Enter Initial stock price: ";
	cin>>stockvalue;
	if(stockvalue<0)
		cout<<"Error!!!\n";
	return stockvalue;
}
int Initialize::gtimestep() 
{
	cout<<"Enter timestep: ";
	cin>>timestep;
	if(timestep<=0)
		cout<<"Error!!!\n";
	return timestep;
}
double Initialize::grate() 
{
	cout<<"Enter risk-free rate of return (as a decimal): ";
	cin>>rate;
	if(rate<0)
		cout<<"Error!!!\n";
	return rate;
}
double Initialize::gstrike() 
{
	cout<<"Enter strike price: ";
	cin>>strike;
	if(strike<0)
		cout<<"Error!!!\n";
	return strike;
}
double Initialize::gvolatility() 
{
	cout<<"Enter volatility (as a decimal): ";
	cin>>volatility;
	if(volatility<0)
		cout<<"Error!!!\n";
	return volatility;
}
double Initialize::gdivyield() 
{
	cout<<"Enter dividend yield (as a decimal): ";
	cin>>divyield;
	if(divyield<0)
		cout<<"Error!!!\n";
	return divyield;
}
double Initialize::gexpire() 
{
	cout<<"Enter expiration date (in years): ";
	cin>>expire;
	if(expire<0)
		cout<<"Error!!!\n";
	return expire;
}
double Initialize::gcash() 
{
	cout<<"Enter Cash Amount ";							
	cin>>cash;
	if(cash<0)
		cout<<"Error!!!\n";
	return cash;
}

