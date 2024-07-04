// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "7x7-CP.h"


led_config_t g_led_config = { 
//key matrix to LED index
{
    {0,       1,       2,      3,      4,       5,       6},
    {7,       8,       9,     10,     11,      12,      13},
    {14,     15,      16,     17,     18,      19,      20},
    {21,     22,      23,     24,     25,      26,      27},
    {28,     29,      30,     31,     32,      33,      34},
    {NO_LED, 36,      36,     37,     38,  NO_LED,  NO_LED},
    {NO_LED, 39,      40,     41,     42,  NO_LED,  NO_LED},
    {     49,     48,     47,     46,     45,     44,     43},
	{     56,     55,     54,     53,     52,     51,     50},
	{     63,     62,     61,     60,     59,     58,     57},
	{     70,     69,     68,     67,     66,     65,     64},
	{     77,     76,     75,     74,     73,     72,     71},
	{ NO_LED,  NO_LED,    81,     80,     79,     78, NO_LED},
	{ NO_LED,  NO_LED,    85,     84,     83,     82, NO_LED}
},
//LED Index to physical postion
{
		{0, 0}, //0
		{15, 0}, //1
		{30, 0}, //2
		{45, 0}, //3
		{60, 0}, //4
		{75, 0}, //5
		{90, 0}, //6
		{0, 6}, //7
		{15, 6}, //8
		{30, 6}, //9
		{45, 6}, //10
		{60, 6}, //11
		{75, 6}, //12
		{90, 6}, //13
		{0, 12}, //14
		{15, 12}, //15
		{30, 12}, //16
		{45, 12}, //17
		{60, 12}, //18
		{75, 12}, //19
		{90, 12}, //20
		{0, 18}, //21
		{15, 18}, //22
		{30, 18}, //23
		{45, 18}, //24
		{60, 18}, //25
		{75, 18}, //26
		{90, 18}, //27
		{0, 24}, //28
		{15, 24}, //29
		{30, 24}, //30
		{45, 24}, //31
		{60, 24}, //32
		{75, 24}, //33
		{90, 24}, //34
		{30, 30}, //35
		{45, 36}, //36
		{60, 42}, //37
		{60, 48}, //38
		{45, 30}, //39
		{60, 36}, //40
		{75, 42}, //41
		{75, 48}, //42
		{195, 0}, //43
		{180, 0}, //44
		{165, 0}, //45
		{150, 0}, //46
		{135, 0}, //47
		{120, 0}, //48
		{105, 0}, //49
		{195, 6}, //50
		{180, 6}, //51
		{165, 6}, //52
		{150, 6}, //53
		{135, 6}, //54
		{120, 6}, //55
		{105, 6}, //56
		{195, 12}, //57
		{180, 12}, //58
		{165, 12}, //59
		{150, 12}, //60
		{135, 12}, //61
		{120, 12}, //62
		{105, 12}, //63
		{195, 18}, //64
		{180, 18}, //65
		{165, 18}, //66
		{150, 18}, //67
		{135, 18}, //68
		{120, 18}, //69
		{105, 18}, //70
		{195, 24}, //71
		{180, 24}, //72
		{165, 24}, //73
		{150, 24}, //74
		{135, 24}, //75
		{120, 24}, //76
		{105, 24}, //77
		{165, 30}, //78
		{150, 36}, //79
		{135, 42}, //80
		{135, 48}, //81
		{150, 30}, //82
		{135, 36}, //83
		{120, 42}, //84
		{120, 48} //85
},
//LED Index to Flags
{
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT,	
      LED_FLAG_KEYLIGHT	
    }
};
