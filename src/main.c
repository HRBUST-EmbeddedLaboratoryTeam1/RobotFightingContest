#include "UPLib\\UP_System.h"


/**************************************************************************************************************/
/***********************************************����Begin*******************************************************/
/**************************************************************************************************************/

//����͵�����
const int MOTOR_LEFT = 5;
const int MOTOR_RIGHT = 6;
const int GEAR_FRONT_LEFT = 3;
const int GEAR_FRONT_RIGHT = 4;
const int GEAR_BACK_LEFT = 1;
const int GEAR_BACK_RIGHT = 2;

//���ƽ��λ�ýǶ�
const int GEAR_ANGLE_FRONT_LEFT = 500 + 20;	 //��ǰצƽ��λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT = 550 - 20; //��ǰצƽ��λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT = 520;	     //���צƽ��λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT = 450;	     //�Һ�צƽ��λ�ýǶ�

const int GEAR_ANGLE_FRONT_LEFT_ONSTAGE = 400;	//��ǰצ��̨λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT_ONSTAGE = 750;	//��ǰצ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT_ONSTAGE = 670;	//���צ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT_ONSTAGE = 300;	//�Һ�צ��̨λ�ýǶ�

const int GEAR_ANGLE_FRONT_LEFT_BEGIN = 250;	//��ǰצ��̨λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT_BEGIN = 900;	//��ǰצ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT_BEGIN = 170;	    //���צ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT_BEGIN = 800;	//�Һ�צ��̨λ�ýǶ�

//���������
const int INFRARED_BL = 10;	//�����⴫����
const int INFRARED_FL = 9;	//��ǰ���⴫����
const int INFRARED_BR = 7;	//�Һ���⴫����
const int INFRARED_FR = 6;	//��ǰ���⴫����
const int INFRARED_F = 0;	//ǰ����⴫����
const int INFRARED_B = 2;	//�����⴫����
const int INFRARED_L = 1;   //��ߺ��⴫����
const int INFRARED_R = 3; 	//�ұߺ��⴫����
const int INFRARED_LF = 11; //������ߺ��⴫����
const int INFRARED_RF = 8;  //�����ұߺ��⴫����
const int GRAY = 5;         //��������Ҷȴ�����
const int DISTANCE_F = 12;  //ǰ����
const int DISTANCE_R = 13;	//�Ҳ���
const int DISTANCE_L = 14;	//�����
const int DISTANCE_B = 15;	//�����
const int DIP_ANGLE = 4;	//���

//�����ʼ���Ƕ�
const int GEAR_ANGLE_INIT = 400; //��ʼ������任�Ƕ�

//�ٶ�
const int SPEED_GEAR = 800;	//����ٶ�
const int SPEED_MOTOR = 500; //��̨ʱ����ٶ�
const int SPEED_MOTOR_TURN = 400; //ת��ʱ����ٶ�
const int SPEED_MOTOR_ON_STAGE = 400; //��̨�����ٶ�
const int SPEED_MOTOR_ATTACK = 700;	//��̨��Ĺ����ٶ�
const int SPEED_MOTOR_TURN_ATTACK = 500; //��̨���ת�򹥻��ٶ�
const int SPEED_MOTOR_TURN_ATTACK_TIME = 400; //��̨��ת�򹥻���ʱ
const int SPEED_MOTOR_STOP = 1000;	//ɲ����ת�ٶ�

//��ʱ
const int DELAY_UP_STAGE = 750; //��̨��ʱ
const int DELAY_UP_BACK = 50; //��ת�ӳ�
const int DELAY_UP_STOP = 10; //ͣ������ʱ
const int DELAY_DOWN_STAGE = 100; //̨����ת��ʱ

/**************************************************************************************************************/
/***********************************************����End**********************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/***********************************************����Begin********************************************************/
/**************************************************************************************************************/

bool G_flagTurnF = FALSE;	//��¼�Ƿ���Ҫɲ��
bool AttackFlag = FALSE;	//�Ƿ���ù�����״̬

/**************************************************************************************************************/
/***********************************************����End**********************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/***********************************************��������Begin***************************************************/
/**************************************************************************************************************/

//��ʼ������
void InitSys();		//��ʼ��ϵͳ
void InitGear();	//��ʼ�����
void InitMotor();	//��ʼ�����
void InitForepaw(); //��ʼ��ǰצ
void InitHindpaw(); //��ʼ����צ 
void InitClaw();	//��ʼ��צ��

//�ƶ�����
void MoveForword(int); 		//��ǰ��
void MoveLeft(int);			//��ת
void MoveRight(int);		//��ת
void MoveBack(int);
void MoveStop(); 			//ͣ��

void SoftStart(); 	//����������
void OnStage();		//��̨�ϵ�������
void OutStage();    //̨��������̨����

