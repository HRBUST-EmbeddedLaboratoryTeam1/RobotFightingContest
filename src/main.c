#include "UPLib\\UP_System.h"

//�������ֵ3.41 Լ���� 1��
const int GEAR_ANGLE_3 = 490;	//3�Ŷ��ƽ��λ�ýǶ� 
const int GEAR_ANGLE_6 = 485;	//6�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_4 = 511;	//4�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_5 = 515;	//5�Ŷ��ƽ��λ�ýǶ�

const int GEAR_ANGLE_INIT = 400; //��ʼ������任�Ƕ�

const int SPEED_GEAR = 350;	//����ٶ�

void InitSys();	//��ʼ��ϵͳ
void InitGear();	//��ʼ�����
void InitMotor();	//��ʼ�����

void InitForepaw(); //��ʼ��ǰצ
void InitHindpaw(); //��ʼ����צ 

void InitClaw();	//��ʼ��צ��

void FirstUpStage();	//��һ����̨

void DebugGearbalan();	//����צ��ƽ��λ��
void DebugInfraredSensor(int,int,int); //���Ժ��⴫����


void MoveForword(int,int); //��ǰ��

/**
 * Title: Init()
 * Return: None
 * Author: Ben
 * Descr: ��ʼ��ϵͳ
 * LastBuild: 20200928
 */
void Init()
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

/**
 * Title: MoveForword(int,int)
 * args: spped - �����ٶ�
 * args: time - ����ʱ��
 * Return: None
 * Author: Altria
 * Descr: ���ٶ�spee��ǰ��ʻtimeʱ��
 * LastBuild: 20200928
 */
void MoveForword(int speed, int time) {
	UP_CDS_SetSpeed(1, -speed);
	UP_CDS_SetSpeed(2, speed);
	UP_delay_ms(time);
	UP_CDS_SetSpeed(1, 0);
	UP_CDS_SetSpeed(2, 0);
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
 * Title: DebugInfraredSensor(int)
 * Return: None
 * Author: Altria
 * Descr: ���Ժ��⴫����
 * LastBuild: 20200928
 */
void DebugInfraredSensor(int x,int y,int id) {
	int AD = UP_ADC_GetValue(id);
	// printf("begin\n");
	UP_LCD_ShowInt(x,y,AD);	//��ʾ���⴫����ֵ
	// printf("end\n");
}

/**
 * Title: DebugAllInfraredSensor(int)
 * Return: None
 * Author: Ben
 * Descr: ����ȫ�����⴫����
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

/**
 * Title: FirstUpStage()
 * Return: None
 * Author: Altria
 * Descr: ��һ����̨
 * LastBuild: 20200929
 */
void FirstUpStage()
{
	//ǰצ����
	UP_CDS_SetAngle(3,400,SPEED_GEAR);
	UP_CDS_SetAngle(6,575,SPEED_GEAR);
	UP_delay_ms(1500);
	
	//��������
	MoveForword(SPEED_GEAR,700);
	UP_delay_ms(1500);

	//ǰצ��λ
	InitForepaw();
	UP_delay_ms(1500);

	//��צ�ŵ�
	UP_CDS_SetAngle(4, GEAR_ANGLE_4 - 120, SPEED_GEAR);
	UP_CDS_SetAngle(5, GEAR_ANGLE_5 + 120, SPEED_GEAR);
	UP_delay_ms(1500);

	//ǰ������
	MoveForword(SPEED_GEAR,700);
	UP_delay_ms(1500);

	//��צ��λ
	InitHindpaw();
	UP_delay_ms(1500);
}

int main(void)
{	
	Init();

	// UP_LCD_ClearScreen();
	
	// DebugGearBalan();	//���Զ��ƽ��λ��

	/*******************************************����������**************************************************/

	//��һ����̨
	FirstUpStage();

	UP_delay_ms(1000);								
	UP_LCD_ClearLine(1);							//�����2���ַ�
}
