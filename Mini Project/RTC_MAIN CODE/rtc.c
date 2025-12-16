//all headers included in "HEADERS.H" file.....
#include "HEADERS.h"


// Array to hold names of days of the week
s8 week[][4] = {"he11","SUN","MON","TUE","WED","THU","FRI","SAT"};

f32 eAR;
u32 adcDVal;
u32 temperature;
u8 alarm_triggered = 0;
u8 alarm_hour = 0, alarm_min = 0;

/*********************************************************************************/
/*****************  INITIALISING THE RTC TO ENABLE *******************************/
/*********************************************************************************/
void RTC_Init(void) 
{
  
	CCR = RTC_RESET;               // Disable and reset the RTC
	PREINT = PREINT_VAL;           // Set prescaler integer and fractional parts
	PREFRAC = PREFRAC_VAL;
	CCR = RTC_ENABLE | RTC_CLKSRC; // Enable the RTC 
}

/*********************************************************************************/
/********************GETTING TIME TO UPDATE ON LCD********************************/
/*********************************************************************************/

void SetRTCHoursInfo(u32 hour)
{
	HOUR = hour;                  // upadating the hours to sfr
}
void SetRTCMinutesInfo(u32 minute)
{
	MIN = minute;                 // upadating the minutes to sfr
}
void SetRTCSecondsInfo(u32 second)
{
	SEC = second;                 // upadating the seconds to sfr
}

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

void DisplayRTCTime(s32 hour, s32 minute, s32 second)
{
	// upadating the time to LCD.
	CmdLCD(GOTO_LINE1_POS0);
	CharLCD((hour/10)+48);
	CharLCD((hour%10)+48);
	CharLCD(':');
	CharLCD((minute/10)+0x30);
	CharLCD((minute%10)+0x30);
	CharLCD(':');
	CharLCD((second/10)+'0');
	CharLCD((second%10)+'0');

}

/*********************************************************************************/
/********************GETTING DATE TO UPDATE ON LCD********************************/
/*********************************************************************************/

void SetRTCDateInfo(u32 date)
{
	DOM = date;                // upadating the date to sfr
}
void SetRTCMonthInfo(u32 month)
{
	MONTH = month;             // upadating the month to sfr
}
void SetRTCYearInfo(u32 year)
{
	YEAR = year;               // upadating the year to sfr
}

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

void DisplayRTCDate(u32 date, u32 month, u32 year)
{
	// upadating the date to LCD
	CmdLCD(GOTO_LINE2_POS0);
	CharLCD((date/10)+48);
	CharLCD((date%10)+48);
	CharLCD('/');
	CharLCD((month/10)+0x30);
	CharLCD((month%10)+0x30);
	CharLCD('/');
	U32LCD(year);	

}

/*********************************************************************************/
/*********************GETTING DAY TO UPDATE ON LCD********************************/
/*********************************************************************************/

void SetRTCDay(u32 dayofweek)
{
		DOW = dayofweek;  // upadating the day to sfr
}

void GetRTCDay(s32 *dayofweek)
{
	*dayofweek = DOW; 
}

void DisplayRTCDay(u32 dayofweek)
{
	// upadating the day to LCD
	CmdLCD(GOTO_LINE1_POS0+13);
	StrLCD(week[dayofweek]);  
}


/*********************************************************************************/
/*****************ALARM SYMBOLL TO DISPLAY ALARAM ACTIVE**************************/
/*********************************************************************************/

void AlarmDisplay(void)
{
	u8 alarm[24]=          // by the CGRAM code initialisation to display the alaram..
	{
	0x04,0x08,0x12,0x14,0x14,0x12,0x08,0x04,
	0x04,0x0e,0x0e,0x0e,0x0e,0x1f,0x1f,0x04,
	0x04,0x02,0x09,0x05,0x05,0x09,0x02,0x04
	};
	BuildCGRAM(alarm,24);
	CmdLCD(GOTO_LINE1_POS0+12);
	CharLCD(0);
	CharLCD(1);
	CharLCD(2);
}

/*********************************************************************************/
/****************TO DISPLAY TEMPERATURE ON LCD WITH SENSOR************************/
/*********************************************************************************/

void TempDisplay(void)
{
	CmdLCD(GOTO_LINE2_POS0+10);
	CharLCD('T');
	CharLCD(':');
	
	CmdLCD(GOTO_LINE2_POS0+14);
	CharLCD(0xdf);
	CharLCD('C');
}

