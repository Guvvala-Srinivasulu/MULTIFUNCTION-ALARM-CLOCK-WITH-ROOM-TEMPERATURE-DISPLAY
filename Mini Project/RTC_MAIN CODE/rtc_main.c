#include "HEADERS.h"

s32 hour,min,sec,date,month,year,day;

// Main function
int main()
{
	RTC_Init();
	Init_INT();
	Init_LCD();
	Init_KPM();
	Init_ADC();
	
  // Set the initial time (hours, minutes, seconds)
	/*SetRTCTimeInfo(19,30,00);
	SetRTCDateInfo(18,10,2025);*/
	//SetRTCDay(5);
	

  while (1) 
	{
    // Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
		displayAlaramactive();
	  TempDisplay();
		Displaytemperature();
	}
}

