#include "UPLib\\UP_System.h"


/***********************************************����Begin*******************************************************/

//�������ֵ3.41 Լ���� 1��
const int GEAR_ANGLE_3 = 490;	//3�Ŷ��ƽ��λ�ýǶ� 
const int GEAR_ANGLE_6 = 485;	//6�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_4 = 511;	//4�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_5 = 515;	//5�Ŷ��ƽ��λ�ýǶ�

const int InfraredBL = 4;	//�����⴫����
const int InfraredFL = 5;	//��ǰ���⴫����
const int InfraredBR = 6;	//�Һ���⴫����
const int InfraredFR = 7;	//��ǰ���⴫����

const int InfraredF = 3;		//ǰ����⴫����

const int GEAR_ANGLE_INIT = 400; //��ʼ������任�Ƕ�

const int SPEED_GEAR = 600;	//����ٶ�
const int SPEED_Motor = 320; //��̨ʱ����ٶ�
const int SPEED_Motor_Turn = 350; //ת��ʱ����ٶ�
const int SPEED_MotorOnStage = 300; //��̨�����ٶ�
const int DELAY_UpStage = 750; //��̨��ʱ

/***********************************************����End**********************************************************/



/***********************************************����Begin********************************************************/



/***********************************************����End**********************************************************/



/***********************************************��������Begin****************************************************/

void InitSys();	//��ʼ��ϵͳ
void InitGear();	//��ʼ�����
void InitMotor();	//��ʼ�����
void InitForepaw(); //��ʼ��ǰצ
void InitHindpaw(); //��ʼ����צ 
void InitClaw();	//��ʼ��צ��

void SoftStart(); //����������
void OnStage();	//��̨�ϵ�������

void MoveBeforeUpStage(); //��̨ǰ����ǰ��
void FirstUpStage();	//��һ����̨

void LcdShowInt(int); //LCD��Ļ����ʾ����
void DebugGearbalan();	//����צ��ƽ��λ��
void DebugInfraredSensor(int,int,int); //���Ժ��⴫����

void MoveForword(int); //��ǰ��
void MoveLeft(int);	//��ת
void MoveRight(int);	//��ת
void MoveBack(int);    //��ת
void MoveStop(); 	//ͣ��

int GetInfraredSenorState();	//��ȡ���⴫����״̬
int SpeedByGraySenor();		//���ݻҶȴ����������ٶ�
int ChangeInfrared(int); //���⴫����ģ����ת��Ϊ������

/***********************************************��������End******************************************************/



/***********************************************������Begin******************************************************/

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

/**********************************************������End********************************************************/



/**********************************************��ʼ������Begin***************************************************/

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
	UP_delay_ms(2000);	//��ʱ2s    
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

/***********************************************��ʼ������End*****************************************************/



/***********************************************�ƶ�����Begin****************************************************/
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
 * Author: Altria
 * Descr: ���ٶ�spee��ǰ��ʻ
 * LastBuild: 20200928
 */
void MoveForword(int speed) {
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, speed);
}

/**
 * Title: MoveBack(int)
 * args: spped - �����ٶ�
 * Return: None
 * Author: Altria
 * Descr: ���ٶ�speed��ת����������Ӱ��
 * LastBuild: 20201006
 */
void MoveBack(int speed) {
	UP_CDS_SetSpeed(1, speed);
	UP_CDS_SetSpeed(2, -speed);
}

/**
 * Title: MoveRight(int)
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�spee��ǰ��ʻ
 * LastBuild: 20201006
 */
void MoveRight(int speed) {
	MoveBack(SPEED_MotorOnStage);
	UP_delay_ms(5);
	UP_CDS_SetSpeed(1, speed);
	UP_CDS_SetSpeed(2, speed);
}

/**
 * Title: MoveLeft(int)
 * args: spped - �����ٶ�
 * Return: None
 * Author: Ben
 * Descr: ���ٶ�spee��ǰ��ʻ
 * LastBuild: 20201006
 */
void MoveLeft(int speed) {
	MoveBack(SPEED_MotorOnStage);
	UP_delay_ms(5);
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, -speed);
}

/***********************************************�ƶ�����End******************************************************/




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
		infraredSensorLeft = ChangeInfrared(0);
		infraredSensorRight = ChangeInfrared(1);
		printf("first: %d %d\n",infraredSensorLeft,infraredSensorRight);
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
	MoveForword(SPEED_Motor);
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
	UP_delay_ms(DELAY_UpStage);

	//ǰצ��λ
	InitForepaw();
	UP_delay_ms(DELAY_UpStage - 100);

	//��צ�ŵ�
	UP_CDS_SetAngle(4, GEAR_ANGLE_4 - 120, SPEED_GEAR);
	UP_CDS_SetAngle(5, GEAR_ANGLE_5 + 120, SPEED_GEAR);
	UP_delay_ms(DELAY_UpStage + 50);

	//��צ��λ
	InitHindpaw();
	UP_delay_ms(DELAY_UpStage);

	// MoveStop();
}

/**
 * Title: GetGraySenorNum()
 * Return: ���ݻҶȴ����������С���ٶ�ֵ
 * Author: Ben
 * Descr: ���ݻҶȴ���������С���ٶ�
 * LastBuild: 20201005
 */
