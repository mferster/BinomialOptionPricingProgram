class Payoff
{
public:
	Payoff();

	//~Payoff();
	double sp;			//each node has a stock price,
	double value;		//option value,
	Payoff* left;
	Payoff* right;
private:
	
};
