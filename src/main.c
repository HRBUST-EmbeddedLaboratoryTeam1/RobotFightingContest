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
<<<<<<< HEAD
const int GEAR_ANGLE_FRONT_LEFT = 500 + 20;	 //��ǰצƽ��λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT = 550 - 20; //��ǰצƽ��λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT = 520;	     //���צƽ��λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT = 450;	     //�Һ�צƽ��λ�ýǶ�

const int GEAR_ANGLE_FRONT_LEFT_ONSTAGE = 400;	//��ǰצ��̨λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT_ONSTAGE = 750;	//��ǰצ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT_ONSTAGE = 670;	//���צ��̨λ�ýǶ�
=======
const int GEAR_ANGLE_FRONT_LEFT = 520;	//��ǰצƽ��λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT = 630;	//��ǰצƽ��λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT = 520;	  //���צƽ��λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT = 450;	//�Һ�צƽ��λ�ýǶ�

const int GEAR_ANGLE_FRONT_LEFT_ONSTAGE = 400;	//��ǰצ��̨λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT_ONSTAGE = 750;	//��ǰצ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_LEFT_ONSTAGE = 670;	  //���צ��̨λ�ýǶ�
>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291
const int GEAR_ANGLE_BACK_RIGHT_ONSTAGE = 300;	//�Һ�צ��̨λ�ýǶ�

const int GEAR_ANGLE_FRONT_LEFT_BEGIN = 250;	//��ǰצ��̨λ�ýǶ� 
const int GEAR_ANGLE_FRONT_RIGHT_BEGIN = 900;	//��ǰצ��̨λ�ýǶ�
<<<<<<< HEAD
const int GEAR_ANGLE_BACK_LEFT_BEGIN = 170;	    //���צ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT_BEGIN = 800;	//�Һ�צ��̨λ�ýǶ�
=======
const int GEAR_ANGLE_BACK_LEFT_BEGIN = 170;	  //���צ��̨λ�ýǶ�
const int GEAR_ANGLE_BACK_RIGHT_BEGIN = 800;	//�Һ�צ��̨λ�ýǶ�

>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291

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

//�����ʼ���Ƕ�
const int GEAR_ANGLE_INIT = 400; //��ʼ������任�Ƕ�

//�ٶ�
const int SPEED_GEAR = 800;	//����ٶ�
const int SPEED_MOTOR = 340; //��̨ʱ����ٶ�
const int SPEED_MOTOR_TURN = 350; //ת��ʱ����ٶ�
const int SPEED_MOTOR_ON_STAGE = 370; //��̨�����ٶ�
const int SPEED_MOTOR_ATTACK = 400;	//��̨��Ĺ����ٶ�
const int SPEED_MOTOR_TURN_ATTACK = 500; //��̨���ת�򹥻��ٶ�
const int SPEED_MOTOR_TURN_ATTACK_TIME = 400; //��̨��ת�򹥻���ʱ

//��ʱ
const int DELAY_UP_STAGE = 750; //��̨��ʱ
const int DELAY_UP_STOP_BACK = 200; //������ʱ
const int DELAY_UP_BACK = 3; //��ת�ӳ�

/**************************************************************************************************************/
/***********************************************����End**********************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/***********************************************����Begin********************************************************/
/**************************************************************************************************************/

bool G_flagTurnF = FALSE;	//��¼�Ƿ���Ҫɲ��

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
void MoveQuickStop(int);    //��ת
void MoveBack(int);
void MoveStop(); 			//ͣ��

void SoftStart(); 	//����������
void OnStage();		//��̨�ϵ�������

void MoveBeforeUpStage(); 	//��̨ǰ����ǰ��
void FirstUpStage();		//��һ����̨

int GetInfraredSenorState();	//��ȡ���⴫����״̬
int ChangeInfrared(int); 		//���⴫����ģ����ת��Ϊ������
int GetGraySenorState(); 		//��ȡ�Ҷȴ�����״̬

void ClawDownF();	//����ǰצ
void ClawDownB();	//���º�צ

//Debug����
// void DebugSensor(int,int,int);
void LcdShowInt(int); 	//LCD��Ļ����ʾ����
void DebugGearbalan();	//����צ��ƽ��λ��
void DebugInfraredSensor(int,int,int); //���Ժ��⴫����
void DebugGrayScaleSensor(); //���ԻҶȴ�����

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

	//������
	//SoftStart();
	
	//��һ����̨
	// MoveBeforeUpStage();
	// FirstUpStage();	

	// DebugInfraredSensor(1,1,INFRARED_F);

	//̨��Ϲ���
	//OnStage();
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
	UP_CDS_SetSpeed(MOTOR_LEFT, speed);
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
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed);
	UP_CDS_SetSpeed(MOTOR_RIGHT, speed);
}

/**
 * Title: MoveQuickStop(int)
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�speed��ת����������Ӱ�죬����ɲ��
 * LastBuild: 20201006
 */
