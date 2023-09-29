/*
 * rtc.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

#ifndef RTC_H_
#define RTC_H_

/* RTC public definition */
#define RTC_COMPENSATION_REFERENCE_VALUE 2020	// ------------------------------------------------------------ //
//																												//
// The date is automatically adjusted for leap years, assuming every year divisible by 4 is a leap year.		//
// Therefore, the reference value must be a leap year, e.g. 2000. The RTC will increment until it reaches		//
// the top value of 23:59:59 December 31st of year 63, and then wrap to 00:00:00 January 1st of year 0.			//
// This will set the Overflow interrupt flag in the Interrupt Flag Status and Clear registers (INTFLAG.OVF).	//
//																												//
extern int rtc_compensation_reference_value; // --------------------------------------------------------------  //

/* RTC */
#define RTC_SECOND(reg_)	(((reg_) >> RTC_MODE2_CLOCK_SECOND_Pos) & (RTC_MODE2_CLOCK_SECOND_Msk >> RTC_MODE2_CLOCK_SECOND_Pos))
#define RTC_MINUTE(reg_)	(((reg_) >> RTC_MODE2_CLOCK_MINUTE_Pos) & (RTC_MODE2_CLOCK_MINUTE_Msk >> RTC_MODE2_CLOCK_MINUTE_Pos))
#define RTC_HOUR(reg_)		(((reg_) >> RTC_MODE2_CLOCK_HOUR_Pos) & (RTC_MODE2_CLOCK_HOUR_Msk >> RTC_MODE2_CLOCK_HOUR_Pos))

#define RTC_DAY(reg_)		(((reg_) >> RTC_MODE2_CLOCK_DAY_Pos) & (RTC_MODE2_CLOCK_DAY_Msk >> RTC_MODE2_CLOCK_DAY_Pos))
#define RTC_MONTH(reg_)		(((reg_) >> RTC_MODE2_CLOCK_MONTH_Pos) & (RTC_MODE2_CLOCK_MONTH_Msk >> RTC_MODE2_CLOCK_MONTH_Pos))
#define RTC_YEAR(reg_)		(((reg_) >> RTC_MODE2_CLOCK_YEAR_Pos) & (RTC_MODE2_CLOCK_YEAR_Msk >> RTC_MODE2_CLOCK_YEAR_Pos))

 #ifdef __cplusplus
 extern "C" {
 #endif
 
	 /*
	  * Private functions
	  */
 
		void RTC_int();	

	 /*
	  * Public functions
	  */
 
		unsigned int date_RTC();
		unsigned char second_RTC();
		unsigned char minute_RTC();
		unsigned char hour_RTC();
		unsigned int year_RTC();
		unsigned char month_RTC();
		unsigned char day_RTC();

 #ifdef __cplusplus
 }
 #endif

#endif /* RTC_H_ */