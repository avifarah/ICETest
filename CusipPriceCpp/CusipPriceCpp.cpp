// CusipPriceCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "..\\CusipPriceProcessorCpp\CusipProcessor.h"
#include "FeedExceptionCpp.h"

using namespace std;

int main()
{
	try
	{
		ifstream ifs("CusipPrice1-Good.txt");
		auto cp = CusipProcessor(ifs);
		auto cusip = cp.ReadCusip();
		cout << cusip << endl;

		while (true)
		{
			auto latestPrice = cp.ReadPricesForCusips();
			if (latestPrice == CusipLatestPrice::NoValue) break;
			cout << "Cusip: " << latestPrice.GetCusip() << ", Price: " << latestPrice.GetPrice() << endl;
		}
	}
	catch (FeedExceptionCpp& ex)
	{
		cout << "Exception caught: " << ex.Message << ".  At line: " << ex.CurrentLineCountOfException << endl;
	}

	cout << endl << "Done" << endl << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
