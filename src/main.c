#include "UPLib\\UP_System.h"


/**************************************************************************************************************/
/***********************************************常量Begin*******************************************************/
/**************************************************************************************************************/

//舵机编号
const int GEAR_ANGLE_3 = 490;	//3号舵机平衡位置角度 
const int GEAR_ANGLE_6 = 485;	//6号舵机平衡位置角度
const int GEAR_ANGLE_4 = 511;	//4号舵机平衡位置角度
const int GEAR_ANGLE_5 = 515;	//5号舵机平衡位置角度

//传感器编号
const int INFRARED_BL = 4;	//左后红外传感器
const int INFRARED_FL = 5;	//左前红外传感器
const int INFRARED_BR = 6;	//右后红外传感器
const int INFRARED_FR = 7;	//右前红外传感器
const int INFRARED_F = 8;	//前侧红外传感器
const int INFRARED_B = 3;	//后侧红外传感器
const int INFRARED_L = 1;   //左边红外传感器
const int INFRARED_R = 0; 	//右边红外传感器
const int GRAY_BL = 10;		//左后灰度传感器
const int GRAY_FL = 9;		//左前灰度传感器
const int GRAY_BR = 11;		//右后灰度传感器
const int GRAY_FR = 2;		//右前灰度传感器
const int GRAY = 12;        //中央灰度传感器

//舵机初始化角度
const int GEAR_ANGLE_INIT = 400; //初始化舵机变换角度

//速度
const int SPEED_GEAR = 600;	//舵机速度
const int SPEED_MOTOR = 340; //上台时电机速度
const int SPEED_MOTOR_TURN = 550; //转向时电机速度
const int SPEED_MOTOR_ON_STAGE = 400; //上台后电机速度
const int SPEED_MOTOR_ATTACK = 400;	//上台后的攻击速度
const int SPEED_MOTOR_TURN_ATTACK = 350;	//上台后的转向攻击速度
const int SPEED_MOTOR_TURN_ATTACK_TIME = 400; //上台后转向攻击延时

//延时
const int DELAY_UP_STAGE = 750; //上台延时
const int DELAY_UP_STOP_BACK = 1000; //后退延时
const int DELAY_UP_BACK = 3; //反转延迟

/**************************************************************************************************************/
/***********************************************常量End**********************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/***********************************************变量Begin********************************************************/
/**************************************************************************************************************/

bool G_flagTurnF = FALSE;	//记录是否需要刹车

/**************************************************************************************************************/
/***********************************************变量End**********************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/***********************************************声明函数Begin***************************************************/
/**************************************************************************************************************/

//初始化函数
void InitSys();		//初始化系统
void InitGear();	//初始化舵机
void InitMotor();	//初始化电机
void InitForepaw(); //初始化前爪
void InitHindpaw(); //初始化后爪 
void InitClaw();	//初始化爪子

//移动函数
void MoveForword(int); 		//向前走
void MoveLeft(int);			//左转
void MoveRight(int);		//右转
void MoveQuickStop(int);    //反转
void MoveBack(int);
void MoveStop(); 			//停下

void SoftStart(); 	//软启动函数
void OnStage();		//在台上的主函数

void MoveBeforeUpStage(); 	//上台前的向前走
void FirstUpStage();		//第一次上台

int GetInfraredSenorState();	//获取红外传感器状态
int ChangeInfrared(int); 		//红外传感器模拟量转话为数字量
int GetGraySenorState(); 		//获取灰度传感器状态

void ClawDownF();	//放下前爪
void ClawDownB();	//放下后爪

//Debug函数
// void DebugSensor(int,int,int);
void LcdShowInt(int); 	//LCD屏幕上显示数字
void DebugGearbalan();	//测试爪子平衡位置
void DebugInfraredSensor(int,int,int); //测试红外传感器
void DebugGrayScaleSensor(); //测试灰度传感器

/***************************************************************************************************************/
/***********************************************声明函数End******************************************************/
/***************************************************************************************************************/