void MoveBeforeUpStage(); 	//��̨ǰ����ǰ��
void FirstUpStage();		//��һ����̨

int GetInfraredSenorState();	//��ȡ���⴫����״̬
int ChangeInfrared(int); 		//���⴫����ģ����ת��Ϊ������
int GetGraySenorState(); 		//��ȡ�Ҷȴ�����״̬
int GrayCheck();				//���ݻҶȴ�������ȡ�ٶ�

void ClawDownF();	//����ǰצ
void ClawDownB();	//���º�צ

bool Fight();

//Debug����
void LcdShowInt(char[], int); 			//LCD��Ļ����ʾ����
void DebugGearbalan();					//����צ��ƽ��λ��
void DebugInfraredSensor(int,int,int);	//���Ժ��⴫����
void DebugGrayScaleSensor(); 			//���ԻҶȴ�����
void DebugDistance(int);				//���Բ��
void DebugDipAngle();					//�������

/***************************************************************************************************************/
/***********************************************��������End******************************************************/
/***************************************************************************************************************/



/***************************************************************************************************************/
/***********************************************������Begin******************************************************/
/***************************************************************************************************************/

int main(void)
{	
	//��ʼ������
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

	//������
	// SoftStart();
	
	//��һ����̨
	// MoveBeforeUpStage();
	// FirstUpStage();	
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);

	//̨��Ϲ���
	// OnStage();
	OutStage();
}

/**************************************************************************************************************/
/**********************************************������End********************************************************/
/**************************************************************************************************************/



/***************************************************************************************************************/
/**********************************************��ʼ������Begin***************************************************/
/***************************************************************************************************************/

/**
 * Title: InitSys()
 * Return: None
 * Author: Ben
 * Descr: ��ʼ��ϵͳ
 * LastBuild: 20200928
 */
void InitSys()
{
    /*��ʼ��ϵͳ*/
    UP_System_Init();

	// printf("DEMO 1.0\n");	//��ʾDemo����
	// UP_LCD_ShowCharacterString(0,1,"BenFromHRBUST");	//��ʾ�����Ŷ�
	// UP_LCD_ShowCharacterString(0,2,"�����˸񶷴���");	//��ʾ����Ҳ��֪����ɶ��
	// UP_delay_ms(500);	//��ʱ2s    
	// UP_LCD_ClearScreen();	//����

	//��ʼ�����
	InitGear();
	InitMotor();

	//����Ԥ������
	InitClaw();
}

/**
 * Title: InitGear()
 * Return: None
 * Author: Ben
 * Descr: ��ʼ�����ж��
 * LastBuild: 20200928
 */
void InitGear()
{
	// printf("SET SERVO MODE\n");	//���ģʽ
	UP_CDS_SetMode(GEAR_FRONT_LEFT, CDS_SEVMODE);		//����3�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(GEAR_FRONT_RIGHT, CDS_SEVMODE);		//����6�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(GEAR_BACK_LEFT, CDS_SEVMODE);		//����4�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(GEAR_BACK_RIGHT, CDS_SEVMODE);		//����5�Ŷ��Ϊ���ģʽ	
	// printf("SET FINISH\n");	//���ģʽ
}

/**
 * Title: InitMotor()
 * Return: None
 * Author: Ben
 * Descr: ��ʼ�����ж��
 * LastBuild: 20200928
 */
void InitMotor()
{
	// printf("SET MOTO MODE\n");	//���ģʽ
	UP_CDS_SetMode(MOTOR_LEFT, CDS_MOTOMODE);	//����1�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(MOTOR_RIGHT, CDS_MOTOMODE);	//����2�Ŷ��Ϊ���ģʽ	
	// printf("SET FINISH\n");	//���ģʽ
}

/**
 * Title: InitForepaw()
 * Return: None
 * Author: Altria
 * Descr: ��ʼ��ǰצ
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
 * Descr: ��ʼ����צ
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
 * Descr: ����צ�ӳ�ʼ״̬
 * LastBuild: 20200929
 */
void InitClaw()
{
	InitForepaw();
	InitHindpaw();
	UP_delay_ms(500);
}

/****************************************************************************************************************/
/***********************************************��ʼ������End*****************************************************/
/****************************************************************************************************************/



/***************************************************************************************************************/
/***********************************************�ƶ�����Begin****************************************************/
/***************************************************************************************************************/
/**
 * Title: MoveStop()
 * Return: None
 * Author: Altria
 * Descr: ͣ��
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
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�speed��ǰ��ʻ
 * LastBuild: 20201006
 */
void MoveForword(int speed) {
	UP_CDS_SetSpeed(MOTOR_LEFT, speed + 15);
	UP_CDS_SetSpeed(MOTOR_RIGHT, -speed);
	G_flagTurnF = TRUE;
}

/**
 * Title: MoveBack(int)
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�speed�����ʻ
 * LastBuild: 20201006
 */