void Displaytemperature(void)
{
	Read_ADC(1,&adcDVal,&eAR);
	temperature = eAR*100;
	CmdLCD(GOTO_LINE2_POS0+12);
	U32LCD(temperature);
}

/*********************************************************************************/
/*****************EDITING THE TIME WITH SUPERATE FUNCTION ************************/
/*********************************************************************************/

void RTC_TimeEdit(void)
{
	u8 option=0;	

start_loop:	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.HOUR  2.MINUTES");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("3.SECONDS 4.EXIT");
	while((option=KeyScan())!=0);
	while(1)
	{
		
		option=KeyScan();
		while(ColScan()==0);
		switch(option)
		{
			case '1':CmdLCD(CLEAR_LCD);
							StrLCD("HOUR EDIT........");
							RTC_HoursEdit();
							goto start_loop;
							//break;
			case '2':CmdLCD(CLEAR_LCD);
							StrLCD("MINUTES EDIT....");
							RTC_MinutesEdit();
							goto start_loop;
			case '3':CmdLCD(CLEAR_LCD);
							StrLCD("SECONDS EDIT...");
							RTC_SecondsEdit();
							goto start_loop;
			case '4':CmdLCD(CLEAR_LCD);
							StrLCD("EXITING MENU....");
							return;
			default:CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0);
							StrLCD("INVALID KEY");
							delay_s(1);
							goto start_loop;
			}
	}
}
/*****************************HOUR EDIT*******************************************/
void RTC_HoursEdit(void)
{
	u8 hour=0, key=0,count=0;
start_pos:
	hour = 0;
	count = 0;
	CmdLCD(CLEAR_LCD);
	StrLCD("SET HOURS:(0-24)");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("00");
	while(KeyScan() != 0);
	while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 2)   // allow 2 digits
		{
			hour = (hour * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			hour = hour / 10;                     
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');                         
			CmdLCD(GOTO_LINE2_POS0 + count);      
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 2)
		{
			delay_ms(300);
			break;
		}
	}
	
	if(hour>23)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID INPUT!");
		delay_s(1);
		goto start_pos;   // restart entry
	}

	// Update RTC hour (keeping existing minute & second)
	SetRTCHoursInfo(hour);

	CmdLCD(CLEAR_LCD);
	StrLCD("Hour Updated!");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
}
/*****************************MINUTES EDIT****************************************/
void RTC_MinutesEdit(void)
{
	u8 count=0,key ,min=0;
start_pos:
	min=0;
	count=0;
	CmdLCD(CLEAR_LCD);
	StrLCD("SET MIN:(0-59)");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("00");
	while(KeyScan() != 0);
	while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 2)   // allow 2 digits
		{
			min = (min * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			min = min / 10;                     // remove last digit
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');                       // replace with '0'
			CmdLCD(GOTO_LINE2_POS0 + count);    // move cursor back
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 2)
		{
			delay_ms(300);
			break;
		}
	}
	if(min>59)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID INPUT!");
		delay_s(1);
		goto start_pos;   // restart entry
	}
	// Update RTC minute (keeping existing hour & second)
	SetRTCMinutesInfo(min);

	CmdLCD(CLEAR_LCD);
	StrLCD("Minute Updated!");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
}
/*****************************SECONDS EDIT*******************************************/
void RTC_SecondsEdit(void)
{
    u8 sec=0, key,count=0;
	start_pos:
	sec=0;
	count =0;
    CmdLCD(CLEAR_LCD);
    StrLCD("SET SEC:(0-59)");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("00");
		while(KeyScan() != 0);
    while(1)
    {
			key = KeyScan();
			if(key >= '0' && key <= '9' && count < 2)   // allow 2 digits
			{
				sec = (sec * 10) + (key - '0');
				CmdLCD(GOTO_LINE2_POS0+count);
				CharLCD(key);
				count++;
				delay_ms(300);
				while(ColScan()==0);
			}
			else if((key == 'C' || key == 'c') && count > 0)
			{
				count--;
				sec = sec / 10;                     // remove last digit
				CmdLCD(GOTO_LINE2_POS0 + count);
				CharLCD('0');                       // replace with '0'
				CmdLCD(GOTO_LINE2_POS0 + count);    // move cursor back
				delay_ms(300);
				while(ColScan()==0);
			}
			else if(key == '=' || count >= 2)
			{
				delay_ms(300);
				break;
			}
    }
		if(sec>59)
    {
			CmdLCD(CLEAR_LCD);
			StrLCD("INVALID INPUT!");
			delay_s(1);
			goto start_pos;   // restart entry
    }
    // Update RTC second (keeping existing hour & minute)
    SetRTCSecondsInfo(sec);

    CmdLCD(CLEAR_LCD);
    StrLCD("Second Updated!");
    delay_s(1);
    CmdLCD(CLEAR_LCD);
}