/***************************************************************************************************************/
/***********************************************主函数Begin******************************************************/
/***************************************************************************************************************/

int main(void)
{	
	//初始化函数
	InitSys();
	// DebugGrayScaleSensor();

	// UP_LCD_ClearScreen();

	// AD = UP_ADC_GetValue(INFRARED_F);
	// // LcdShowInt(AD);
	// if(AD == 0) {
	// 	MoveQuickStop(SPEED_MOTOR_ON_STAGE);
	// 	UP_delay_ms(10);
	// }

	//软启动
	SoftStart();
	
	//第一次上台
	MoveBeforeUpStage();
	FirstUpStage();	

	// DebugInfraredSensor(1,1,INFRARED_F);

	//台上瞎溜达
	OnStage();
}

/**************************************************************************************************************/
/**********************************************主函数End********************************************************/
/**************************************************************************************************************/



/***************************************************************************************************************/
/**********************************************初始化函数Begin***************************************************/
/***************************************************************************************************************/

/**
 * Title: InitSys()
 * Return: None
 * Author: Ben
 * Descr: 初始化系统
 * LastBuild: 20200928
 */
void InitSys()
{
    /*初始化系统*/
    UP_System_Init();

	// printf("DEMO 1.0\n");	//显示Demo名称
	// UP_LCD_ShowCharacterString(0,1,"BenFromHRBUST");	//显示作者团队
	// UP_LCD_ShowCharacterString(0,2,"机器人格斗大赛");	//显示（我也不知道是啥）
	// UP_delay_ms(500);	//延时2s    
	// UP_LCD_ClearScreen();	//清屏

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
	// printf("SET SERVO MODE\n");	//舵机模式
	UP_CDS_SetMode(3, CDS_SEVMODE);		//设置3号舵机为舵机模式	
	UP_CDS_SetMode(6, CDS_SEVMODE);		//设置6号舵机为舵机模式	
	UP_CDS_SetMode(4, CDS_SEVMODE);		//设置4号舵机为舵机模式	
	UP_CDS_SetMode(5, CDS_SEVMODE);		//设置5号舵机为舵机模式	
	// printf("SET FINISH\n");	//舵机模式
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
	// printf("SET MOTO MODE\n");	//电机模式
	UP_CDS_SetMode(1, CDS_MOTOMODE);	//设置1号舵机为电机模式	
	UP_CDS_SetMode(2, CDS_MOTOMODE);	//设置2号舵机为电机模式	
	// printf("SET FINISH\n");	//电机模式
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
	UP_delay_ms(500);
}

/****************************************************************************************************************/
/***********************************************初始化函数End*****************************************************/
/****************************************************************************************************************/



/***************************************************************************************************************/
/***********************************************移动函数Begin****************************************************/
/***************************************************************************************************************/
/**
 * Title: MoveStop()
 * Return: None
 * Author: Altria
 * Descr: 停下
 * LastBuild: 20200929
 */
void MoveStop() {
	MoveBack(SPEED_MOTOR_ON_STAGE + 400);
	UP_delay_ms(3);
}

/**
 * Title: MoveForword(int)
 * args: spped - 运行速度
 * Return: None
 * Author: Ben
 * Descr: 以速度speed向前行驶
 * LastBuild: 20201006
 */
void MoveForword(int speed) {
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, speed);
	G_flagTurnF = TRUE;
}

/**
 * Title: MoveBack(int)
 * args: spped - 运行速度
 * Return: None
 * Author: Ben
 * Descr: 以速度speed向后行驶
 * LastBuild: 20201006
 */
void MoveBack(int speed) {
	UP_CDS_SetSpeed(1, speed);
	UP_CDS_SetSpeed(2, -speed);
}

/**
 * Title: MoveQuickStop(int)
 * args: spped - 运行速度
 * Return: None
 * Author: Ben
 * Descr: 以速度speed反转，抵消惯性影响，快速刹车
 * LastBuild: 20201006
 */
