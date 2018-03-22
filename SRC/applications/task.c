#include "app_cfg.h"
#include "includes.h"
#include "time.h"
#include "mpu6050.h"
#include "ak8975.h"
#include "led.h"
#include "rc.h"
#include "imu.h"
#include "pwm_in.h"
#include "ctrl.h"
#include "ms5611.h"
#include "parameter.h"
#include "ultrasonic.h"
#include "height_ctrl.h"
#include "fly_mode.h"

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void  AppTaskCreate         (void);
void  AppTask_1ms         (void     *p_arg);
void  AppTask_2ms         (void     *p_arg);
void  AppTask_5ms         (void     *p_arg);
void  AppTask_10ms         (void     *p_arg);
void  AppTask_20ms         (void     *p_arg);
void  AppTask_50ms         (void     *p_arg);


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
static  OS_TCB   AppTask_1ms_TCB;
static  CPU_STK  AppTask_1ms_Stk[APP_CFG_TASK_1ms_STK_SIZE];

static  OS_TCB   AppTask_2ms_TCB;
static  CPU_STK  AppTask_2ms_Stk[APP_CFG_TASK_2ms_STK_SIZE];

static  OS_TCB   AppTask_5ms_TCB;
static  CPU_STK  AppTask_5ms_Stk[APP_CFG_TASK_5ms_STK_SIZE];

static  OS_TCB   AppTask_10ms_TCB;
static  CPU_STK  AppTask_10ms_Stk[APP_CFG_TASK_10ms_STK_SIZE];

static  OS_TCB   AppTask_20ms_TCB;
static  CPU_STK  AppTask_20ms_Stk[APP_CFG_TASK_20ms_STK_SIZE];

static  OS_TCB   AppTask_50ms_TCB;
static  CPU_STK  AppTask_50ms_Stk[APP_CFG_TASK_50ms_STK_SIZE];


s16 loop_cnt;


loop_t loop;

float test[5];




/*
*********************************************************************************************************
*	函 数 名: AppTask_1ms
*	功能说明: 
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：
*********************************************************************************************************
*/
void AppTask_1ms(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;
		  
	while(1)
	{		
		Get_Cycle_T(1)/1000000.0f;

		ANO_DT_Data_Exchange();				//数传通信定时调用
		
		OSTimeDly(1, OS_OPT_TIME_DLY, &err);
		
		//System testing for ucOS magicUVC by LiuYang
//		printf("Data exchange!\n");
		//Test end
	}   
}



/*
*********************************************************************************************************
*	函 数 名: AppTask_2ms
*	功能说明: 
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：
*********************************************************************************************************
*/
void AppTask_2ms(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;
	float inner_loop_time;
		  
	while(1)
	{		
		inner_loop_time = Get_Cycle_T(0)/1000000.0f; 						//获取内环准确的执行周期
		
		test[0] = GetSysTime_us()/1000000.0f;

//		//System testing for ucOS magicUVC by LiuYang
//		printf("inner_loop_time:%f\n", inner_loop_time);
//		//Test end
		
		MPU6050_Read(); 															//读取mpu6轴传感器

		MPU6050_Data_Prepare( inner_loop_time );			//mpu6轴传感器数据处理
		
		/*IMU更新姿态。输入：半个执行周期，三轴陀螺仪数据（转换到度每秒），三轴加速度计数据（4096--1G）；输出：ROLPITYAW姿态角*/
		IMUupdate(0.5f *inner_loop_time,mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);
		
		//System testing for ucOS magicUVC by LiuYang
		printf("Roll:%f\n", Roll);
		//Test end


		CTRL_1( inner_loop_time ); 										//内环角速度控制。输入：执行周期，期望角速度，测量角速度，角度前馈；输出：电机PWM占空比。<函数未封装>
		
		RC_Duty( inner_loop_time , Rc_Pwm_In );				// 遥控器通道数据处理 ，输入：执行周期，接收机pwm捕获的数据。
		
		OSTimeDly(2, OS_OPT_TIME_DLY, &err);
	}   
}



/*
*********************************************************************************************************
*	函 数 名: AppTask_5ms
*	功能说明: 	
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：
*********************************************************************************************************
*/
void AppTask_5ms(void *p_arg)
{
	OS_ERR      err;

	(void)p_arg;
	
	float outer_loop_time; 
	
	while(1)
	{		
		outer_loop_time = Get_Cycle_T(2)/1000000.0f;								//获取外环准确的执行周期
		
		test[2] = GetSysTime_us()/1000000.0f;

	 	CTRL_2( outer_loop_time ); 											// 外环角度控制。输入：执行周期，期望角度（摇杆量），姿态角度；输出：期望角速度。<函数未封装>
		
		test[3] = GetSysTime_us()/1000000.0f;
		
		OSTimeDly(5, OS_OPT_TIME_DLY, &err);
	}   
}


/*
*********************************************************************************************************
*	函 数 名: AppTask_10ms
*	功能说明: 	
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：
*********************************************************************************************************
*/
void AppTask_10ms(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;
		  
	while(1)
	{		
		ANO_AK8975_Read();			//获取电子罗盘数据
		OSTimeDly(10, OS_OPT_TIME_DLY, &err);
	}   
}


/*
*********************************************************************************************************
*	函 数 名: AppTask_20ms
*	功能说明: 	
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：
*********************************************************************************************************
*/
void AppTask_20ms(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;
		  
	while(1)
	{		
		Parameter_Save();
		OSTimeDly(20, OS_OPT_TIME_DLY, &err);
	}   
}


/*
*********************************************************************************************************
*	函 数 名: AppTask_50ms
*	功能说明: 	
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：
*********************************************************************************************************
*/
void AppTask_50ms(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;
		  
	while(1)
	{		
		mode_check(CH_filter,mode_value);
		LED_Duty();								//LED任务
		Ultra_Duty();
		OSTimeDly(50, OS_OPT_TIME_DLY, &err);
	}   
}


/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
*********************************************************************************************************
*/
void  AppTaskCreate (void)
{
	OS_ERR      err;
	
	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_1ms_TCB,             
                 (CPU_CHAR     *)"App Task 1ms",
                 (OS_TASK_PTR   )AppTask_1ms, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_1ms_PRIO,
                 (CPU_STK      *)&AppTask_1ms_Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_1ms_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_1ms_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_2ms_TCB,             
                 (CPU_CHAR     *)"App Task 2ms",
                 (OS_TASK_PTR   )AppTask_2ms, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_2ms_PRIO,
                 (CPU_STK      *)&AppTask_2ms_Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_2ms_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_2ms_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_5ms_TCB,             
                 (CPU_CHAR     *)"App Task 5ms",
                 (OS_TASK_PTR   )AppTask_5ms, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_5ms_PRIO,
                 (CPU_STK      *)&AppTask_5ms_Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_5ms_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_5ms_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_10ms_TCB,             
                 (CPU_CHAR     *)"App Task 10ms",
                 (OS_TASK_PTR   )AppTask_10ms, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_10ms_PRIO,
                 (CPU_STK      *)&AppTask_10ms_Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_10ms_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_10ms_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_20ms_TCB,             
                 (CPU_CHAR     *)"App Task 20ms",
                 (OS_TASK_PTR   )AppTask_20ms, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_20ms_PRIO,
                 (CPU_STK      *)&AppTask_20ms_Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_20ms_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_20ms_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTask_50ms_TCB,             
                 (CPU_CHAR     *)"App Task 50ms",
                 (OS_TASK_PTR   )AppTask_50ms, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_50ms_PRIO,
                 (CPU_STK      *)&AppTask_50ms_Stk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_50ms_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_50ms_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);			 
}

