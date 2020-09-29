#include "UPLib\\UP_System.h"

//舵机参数值3.41 约等于 1°
const int GEAR_ANGLE_3 = 490;	//3号舵机平衡位置角度 
const int GEAR_ANGLE_6 = 485;	//6号舵机平衡位置角度
const int GEAR_ANGLE_4 = 511;	//4号舵机平衡位置角度
const int GEAR_ANGLE_5 = 515;	//5号舵机平衡位置角度

const int SPEED_GEAR = 350;	//舵机速度

void InitSys();	//初始化系统
void InitGear();	//初始化舵机
void InitMotor();	//初始化电机
void InitClaw();	//初始化爪子

void FirstUpStage();	//第一次上台

void DebugGearbalan();	//测试爪子平衡位置
void DebugInfraredSensor(int,int,int); //测试红外传感器

/**
 * Title: Init()
 * Return: None
 * Author: Ben
 * Descr: 初始化系统
 * LastBuild: 20200928
 */
void Init()
{
    /*初始化系统*/
    UP_System_Init();

	printf("DEMO 1.0\n");	//显示Demo名称
	UP_LCD_ShowCharacterString(0,1,"BenFromHRBUST");	//显示作者团队
	UP_LCD_ShowCharacterString(0,2,"机器人格斗大赛");	//显示（我也不知道是啥）
	UP_delay_ms(2000);	//延时2s    
	UP_LCD_ClearScreen();	//清屏

	//初始化舵机
	InitGear();
	InitMotor();

	//设置预备动作
	InitClaw();
}

/**
 * Title: InitGear()
 * Return: None
 * Author: Ben
 * Descr: 初始化所有舵机
 * LastBuild: 20200928
 */
void InitGear()
{
	printf("SET SERVO MODE\n");	//舵机模式
	UP_CDS_SetMode(3, CDS_SEVMODE);		//设置3号舵机为舵机模式	
	UP_CDS_SetMode(6, CDS_SEVMODE);		//设置6号舵机为舵机模式	
	UP_CDS_SetMode(4, CDS_SEVMODE);		//设置4号舵机为舵机模式	
	UP_CDS_SetMode(5, CDS_SEVMODE);		//设置5号舵机为舵机模式	
	printf("SET FINISH\n");	//舵机模式
}

/**
 * Title: InitMotor()
 * Return: None
 * Author: Ben
 * Descr: 初始化所有舵机
 * LastBuild: 20200928
 */
void InitMotor()
{
	printf("SET MOTO MODE\n");	//电机模式
	UP_CDS_SetMode(1, CDS_MOTOMODE);	//设置1号舵机为电机模式	
	UP_CDS_SetMode(2, CDS_MOTOMODE);	//设置2号舵机为电机模式	
	printf("SET FINISH\n");	//电机模式
}

/**
 * Title: InitMClaw()
 * Return: None
 * Author: Ben
 * Descr: 设置爪子初始状态
 * LastBuild: 20200928
 */
void InitClaw()
{
	UP_CDS_SetAngle(3, 511+450, SPEED_GEAR);
	UP_CDS_SetAngle(6, 511-450, SPEED_GEAR);
	UP_CDS_SetAngle(4, 511+450, SPEED_GEAR);
	UP_CDS_SetAngle(5, 511-450, SPEED_GEAR);
	UP_delay_ms(2000);
}

/**
 * Title: DebugGearBalan()
 * Return: None
 * Author: Ben
 * Descr: 测试舵机平衡位置
 * LastBuild: 20200928
 */
void DebugGearBalan()
{
	UP_CDS_SetAngle(3, 490, SPEED_GEAR);
	UP_CDS_SetAngle(6, 485, SPEED_GEAR);
	UP_CDS_SetAngle(4, 511, SPEED_GEAR);
	UP_CDS_SetAngle(5, 515, SPEED_GEAR);
}

/**
 * Title: DebugInfraredSensor(int)
 * Return: None
 * Author: Altria
 * Descr: 调试红外传感器
 * LastBuild: 20200928
 */
void DebugInfraredSensor(int x,int y,int id) {
	int AD = UP_ADC_GetValue(id);
	// printf("begin\n");
	UP_LCD_ShowInt(x,y,AD);	//显示红外传感器值
	// printf("end\n");
}

/**
 * Title: FirstUpStage()
 * Return: None
 * Author: Ben
 * Descr: 第一次上台
 * LastBuild: 20200928
 */
void FirstUpStage()
{
	//前爪向下
	UP_CDS_SetAngle(3,400,SPEED_GEAR);
	UP_CDS_SetAngle(6,575,SPEED_GEAR);
	UP_delay_ms(1500);
	
	//后轮启动
	UP_CDS_SetSpeed(1, -SPEED_GEAR);
	UP_CDS_SetSpeed(2, SPEED_GEAR);
	UP_delay_ms(800);
	UP_CDS_SetSpeed(1, 0);
	UP_CDS_SetSpeed(2, 0);
}

int main(void)
{	
	Init();

	UP_LCD_ClearScreen();
	// while(1) {
	// 	DebugInfraredSensor(1,1,0);
	// 	DebugInfraredSensor(1,2,1);
	// 	DebugInfraredSensor(1,3,3);
	// 	UP_delay_ms(500);
	// }
	
	// DebugGearBalan();	//测试舵机平衡位置

	/*****************************************************软启动函数********************************************************/

	//第一次上台
	FirstUpStage();

	// UP_CDS_SetAngle(3, GEAR_ANGLE-160, 300);				//设置舵机转角(0~1023对应0~300°)，速度（0~1023）
	// UP_CDS_SetAngle(6, GEAR_ANGLE+130, 300);				//设置舵机转角(0~1023对应0~300°)，速度（0~1023）
	UP_delay_ms(1000);								
	UP_LCD_ClearLine(1);							//清除第2行字符














		
//		UP_CDS_SetAngle(4, 200, 500);				//设置舵机转角(0~1023对应0~300°)，速度（0~1023）
//		UP_delay_ms(1000);								
//		UP_LCD_ClearLine(1);							//清除第2行字符
//		
//		UP_CDS_SetAngle(5, 200, 500);				//设置舵机转角(0~1023对应0~300°)，速度（0~1023）
//		UP_delay_ms(1000);								
//		UP_LCD_ClearLine(1);							//清除第2行字符
//		
//		UP_CDS_SetAngle(6, 200, 500);				//设置舵机转角(0~1023对应0~300°)，速度（0~1023）
//		UP_delay_ms(1000);								
//		UP_LCD_ClearLine(1);							//清除第2行字符
		
		
//		printf("\nAngle:235");							
//		UP_CDS_SetAngle(4, 800, 500);	
//		UP_delay_ms(2000); 								//延时2s
//		UP_LCD_ClearScreen();							//清屏
//		
//		

//		
//		printf("Speed:+800");	
//		UP_CDS_SetSpeed(1, 800);					//设置电机模式下的速度，范围-1023~+1023	
//		UP_delay_ms(1000);								//延时1s
//		UP_LCD_ClearLine(1);							//清除第2行字符
//		
//		printf("\nSpeed:-800");	
//		UP_CDS_SetSpeed(2, 800);					//设置电机模式下的速度，范围-1023~+1023
//		UP_delay_ms(1000); 								//延时1s		
//		UP_LCD_ClearLine(1);							//清除第2行字符
//		
//		printf("\nStop");
//		UP_CDS_SetSpeed(1, 0);						//停止
//		UP_delay_ms(1000); 								//延时2s
//		UP_LCD_ClearScreen();							//清屏 
}
