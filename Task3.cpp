#include <iostream>
#include <random>
#include <ctime>

using namespace std;

const int LAPTOP_PRICE = 450;
const int STORAGE_COST = 50;
const int UNSATISFIED_CUSTOMER_COST = 100;

void model(const int&);
int generate_demand(default_random_engine&);

int main()
{
	int number_of_weeks = 0;
	cout << "Enter The Number of Weeks :";
	cin >> number_of_weeks;

	model(number_of_weeks);
	system("Pause");
	return 0;
}

void model(const int& num_of_weeks)
{
	for (int weekly_order = 1; weekly_order <= 2; weekly_order++)
	{
		default_random_engine generator;
		generator.seed(13);
		
		long double average_profit = 0;
		int weekly_demand = 0;
		int current_storage = 0;

		for (int i = 0; i < num_of_weeks; i++)
		{
			double weekly_profit = 0;
			current_storage += weekly_order;
			weekly_demand = generate_demand(generator);
			
			if (weekly_demand > current_storage)
			{
				int diff = weekly_demand - current_storage;
				weekly_profit +=  current_storage * LAPTOP_PRICE;
				weekly_profit -= diff * UNSATISFIED_CUSTOMER_COST;
				current_storage = 0;
			}
			else if (current_storage > weekly_demand)
			{
				int diff = current_storage - weekly_demand;
				weekly_profit += weekly_demand * LAPTOP_PRICE;
				weekly_profit -= diff * STORAGE_COST;
				current_storage = diff;	
			}
			else
			{
				weekly_profit += weekly_demand * LAPTOP_PRICE;
				current_storage = 0;
			}
			average_profit += weekly_profit;
			//cout << "Generated Demand :" << weekly_demand << endl;
			//cout << "Weekly Profit :" << weekly_profit << endl;
		}
		average_profit = average_profit / num_of_weeks;
		cout << "Average Profit When " << weekly_order << " Laptop Ordered Per Week IS :"
			 << average_profit << endl;
	}
}
int generate_demand(default_random_engine& generator)
{
	uniform_real_distribution<double> dist(0, 1);
	double random = dist(generator);
	if (random >= 0 && random < 0.2)
	{
		return 0;
	}
	else if (random >= 0.2 && random < 0.6)
	{
		return 1;
	}
	else if (random >= 0.6 && random < 0.8)
	{
		return 2;
	}
	else if(random >= 0.8 && random < 0.9)
	{
		return 3;
	}
	else if (random >= 0.9 && random < 1)
	{
		return 4;
	}
}