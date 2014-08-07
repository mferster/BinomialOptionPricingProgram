// BinomialOption.cpp : Defines the entry point for the application.
//
//Mathieu Ferster
#include<iostream>
#include<math.h>
#include"Initialize.h"
#include"Payoff.h"


using namespace std;

//Displays the option pricing menu and quit option. 
int menu(void);

//Collects the stock data from the user
void initialize(double &stockvalue, double &rate, double &strike, double&volatility,
			double &divyield, double &expire, int &timestep, int &choice, double &cash, Initialize &data);

//Inserts a new node into the Tree
void insert(Payoff* &so,const double v,int count,const double stockvalue,int timestep,
			const double strike,const int choice,const double cash);

//Creates a new node on the Payoff tree
inline void newnode(Payoff* &so,double volatility,int count,int timestep,
			const double strike,const int choice,const double cash);

//Calculates option price given root of binary tree which points to complete Payoff function
void optionval(Payoff* &so,int count,int timestep,double b, double p,
			   const double strike,const int choice,const double cash);


int main()
{
	int choice=0;					// choice=menu selection
	int timestep;					// the amount of timesteps or the depth of the tree
	int count=0;					// step number, used to traverse binary tree
	double stockvalue;				// stock value at time t=0
	double expire;					// expiration date
	double rate;					// risk-free rate of return
	double cash=1;					// cash=cash payoff
	double divyield;				// divident yield
	double volatility;				// volatility of the stock
	double strike;					// the strike price on the option
	
	Initialize data;
	do
	{ 
		choice=menu();									//choose option to price or Quit
		if(choice<7 && choice>0)
		{
			initialize(stockvalue, rate, strike, volatility, divyield, expire, timestep, choice, cash, data);
													// Calculates:
			double steplen=data.gsteplength();		// length of each step      
			double v=data.gv();						// the volitility of the stock
			double a=data.ga();						// ratio of stock:option to hedge position
			const double p=data.gp();				// probability stock will go up
			const double b=data.gb();				// discount for option price

			Payoff *so=new Payoff; 					// pointer to root of the Payoff f(x) 
	                                             
			insert(so,v,count,stockvalue,timestep,strike,choice,cash);//inserts stock node into binomial tree
			optionval(so,count,timestep,b,p,strike,choice,cash);//calculates the option value

			delete so;
		}
	}while(choice<7 && choice>0);					// 1-6 select the option, or else quit

	return 0;
}

//Displays the option pricing menu and quit option. 
int menu(void)
{
	int choice;
	cout<<"\nChoose Option Type\n";
	cout<<"1. European Vanilla call option\n";
	cout<<"2. American Vanilla call option\n";
	cout<<"3. European digital asset-or-nothing option\n";
	cout<<"4. American digital asset-or-nothing option\n";
	cout<<"5. European digital cash-or-nothing option\n";
	cout<<"6. American digital cash-or-nothing option\n";
	cout<<"7. Quit the program --> ";
	cin>>choice;
	return choice;
}

//Collects the stock data from the user
void initialize(double &stockvalue, double &rate, double &strike, double&volatility,
			double &divyield, double &expire, int &timestep, int &choice, double &cash, Initialize &data)
{
	stockvalue=data.gstockvalue();
	rate=data.grate();
	strike=data.gstrike();
	volatility=data.gvolatility();
	divyield=data.gdivyield();
	expire=data.gexpire();
	timestep=data.gtimestep();

	if(choice==5||choice==6)
		cash=data.gcash();
}

//Inserts a new node into the Tree
void insert(Payoff* &so,const double v,int count,const double stockvalue,int timestep,
			const double strike,const int choice,const double cash)
{
	newnode(so,stockvalue,count,timestep,strike,choice,cash);	// creates new node

	if(count==timestep)											//for final leaf of tree
		return;

	insert(so->left,v,count+1,stockvalue*exp(-v),timestep,strike,choice,cash);//up/down-state of stock 
	insert(so->right,v,count+1,stockvalue*exp(v),timestep,strike,choice,cash);//price calculated here
}

//Creates a new node on the Payoff tree
inline void newnode(Payoff* &so,double stockvalue,int count,int timestep,
			const double strike,const int choice,const double cash)
{
	Payoff *newprice= new Payoff();
	
	newprice->sp=stockvalue;  
	newprice->value=0;
	so=newprice;
	if(count==timestep&&(so->sp)>strike)
	{													//sets option value on terminal leaves
		if(choice==1||choice==2)						
			so->value=so->sp-strike;					//for vanilla call
		if(choice==3||choice==4)
			so->value=so->sp;							//for asset-or-nothing
		if(choice==5||choice==6)
			so->value=cash;
	}
}

//Calculates option price given root of binary tree which points to complete Payoff function
//count=step number 
//b=exp^(-rate*steplenght)		
//p=probability stock will move to up-state
void optionval(Payoff* &so,int count,int timestep,double b, double p,
			   const double strike,const int choice,const double cash)
{
	if(count==timestep)						//tree traversal begins at root, but we must start from the terminal leaves
		return;
	optionval(so->left,count+1,timestep,b,p,strike,choice,cash);	//traverses tree in Postorder
	optionval(so->right,count+1,timestep,b,p,strike,choice,cash);
	double val;								//holds option value at each node
	Payoff* X=new Payoff();					//dummy nodes to hold option values for calculation
	Payoff* Y=new Payoff();
	X=so->left;
	Y=so->right;
	val=b*(p*Y->value+(1-p)*X->value);		//calculation
	so->value=val;							//for choice== 1,3, or 5
	if(choice==2)
		if(so->sp-strike>val)				//value is the better of the European Option price
			so->value=so->sp-strike;		//and the exercise value at time t (American vanil)
	if(choice==4)
		if(so->sp>strike)					//value is the better of the European Option price
			so->value=so->sp;				//and the exercise value at time t	(Amer asst-not)
	if(choice==6)
		if(so->sp>strike)					//value is the better of the European Option price
			so->value=cash;					//and the exercise value at time t	(Amer cash-not)
	delete X,Y;
	
	if(count==0)							//print option value
		cout<<"\nOption("<<timestep<<")= "<<so->value<<endl<<endl;
}