int SpeedByGraySenor() {
	return SPEED_MotorOnStage + (UP_ADC_GetValue(2)-1600)/10;
}

/**
 * Title: GetInfraredSenorState()
 * Return: int - ����С��״̬����Ϊ0~8״̬��
 * Author: Ben
 * Descr: ���ݺ���ģ���ֵ������С����̨�ϵ�״̬���Ƿ�����̨��Ե�� 
 * LastBuild: 20201004
 */
int GetInfraredSenorState() {

	if(ChangeInfrared(InfraredFR)==0&&ChangeInfrared(InfraredFL)==0&&ChangeInfrared(InfraredBR)==0&&ChangeInfrared(InfraredBL)==0)
		return 0;
	else if(ChangeInfrared(InfraredFR)==1&&ChangeInfrared(InfraredFL)==0&&ChangeInfrared(InfraredBR)==0&&ChangeInfrared(InfraredBL)==0)
		return 1;
	else if(ChangeInfrared(InfraredFR)==0&&ChangeInfrared(InfraredFL)==1&&ChangeInfrared(InfraredBR)==0&&ChangeInfrared(InfraredBL)==0)
		return 2;
	else if(ChangeInfrared(InfraredFR)==0&&ChangeInfrared(InfraredFL)==0&&ChangeInfrared(InfraredBR)==1&&ChangeInfrared(InfraredBL)==0)
		return 3;
	else if(ChangeInfrared(InfraredFR)==0&&ChangeInfrared(InfraredFL)==0&&ChangeInfrared(InfraredBR)==0&&ChangeInfrared(InfraredBL)==1)
		return 4;
	else if(ChangeInfrared(InfraredFR)==1&&ChangeInfrared(InfraredFL)==1&&ChangeInfrared(InfraredBR)==0&&ChangeInfrared(InfraredBL)==0)
		return 5;
	else if(ChangeInfrared(InfraredFR)==0&&ChangeInfrared(InfraredFL)==1&&ChangeInfrared(InfraredBR)==0&&ChangeInfrared(InfraredBL)==1)
		return 6;
	else if(ChangeInfrared(InfraredFR)==0&&ChangeInfrared(InfraredFL)==0&&ChangeInfrared(InfraredBR)==1&&ChangeInfrared(InfraredBL)==1)
		return 7;
	else if(ChangeInfrared(InfraredFR)==1&&ChangeInfrared(InfraredFL)==0&&ChangeInfrared(InfraredBR)==1&&ChangeInfrared(InfraredBL)==0)
		return 8;
	return -1;
}

/**
 * Title: OnStage()
 * Return: None
 * Author: Ben
 * Descr: ��̨�ϵ�������
 * LastBuild: 20201006
 */
void OnStage() {
	int InfraredSensorState;
	int DebugErrorCnt = 0;
	while(1) {
		// printf("%d %d %d %d\n",UP_ADC_GetValue(4),UP_ADC_GetValue(5),UP_ADC_GetValue(6),UP_ADC_GetValue(7));
		// UP_delay_ms(400);
		// UP_LCD_ClearScreen();
		InfraredSensorState = GetInfraredSenorState();
		printf("%d\n",InfraredSensorState);
		// LcdShowInt(InfraredSensorState);
		// if (ChangeInfrared(InfraredB)==1) {	//����ײ������
		// 	if () {	//С��û����б ---------------------------------------------------------------
		// 		//������ ------------------------------------------------------------------------
		// 	}
		// 	else {
		// 		//����---------------------------------------------------------------------------
		// 	}
		// }
		// else if (ChangeInfrared(InfraredF)==1) {	//ǰ��ײ������
		// 	if () {	//С��û����б ---------------------------------------------------------------
		// 		//������ ------------------------------------------------------------------------
		// 	}
		// 	else {
		// 		//����---------------------------------------------------------------------------
		// 	}
		// }
		// else {
			switch (InfraredSensorState)
			{
			case 0:
				MoveForword(SPEED_MotorOnStage);
				break;
			case 1:
				MoveLeft(SPEED_Motor_Turn);
				break;
			case 2:
				MoveRight(SPEED_Motor_Turn);
				break;
			case 3:
				MoveRight(SPEED_Motor_Turn);
				break;
			case 4:
				MoveLeft(SPEED_Motor_Turn);
				break;
			case 5:
				MoveLeft(SPEED_Motor_Turn);
				break;
			case 6:
				MoveRight(SPEED_Motor_Turn);
				break;
			case 7:
				MoveForword(SPEED_MotorOnStage);
				break;
			case 8:
				MoveLeft(SPEED_Motor_Turn);
				// UP_delay_ms(500);
			default:
				DebugErrorCnt ++;
				UP_LCD_ClearScreen();
				printf("%d: ERROR!\n", DebugErrorCnt);
				printf("Infrared\n");
				break;
			}
		// }
	}
	
	//700 - 800��Ե
}

/**
 * Title: ChangeInfrared()
 * Return: int - ���غ��⴫������ֵ����������
 * Author: Ben
 * Descr: �����⴫������ģ��ֵ��Ϊ������
 * LastBuild: 20201005
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