void MoveQuickStop(int speed) {
	UP_CDS_SetSpeed(1, speed + 200);
	UP_CDS_SetSpeed(2, -speed - 200);
}

/**
 * Title: MoveRight(int)
 * args: spped - 运行速度
 * Return: None
 * Author: Ben
 * Descr: 以速度speed向右转行驶
 * LastBuild: 20201006
 */
void MoveRight(int speed) {
	if (G_flagTurnF == TRUE) {
		MoveStop();
	}
	UP_CDS_SetSpeed(2, speed - 25);
	UP_CDS_SetSpeed(1, speed + 25);
	// UP_delay_ms(100);
	G_flagTurnF = FALSE;
}

/**
 * Title: MoveLeft(int)
 * args: spped - 运行速度
 * Return: None
 * Author: Ben
 * Descr: 以速度speed左转行驶
 * LastBuild: 20201006
 */
void MoveLeft(int speed) {
	if (G_flagTurnF == TRUE) {
		MoveStop();
	}
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, -speed);
	// UP_delay_ms(100);
	G_flagTurnF = FALSE;
}

/***************************************************************************************************************/
/***********************************************移动函数End******************************************************/
/***************************************************************************************************************/




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
		infraredSensorLeft = ChangeInfrared(1);
		infraredSensorRight = ChangeInfrared(0);
		// printf("first: %d %d\n",infraredSensorLeft,infraredSensorRight);
		if(infraredSensorLeft == 0 && infraredSensorRight == 0) {
			break;
		}
	}
	// printf("Game Begin!\n");
}

/**
 * Title: MoveBeforeUpStage()
 * Return: None
 * Author: Altria
 * Descr: 上台前行走至可以上台的位置
 * LastBuild: 20201004
 */
void MoveBeforeUpStage() {
	MoveForword(SPEED_MOTOR);
	UP_delay_ms(1000);	//行走至擂台边缘
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
	UP_delay_ms(DELAY_UP_STAGE);

	//前爪复位
	InitForepaw();
	UP_delay_ms(DELAY_UP_STAGE - 100);

	//Τ诺?
	UP_CDS_SetAngle(4, GEAR_ANGLE_4 - 120, SPEED_GEAR);
	UP_CDS_SetAngle(5, GEAR_ANGLE_5 + 120, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);

	//进入攻击状态（前爪放下）
	ClawDownF();
	// ClawDownB();
	InitHindpaw();
	UP_delay_ms(DELAY_UP_STAGE);
}


/**
 * Title: ClawDownF()
 * Return: None
 * Author: Ben
 * Descr: 放下前爪
 * LastBuild: 20201007
 */
void ClawDownF() {
	UP_CDS_SetAngle(3,GEAR_ANGLE_3 + 105,SPEED_GEAR);
	UP_CDS_SetAngle(6,GEAR_ANGLE_6 - 105,SPEED_GEAR);
}

/**
 * Title: ClawDownB()
 * Return: None
 * Author: Ben
 * Descr: 放下后爪
 * LastBuild: 20201007
 */
void ClawDownB() {
	UP_CDS_SetAngle(4,GEAR_ANGLE_4,SPEED_GEAR);
	UP_CDS_SetAngle(5,GEAR_ANGLE_5,SPEED_GEAR);
}

/**
 * Title: GetInfraredSenorState()
 * Return: int - 返回小车状态，分为0~8状态。
 * Author: Ben
 * Descr: 根据红外模块的值，返回小车在台上的状态（是否在擂台边缘） 
 * LastBuild: 20201004
 */
