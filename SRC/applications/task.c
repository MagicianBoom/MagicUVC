#include  <includes.h>
#include "app_cfg.h"

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void  AppTaskCreate         (void);
void  AppTaskStart          (void     *p_arg);
void  AppTaskUserIF         (void     *p_arg);
void  AppTaskCOM			(void 	  *p_arg);

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
                                                              

static  OS_TCB   AppTaskUpdateTCB;
static  CPU_STK  AppTaskUpdateStk[APP_CFG_TASK_UPDATE_STK_SIZE];

static  OS_TCB   AppTaskCOMTCB;
static  CPU_STK  AppTaskCOMStk[APP_CFG_TASK_COM_STK_SIZE];

static  OS_TCB   AppTaskUserIFTCB;
static  CPU_STK  AppTaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE];




/*
*********************************************************************************************************
*	函 数 名: AppTaskGUIUpdate
*	功能说明: LED2闪烁	
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：3
*********************************************************************************************************
*/
void AppTaskGUIUpdate(void *p_arg)
{
	OS_ERR      err;
	
	(void)p_arg;
		  
	while(1)
	{	
//		bsp_LedToggle(2);
	
		LED1 = ~LED1;
		OSTimeDly(200, OS_OPT_TIME_DLY, &err);								  	 	       											  
	}   
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskCom
*	功能说明: LED3闪烁	
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：3
*********************************************************************************************************
*/
void AppTaskCOM(void *p_arg)
{	
	
	
	OS_ERR      err;

	(void)p_arg;
	 
	while(1)
	{

//		bsp_LedToggle(3);
//		BEEP = ~BEEP;
		OSTimeDly(300, OS_OPT_TIME_DLY, &err);	
	}
	 						  	 	       											   
   
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskUserIF
*	功能说明: LED4闪烁
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级：2
*********************************************************************************************************
*/
void AppTaskUserIF(void *p_arg)
{
	OS_ERR      err;
  
	while (1) 
	{   		
//        bsp_LedToggle(4);
		OSTimeDly(100, OS_OPT_TIME_DLY, &err);     
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
	OSTaskCreate((OS_TCB       *)&AppTaskUpdateTCB,             
                 (CPU_CHAR     *)"App Task Update",
                 (OS_TASK_PTR   )AppTaskGUIUpdate, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_UPDATE_PRIO,
                 (CPU_STK      *)&AppTaskUpdateStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_UPDATE_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_UPDATE_STK_SIZE,
                 (OS_MSG_QTY    )1,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
	
	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTaskCOMTCB,            
                 (CPU_CHAR     *)"App Task COM",
                 (OS_TASK_PTR   )AppTaskCOM, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_COM_PRIO,
                 (CPU_STK      *)&AppTaskCOMStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_COM_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_COM_STK_SIZE,
                 (OS_MSG_QTY    )2,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
	
	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTaskUserIFTCB,             
                 (CPU_CHAR     *)"App Task UserIF",
                 (OS_TASK_PTR   )AppTaskUserIF, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_USER_IF_PRIO,
                 (CPU_STK      *)&AppTaskUserIFStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_USER_IF_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_USER_IF_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
				 
}

