#include "UPLib\\UP_System.h"


/**************************************************************************************************************/
/***********************************************常量Begin*******************************************************/
/**************************************************************************************************************/

//舵机和电机编号
const int MOTOR_LEFT = 5;
const int MOTOR_RIGHT = 6;
const int GEAR_FRONT_LEFT = 3;
const int GEAR_FRONT_RIGHT = 4;
const int GEAR_BACK_LEFT = 1;
const int GEAR_BACK_RIGHT = 2;

//舵机平衡位置角度
const int GEAR_ANGLE_FRONT_LEFT = 500 + 20;	 //左前爪平衡位置角度 
const int GEAR_ANGLE_FRONT_RIGHT = 550 - 20; //右前爪平衡位置角度
const int GEAR_ANGLE_BACK_LEFT = 520;	     //左后爪平衡位置角度
const int GEAR_ANGLE_BACK_RIGHT = 450;	     //右后爪平衡位置角度

const int GEAR_ANGLE_FRONT_LEFT_ONSTAGE = 400;	//左前爪上台位置角度 
const int GEAR_ANGLE_FRONT_RIGHT_ONSTAGE = 750;	//右前爪上台位置角度
const int GEAR_ANGLE_BACK_LEFT_ONSTAGE = 670;	//左后爪上台位置角度
const int GEAR_ANGLE_BACK_RIGHT_ONSTAGE = 300;	//右后爪上台位置角度

const int GEAR_ANGLE_FRONT_LEFT_BEGIN = 250;	//左前爪上台位置角度 
const int GEAR_ANGLE_FRONT_RIGHT_BEGIN = 900;	//右前爪上台位置角度
const int GEAR_ANGLE_BACK_LEFT_BEGIN = 170;	    //左后爪上台位置角度
const int GEAR_ANGLE_BACK_RIGHT_BEGIN = 800;	//右后爪上台位置角度

//传感器编号
const int INFRARED_BL = 10;	//左后红外传感器
const int INFRARED_FL = 9;	//左前红外传感器
const int INFRARED_BR = 7;	//右后红外传感器
const int INFRARED_FR = 6;	//右前红外传感器
const int INFRARED_F = 0;	//前侧红外传感器
const int INFRARED_B = 2;	//后侧红外传感器
const int INFRARED_L = 1;   //左边红外传感器
const int INFRARED_R = 3; 	//右边红外传感器
const int INFRARED_LF = 11; //铲子左边红外传感器
const int INFRARED_RF = 8;  //铲子右边红外传感器
const int GRAY = 5;         //铲子下面灰度传感器
const int DISTANCE_F = 12;  //前侧测距
const int DISTANCE_R = 13;	//右侧测距
const int DISTANCE_L = 14;	//左侧测距
const int DISTANCE_B = 15;	//后侧测距
const int DIP_ANGLE = 4;	//倾角

//舵机初始化角度
const int GEAR_ANGLE_INIT = 400; //初始化舵机变换角度

//速度
const int SPEED_GEAR = 800;	//舵机速度
const int SPEED_MOTOR = 500; //上台时电机速度
const int SPEED_MOTOR_TURN = 400; //转向时电机速度
const int SPEED_MOTOR_ON_STAGE = 400; //上台后电机速度
const int SPEED_MOTOR_ATTACK = 700;	//上台后的攻击速度
const int SPEED_MOTOR_TURN_ATTACK = 500; //上台后的转向攻击速度
const int SPEED_MOTOR_TURN_ATTACK_TIME = 400; //上台后转向攻击延时
const int SPEED_MOTOR_STOP = 1000;	//刹车反转速度

//延时
const int DELAY_UP_STAGE = 750; //上台延时
const int DELAY_UP_BACK = 50; //反转延迟
const int DELAY_UP_STOP = 10; //停下来延时
const int DELAY_DOWN_STAGE = 100; //台下旋转延时

/**************************************************************************************************************/
/***********************************************常量End**********************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/***********************************************变量Begin********************************************************/
/**************************************************************************************************************/

bool G_flagTurnF = FALSE;	//记录是否需要刹车
bool AttackFlag = FALSE;	//是否调用过攻击状态

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
void MoveBack(int);
void MoveStop(); 			//停下

