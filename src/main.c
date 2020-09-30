#include "UPLib\\UP_System.h"

//舵机参数值3.41 约等于 1°
const int GEAR_ANGLE_3 = 490;	//3号舵机平衡位置角度 
const int GEAR_ANGLE_6 = 485;	//6号舵机平衡位置角度
const int GEAR_ANGLE_4 = 511;	//4号舵机平衡位置角度
const int GEAR_ANGLE_5 = 515;	//5号舵机平衡位置角度

const int GEAR_ANGLE_INIT = 400; //初始化舵机变换角度

const int SPEED_GEAR = 600;	//舵机速度
const int SPEED_Motor = 320; //电机速度
const int DELAY_UpStage = 750; //上台延时

void InitSys();	//初始化系统
void InitGear();	//初始化舵机
void InitMotor();	//初始化电机
void InitForepaw(); //初始化前爪
void InitHindpaw(); //初始化后爪 
void InitClaw();	//初始化爪子

void SoftStart(); //软启动函数

void MoveBeforeUpStage(); //上台前的向前走
void FirstUpStage();	//第一次上台

void LcdShowInt(int); //LCD屏幕上显示数字
void DebugGearbalan();	//测试爪子平衡位置
void DebugInfraredSensor(int,int,int); //测试红外传感器

void MoveForword(int); //向前走
void MoveStop(); //停下

/**
 * Title: LcdShowInt()
 * Return: None
 * Author: Altria
 * Descr: 显示屏上显示数字x
 * LastBuild: 20200930
 */
void LcdShowInt(int x) {
	UP_delay_ms(400);
	UP_LCD_ClearScreen();
	printf("%d\n",x);
}

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
 * Title: InitForepaw()
 * Return: None
 * Author: Altria
 * Descr: 初始化前爪
 * LastBuild: 20200929
 */
void InitForepaw() {
	UP_CDS_SetAngle(3, GEAR_ANGLE_3 + GEAR_ANGLE_INIT, SPEED_GEAR);
	UP_CDS_SetAngle(6, GEAR_ANGLE_6 - GEAR_ANGLE_INIT, SPEED_GEAR);
}

/**
 * Title: InitHindpaw()
 * Return: None
 * Author: Altria
 * Descr: 初始化后爪
 * LastBuild: 20200929
 */
void InitHindpaw() {
	UP_CDS_SetAngle(4, GEAR_ANGLE_4 + GEAR_ANGLE_INIT, SPEED_GEAR);
	UP_CDS_SetAngle(5, GEAR_ANGLE_5 - GEAR_ANGLE_INIT, SPEED_GEAR);
}

/**
 * Title: InitClaw()
 * Return: None
 * Author: Altria
 * Descr: 设置爪子初始状态
 * LastBuild: 20200929
 */
void InitClaw()
{
	InitForepaw();
	InitHindpaw();
	UP_delay_ms(2000);
}

/**
 * Title: MoveStop()
 * Return: None
 * Author: Altria
 * Descr: 停下
 * LastBuild: 20200929
 */
void MoveStop() {
	UP_CDS_SetSpeed(1, 0);
	UP_CDS_SetSpeed(2, 0);
}

/**
 * Title: MoveForword(int)
 * args: spped - 运行速度
 * Return: None
 * Author: Altria
 * Descr: 以速度spee向前行驶
 * LastBuild: 20200928
 */
void MoveForword(int speed) {
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, speed);
}

/**
 * Title: SoftStart()
 * Return: None
 * Author: Altria
 * Descr: 软启动函数
 * LastBuild: 20200930
 */
void SoftStart() {
	int infraredSensorLeft, infraredSensorRight;
	while(1) {
		infraredSensorLeft = UP_ADC_GetValue(0);
		infraredSensorRight = UP_ADC_GetValue(1);
		if(infraredSensorLeft >= 2500 && infraredSensorRight >= 2500) {
			break;
		}
	}
}

/**
 * Title: MoveBeforeUpStage()
 * Return: None
 * Author: Altria
 * Descr: 上台前行走至可以上台的位置
 * LastBuild: 20200929
 */
void MoveBeforeUpStage() {
	// int preInfraredSensor;
	MoveForword(SPEED_Motor);
	UP_delay_ms(1000);
	// while(1) {
	// 	preInfraredSensor = UP_ADC_GetValue(0);
	// 	// UP_delay_ms(1);
	// 	// printf("%d\n",preInfraredSensor);
	// 	// UP_delay_ms(200);
	// 	// UP_LCD_ClearScreen();
	// 	if(preInfraredSensor >= 1100) {
	// 		// MoveStop();
	// 		// UP_delay_ms(1500);
	// 		break;
	// 	}
	// }
	// printf("%d\n",preInfraredSensor);
}

/**
 * Title: FirstUpStage()
 * Return: None
 * Author: Altria
 * Descr: 第一次上台
 * LastBuild: 20200930
 */
void FirstUpStage()
{
	// printf("XXXXXXXXXXXXXXXXX");
	//前爪向下
	UP_CDS_SetAngle(3,GEAR_ANGLE_3 - 90,SPEED_GEAR);
	UP_CDS_SetAngle(6,GEAR_ANGLE_6 + 90,SPEED_GEAR);
	UP_delay_ms(DELAY_UpStage);
	
	//前进
	// MoveForword(SPEED_GEAR);
	// UP_delay_ms(700);
	// MoveStop();
	// UP_delay_ms(1500);

	//前爪复位
	InitForepaw();
	UP_delay_ms(DELAY_UpStage - 100);

	//后爪撑地
	UP_CDS_SetAngle(4, GEAR_ANGLE_4 - 120, SPEED_GEAR);
	UP_CDS_SetAngle(5, GEAR_ANGLE_5 + 120, SPEED_GEAR);
	UP_delay_ms(DELAY_UpStage + 50);

	//前进
	// MoveForword(SPEED_GEAR);
	// UP_delay_ms(700);
	// MoveStop();
	// UP_delay_ms(1500);

	//后爪复位
	InitHindpaw();
	UP_delay_ms(DELAY_UpStage);

	MoveStop();
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
	// printf("%d\n",AD);
	UP_delay_ms(400);
	UP_LCD_ClearScreen();
	// printf("end\n");
}

/**
 * Title: DebugAllInfraredSensor(int)
 * Return: None
 * Author: Ben
 * Descr: 调试全部红外传感器
 * LastBuild: 20200928
 */
void DebugAllInfraredSensor()
{
	while(1) {
		DebugInfraredSensor(1,1,0);
		DebugInfraredSensor(1,2,1);
		DebugInfraredSensor(1,3,3);
		UP_delay_ms(500);
	}
}

int main(void)
{	
	Init();
	UP_LCD_ClearScreen();

	//软启动
	SoftStart();
	
	//第一次上台
	MoveBeforeUpStage();
	FirstUpStage();	
}