void MoveBack(int speed) {
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed - 15);
	UP_CDS_SetSpeed(MOTOR_RIGHT, speed);
}

/**
 * Title: MoveRight(int)
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�speed����ת��ʻ
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
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�speed��ת��ʻ
 * LastBuild: 20201006
 */
void MoveLeft(int speed) {
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed);
	UP_CDS_SetSpeed(MOTOR_RIGHT, -speed);
	G_flagTurnF = FALSE;
}

/***************************************************************************************************************/
/***********************************************�ƶ�����End******************************************************/
/***************************************************************************************************************/

/**
 * Title: SoftStart()
 * Return: None
 * Author: Altria
 * Descr: ����������
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
 * Descr: ��̨ǰ������������̨��λ��
 * LastBuild: 20201004
 */
void MoveBeforeUpStage() {
	MoveBack(SPEED_MOTOR);
	UP_delay_ms(300);	//��������̨��Ե
}

/**
 * Title: FirstUpStage()
 * Return: None
 * Author: Altria
 * Descr: ��һ����̨
 * LastBuild: 20200930
 */
void FirstUpStage()
{
	//��צ����
	UP_CDS_SetAngle(GEAR_BACK_LEFT,GEAR_ANGLE_BACK_LEFT + 150, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_BACK_RIGHT,GEAR_ANGLE_BACK_RIGHT - 150, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE);

	//��צ��λ
	InitHindpaw();
	// UP_delay_ms(DELAY_UP_STAGE - 100);

	//ǰצ����
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT + 200, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT - 200, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
	//ǰצ��λ
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
	MoveStop();
	// UP_delay_ms(DELAY_UP_STAGE + 50);
	
	//���빥��״̬��ת��
	MoveLeft(SPEED_MOTOR_TURN_ATTACK);
	UP_delay_ms(770);
	MoveStop();
}


/**
 * Title: ClawDownF()
 * Return: None
 * Author: Ben
 * Descr: ����ǰצ
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
 * Descr: ���º�צ
 * LastBuild: 20201007
 */
void ClawDownB() {
	UP_CDS_SetAngle(4,GEAR_ANGLE_BACK_LEFT,SPEED_GEAR);
	UP_CDS_SetAngle(5,GEAR_ANGLE_BACK_RIGHT,SPEED_GEAR);
}

/**
 * Title: GetInfraredSenorState()
 * Return: int - ����С��״̬����Ϊ0~8״̬��
 * Author: Ben
 * Descr: ���ݺ���ģ���ֵ������С����̨�ϵ�״̬���Ƿ�����̨��Ե�� 
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
	int InfraredSensorStateTurn;	//ת�����״̬
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
 * Descr: ��̨�ϵ�������
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
 * Return: int - ���غ��⴫������ֵ����������
 * Author: Ben
 * Descr: �����⴫������ģ��ֵ��Ϊ���������ڵ�-0�����ڵ�-1
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
	//ǰצ�ͺ�צ��̧����
	InitClaw();
	//��ת
	while (ChangeInfrared(INFRARED_L) == 1 || ChangeInfrared(INFRARED_R) == 1) {
		MoveLeft(SPEED_MOTOR_TURN);
	}
	while (ChangeInfrared(INFRARED_B) == 0) {
		MoveForword(SPEED_MOTOR_ON_STAGE);
	}
	//ת����ȷ��λ��
	MoveLeft(SPEED_MOTOR_TURN);
	UP_delay_ms(DELAY_DOWN_STAGE);
	//��̨
	MoveForword(SPEED_MOTOR_ON_STAGE);
	FirstUpStage();
}

/**************************************************************************************************************/
/***********************************************DEBUG����******************************************************/
/**************************************************************************************************************/


/**
 * Title: LcdShowInt()
 * Return: None
 * Author: Altria
 * Descr: ��ʾ������ʾ����x
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
 * Descr: ���Զ��ƽ��λ��
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
 * Descr: �������⴫��������LCD����ʾ��������Ӧ��ֵ
 * LastBuild: 20201004
 */
void DebugSensor(int x,int y,int id) {
	int AD = UP_ADC_GetValue(id);
	// LcdShowInt(AD);
	// printf("begin\n");
	UP_LCD_ShowInt(x,y,AD);	//��ʾ���⴫����ֵ
	// printf("%d\n",AD);
	UP_delay_ms(400);
	UP_LCD_ClearScreen();
	// printf("end\n");
}

/**
 * ���Ծ���
 */
void DebugDistance(int dis) {
	int disState = UP_ADC_GetValue(dis);
	LcdShowInt("DISTANCE", disState);
}

/**
 * �������
 */
void DebugDipAngle() {
	int angle = UP_ADC_GetValue(DIP_ANGLE);
	LcdShowInt("DIP_ANGLE", angle);
}