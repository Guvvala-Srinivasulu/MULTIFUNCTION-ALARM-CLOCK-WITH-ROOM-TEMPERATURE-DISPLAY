#ifndef RTC_H
#define RTC_H

#include "types.h"

void RTC_Init(void);
void GetRTCTimeInfo(s32 *,s32 *,s32 *);
void DisplayRTCTime(s32,s32,s32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);

void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);

void SetRTCHoursInfo(u32);
void SetRTCMintesInfo(u32);
void SetRTCSecondsInfo(u32);

void SetRTCDateinfo(u32);
void SetRTCMonthinfo(u32);
void SetRTCYearinfo(u32);
void SetRTCDay(u32);

void GetRTCHour(s32 *);
void GetRTCMin(s32 *);
void GetRTCSec(s32 *);
void GetRTCDate(s32 *);
void GetRTCMonth(s32 *);
void GetRTCYear(s32 *);
void GetDay(void);

void AlarmDisplay(void);
void TempDisplay(void);
void Displaytemperature(void);

void RTC_TimeEdit(void);
void RTC_DateEdit(void);

void RTC_HoursEdit(void);
void RTC_MinutesEdit(void);
void RTC_SecondsEdit(void);

void RTC_Date_Edit(void);
void RTC_MonthEdit(void);
void RTC_YearEdit(void);

void RTC_DayEdit(void);
void RTC_AlarmSet(void);

void displayAlaramactive(void);

#endif
