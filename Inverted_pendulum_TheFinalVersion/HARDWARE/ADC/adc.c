 #include   "adc.h"
 
//==== PA4  ADC4     �õ��Ƕ�
 
		    
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
				ADC_InitTypeDef ADC_InitStructure; 
				GPIO_InitTypeDef GPIO_InitStructure;
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
			 
				RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
				///=======   PA1
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
				GPIO_Init(GPIOA, &GPIO_InitStructure);	

				ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

				ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
				ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//====ģ��ת�������ڵ�ͨ��ģʽ
				ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//====ģ��ת�������ڵ���ת��ģʽ
				ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ⲿ��������
				ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
				ADC_InitStructure.ADC_NbrOfChannel = 1;	//====˳����й���ת����ADCͨ������Ŀ
				ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
 

				ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
				
				ADC_ResetCalibration(ADC1);	//����ָ����ADC1��У׼�Ĵ���
				 
				while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
				
				ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
			 
				while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
			 
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
					//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
				ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    
				
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������	
				 
				while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

				return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


int  Angle_Get(void)  // ====      0 - 180
{
	
							short temp=0;
							short Angle_value = 0;
	            short adc_value;
							u8 i=0;
							for(i=0;i<5;i++)
							{
								temp += Get_Adc(1);        //====
							}
							temp = temp/5;
  				
							if((temp>=1113)&&(temp<=3241))
							{
								Angle_value = 180-(short)((temp-1113)/11.789);
							}
							else
							{
								if(temp<1113)	{temp+=4096;}
								Angle_value = -(short)((temp-3241)/10.961);
								if(Angle_value==-180)	{Angle_value=180;}
							}
							
							if(Angle_value<0)
							{
								Angle_value +=360;
							}
					    
							return Angle_value;
							
}
























