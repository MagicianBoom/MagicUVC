#include "fly_mode.h"
#include "rc.h"

u8 mode_value[10];
u8 mode_state,mode_state_old;
void mode_check(float *ch_in,u8 *mode_value)
{
	
	if(*(ch_in+AUX1) <-200)
	{
		mode_state = 0;//0;
	}
	else if(*(ch_in+AUX1) >200)
	{
		mode_state = 2;
	}
	else
	{
		mode_state = 1;
	}
	
	//=========== GPS����ѹ���� ===========
	if(mode_state == 0 )
	{
		*(mode_value+GPS) = *(mode_value+BARO) = 0;
	}
	else
	{
		*(mode_value+GPS) = *(mode_value+BARO) = 1;
	}
	
//	//=========== ����ģʽ ===========
//	if(fly_ready )
//	{
//		if(( mode_state == 2 && mode_state_old != 2) || rc_lose == 1)
//		{

//			*(mode_value+BACK_HOME) = 1;
//			

//		}
//		else if(mode_state != 2)
//		{
//			*(mode_value+BACK_HOME) = 0;
//		}
//	}
//	else
//	{
//		*(mode_value+BACK_HOME) = 0;
//	}
	
	
 
	//===========   ===========
	mode_state_old = mode_state; //��ʷģʽ
}
