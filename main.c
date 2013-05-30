
#include "lpc23xx.h"
#include "init.h"

void dele(int dd)	{
	int g;
	int i;
	int dum;
		for (i=0; i<dd; i++)	{
		dum = FIO0DIR;
	}
}

		

int main( void )	{
	init();
	
	FIO0DIR = LED_UTAMA;
	FIO0CLR = LED_UTAMA;

	while(1)	{
		dele(1000000);
		FIO0CLR = LED_UTAMA;
		dele(1000000);
		FIO0SET = LED_UTAMA;
	}

	
	return 0;

}
