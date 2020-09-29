#include "UPLib\\UP_System.h"

//�������ֵ3.41 Լ���� 1��
const int GEAR_ANGLE_3 = 490;	//3�Ŷ��ƽ��λ�ýǶ� 
const int GEAR_ANGLE_6 = 485;	//6�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_4 = 511;	//4�Ŷ��ƽ��λ�ýǶ�
const int GEAR_ANGLE_5 = 515;	//5�Ŷ��ƽ��λ�ýǶ�

const int SPEED_GEAR = 350;	//����ٶ�

void InitSys();	//��ʼ��ϵͳ
void InitGear();	//��ʼ�����
void InitMotor();	//��ʼ�����
void InitClaw();	//��ʼ��צ��

void FirstUpStage();	//��һ����̨

void DebugGearbalan();	//����צ��ƽ��λ��
void DebugInfraredSensor(int,int,int); //���Ժ��⴫����

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
 * Title: InitMClaw()
 * Return: None
 * Author: Ben
 * Descr: ����צ�ӳ�ʼ״̬
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
 * Title: FirstUpStage()
 * Return: None
 * Author: Ben
 * Descr: ��һ����̨
 * LastBuild: 20200928
 */
void FirstUpStage()
{
	//ǰצ����
	UP_CDS_SetAngle(3,400,SPEED_GEAR);
	UP_CDS_SetAngle(6,575,SPEED_GEAR);
	UP_delay_ms(1500);
	
	//��������
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
	
	// DebugGearBalan();	//���Զ��ƽ��λ��

	/*****************************************************����������********************************************************/

	//��һ����̨
	FirstUpStage();

	// UP_CDS_SetAngle(3, GEAR_ANGLE-160, 300);				//���ö��ת��(0~1023��Ӧ0~300��)���ٶȣ�0~1023��
	// UP_CDS_SetAngle(6, GEAR_ANGLE+130, 300);				//���ö��ת��(0~1023��Ӧ0~300��)���ٶȣ�0~1023��
	UP_delay_ms(1000);								
	UP_LCD_ClearLine(1);							//�����2���ַ�














		
//		UP_CDS_SetAngle(4, 200, 500);				//���ö��ת��(0~1023��Ӧ0~300��)���ٶȣ�0~1023��
//		UP_delay_ms(1000);								
//		UP_LCD_ClearLine(1);							//�����2���ַ�
//		
//		UP_CDS_SetAngle(5, 200, 500);				//���ö��ת��(0~1023��Ӧ0~300��)���ٶȣ�0~1023��
//		UP_delay_ms(1000);								
//		UP_LCD_ClearLine(1);							//�����2���ַ�
//		
//		UP_CDS_SetAngle(6, 200, 500);				//���ö��ת��(0~1023��Ӧ0~300��)���ٶȣ�0~1023��
//		UP_delay_ms(1000);								
//		UP_LCD_ClearLine(1);							//�����2���ַ�
		
		
//		printf("\nAngle:235");							
//		UP_CDS_SetAngle(4, 800, 500);	
//		UP_delay_ms(2000); 								//��ʱ2s
//		UP_LCD_ClearScreen();							//����
//		
//		

//		
//		printf("Speed:+800");	
//		UP_CDS_SetSpeed(1, 800);					//���õ��ģʽ�µ��ٶȣ���Χ-1023~+1023	
//		UP_delay_ms(1000);								//��ʱ1s
//		UP_LCD_ClearLine(1);							//�����2���ַ�
//		
//		printf("\nSpeed:-800");	
//		UP_CDS_SetSpeed(2, 800);					//���õ��ģʽ�µ��ٶȣ���Χ-1023~+1023
//		UP_delay_ms(1000); 								//��ʱ1s		
//		UP_LCD_ClearLine(1);							//�����2���ַ�
//		
//		printf("\nStop");
//		UP_CDS_SetSpeed(1, 0);						//ֹͣ
//		UP_delay_ms(1000); 								//��ʱ2s
//		UP_LCD_ClearScreen();							//���� 
}