void SoftStart(); 	//软启动函数
void OnStage();		//在台上的主函数
void OutStage();    //台下主动上台函数

void MoveBeforeUpStage(); 	//上台前的向前走
void FirstUpStage();		//第一次上台

int GetInfraredSenorState();	//获取红外传感器状态
int ChangeInfrared(int); 		//红外传感器模拟量转话为数字量
int GetGraySenorState(); 		//获取灰度传感器状态
int GrayCheck();				//根据灰度传感器获取速度

void ClawDownF();	//放下前爪
void ClawDownB();	//放下后爪

bool Fight();

//Debug函数
void LcdShowInt(char[], int); 			//LCD屏幕上显示数字
void DebugGearbalan();					//测试爪子平衡位置
void DebugInfraredSensor(int,int,int);	//测试红外传感器
void DebugGrayScaleSensor(); 			//测试灰度传感器
void DebugDistance(int);				//测试测距
void DebugDipAngle();					//测试倾角

/***************************************************************************************************************/
/***********************************************声明函数End******************************************************/
/***************************************************************************************************************/



/***************************************************************************************************************/
/***********************************************主函数Begin******************************************************/
/***************************************************************************************************************/

int main(void)
{	
	//初始化函数
	// InitSys();
	// DebugGrayScaleSensor();
	UP_System_Init();
	// UP_LCD_ClearScreen();

	// AD = UP_ADC_GetValue(INFRARED_F);
	// // LcdShowInt(AD);
	// if(AD == 0) {
	// 	MoveQuickStop(SPEED_MOTOR_ON_STAGE);
	// 	UP_delay_ms(10);
	// }
	// while(1) {
	// 	printf("L = %d\n", ChangeInfrared(INFRARED_L));
	// 	printf("R = %d\n", ChangeInfrared(INFRARED_R));
	// 	printf("B = %d\n", ChangeInfrared(INFRARED_B));
	// 	printf("LF = %d\n", ChangeInfrared(INFRARED_LF));
	// 	printf("RF = %d\n", ChangeInfrared(INFRARED_RF));
	// 	UP_delay_ms(400);
	// 	UP_LCD_ClearScreen();
	// }

	//软启动
	// SoftStart();
	
	//第一次上台
	// MoveBeforeUpStage();
	// FirstUpStage();	
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);

	//台上瞎溜达
	// OnStage();
	OutStage();
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
	UP_CDS_SetMode(GEAR_FRONT_LEFT, CDS_SEVMODE);		//设置3号舵机为舵机模式	
	UP_CDS_SetMode(GEAR_FRONT_RIGHT, CDS_SEVMODE);		//设置6号舵机为舵机模式	
	UP_CDS_SetMode(GEAR_BACK_LEFT, CDS_SEVMODE);		//设置4号舵机为舵机模式	
	UP_CDS_SetMode(GEAR_BACK_RIGHT, CDS_SEVMODE);		//设置5号舵机为舵机模式	
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
	UP_CDS_SetMode(MOTOR_LEFT, CDS_MOTOMODE);	//设置1号舵机为电机模式	
	UP_CDS_SetMode(MOTOR_RIGHT, CDS_MOTOMODE);	//设置2号舵机为电机模式	
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
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT_BEGIN, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT_BEGIN, SPEED_GEAR);
}

/**
 * Title: InitHindpaw()
 * Return: None
 * Author: Altria
 * Descr: 初始化后爪
 * LastBuild: 20200929
 */
