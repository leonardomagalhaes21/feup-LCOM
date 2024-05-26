#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../../game/structs.h"

struct real_time_clock_info rtc_info;
uint8_t output;

int read_rtc_output(uint8_t command, uint8_t *output);
int is_rtc_updating();
int is_rtc_binary();
uint8_t to_binary(uint8_t bcd_value);
int read_rtc_time();



#endif
