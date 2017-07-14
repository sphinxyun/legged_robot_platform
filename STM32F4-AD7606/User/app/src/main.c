/*
*********************************************************************************************************
*
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : �����������
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		v1.0    2015-12-09 armfly  �׷�
*
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"			/* �ײ�Ӳ������ */

static void AD7606_Mak(void);
static void AD7606_Disp(void);

/*�Ƕ�*/
float a[3],w[3],angle[3],T;
extern unsigned char Re_buf[11],temp_buf[11],counter;
extern unsigned char sign;
/*AD*/
static int16_t s_volt[8];
static int16_t s_dat[8];
static double s_force[8];

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
	unsigned char Temp[11];
	uint8_t ucFifoMode;
	int16_t i;	
	int16_t iTemp;
	
	
	bsp_Init();		/* Ӳ����ʼ�� */

	ucFifoMode = 0;	 	/* AD7606������ͨ����ģʽ */

	bsp_InitAD7606();	/* ����AD7606���õ�GPIO */
	AD7606_StartRecord(1000);		/* �����Զ��ɼ�ģʽ������Ƶ��1KHz�����ݴ����ȫ��FIFO */
	
	/*���ù�����������*/
	AD7606_SetOS(AD_OS_X64);		/* ����������6 */
	//AD7606_SetOS(AD_OS_NO);		/* �޹����� */
	AD7606_SetInputRange(0);	/* 0��ʾ��������Ϊ����5V, 1��ʾ����10V */
	AD7606_StartConvst();		/* ����1��ת�� */

	bsp_StartAutoTimer(0, 500);	/* ����1��200ms���Զ���װ�Ķ�ʱ�� */

	while (1)
	{
//		printf("count = %6d \r\n", count);
//		/* Ҳ������ sprintf�������һ��buf��Ȼ���ڷ��͵����� */
//		{
//			char buf[64];
//			sprintf(buf, "count = %6d \r", count);
//			comSendBuf(COM1, (uint8_t *)buf, strlen(buf));
//		}
		
//		AD7606_ReadNowAdc();		/* ��ȡ������� */
//		printf("CH1 = %6d, CH2 = %6d, CH3 = %6d, CH4 = %6d, \r\n",
//		g_tAD7606.sNowAdc[0], g_tAD7606.sNowAdc[1], g_tAD7606.sNowAdc[2], g_tAD7606.sNowAdc[3]);

		/* �������� */
		AD7606_Mak();
						 
		/* ��ӡADC������� */
//		AD7606_Disp(); 

		s_force[0]=80.0 / 1000 * (s_volt[0]+38);
		s_force[1]=80.0 / 1000 * (s_volt[1]+191);
		s_force[2]=160.0 / 1000 * (s_volt[2]-95);
		printf("%f,%f,%f,%f,%f,%f,%f,%f,%f", s_force[0],s_force[1],s_force[2],angle[0],angle[1],angle[2],a[0],a[1],a[2]);
//		printf("%6dmV,", s_volt[i]);
//		printf(" CH%d = %6d,0x%04X (-%d.%d%d%d V) \r\n", i+1, s_dat[i], (uint16_t)s_dat[i], iTemp /1000, (iTemp%1000)/100, (iTemp%100)/10,iTemp%10);
		printf("\r\n");
			
		

		if (ucFifoMode == 0)	/* AD7606 ��ͨ����ģʽ */
		{
			if (bsp_CheckTimer(0))
			{
				/* ÿ��500ms ����һ��. ���������ת�� */
				AD7606_ReadNowAdc();		/* ��ȡ������� */
				AD7606_StartConvst();		/* �����´�ת�� */
			}
		}
		if (ucFifoMode == 1)  /* AD7606����FIFO����ģʽ */
		{
			printf("\33[%dA", (int)1);  /* �������n�� */	
			printf("AD7606����FIFO����ģʽ (200KHz 8ͨ��ͬ���ɼ�)...\r\n");
			AD7606_StartRecord(200000);		/* ����200kHz�������� */
		}		
		
		
		
		if(sign)
		{  
			memcpy(Temp,Re_buf,11);
			sign=0;
			if(Re_buf[0]==0x55)       //���֡ͷ
			{  
				switch(Re_buf[1])
				{
					case 0x51: //��ʶ������Ǽ��ٶȰ�
					a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X����ٶ�
					a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y����ٶ�
					a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z����ٶ�
					T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //�¶�
					break;
					case 0x52: //��ʶ������ǽ��ٶȰ�
					w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X����ٶ�
					w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y����ٶ�
					w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z����ٶ�
					T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //�¶�
					break;
					case 0x53: //��ʶ������ǽǶȰ�
					angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
					angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
					angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
					T        = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //�¶�

					//printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);
					break;
					default:  break;
				}
				//printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);	
				//printf("X�Ƕȣ�%.2f  Y�Ƕȣ�%.2f  Z�Ƕȣ�%.2f  X�ٶȣ�%.2f  Y�ٶȣ�%.2f  Z�ٶȣ�%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);
			}

		}
//		bsp_DelayMS(50);

	}
}


/*
*********************************************************************************************************
*	�� �� ��: AD7606_Mak
*	����˵��: ��������������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AD7606_Mak(void)
{
	uint8_t i;
	int16_t value;  //�з���λ
	int32_t volt;
	
	for (i = 0; i < 8; i++)
	{		
	/* 
		32767 = 5V , ��������ֵ��ʵ�ʿ��Ը���5V��׼��ʵ��ֵ���й�ʽ���� 
		volt[i] = ((int16_t)dat[i] * 5000) / 32767;	����ʵ�ʵ�ѹֵ�����ƹ���ģ�������׼ȷ�������У׼            
		volt[i] = dat[i] * 0.3051850947599719
	*/	
		s_dat[i] = g_tAD7606.sNowAdc[i]& 0x0000FFFF;  //����֮��Ϊ�޷���λ����ֵ��value֮��Ϊ�з���λ��
		if (g_tAD7606.ucRange == 0)
		{
			s_volt[i] = (s_dat[i] * 5000) / 32767;
		}
		else
		{
			s_volt[i] = (s_dat[i] * 10000) / 32767;
		}
	}
}
 
/*
*********************************************************************************************************
*	�� �� ��: AD7606_Disp
*	����˵��: ��ʾ�����������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AD7606_Disp(void)
{
	int16_t i;	
	int16_t iTemp;

	/* ��ӡ�ɼ����� */
//	printf(" OS  =  %d \r\n", g_tAD7606.ucOS);
	
	for (i = 0; i < 4; i++)
	{                
   		iTemp = s_volt[i];	/* uV  */
		
		if (s_dat[i] < 0)
		{
			iTemp = -iTemp;
//			s_volt[0]=s_volt[0];
//			s_volt[1]=s_volt[1];
//			s_volt[2]=s_volt[2];
			printf("%6dmV  ", s_volt[i]);
			//printf(" CH%d = %6d,0x%04X (-%d.%d%d%d V) \r\n", i+1, s_dat[i], (uint16_t)s_dat[i], iTemp /1000, (iTemp%1000)/100, (iTemp%100)/10,iTemp%10);
		}
		else
		{
			printf("%6dmV  ", s_volt[i]);
      //printf(" CH%d = %6d,0x%04X ( %d.%d%d%d V) \r\n", i+1, s_dat[i], (uint16_t)s_dat[i] , iTemp /1000, (iTemp%1000)/100, (iTemp%100)/10,iTemp%10);                    
		}
	}
	printf("\r\n");
//	printf("\33[%dA", (int)9);  /* �������n�� */		
}