void InitHindpaw() {
	UP_CDS_SetAngle(GEAR_BACK_LEFT, GEAR_ANGLE_BACK_LEFT_BEGIN, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_BACK_RIGHT, GEAR_ANGLE_BACK_RIGHT_BEGIN, SPEED_GEAR);
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
	// MoveBack(SPEED_MOTOR_ON_STAGE + 400);
	UP_CDS_SetSpeed(MOTOR_LEFT, 0);
	UP_CDS_SetSpeed(MOTOR_RIGHT, 0);
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
	UP_CDS_SetSpeed(MOTOR_LEFT, speed + 15);
	UP_CDS_SetSpeed(MOTOR_RIGHT, -speed);
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
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed - 15);
	UP_CDS_SetSpeed(MOTOR_RIGHT, speed);
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
	UP_CDS_SetSpeed(MOTOR_LEFT, speed);
	UP_CDS_SetSpeed(MOTOR_RIGHT, speed);
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
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed);
	UP_CDS_SetSpeed(MOTOR_RIGHT, -speed);
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
		infraredSensorLeft = ChangeInfrared(INFRARED_L);
		infraredSensorRight = ChangeInfrared(INFRARED_R);
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
	MoveBack(SPEED_MOTOR);
	UP_delay_ms(300);	//行走至擂台边缘
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
	//后爪向下
	UP_CDS_SetAngle(GEAR_BACK_LEFT,GEAR_ANGLE_BACK_LEFT + 150, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_BACK_RIGHT,GEAR_ANGLE_BACK_RIGHT - 150, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE);

	//后爪复位
	InitHindpaw();
	// UP_delay_ms(DELAY_UP_STAGE - 100);

	//前爪向下
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT + 200, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT - 200, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
	//前爪复位
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
	MoveStop();
	// UP_delay_ms(DELAY_UP_STAGE + 50);
	
	//进入攻击状态，转身
	MoveLeft(SPEED_MOTOR_TURN_ATTACK);
	UP_delay_ms(770);
	MoveStop();
}


/**
 * Title: ClawDownF()
 * Return: None
 * Author: Ben
 * Descr: 放下前爪
 * LastBuild: 20201007
 */
void ClawDownF() {
	UP_CDS_SetAngle(3,GEAR_ANGLE_FRONT_LEFT + 105,SPEED_GEAR);
	UP_CDS_SetAngle(6,GEAR_ANGLE_FRONT_RIGHT - 105,SPEED_GEAR);
}

/**
 * Title: ClawDownB()
 * Return: None
 * Author: Ben
 * Descr: 放下后爪
 * LastBuild: 20201007
 */
