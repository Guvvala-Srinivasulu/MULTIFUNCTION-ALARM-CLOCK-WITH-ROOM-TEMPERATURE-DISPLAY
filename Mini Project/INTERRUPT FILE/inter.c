#include "HEADERS.h"


#define EINT0_VIC_CHN0 14

void Init_INT(void)
{
  CfgPortPinFunc(0,1,EINT0_0_1);	 
	VICIntEnable = 1<<EINT0_VIC_CHN0;
	VICVectCntl0 = (1<<5)|EINT0_VIC_CHN0;
	VICVectAddr0 = (u32 )eint0_isr;
	EXTMODE = 1<<0;
}

void eint0_isr(void) __irq
{
	u8 key;	

	start_loop:	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.TIME  2.DATE");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("3.ALARM 4.EXIT>");
	
	while(1)
	{
		
		key=KeyScan();
		while(ColScan()==0);
		switch(key)
		{
			case '1':CmdLCD(CLEAR_LCD);
							StrLCD("SETTING TIME....");
							RTC_TimeEdit();
							goto start_loop;
			case '2':CmdLCD(CLEAR_LCD);
							StrLCD("SETTING DATA....");
							RTC_DateEdit();
							goto start_loop;
			case '3':CmdLCD(CLEAR_LCD);
							StrLCD("SETTING ALARM...");
							RTC_AlarmSet();
							goto start_loop;
			case '4':CmdLCD(CLEAR_LCD);
							StrLCD("EXITING MENU....");
							delay_s(1);
				      goto exit_loop;
			default:CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0);
							StrLCD("INVALID KEY");
							delay_s(1);
							goto start_loop;
							
		}	
	}	

exit_loop: 
	EXTINT=1<<0;
	VICVectAddr=0;
	CmdLCD(CLEAR_LCD);
}
