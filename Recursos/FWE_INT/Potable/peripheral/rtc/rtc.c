/*
 * rtc.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 
/* 
 * Uso de las macros predefinidas __DATE__ y __TIME__ para 
 * sincronizar hora y fecha del RTC durante compilación.
 *
 * Example of __DATE__ string: "Jul 27 2012"
 * Example of __TIME__ string: "21:06:19"
 *
 */

 #define COMPUTE_BUILD_YEAR \
 ( \
 (__DATE__[ 7] - '0') * 1000 + \
 (__DATE__[ 8] - '0') *  100 + \
 (__DATE__[ 9] - '0') *   10 + \
 (__DATE__[10] - '0') \
 )
 
 #define COMPUTE_BUILD_DAY \
 ( \
 ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') * 10 : 0) + \
 (__DATE__[5] - '0') \
 )
 
 #define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
 #define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
 #define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
 #define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
 #define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
 #define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
 #define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
 #define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
 #define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
 #define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
 #define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
 #define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')
 
 #define COMPUTE_BUILD_MONTH \
 ( \
 (BUILD_MONTH_IS_JAN) ?  1 : \
 (BUILD_MONTH_IS_FEB) ?  2 : \
 (BUILD_MONTH_IS_MAR) ?  3 : \
 (BUILD_MONTH_IS_APR) ?  4 : \
 (BUILD_MONTH_IS_MAY) ?  5 : \
 (BUILD_MONTH_IS_JUN) ?  6 : \
 (BUILD_MONTH_IS_JUL) ?  7 : \
 (BUILD_MONTH_IS_AUG) ?  8 : \
 (BUILD_MONTH_IS_SEP) ?  9 : \
 (BUILD_MONTH_IS_OCT) ? 10 : \
 (BUILD_MONTH_IS_NOV) ? 11 : \
 (BUILD_MONTH_IS_DEC) ? 12 : \
 /* error default */  99 \
 )
 
 #define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
 #define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
 #define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')
 
 #define BUILD_DATE_IS_BAD (__DATE__[0] == '?')
 
 #define BUILD_YEAR  ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_YEAR)
 #define BUILD_MONTH ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_MONTH)
 #define BUILD_DAY   ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_DAY)
 
 #define BUILD_TIME_IS_BAD (__TIME__[0] == '?')
 
 #define BUILD_HOUR  ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_HOUR)
 #define BUILD_MIN   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_MIN)
 #define BUILD_SEC   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_SEC)
 
 #define _YEAR_		/*(2)*/			(BUILD_YEAR - RTC_COMPENSATION_REFERENCE_VALUE) << RTC_MODE2_CLOCK_YEAR_Pos
 #define _MONTH_	/*(5)*/			(BUILD_MONTH) << RTC_MODE2_CLOCK_MONTH_Pos
 #define _DAY_		/*(9)*/			(BUILD_DAY) << RTC_MODE2_CLOCK_DAY_Pos
 #define _HOUR_		/*(13)*/		(BUILD_HOUR) << RTC_MODE2_CLOCK_HOUR_Pos
 #define _MINUTE_	/*(00)*/		(BUILD_MIN) << RTC_MODE2_CLOCK_MINUTE_Pos
 #define _SECOND_	/*(00 + 14)*/	(BUILD_SEC) << RTC_MODE2_CLOCK_SECOND_Pos

 int rtc_compensation_reference_value = RTC_COMPENSATION_REFERENCE_VALUE;
 
 void RTC_int(){
	 
	// Setting Generic Clock RTC
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_RTC_Val) | GCLK_CLKCTRL_GEN_GCLK2 | GCLK_CLKCTRL_CLKEN ;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
	// Setting Operating Mode as Clock/Calendar
	RTC->MODE2.CTRL.bit.MODE = RTC_MODE0_CTRL_MODE_CLOCK_Val;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	// Setting prescaling factor for the RTC in DIV8
	RTC->MODE2.CTRL.bit.PRESCALER = RTC_MODE0_CTRL_PRESCALER_DIV1024_Val;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	// Setting Clock Representation as 24 Hour
	RTC->MODE2.CTRL.bit.CLKREP = LOW;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	// Overflow Interrupt Enable
	RTC->MODE2.INTENSET.bit.OVF = HIGH;
	
	//Clock init
	RTC->MODE2.CLOCK.reg = _YEAR_ | _MONTH_ | _DAY_ | _HOUR_ | _MINUTE_ | _SECOND_;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);

 }
 
/*
 * Devuelve fecha y hoira en formato CLOCK - RTC.
 */
unsigned int date_RTC(){
	
	unsigned int date = 0;
	
	date = RTC->MODE2.CLOCK.reg;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return date;
}

/*
 * Devuelve segundos.
 */
unsigned char second_RTC(){
	
	unsigned char second = 0;
	
	second = RTC->MODE2.CLOCK.bit.SECOND;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return second;
}

/*
 * Devuelve minutos.
 */
unsigned char minute_RTC(){
	
	unsigned char minute = 0;
	
	minute = RTC->MODE2.CLOCK.bit.MINUTE;
 	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return minute;
}

/*
 * Devuelve hora.
 */
unsigned char hour_RTC(){
	
	unsigned char hour = 0;

	hour = RTC->MODE2.CLOCK.bit.HOUR;
 	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return hour;
}

/*
 * Devuelve dia.
 */
unsigned char day_RTC(){
	
	unsigned char day = 0;
	
	day = RTC->MODE2.CLOCK.bit.DAY;
 	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return day;
}

/*
 * Devuelve mes.
 */
unsigned char month_RTC(){
	
	unsigned char month = 0;
	
	month = RTC->MODE2.CLOCK.bit.MONTH;
 	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return month;
}

/*
 * Devuelve año.
 */
unsigned int year_RTC(){
	
	unsigned char year = 0;
	
	year = RTC->MODE2.CLOCK.bit.YEAR;
 	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);
	
	return rtc_compensation_reference_value + year;
}

/*
 * NVIC Handler
 */
void RTC_Handler(){
	
	if (RTC->MODE2.INTFLAG.bit.OVF == HIGH){		// Overflow at 23:59:59 December 31st of year 63
		rtc_compensation_reference_value += 60;
		RTC->MODE2.CLOCK.bit.YEAR = 4;
		
		RTC->MODE2.INTFLAG.reg |= RTC_MODE0_INTFLAG_OVF;
	}
}