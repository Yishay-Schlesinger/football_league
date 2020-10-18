#include "football_league_headers.h"
#include <iostream>
using namespace std;

int main()
{
	League* league = new League;
	initializingLeague(*league);
	while (!operate(*league))
	{
		cout << "\n";
	}
	cout << "Goodbye!\n\n";
}