/*********************************************************************************/
/*****************EDITING THE DATE WITH SUPERATE FUNCTION ************************/
/*********************************************************************************/

void RTC_DateEdit(void)
{
	u8 option=0;	
start_loop:	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.DAT 2.MON 5.EXIT");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("3.YEAR 4.DAY ");
	while((option=KeyScan())!=0);
	while(1)
	{
		option=KeyScan();
		while(ColScan()==0);
		switch(option)
		{
			case '1':CmdLCD(CLEAR_LCD);
							StrLCD("DATE EDIT........");
							RTC_Date_Edit();
							goto start_loop;
			case '2':CmdLCD(CLEAR_LCD);
							StrLCD("MONTH EDIT....");
							RTC_MonthEdit();
							goto start_loop;
			case '3':CmdLCD(CLEAR_LCD);
							StrLCD("YEAR EDIT...");
							RTC_YearEdit();
							goto start_loop;
			case '4':CmdLCD(CLEAR_LCD);
							StrLCD("DAY EDIT...");
							RTC_DayEdit();
							goto start_loop;
			case '5':CmdLCD(CLEAR_LCD);
							StrLCD("EXITING MENU....");
							return;
			default:CmdLCD(CLEAR_LCD);
							CmdLCD(GOTO_LINE1_POS0);
							StrLCD("INVALID KEY");
							delay_s(1);
							goto start_loop;
			}
	}
}
/*****************************DATE EDIT*******************************************/
void RTC_Date_Edit(void)
{
    u8 date = 0, key = 0, count = 0;
	start_pos:
	date=0;
	count=0;
	CmdLCD(CLEAR_LCD);
	StrLCD("SET DATE:(1-31)");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("00");
	while(KeyScan() != 0);

  while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 2)   //it can  allow 2 digits only...................................
		{
			date = (date * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		 }
			else if((key == 'C' || key == 'c') && count > 0)
			{
				count--;
				date = date / 10;
				CmdLCD(GOTO_LINE2_POS0 + count);
				CharLCD('0');
				CmdLCD(GOTO_LINE2_POS0 + count);
				delay_ms(300);
				while(ColScan()==0);
			}
			else if(key == '=' || count >= 2)
			{
				delay_ms(300);
				break;
			}
    }
		if(date>31)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("INVALID INPUT!");
			delay_s(1);
			goto start_pos;   // restart entry
		}
    SetRTCDateInfo(date);

    CmdLCD(CLEAR_LCD);
    StrLCD("Date Updated!");
    delay_s(1);
    CmdLCD(CLEAR_LCD);
}
/*****************************MONTH EDIT*******************************************/
void RTC_MonthEdit(void)
{
  u8 month = 0, key = 0, count = 0;
	start_pos:
	month=0;
	count=0;
	CmdLCD(CLEAR_LCD);
	StrLCD("SET MONTH:(1-12)");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("00");
	while(KeyScan() != 0);

	while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 2)   // allow 2 digits
		{
			month = (month * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			month = month / 10;
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');
			CmdLCD(GOTO_LINE2_POS0 + count);
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 2)
		{
			delay_ms(300);
			break;
		}
	}
	if(month>12)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID INPUT!");
		delay_s(1);
		goto start_pos;   // restart entry
	}

	SetRTCMonthInfo(month);

	CmdLCD(CLEAR_LCD);
	StrLCD("Month Updated!");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
}
/*****************************YEAR EDIT*******************************************/
void RTC_YearEdit(void)
{
	u16 year = 0;
	u8 key = 0, count = 0;

	CmdLCD(CLEAR_LCD);
	StrLCD("SET YEAR:");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("0000");
	while(KeyScan() != 0);

	while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 4)   // allow 4 digits
		{
			year = (year * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		 else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			year = year / 10;
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');
			CmdLCD(GOTO_LINE2_POS0 + count);
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 4)
		{
			delay_ms(300);
			break;
		}
	}

	SetRTCYearInfo(year);

	CmdLCD(CLEAR_LCD);
	StrLCD("Year Updated!");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
}