int GetInfraredSenorState() {

	if(ChangeInfrared(INFRARED_FR)==0&&ChangeInfrared(INFRARED_FL)==0&&ChangeInfrared(INFRARED_BR)==0&&ChangeInfrared(INFRARED_BL)==0)
		return 0;
	else if(ChangeInfrared(INFRARED_FR)==1&&ChangeInfrared(INFRARED_FL)==0&&ChangeInfrared(INFRARED_BR)==0&&ChangeInfrared(INFRARED_BL)==0)
		return 1;
	else if(ChangeInfrared(INFRARED_FR)==0&&ChangeInfrared(INFRARED_FL)==1&&ChangeInfrared(INFRARED_BR)==0&&ChangeInfrared(INFRARED_BL)==0)
		return 2;
	else if(ChangeInfrared(INFRARED_FR)==0&&ChangeInfrared(INFRARED_FL)==0&&ChangeInfrared(INFRARED_BR)==1&&ChangeInfrared(INFRARED_BL)==0)
		return 3;
	else if(ChangeInfrared(INFRARED_FR)==0&&ChangeInfrared(INFRARED_FL)==0&&ChangeInfrared(INFRARED_BR)==0&&ChangeInfrared(INFRARED_BL)==1)
		return 4;
	else if(ChangeInfrared(INFRARED_FR)==1&&ChangeInfrared(INFRARED_FL)==1&&ChangeInfrared(INFRARED_BR)==0&&ChangeInfrared(INFRARED_BL)==0)
		return 5;
	else if(ChangeInfrared(INFRARED_FR)==0&&ChangeInfrared(INFRARED_FL)==1&&ChangeInfrared(INFRARED_BR)==0&&ChangeInfrared(INFRARED_BL)==1)
		return 6;
	else if(ChangeInfrared(INFRARED_FR)==0&&ChangeInfrared(INFRARED_FL)==0&&ChangeInfrared(INFRARED_BR)==1&&ChangeInfrared(INFRARED_BL)==1)
		return 7;
	else if(ChangeInfrared(INFRARED_FR)==1&&ChangeInfrared(INFRARED_FL)==0&&ChangeInfrared(INFRARED_BR)==1&&ChangeInfrared(INFRARED_BL)==0)
		return 8;
	return -1;
}

/**
 * Title: GetGraySenorState()
 * Return: int - 返回小车灰度传感器状态，共0~1种
 * Author: Ben
 * Descr: 根据灰度传感器的值，返回小车在台上的状态（推箱子时是否会掉下去） 
 * LastBuild: 20201007
 */
int GetGraySenorState() {
	int graySenorFL, graySenorFR, graySenorBL, graySenorBR;
	graySenorFL = UP_ADC_GetValue(GRAY_FL);
	graySenorFR = UP_ADC_GetValue(GRAY_FR);
	graySenorBL = UP_ADC_GetValue(GRAY_BL);
	graySenorBR = UP_ADC_GetValue(GRAY_BR);

	// printf("%d %d %d %d\n",graySenorFL,graySenorFR,graySenorBL,graySenorBR);
	// UP_delay_ms(400);
	// UP_LCD_ClearScreen();

	//后面快下去了
	if(graySenorBL < 750 || graySenorBR < 500) {
		return 0;
	}
	//前面快掉下来了
	else if(graySenorFL < 650 || graySenorFR < 650){
		return 1;
	}
	return -1;
}

void GrayCheck() {
	int GrayState;
	GrayState = UP_ADC_GetValue(GRAY);
	LcdShowInt(GrayState);
	if(GrayState <= 950) {
		// printf("%d\n",GrayState);
		MoveBack(SPEED_MOTOR_ON_STAGE + 150);
		UP_delay_ms(1000);
	}
}

void Fight() {
	int cnt = 0;
	int countCnt = 60;
	if(ChangeInfrared(INFRARED_B) == 0 || ChangeInfrared(INFRARED_L) == 0 || ChangeInfrared(INFRARED_R) == 0) {
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(3);
		// MoveStop();
		// UP_delay_ms(100);
		if(ChangeInfrared(INFRARED_B) == 0) {
			MoveLeft(SPEED_MOTOR_TURN);
			countCnt = 120;
		} else if(ChangeInfrared(INFRARED_L) == 0) {
			MoveLeft(SPEED_MOTOR_TURN);
		} else if(ChangeInfrared(INFRARED_R) == 0) {
			MoveRight(SPEED_MOTOR_TURN);
		}
		while(ChangeInfrared(INFRARED_F) == 1 && cnt <= countCnt) {
			cnt++;
			// printf("%d\n",cnt);
		}
		cnt = 0;
		UP_delay_ms(500);
		MoveStop();
	}
	if (ChangeInfrared(INFRARED_F) == 0) {	//前面检测到物体
		MoveForword(SPEED_MOTOR_ATTACK);
	}
}