void ClawDownB() {
	UP_CDS_SetAngle(4,GEAR_ANGLE_BACK_LEFT,SPEED_GEAR);
	UP_CDS_SetAngle(5,GEAR_ANGLE_BACK_RIGHT,SPEED_GEAR);
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

int GrayCheck() {
	int GrayState;
	float GrayImin, GrayImax;
	float SpeedImin, SpeedImax;
	float Speed;
	GrayState = UP_ADC_GetValue(GRAY);
	// LcdShowInt("GrayState", GrayState);

	GrayImin = 2500, GrayImax = 3100;
	SpeedImin = 200, SpeedImax = 500;
	Speed = ((SpeedImax - SpeedImin) / (GrayImax - GrayImin)) * (GrayState) + SpeedImin ;
	// LcdShowInt("Speed", (int)Speed);
	return (int)Speed;
}

bool Fight() {
	int cnt;
	if (ChangeInfrared(INFRARED_B) == 0) {
		cnt = 0;
		while ((ChangeInfrared(INFRARED_LF)==1 || ChangeInfrared(INFRARED_RF)==1) && ChangeInfrared(INFRARED_R)==1 && ChangeInfrared(INFRARED_L)==1 && cnt < 120) {
			cnt ++;
			MoveLeft(SPEED_MOTOR_TURN_ATTACK);
		}
		return TRUE;
	}
	else if (ChangeInfrared(INFRARED_L) == 0) {
		// LcdShowInt("L", 0);
		cnt = 0;
		while ((ChangeInfrared(INFRARED_LF)==1 || ChangeInfrared(INFRARED_RF)==1) && ChangeInfrared(INFRARED_R)==1 && ChangeInfrared(INFRARED_B)==1 && cnt < 60) {
			cnt ++;
			MoveRight(SPEED_MOTOR_TURN_ATTACK);
		}
		return TRUE;
	}
	else if (ChangeInfrared(INFRARED_R) == 0) {
		// LcdShowInt("R", 0);
		cnt = 0;
		while ((ChangeInfrared(INFRARED_LF)==1 || ChangeInfrared(INFRARED_RF)==1) && ChangeInfrared(INFRARED_B)==1 && ChangeInfrared(INFRARED_L)==1 && cnt < 60) {
			cnt ++;
			MoveLeft(SPEED_MOTOR_TURN_ATTACK);
		}
		return TRUE;
	}
	else if ((ChangeInfrared(INFRARED_LF) == 0 || ChangeInfrared(INFRARED_RF) == 0) && (ChangeInfrared(INFRARED_FL) == 0 && ChangeInfrared(INFRARED_FR) == 0)) {
		// LcdShowInt("F", 0);
		AttackFlag = TRUE;
		MoveForword(SPEED_MOTOR_ATTACK);
		return TRUE;
	}
	else {
		// LcdShowInt("else", 0);
		if (AttackFlag == TRUE && (ChangeInfrared(INFRARED_FL) == 1 || ChangeInfrared(INFRARED_FR) == 1)) {
			MoveBack(SPEED_MOTOR_STOP);
			UP_delay_ms(DELAY_UP_BACK * 5);
		}
		AttackFlag = FALSE;
		MoveForword(SPEED_MOTOR_ON_STAGE);
		return TRUE;
	}
	// LcdShowInt("Normal", 0);
	return FALSE;
}

void WakeOnStage() {
	int InfraredSensorStateTurn;	//转向红外状态
	InfraredSensorStateTurn = GetInfraredSenorState();
	// LcdShowInt("DebugStatus", InfraredSensorStateTurn);
	switch (InfraredSensorStateTurn)
	{
	case 0:
		if (!Fight()) {
			// LcdShowInt("normal", 1);
			MoveForword(SPEED_MOTOR_ON_STAGE);
		} else {
			// LcdShowInt("Attack", 1);
		}
		break;
	case 1:
		if (G_flagTurnF == TRUE) {
			MoveBack(SPEED_MOTOR_STOP);
			UP_delay_ms(DELAY_UP_STOP);
		}
		MoveLeft(SPEED_MOTOR_TURN);
		break;
	case 2:
		if (G_flagTurnF == TRUE) {
			MoveBack(SPEED_MOTOR_STOP);
			UP_delay_ms(DELAY_UP_STOP);
		}
		MoveRight(SPEED_MOTOR_TURN);
		break;
	case 3:
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 4:
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 5:
		MoveBack(SPEED_MOTOR_STOP);
		UP_delay_ms(DELAY_UP_STOP);
		break;
	case 6:
		if (G_flagTurnF == TRUE) {
			MoveBack(SPEED_MOTOR_STOP);
			UP_delay_ms(DELAY_UP_STOP);
		}
		MoveRight(SPEED_MOTOR_TURN);
		break;
	case 7:
		MoveForword(SPEED_MOTOR_ON_STAGE);
		break;
	case 8:
		if (G_flagTurnF == TRUE) {
			MoveBack(SPEED_MOTOR_STOP);
			UP_delay_ms(DELAY_UP_STOP);
		}
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
		DebugDipAngle();
	    // WakeOnStage();
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

/**
 * Title: OutStage()
 * Return: void
 * Author: Ben
 * Descr: When you are out of the stage, called this function.
 */
void OutStage() {
	//前爪和后爪都抬起来
	InitClaw();
	//旋转
	while (ChangeInfrared(INFRARED_L) == 1 || ChangeInfrared(INFRARED_R) == 1) {
		MoveLeft(SPEED_MOTOR_TURN);
	}
	while (ChangeInfrared(INFRARED_B) == 0) {
		MoveForword(SPEED_MOTOR_ON_STAGE);
	}
	//转向正确的位置
	MoveLeft(SPEED_MOTOR_TURN);
	UP_delay_ms(DELAY_DOWN_STAGE);
	//上台
	MoveForword(SPEED_MOTOR_ON_STAGE);
	FirstUpStage();
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
void LcdShowInt(char ch[], int x) {
	printf("%s = %d\n", ch, x);
	UP_delay_ms(400);
	UP_LCD_ClearScreen();
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
 * 测试距离
 */
void DebugDistance(int dis) {
	int disState = UP_ADC_GetValue(dis);
	LcdShowInt("DISTANCE", disState);
}

/**
 * 测试倾角
 */
void DebugDipAngle() {
	int angle = UP_ADC_GetValue(DIP_ANGLE);
	LcdShowInt("DIP_ANGLE", angle);
}