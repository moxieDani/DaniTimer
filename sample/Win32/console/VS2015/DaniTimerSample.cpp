//
//  main.cpp
//  DaniTimerTest
//
//  Created by daniel-kisoon-kwon on 2016. 8. 27..
//  Copyright © 2016 daniel-kisoon-kwon. All rights reserved.
//

#include <iostream>
#include "DaniTimer.h"
#include <windows.h>

using namespace std;

#if defined _WIN32 || _WIN64
#include <windows.h>
#define SLEEP(x) Sleep(x*1000)
#else
#include <unistd.h>
#define SLEEP(x) sleep(x)
#endif

#include <iostream>
#include "DaniTimer.h"

using namespace std;

int onTime(unsigned long long milliSec);

int onTime(unsigned long long milliSec)
{
	cout << "onTime : " << milliSec << endl;
	return 0;
}
int main(int argc, const char * argv[]) {
	cout << "Dani Timer test\n";

	DaniTimer timer;
	if (0 == timer.setOnTime(onTime) )
		cout << "========== setOnTime ========== " << endl;
	else
		cout << "Start Error" << endl;

	if (0 == timer.start())
		cout << "========== Dani Timer started! ========== " << endl;
	else
		cout << "Start Error" << endl;

	SLEEP(3);
	if (0 == timer.reset())
		cout << "========== Dani Timer reset! ==========" << endl;
	else
		cout << "Reset Error!" << endl;
	
	return 0;
}
