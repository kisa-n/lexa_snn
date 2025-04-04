#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"queueh.h"

#define _l_o_w (float)2.2924316695645764   //const preobrazovaniya tochnost N3LNlshHRR
#define _herons_activations_lim 1   // heron`s activation nopor

// нужны для работы not_adecvate_change:
#define _tall_v 32  // period "BblCOKON chastoty" B TIK-ax
#define _kakie 1000 // float n=  (float)(signed char pn) / (float)_kakie_

class heron;

extern bool tik;
extern char tiks_counter;
extern queue_element* dellist;
extern heron zero;
/* every tik
counter_i++;
if (counter_i > 230)counter_i = 0;
*/

inline unsigned long stepen2(char n) {
	switch (n) {
	case(0):return(1);
	case(1):return(2);
	case(2):return(4);
	case(3):return(8);
	case(4):return(16);
	case(5):return(32);
	case(6):return(64);
	case(7):return(128);
	case(8):return(256);
	case(9):return(512);
	case(10):return(1024);
	case(11):return(2048);
	case(12):return(4096);
	case(13):return(8192);
	case(14):return(16384);
	case(15):return(32768);
	case(16):return(65536);
	case(17):return(131072);
	case(18):return(262144);
	case(19):return(524288);
	case(20):return(1048576);
	case(21):return(2097152);
	case(22):return(4194304);
	case(23):return(8388608);
	case(24):return(16777216);
	case(25):return(33554432);
	case(26):return(67108864);
	case(27):return(134217728);
	case(28):return(268435456);
	case(29):return(536870912);
	case(30):return(1073741824);
	case(31):return(2147483648);
	case(32):return(4294967295);//2^32-1
	default:
		n = 0;//crash program
		*((int*)((long long)n)) = 0;
	}
	return(0);
}
