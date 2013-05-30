
#define PLL_MUL				60
#define mainPLL_MUL			( ( unsigned long ) ( PLL_MUL - 1 ) )
#define PLL_DIV				1
#define mainPLL_DIV			( ( unsigned long ) (PLL_DIV - 1) )
#define CLK_DIV				8
#define mainCPU_CLK_DIV		( ( unsigned long ) (CLK_DIV-1) )
#define mainPLL_ENABLE		( ( unsigned long ) 0x0001 )
#define mainPLL_CONNECT		( ( ( unsigned long ) 0x0002 ) | mainPLL_ENABLE )
#define mainPLL_FEED_BYTE1	( ( unsigned long ) 0xaa )
#define mainPLL_FEED_BYTE2	( ( unsigned long ) 0x55 )
#define mainPLL_LOCK		( ( unsigned long ) 0x4000000 )
#define mainPLL_CONNECTED	( ( unsigned long ) 0x2000000 )
#define mainOSC_ENABLE		( ( unsigned long ) 0x20 )
#define mainOSC_STAT		( ( unsigned long ) 0x40 )
#define mainOSC_SELECT		( ( unsigned long ) 0x01 )			// Kristal External 
#define intRC_SELECT		( ( unsigned long ) 0x00 )			// Internal RC	==> CANnet jangan pakai ini
#define RTC_SELECT			( ( unsigned long ) 0x10 )			// RTC

#define mainMAM_TIM_3		( ( unsigned char ) 0x03 )
#define mainMAM_TIM_4		( ( unsigned char ) 0x04 )
#define mainMAM_MODE_FULL	( ( unsigned char ) 0x02 )


#define BIT(x)	(1 << (x))

#define LED_UTAMA		BIT(27)		// 1 << 27

void init(void)	;
void sysInit(void);
void gpio_init(void);
