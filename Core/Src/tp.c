#include "tp.h"
#include "ssd1963_headerfile.h"
float te=0;		
uint16_t ADS_Read_AD(uint8_t CMD)	  
{ 	 		
	uint16_t lc_cnt=0;
	uint8_t SEND[2]={0xFF,0xFF};
	uint8_t REC[2];
	uint16_t ret_val;
	HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,GPIO_PIN_RESET);	
	HAL_SPI_Transmit(&hspi2,&CMD,1,100);	
	for(lc_cnt=0;lc_cnt<300;lc_cnt++);
	HAL_SPI_TransmitReceive(&hspi2,SEND,&REC[0],1,100);	
	HAL_SPI_TransmitReceive(&hspi2,SEND,&REC[1],1,100);	
	HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,GPIO_PIN_SET);	
	//REC[0] &= 0x0F;
	ret_val = (REC[0] << 8) | (REC[1]);
	ret_val >>= 4;
	return(ret_val);
}
uint16_t ADS_Read_XY(uint8_t xy)
{
	uint16_t i, j; 
	uint16_t buf[READ_TIMES];
	uint16_t sum=0;
	uint16_t temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 

uint8_t Read_ADS(uint16_t *x,uint16_t *y)
{
	uint16_t xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	  												   
	if(xtemp<70||ytemp<70)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}
uint8_t Read_ADS2(uint16_t *x,uint16_t *y) 
{
	uint16_t x1,y1;
 	uint16_t x2,y2;
 	uint8_t flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
} 

uint8_t tp_read(uint16_t *x,uint16_t *y)
{						
	uint32_t lc_tp_x=0,lc_tp_y=0,lc_tp_z1=0,lc_tp_z2=0;
	float lc_tp_pres=0;	
	uint8_t lc_cnt=0;
	for(lc_cnt=0;lc_cnt<5;lc_cnt++)
	{
			lc_tp_x += ADS_Read_AD(CMD_RDX);				
			lc_tp_y += ADS_Read_AD(CMD_RDY);
			lc_tp_z1 += ADS_Read_AD(CMD_RDZ1);
			lc_tp_z2 += ADS_Read_AD(CMD_RDZ2);
	}
	lc_tp_x /= 5;
	lc_tp_y /= 5;
	lc_tp_z1 /= 5;
	lc_tp_z2 /= 5;
	
	if(lc_tp_z2 > lc_tp_z1)
	{
		lc_tp_pres = 100 * lc_tp_x;			
		lc_tp_pres = lc_tp_pres * (lc_tp_z2 - lc_tp_z1);			
		lc_tp_pres = lc_tp_pres /(4096 * lc_tp_z1);
	}
	else
	{
		lc_tp_pres = 0;
	}			
	te = lc_tp_pres;
	if(lc_tp_pres < tp_pres_thr && lc_tp_x > tp_x_min && lc_tp_y > tp_y_min)				
	{	
		lc_tp_x -= tp_x_min;
		lc_tp_x *= TFT_WIDTH;
		lc_tp_x /= (tp_x_max - tp_x_min);
		if(lc_tp_x < TFT_WIDTH)
			lc_tp_x = TFT_WIDTH - lc_tp_x;
		else
			lc_tp_x = 0;
		
		lc_tp_y -= tp_y_min;
		lc_tp_y *= TFT_HEIGHT;
		lc_tp_y /= (tp_y_max - tp_y_min);
		// my expansion
		
		
		
		//---------------------
		*x = lc_tp_x;
		*y = lc_tp_y;
		return 1;
	}
	return 0;			
}

uint8_t tp_read2(uint16_t *x,uint16_t *y)
{						
	uint32_t lc_tp_x=0,lc_tp_y=0,lc_tp_z1=0,lc_tp_z2=0;
	float lc_tp_pres=0;	
	uint8_t lc_cnt=0;
	for(lc_cnt=0;lc_cnt<5;lc_cnt++)
	{
			lc_tp_y += ADS_Read_AD(CMD_RDX);				
			lc_tp_x += ADS_Read_AD(CMD_RDY);
			lc_tp_z1 += ADS_Read_AD(CMD_RDZ1);
			lc_tp_z2 += ADS_Read_AD(CMD_RDZ2);
	}
	lc_tp_x /= 5;
	lc_tp_y /= 5;
	lc_tp_z1 /= 5;
	lc_tp_z2 /= 5;
	
	if(lc_tp_z2 > lc_tp_z1)
	{
		lc_tp_pres = 100 * lc_tp_x;			
		lc_tp_pres = lc_tp_pres * (lc_tp_z2 - lc_tp_z1);			
		lc_tp_pres = lc_tp_pres /(4096 * lc_tp_z1);
	}
	else
	{
		lc_tp_pres = 0;
	}			
	te = lc_tp_pres;
	if(lc_tp_pres < tp_pres_thr && lc_tp_x > tp_x_min && lc_tp_y > tp_y_min)				
	{	
		lc_tp_x -= tp_x_min;
		lc_tp_x *= TFT_WIDTH;
		lc_tp_x /= (tp_x_max - tp_x_min);
		if(lc_tp_x < TFT_WIDTH)
			lc_tp_x = TFT_WIDTH - lc_tp_x;
		else
			lc_tp_x = 0;
		
		lc_tp_y -= tp_y_min;
		lc_tp_y *= TFT_HEIGHT;
		lc_tp_y /= (tp_y_max - tp_y_min);
		
		if(lc_tp_y < TFT_HEIGHT)
			lc_tp_y = TFT_HEIGHT - lc_tp_y;
		else
			lc_tp_y = 0;
		// my expansion
		
		
		
		//---------------------
		*x = lc_tp_x;
		*y = lc_tp_y;
		return 1;
	}
	return 0;			
}


uint8_t tp_read3(uint16_t *x,uint16_t *y)
{						
	uint32_t lc_tp_x=0,lc_tp_y=0,lc_tp_z1=0,lc_tp_z2=0;
	float lc_tp_pres=0;	
	uint8_t lc_cnt=0;
	for(lc_cnt=0;lc_cnt<NUM_READ;lc_cnt++)
	{
			lc_tp_y += ADS_Read_XY(CMD_RDX);//ADS_Read_AD(CMD_RDX);				
			lc_tp_x += ADS_Read_XY(CMD_RDY);//ADS_Read_AD(CMD_RDY);
			lc_tp_z1 += ADS_Read_XY(CMD_RDZ1);//ADS_Read_AD(CMD_RDZ1);
			lc_tp_z2 += ADS_Read_XY(CMD_RDZ2);//ADS_Read_AD(CMD_RDZ2);
	}
	lc_tp_x /= NUM_READ;
	lc_tp_y /= NUM_READ;
	lc_tp_z1 /= NUM_READ;
	lc_tp_z2 /= NUM_READ;
	
	if(lc_tp_z2 > lc_tp_z1)
	{
		lc_tp_pres = 100 * lc_tp_x;			
		lc_tp_pres = lc_tp_pres * (lc_tp_z2 - lc_tp_z1);			
		lc_tp_pres = lc_tp_pres /(4096 * lc_tp_z1);
	}
	else
	{
		return 0;
		lc_tp_pres = 0;
	}			
	te = lc_tp_pres;
	if(lc_tp_pres < tp_pres_thr && lc_tp_x > tp_x_min && lc_tp_y > tp_y_min)				
	{	
		lc_tp_x -= tp_x_min;
		lc_tp_x *= (TFT_WIDTH-10);
		lc_tp_x /= (tp_x_max - tp_x_min);
		if(lc_tp_x < TFT_WIDTH)
			lc_tp_x = TFT_WIDTH -10 - lc_tp_x;
		else
			return 0;
			//lc_tp_x = 0;
		
		lc_tp_y -= tp_y_min;
		lc_tp_y *= (TFT_HEIGHT-10);
		lc_tp_y /= (tp_y_max - tp_y_min);
		
		if(lc_tp_y < TFT_HEIGHT)
			//lc_tp_y = TFT_HEIGHT - lc_tp_y;
			lc_tp_y = lc_tp_y;
		else
			return 0;
			//lc_tp_y = 0;
		// my expansion
		
		
		
		//---------------------
		*x = lc_tp_x;
		*y = lc_tp_y;
		return 1;
	}
	return 0;			
}

void Init_TOUCH(void)
{	

}

