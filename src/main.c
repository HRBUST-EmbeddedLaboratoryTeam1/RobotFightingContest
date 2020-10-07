#include "UPLib\\UP_System.h"


/**************************************************************************************************************/
/***********************************************����Begin*******************************************************/
/**************************************************************************************************************/

//������
const int GEAR_ANGLE_3 = 490;	//3�Ŷ��ƽ��λ�ýǶ� 
const int GEAR_ANGLE_6 = 485;	//6�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_4 = 511;	//4�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_5 = 515;	//5�Ŷ��ƽ��λ�ýǶ�

//���������
const int INFRARED_BL = 4;	//�����⴫����
const int INFRARED_FL = 5;	//��ǰ���⴫����
const int INFRARED_BR = 6;	//�Һ���⴫����
const int INFRARED_FR = 7;	//��ǰ���⴫����
const int INFRARED_F = 8;	//ǰ����⴫����
const int INFRARED_B = 3;	//�����⴫����
const int INFRARED_L = 1;   //��ߺ��⴫����
const int INFRARED_R = 0; 	//�ұߺ��⴫����
const int GRAY_BL = 10;		//���Ҷȴ�����
const int GRAY_FL = 9;		//��ǰ�Ҷȴ�����
const int GRAY_BR = 11;		//�Һ�Ҷȴ�����
const int GRAY_FR = 2;		//��ǰ�Ҷȴ�����

//�����ʼ���Ƕ�
const int GEAR_ANGLE_INIT = 400; //��ʼ������任�Ƕ�

//�ٶ�
const int SPEED_GEAR = 600;	//����ٶ�
const int SPEED_MOTOR = 400; //��̨ʱ����ٶ�
const int SPEED_MOTOR_TURN = 450; //ת��ʱ����ٶ�
const int SPEED_MOTOR_ON_STAGE = 450; //��̨�����ٶ�
const int SPEED_MOTOR_ATTACK = 600;	//��̨��Ĺ����ٶ�
const int SPEED_MOTOR_TURN_ATTACK = 500;	//��̨���ת�򹥻��ٶ�

//��ʱ
const int DELAY_UP_STAGE = 750; //��̨��ʱ
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
void MoveStop(); 			//ͣ��

void SoftStart(); 	//����������
void OnStage();		//��̨�ϵ�������

void MoveBeforeUpStage(); 	//��̨ǰ����ǰ��
void FirstUpStage();		//��һ����̨

int GetInfraredSenorState();	//��ȡ���⴫����״̬
int ChangeInfrared(int); 		//���⴫����ģ����ת��Ϊ������

void ClawDownF();	//����ǰצ
void ClawDownB();	//���º�צ

//Debug����
void LcdShowInt(int); 	//LCD��Ļ����ʾ����
void DebugGearbalan();	//����צ��ƽ��λ��
void DebugInfraredSensor(int,int,int); //���Ժ��⴫����

/***************************************************************************************************************/
/***********************************************��������End******************************************************/
/***************************************************************************************************************/



/***************************************************************************************************************/
/***********************************************������Begin******************************************************/
/***************************************************************************************************************/

int main(void)
{	
	InitSys();
	UP_LCD_ClearScreen();

	//������
	SoftStart();
	
	//��һ����̨
	MoveBeforeUpStage();
	FirstUpStage();	

	//̨��Ϲ���
	OnStage();
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

	printf("DEMO 1.0\n");	//��ʾDemo����
	UP_LCD_ShowCharacterString(0,1,"BenFromHRBUST");	//��ʾ�����Ŷ�
	UP_LCD_ShowCharacterString(0,2,"�����˸񶷴���");	//��ʾ����Ҳ��֪����ɶ��
	UP_delay_ms(500);	//��ʱ2s    
	UP_LCD_ClearScreen();	//����

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
	printf("SET SERVO MODE\n");	//���ģʽ
	UP_CDS_SetMode(3, CDS_SEVMODE);		//����3�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(6, CDS_SEVMODE);		//����6�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(4, CDS_SEVMODE);		//����4�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(5, CDS_SEVMODE);		//����5�Ŷ��Ϊ���ģʽ	
	printf("SET FINISH\n");	//���ģʽ
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
	printf("SET MOTO MODE\n");	//���ģʽ
	UP_CDS_SetMode(1, CDS_MOTOMODE);	//����1�Ŷ��Ϊ���ģʽ	
	UP_CDS_SetMode(2, CDS_MOTOMODE);	//����2�Ŷ��Ϊ���ģʽ	
	printf("SET FINISH\n");	//���ģʽ
}

/**
 * Title: InitForepaw()
 * Return: None
 * Author: Altria
 * Descr: ��ʼ��ǰצ
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
 * Descr: ��ʼ����צ
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
 * Descr: ����צ�ӳ�ʼ״̬
 * LastBuild: 20200929
 */