/*********************************************************************************/
/***************EDITING THE WEEK DAY WITH SUPERATE FUNCTION **********************/
/*********************************************************************************/
void RTC_DayEdit(void)
{
	
	u16 day = 0,key = 0, count = 0;
	start_pos:
	day=0,count=0;
	// Step 4: Edit Day (1�7)
	CmdLCD(CLEAR_LCD);
	StrLCD("SET DAY:(1-7)");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("0");
	while(KeyScan() != 0);
	while(1)
	{
		key = KeyScan();
		if(key >= '1' && key <= '7' && count < 1)   // only 1 digit for day
		{
			day = key - '0';
			CmdLCD(GOTO_LINE2_POS0+count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		 else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			day = day / 10;
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');
			CmdLCD(GOTO_LINE2_POS0 + count);
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 1)
		{
			delay_ms(300);
			break;
		}
	}
	if(day>7)
	{
	CmdLCD(CLEAR_LCD);
	StrLCD("INVALID INPUT!");
	delay_s(1);
	goto start_pos;   // restart again from start
	}

	SetRTCDay(day);
	CmdLCD(CLEAR_LCD);
	StrLCD("DAY Updated!");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
}
/*********************************************************************************/
/************************** SETTING THE ALARM  ***********************************/
/*********************************************************************************/
void RTC_AlarmSet(void)
{
	u8 key = 0, count = 0;
	u8 temp_hour = 0, temp_min = 0;

start_alarm:
	temp_hour = 0;
	temp_min = 0;
	count = 0;

	CmdLCD(CLEAR_LCD);
	StrLCD("SET ALARAM HR:");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("00");
	while(KeyScan() != 0);

	// ---- Enter Hour ----
	while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 2)
		{
			temp_hour = (temp_hour * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+ count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			temp_hour = temp_hour / 10;
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');
			CmdLCD(GOTO_LINE2_POS0 + count);
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 2)
		{
			delay_ms(300);
			break;
		}
	}
	if(temp_hour > 23)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("Invalid Hour!");
		delay_s(1);
		goto start_alarm;
	}

	// ---- Enter Minute ----
	CmdLCD(CLEAR_LCD);
	StrLCD("SET ALARAM MIN:");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("00");
	count = 0;
	while(KeyScan() != 0);
	while(1)
	{
		key = KeyScan();
		if(key >= '0' && key <= '9' && count < 2)
		{
			temp_min = (temp_min * 10) + (key - '0');
			CmdLCD(GOTO_LINE2_POS0+ count);
			CharLCD(key);
			count++;
			delay_ms(300);
			while(ColScan()==0);
		}
		else if((key == 'C' || key == 'c') && count > 0)
		{
			count--;
			temp_min = temp_min / 10;
			CmdLCD(GOTO_LINE2_POS0 + count);
			CharLCD('0');
			CmdLCD(GOTO_LINE2_POS0 + count);
			delay_ms(300);
			while(ColScan()==0);
		}
		else if(key == '=' || count >= 2)
		{
			delay_ms(300);
			break;
		}
	}
	if(temp_min > 59)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("Invalid Minute!");
		delay_s(1);
		goto start_alarm;
	}
	// ---- Save Alarm ----
	alarm_hour = temp_hour;
	alarm_min = temp_min;

	CmdLCD(CLEAR_LCD);
	StrLCD("Alarm Set:");
	CmdLCD(GOTO_LINE2_POS0);
	U32LCD(alarm_hour);   // display hour (you can make your own DisplayLCD)
	CharLCD(':');
	U32LCD(alarm_min);
	delay_s(2);
	CmdLCD(CLEAR_LCD);
}

/*********************************************************************************/
/************************* ALARAM ACTIVATING MODE ********************************/
/*********************************************************************************/

void displayAlaramactive(void)
{
	IODIR0 |= (1 << BUZZER_SW);  
 if ((alarm_hour != 0 || alarm_min != 0) && (HOUR == alarm_hour) && (MIN == alarm_min))//&& (alarm_triggered == 0)
	{
		IOSET0 |= (1 << BUZZER_SW);   
		CmdLCD(CLEAR_LCD);
		StrLCD("Alarm Time!");
		AlarmDisplay();                
		delay_s(5);                   
		IOCLR0 |= (1 << BUZZER_SW);   
		CmdLCD(CLEAR_LCD);
		StrLCD("Alarm Off!");
		delay_s(1);
		CmdLCD(CLEAR_LCD);
		alarm_triggered = 1;	
	}
	/*	if((HOUR != alarm_hour) || (MIN != alarm_min))
		alarm_triggered = 0;*/
}