void MoveQuickStop(int speed) {
<<<<<<< HEAD
	UP_CDS_SetSpeed(MOTOR_LEFT, speed + 200);
	UP_CDS_SetSpeed(MOTOR_RIGHT, -speed - 200);
=======
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed - 200);
	UP_CDS_SetSpeed(MOTOR_RIGHT, speed + 200);
>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291
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
	if (G_flagTurnF == TRUE) {
		MoveStop();
	}
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
	if (G_flagTurnF == TRUE) {
		MoveStop();
	}
	UP_CDS_SetSpeed(MOTOR_LEFT, -speed);
	UP_CDS_SetSpeed(MOTOR_RIGHT, -speed);
	// UP_delay_ms(100);
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
<<<<<<< HEAD
	UP_delay_ms(1800);	//��������̨��Ե
	//MoveQuickStop(SPEED_MOTOR);
=======
	UP_delay_ms(1000);	//��������̨��Ե
	MoveQuickStop(SPEED_MOTOR);
>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291
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
	// printf("XXXXXXXXXXXXXXXXX");
	//��צ����
	UP_CDS_SetAngle(GEAR_BACK_LEFT,GEAR_ANGLE_BACK_LEFT + 150, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_BACK_RIGHT,GEAR_ANGLE_BACK_RIGHT - 150, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE);

	//��צ��λ
	InitHindpaw();
<<<<<<< HEAD
	// UP_delay_ms(DELAY_UP_STAGE - 100);

	//ǰצ����
=======
	UP_delay_ms(DELAY_UP_STAGE - 100);

	//��ŵ?
>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT + 200, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT - 200, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
<<<<<<< HEAD
	//ǰצ��λ
=======
>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291
	UP_CDS_SetAngle(GEAR_FRONT_LEFT, GEAR_ANGLE_FRONT_LEFT, SPEED_GEAR);
	UP_CDS_SetAngle(GEAR_FRONT_RIGHT, GEAR_ANGLE_FRONT_RIGHT, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
	MoveStop();
<<<<<<< HEAD
	// UP_delay_ms(DELAY_UP_STAGE + 50);
	
	//���빥��״̬��ת��
	MoveLeft(SPEED_MOTOR_TURN_ATTACK);
	UP_delay_ms(770);
	MoveStop();
	
=======
	UP_delay_ms(DELAY_UP_STAGE + 50);
	
//	//���빥��״̬��ǰצ���£�
>>>>>>> 18eaff450de4aad7e56bae90f4f1849d7f0d7291
//	ClawDownF();
//	// ClawDownB();
//	InitHindpaw();
//	UP_delay_ms(DELAY_UP_STAGE);
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

void GrayCheck() {
	int GrayState;
	GrayState = UP_ADC_GetValue(GRAY);
	// LcdShowInt(GrayState);
	if (GrayState >= 2800) {
		MoveForword(SPEED_MOTOR_ON_STAGE + 100);
	} else {
		MoveForword(SPEED_MOTOR_ON_STAGE - 200);
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
	if (ChangeInfrared(INFRARED_LF) == 0) {
		MoveRight(SPEED_MOTOR_ON_STAGE);
	} else if (ChangeInfrared(INFRARED_RF) == 0) {
		MoveLeft(SPEED_MOTOR_ON_STAGE);
	}
	if (ChangeInfrared(INFRARED_F) == 0) {	//ǰ���⵽����
		MoveForword(SPEED_MOTOR_ATTACK);
	}
}

void WakeOnStage() {
	int InfraredSensorStateTurn;	//ת�����״̬
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
		// MoveStop();
		MoveBack(SPEED_MOTOR_ON_STAGE);
		UP_delay_ms(DELAY_UP_STOP_BACK);
		MoveRight(SPEED_MOTOR_TURN);
		// UP_delay_ms(500);
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
 * Descr: ��̨�ϵ�������
 * LastBuild: 20201007
 */
void OnStage() {
	while(1) {
		WakeOnStage();
		// Fight();
		GrayCheck();
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
void LcdShowInt(int x) {
	printf("grayValue = %d\n",x);
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
 * Title: DebugGrayScaleSensor()
 * Return: None
 * Author: Altria
 * Descr: ���ԻҶȴ�����
 * LastBuild: 20201004
 */
// void DebugGrayScaleSensor() {
// 	int AD1,AD2,AD3,AD4;
// 	ClawDownF();
// 	ClawDownB();
// 	UP_delay_ms(DELAY_UP_STAGE);
// 	while(1) {
// 		AD1 = UP_ADC_GetValue(GRAY_BL);
// 		AD2 = UP_ADC_GetValue(GRAY_BR);
// 		AD3 = UP_ADC_GetValue(GRAY_FL);   
// 		AD4 = UP_ADC_GetValue(GRAY_FR);
// 		// printf("BL: %d\n BR: %d\n FL: %d\n FR: %d\n",AD1,AD2,AD3,AD4);
// 		UP_delay_ms(400);
// 		UP_LCD_ClearScreen();
// 	}
// }