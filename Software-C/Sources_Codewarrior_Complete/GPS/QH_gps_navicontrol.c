/*****************************************************************************************

@file:  QH_gps_navicontrol.c
@autor: Max Pejs
@date:  Datum: 07.05.2011

Copyright (C) 2011 University of Applied Sciences Esslingen

$Id:$
$Rev:$

<h2>Functions for automatic navigation and the distance calculation between two gps coordinates</h2>

------------------------------------------------------------------------------------------
 _
|
| Hochschule Esslingen
| University of Applied Sciences
|_

Subject:	Student Research Project
Faculty:	Information Technology
			Technical Informatics

Project Quadrocopter

*****************************************************************************************/

/* Includes *****************************************************************************/
#include "QH_gps_navicontrol.h"
#include "QH_gps_util.h"
#include "QH_gps_app.h"

/*  contains the longitude degree scales. Array index corresponds to latitude.
*   The calculation way is cos(latitude)*111307. E.g. scaleFactorArr[48] is 74479 corresponds
*   to cos(48)*111307=74479 .
*/
//static uint32 scaleFactorArr[90] = {111307,111290,111239,111154,111036,110883,110697,
//110477,110224,109937,109616,109262,108875,108454,108001,107514,106995,106443,
//105859,105243,104594,103914,103202,102459,101684,100878,100042,99175,98278,97351,
//96395,95409,94394,93350,92278,91177,90049,88894,87711,86502,85266,84004,82717,
//81405,80068,78706,77320,75911,74479,73024,71547,70048,68527,66986,65425,
//63843,62242,60622,58984,57327,55654,53963,52255,50532,48794,47040,45273,43491,
//41696,39889,38069,36238,34396,32543,30680,28808,26928,25039,23142,
//21238,19328,17412,15491,13565,11635,9701,7764,5825,3885,1943,0};
//
// compiler complains about too many elements

/* Functions ****************************************************************************/
uint32 getMeridianScale(int32 lat)
{
	uint32 factor;
	uint16 section;
	if(lat<0)
	{lat = -lat;}

	// getting degree section. round to third digit, then cut everything after the second digit.
	section = (uint16)(rnd( (uint16)(lat / (PRECISION_GPS/10)))) / 10;

	switch(section)
	{
	case	0	:	factor = 111307	;	break;
	case	1	:	factor = 111290	;	break;
	case	2	:	factor = 111239	;	break;
	case	3	:	factor = 111154	;	break;
	case	4	:	factor = 111036	;	break;
	case	5	:	factor = 110883	;	break;
	case	6	:	factor = 110697	;	break;
	case	7	:	factor = 110477	;	break;
	case	8	:	factor = 110224	;	break;
	case	9	:	factor = 109937	;	break;
	case	10	:	factor = 109616	;	break;
	case	11	:	factor = 109262	;	break;
	case	12	:	factor = 108875	;	break;
	case	13	:	factor = 108454	;	break;
	case	14	:	factor = 108001	;	break;
	case	15	:	factor = 107514	;	break;
	case	16	:	factor = 106995	;	break;
	case	17	:	factor = 106443	;	break;
	case	18	:	factor = 105859	;	break;
	case	19	:	factor = 105243	;	break;
	case	20	:	factor = 104594	;	break;
	case	21	:	factor = 103914	;	break;
	case	22	:	factor = 103202	;	break;
	case	23	:	factor = 102459	;	break;
	case	24	:	factor = 101684	;	break;
	case	25	:	factor = 100878	;	break;
	case	26	:	factor = 100042	;	break;
	case	27	:	factor = 99175	;	break;
	case	28	:	factor = 98278	;	break;
	case	29	:	factor = 97351	;	break;
	case	30	:	factor = 96395	;	break;
	case	31	:	factor = 95409	;	break;
	case	32	:	factor = 94394	;	break;
	case	33	:	factor = 93350	;	break;
	case	34	:	factor = 92278	;	break;
	case	35	:	factor = 91177	;	break;
	case	36	:	factor = 90049	;	break;
	case	37	:	factor = 88894	;	break;
	case	38	:	factor = 87711	;	break;
	case	39	:	factor = 86502	;	break;
	case	40	:	factor = 85266	;	break;
	case	41	:	factor = 84004	;	break;
	case	42	:	factor = 82717	;	break;
	case	43	:	factor = 81405	;	break;
	case	44	:	factor = 80068	;	break;
	case	45	:	factor = 78706	;	break;
	case	46	:	factor = 77320	;	break;
	case	47	:	factor = 75911	;	break;
	case	48	:	factor = 74479	;	break;
	case	49	:	factor = 73024	;	break;
	case	50	:	factor = 71547	;	break;
	case	51	:	factor = 70048	;	break;
	case	52	:	factor = 68527	;	break;
	case	53	:	factor = 66986	;	break;
	case	54	:	factor = 65425	;	break;
	case	55	:	factor = 63843	;	break;
	case	56	:	factor = 62242	;	break;
	case	57	:	factor = 60622	;	break;
	case	58	:	factor = 58984	;	break;
	case	59	:	factor = 57327	;	break;
	case	60	:	factor = 55654	;	break;
	case	61	:	factor = 53963	;	break;
	case	62	:	factor = 52255	;	break;
	case	63	:	factor = 50532	;	break;
	case	64	:	factor = 48794	;	break;
	case	65	:	factor = 47040	;	break;
	case	66	:	factor = 45273	;	break;
	case	67	:	factor = 43491	;	break;
	case	68	:	factor = 41696	;	break;
	case	69	:	factor = 39889	;	break;
	case	70	:	factor = 38069	;	break;
	case	71	:	factor = 36238	;	break;
	case	72	:	factor = 34396	;	break;
	case	73	:	factor = 32543	;	break;
	case	74	:	factor = 30680	;	break;
	case	75	:	factor = 28808	;	break;
	case	76	:	factor = 26928	;	break;
	case	77	:	factor = 25039	;	break;
	case	78	:	factor = 23142	;	break;
	case	79	:	factor = 21238	;	break;
	case	80	:	factor = 19328	;	break;
	case	81	:	factor = 17412	;	break;
	case	82	:	factor = 15491	;	break;
	case	83	:	factor = 13565	;	break;
	case	84	:	factor = 11635	;	break;
	case	85	:	factor = 9701	;	break;
	case	86	:	factor = 7764	;	break;
	case	87	:	factor = 5825	;	break;
	case	88	:	factor = 3885	;	break;
	case	89	:	factor = 1943	;	break;
	case	90	:	factor = 0		;	break;
	default		:	factor = 0		;	break;
	}
	return factor;
}

/*--------------------------------------------------------------------------------------*/
uint32 calcDistance( GeograficPosition pos1, GeograficPosition pos2)
{
	uint32 dist = 0, scale, latDist, lonDist;
	int32 deltaLat, deltaLon;

	scale =  getMeridianScale(pos1.Latitude);	//scaleFactorArr[rnd(pos1.Latitude*10/(GPS_PRECISION))];
	deltaLat = pos1.Latitude - pos2.Latitude;

	if(deltaLat < 0)
	{deltaLat = -deltaLat;}
	latDist = (deltaLat * METERS_PER_DEGREE) / PRECISION_GPS;
	deltaLon = pos1.Longitude - pos2.Longitude;
	
	if(deltaLon < 0) {deltaLon = -deltaLon;}
	lonDist = (deltaLon * scale) / PRECISION_GPS;
	
	// Pythagoras
	dist = (uint32)calcSQRT( (latDist*latDist) + (lonDist*lonDist) );
	
	return dist;
}