void InitClaw()
{
	InitForepaw();
	InitHindpaw();
	UP_delay_ms(2000);
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
	UP_CDS_SetSpeed(1, 0);
	UP_CDS_SetSpeed(2, 0);
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
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, speed);
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
	UP_CDS_SetSpeed(1, speed);
	UP_CDS_SetSpeed(2, -speed);
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
	UP_CDS_SetSpeed(1, speed);
	UP_CDS_SetSpeed(2, -speed);
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
		MoveQuickStop(SPEED_MOTOR_ON_STAGE);
		UP_delay_ms(DELAY_UP_BACK);
	}
	UP_CDS_SetSpeed(2, speed);
	UP_CDS_SetSpeed(1, speed);
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
		MoveQuickStop(SPEED_MOTOR_ON_STAGE);
		UP_delay_ms(DELAY_UP_BACK);
	}
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, -speed);
	G_flagTurnF = FALSE;
}

/***************************************************************************************************************/
/***********************************************�ƶ�����End******************************************************/
/***************************************************************************************************************/




/**
 * Title: SoftStart()
 * Return: None
 * Author: Alt��ria
 * Descr: ����������
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
	printf("Game Begin!\n");
}

/**
 * Title: MoveBeforeUpStage()
 * Return: None
 * Author: Altria
 * Descr: ��̨ǰ������������̨��λ��
 * LastBuild: 20201004
 */
void MoveBeforeUpStage() {
	MoveForword(SPEED_MOTOR);
	UP_delay_ms(1000);	//��������̨��Ե
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
	//ǰצ����
	UP_CDS_SetAngle(3,GEAR_ANGLE_3 - 90,SPEED_GEAR);
	UP_CDS_SetAngle(6,GEAR_ANGLE_6 + 90,SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE);

	//ǰצ��λ
	InitForepaw();
	UP_delay_ms(DELAY_UP_STAGE - 100);

	//��צ�ŵ�
	UP_CDS_SetAngle(4, GEAR_ANGLE_4 - 120, SPEED_GEAR);
	UP_CDS_SetAngle(5, GEAR_ANGLE_5 + 120, SPEED_GEAR);
	UP_delay_ms(DELAY_UP_STAGE + 50);

	//���빥��״̬��ǰצ���£�
	ClawDownF();
	ClawDownB();
	UP_delay_ms(DELAY_UP_STAGE);
}


/**
 * Title: ClawDownF()
 * Return: None
 * Author: Ben
 * Descr: ����ǰצ
 * LastBuild: 20201007
 */
void ClawDownF() {
	UP_CDS_SetAngle(3,GEAR_ANGLE_3,SPEED_GEAR);
	UP_CDS_SetAngle(6,GEAR_ANGLE_6,SPEED_GEAR);
}

/**
 * Title: ClawDownB()
 * Return: None
 * Author: Ben
 * Descr: ���º�צ
 * LastBuild: 20201007
 */
void ClawDownB() {
	UP_CDS_SetAngle(4,GEAR_ANGLE_4,SPEED_GEAR);
	UP_CDS_SetAngle(5,GEAR_ANGLE_5,SPEED_GEAR);
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

/**
 * Title: OnStage()
 * Return: None
 * Author: Ben
 * Descr: ��̨�ϵ�������
 * LastBuild: 20201007
 */
void OnStage() {
	int InfraredSensorStateTurn;	//ת�����״̬
	int DebugErrorCnt = 0;
	while(1) {
		//ת�򣬸���
		if (ChangeInfrared(INFRARED_F)==0) {		//ǰ���⵽����
			MoveForword(SPEED_MOTOR_ATTACK);
		}
		else if (ChangeInfrared(INFRARED_B)==0) {	//����������
			MoveRight(SPEED_MOTOR_TURN_ATTACK);
			UP_delay_ms(500);
		}
		else if (ChangeInfrared(INFRARED_L)==0) {	//����⵽����
			MoveLeft(SPEED_MOTOR_TURN_ATTACK);
			UP_delay_ms(250);
		}
		else if (ChangeInfrared(INFRARED_R)==0) {	//�Ҳ��⵽����
			MoveRight(SPEED_MOTOR_TURN_ATTACK);
			UP_delay_ms(250);
		}
		//Ѳ��
		else {
			InfraredSensorStateTurn = GetInfraredSenorState();
			switch (InfraredSensorStateTurn)
			{
			case 0:
				MoveForword(SPEED_MOTOR_ON_STAGE);
				break;
			case 1:
				MoveLeft(SPEED_MOTOR_TURN);
				break;
			case 2:
				MoveRight(SPEED_MOTOR_TURN);
				break;
			case 3:
				MoveForword(SPEED_MOTOR_ON_STAGE);
				break;
			case 4:
				MoveForword(SPEED_MOTOR_ON_STAGE);
				break;
			case 5:
				MoveRight(SPEED_MOTOR_TURN);
				break;
			case 6:
				MoveRight(SPEED_MOTOR_TURN);
				break;
			case 7:
				MoveForword(SPEED_MOTOR_ON_STAGE);
				break;
			case 8:
				MoveLeft(SPEED_MOTOR_TURN);
				break;
			default:
				DebugErrorCnt ++;
				UP_LCD_ClearScreen();
				printf("%d: ERROR!\n", DebugErrorCnt);
				printf("Infrared\n");
				break;
			}
		}
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
	UP_delay_ms(400);
	UP_LCD_ClearScreen();
	printf("%d\n",x);
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
void DebugGrayScaleSensor() {
	MoveForword(300);
	while(1) {
		// printf("2: ");
		DebugSensor(1,1,2);
		// printf("3: ");
		DebugSensor(2,2,3);
	}
}
