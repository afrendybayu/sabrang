
#include "lpc23xx.h"
#include "init.h"


void gpio_init()	{
	// paksa PINSEL untuk GPIO //
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	PINSEL2 = 0x00000000;
	PINSEL3 = 0x00000000;
	PINSEL4 = 0x00000000;
	PINSEL5 = 0x00000000;
	PINSEL6 = 0x00000000;
	PINSEL7 = 0x00000000;
	PINSEL8 = 0x00000000;
	PINSEL9 = 0x00000000;
	PINSEL10 = 0x00000000;
	
	
	// paksa untuk enable pull up //
	PINMODE0 = 0x00000000;
	PINMODE1 = 0x00000000;
	PINMODE2 = 0x00000000;
	PINMODE3 = 0x00000000;
	PINMODE4 = 0x00000000;
	PINMODE5 = 0x00000000;
	PINMODE6 = 0x00000000;
	PINMODE7 = 0x00000000;
	PINMODE8 = 0x00000000;
}


void sysInit(void)	{

	#if 1
	// Disable the PLL. //
	PLLCON = 0;							// 0 = PLL dimatikan dulu
	PLLFEED = mainPLL_FEED_BYTE1;		// 0xAA
	PLLFEED = mainPLL_FEED_BYTE2;		// 0x55
	
	// Configure clock source. //				// SCS = system control dan status register 
//	pakai internal RC saja
//	SCS |= mainOSC_ENABLE;						// mainOSC_ENABLE = 0x20, Hal 42	==> Untuk Kristal External
//	while( !( SCS & mainOSC_STAT ) );			// 
//	CLKSRCSEL = mainOSC_SELECT; 				// mainOSC_SELECT = 0x01 ==> 
	
	// Setup the PLL to multiply the XTAL input by 4. //
	PLLCFG = ( mainPLL_MUL | mainPLL_DIV );		// set fcc jd 480 MHz
	PLLFEED = mainPLL_FEED_BYTE1;
	PLLFEED = mainPLL_FEED_BYTE2;

	// Turn on and wait for the PLL to lock... //
	PLLCON = mainPLL_ENABLE;					// mainPLL_ENABLE = 0x01
	PLLFEED = mainPLL_FEED_BYTE1;
	PLLFEED = mainPLL_FEED_BYTE2;

	CCLKCFG = mainCPU_CLK_DIV;					// mainCPU_CLK_DIV = 8
	while( !( PLLSTAT & mainPLL_LOCK ) );
	
	// Connecting the clock. //
	PLLCON = mainPLL_CONNECT;					// mainPLL_CONNECT = 0x02 | 0x01
	PLLFEED = mainPLL_FEED_BYTE1;
	PLLFEED = mainPLL_FEED_BYTE2;
	while( !( PLLSTAT & mainPLL_CONNECTED ) ); 
	#endif
	/* 
	This code is commented out as the MAM does not work on the original revision
	LPC2368 chips.  If using Rev B chips then you can increase the speed though
	the use of the MAM.
	
	Setup and turn on the MAM.  Three cycle access is used due to the fast
	PLL used.  It is possible faster overall performance could be obtained by
	tuning the MAM and PLL settings.
	*/
	#if 1
	MAMCR = 0;
	//MAMTIM = mainMAM_TIM_3;			// MAMTIM=1 --> 20MHz, MAMTIM=2 --> 40MHz, MAMTIM=3 >40MHz, MAMTIM=4 >=60MHz
	MAMTIM = mainMAM_TIM_4;				// 
	MAMCR = mainMAM_MODE_FULL;
	#endif
}

void init()		{
	sysInit();
	gpio_init();
	
	PCLKSEL0 = 0x55555555;		// PCLK is the same as CCLK
	PCLKSEL1 = 0x55555555;
	
	PCONP   |= 0x80000000;
	FIO1DIR  = 0xFFFFFFFF;

	/* USB Power dinyalakan supaya memory USB bisa dipakai */
	//PCONP   |= 0x80000000;
	//FIO1DIR  = 0xFFFFFFFF;
	SCS 	|= (1<<0); 				// fast mode for port 0 and 1
	MEMMAP = 0x01;					// SCB
	
	
	//blink_led();
}