void WakeOnStage() {
	int InfraredSensorStateTurn;	//转向红外状态
	InfraredSensorStateTurn = GetInfraredSenorState();
	switch (InfraredSensorStateTurn)
	{
	case 0:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(500);
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 1:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(DELAY_UP_STOP_BACK);
		MoveLeft(SPEED_MOTOR_TURN);
		break;
	case 2:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(DELAY_UP_STOP_BACK);
		MoveRight(SPEED_MOTOR_TURN);
		break;
	case 3:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(500);
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 4:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(500);
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 5:
		MoveStop();
		MoveBack(SPEED_MOTOR_ON_STAGE);
		UP_delay_ms(DELAY_UP_STOP_BACK);
		MoveRight(SPEED_MOTOR_TURN);
		UP_delay_ms(500);
		break;
	case 6:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(DELAY_UP_STOP_BACK);
		MoveRight(SPEED_MOTOR_TURN);
		break;
	case 7:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(500);
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 8:
		// MoveStop();
		// MoveBack(SPEED_MOTOR_ON_STAGE);
		// UP_delay_ms(DELAY_UP_STOP_BACK);
		MoveLeft(SPEED_MOTOR_TURN);
		break;
	default:
		break;
	}
}

/**
 * Title: OnStage()
 * Return: None
 * Author: Altria
 * Descr: 在台上的主函数
 * LastBuild: 20201007
 */
void OnStage() {
	while(1) {
		// GrayCheck();
		WakeOnStage();
		Fight();
	}
}

/**
 * Title: ChangeInfrared()
 * Return: int - 返回红外传感器的值（数字量）
 * Author: Ben
 * Descr: 将红外传感器的模拟值改为数字量，遮挡-0，不遮挡-1
 * LastBuild: 20201007
 */
int ChangeInfrared(int id) {
	int AD = UP_ADC_GetValue(id);
	if(AD <= 1000) return 0;
	else return 1;
}





/**************************************************************************************************************/
/***********************************************DEBUG函数******************************************************/
/**************************************************************************************************************/


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
 * Title: DebugSensor(int)
 * Return: None
 * Author: Altria
 * Descr: 调试任意传感器，在LCD上显示传感器对应数值
 * LastBuild: 20201004
 */
void DebugSensor(int x,int y,int id) {
	int AD = UP_ADC_GetValue(id);
	// LcdShowInt(AD);
	// printf("begin\n");
	UP_LCD_ShowInt(x,y,AD);	//显示红外传感器值
	// printf("%d\n",AD);
	UP_delay_ms(400);
	UP_LCD_ClearScreen();
	// printf("end\n");
}

/**
 * Title: DebugGrayScaleSensor()
 * Return: None
 * Author: Altria
 * Descr: 调试灰度传感器
 * LastBuild: 20201004
 */
void DebugGrayScaleSensor() {
	int AD1,AD2,AD3,AD4;
	ClawDownF();
	ClawDownB();
	UP_delay_ms(DELAY_UP_STAGE);
	while(1) {
		AD1 = UP_ADC_GetValue(GRAY_BL);
		AD2 = UP_ADC_GetValue(GRAY_BR);
		AD3 = UP_ADC_GetValue(GRAY_FL);   
		AD4 = UP_ADC_GetValue(GRAY_FR);
		// printf("BL: %d\n BR: %d\n FL: %d\n FR: %d\n",AD1,AD2,AD3,AD4);
		UP_delay_ms(400);
		UP_LCD_ClearScreen();
	}
}