#include "main.h"

TIM_HandleTypeDef TIM_InitStruct;
 

int sayi  ;  // keypad dan okudugumuz deger 

int birinci_basamak ; // 1. basamak

int ikinci_basamak ;	//2. basamak

int ucuncu_basamak ; //3, basamak 

int artan = 0 ; // her bir basamak artisi artar


void TIM_Init(void){   // timerin ayarlamalari 

__HAL_RCC_TIM3_CLK_ENABLE(); 
	
	TIM_InitStruct.Instance 						= TIM3;			 //		
	
	TIM_InitStruct.Init.Prescaler   		= 1000;      //16.000.000 / 1000 = 16000

	TIM_InitStruct.Init.CounterMode 		= TIM_COUNTERMODE_UP;

	TIM_InitStruct.Init.Period 						= 8000;   // 16000 / 8000 = F = 2 
																									// period = 1/f = 1/2 = 0.5sn 
																									// TIM3_IRQHandler() her 0.5sn carilacak
		
	
	while (HAL_TIM_Base_Init(&TIM_InitStruct)!= HAL_OK); // ayarlari olana kadadr bekle
	
	HAL_TIM_Base_Start_IT(&TIM_InitStruct);

	HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	HAL_TIM_Base_Start(&TIM_InitStruct); 								// timer baslat

}




void GPIO_Ayarla(void)
{ 
	//D0 birinci satir
	//D1 ikinci satir
	//D2 ucuncu satir
	//D3 dortuncu satir
	
	//D4 1. sari led
	//D5 2. sari led
	//D6 3. sari led
	
	//D7 yesil led 		dogru sifre
	//D8 kirmizi led	yanlis sifre
	
	
    GPIO_InitTypeDef GPIO_InitStructure;
	
		__HAL_RCC_GPIOD_CLK_ENABLE(); //D pinlerin clk aktiflemek
	
	
    GPIO_InitStructure.Pin   =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4| GPIO_PIN_5| GPIO_PIN_6| GPIO_PIN_7 |  GPIO_PIN_8;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;   
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(GPIOD, &GPIO_InitStructure); // su ayarlari D'ye uygula
	
	
	
	
	
	
	//E0 birinci sutun
	//E1 ikinci sutun
	//E2 ucuncu sutun
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure_girisler ;
	
			__HAL_RCC_GPIOE_CLK_ENABLE();
			
	

	GPIO_InitStructure_girisler.Mode = GPIO_MODE_INPUT;	
	GPIO_InitStructure_girisler.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 ;			  	
	GPIO_InitStructure_girisler.Pull = GPIO_PULLDOWN;	
	
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure_girisler);	

	
	
}












int main(void)
{
  HAL_Init();
  SystemClock_Config();
	

	TIM_Init();
	
	GPIO_Ayarla();
	


	while (1) {
		
	
	

}
}




void TIM3_IRQHandler(void)
{
     HAL_TIM_IRQHandler(&TIM_InitStruct);

	
	// her 0.5 saniye calisacak
	
	
	
	
	// birinci satir test
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0 ,  GPIO_PIN_SET );						// 1. 					 3v 
																																	//2.ve3.ve4.		 0v
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3 ,  GPIO_PIN_RESET );
	
	// sutunlarin degeri olcmek
	if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_0 ) ) == GPIO_PIN_SET ) { // 1.sutun 3v mu
		sayi = 1 ;
		artan ++ ;
	}
	else if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_1 ) ) == GPIO_PIN_SET ) { //2.sutun 3v mu
		sayi = 2 ;
		artan ++ ;
	}
	else if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_2 ) ) == GPIO_PIN_SET ) { //3. sutun 3v mu
		sayi = 3 ;
		
		artan ++ ;
	}
	
	
	
	
	// ikinci satir test
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1 ,  GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3 ,  GPIO_PIN_RESET );
	// sutunlarin degeri olcmek
	if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_0 ) ) == GPIO_PIN_SET ) {
		sayi =  4 ;
		
		artan ++ ;
	}
	else if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_1 ) ) == GPIO_PIN_SET ) {
		sayi = 5 ;
		
		artan ++ ;
	}
	else if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_2 ) ) == GPIO_PIN_SET ) {
	sayi = 6 ;
		
		artan ++ ;
	}
	
	
	
	// ucuncu satir test
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2 ,  GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3 ,  GPIO_PIN_RESET );
	// sutunlarin degeri olcmek
	if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_0 ) ) == GPIO_PIN_SET ) {
		sayi = 7 ;
		
		artan ++ ;
	}
	else if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_1 ) ) == GPIO_PIN_SET ) {
		sayi = 8 ;
		
		artan ++ ;
	}
	else if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_2 ) ) == GPIO_PIN_SET ) {
		sayi = 9 ;
		
		artan ++ ;
	}
	
	
	// dotuncu satir test
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3 ,  GPIO_PIN_SET );
	// sutunlarin degeri olcmek
	
 if ( (HAL_GPIO_ReadPin( GPIOE,  GPIO_PIN_1 ) ) == GPIO_PIN_SET ) { 
		sayi = 0 ;
	 
		artan ++ ;
	}
 
 
	
	
	
	
	
	
	
	
	
	
if ( artan == 1 ) {						// kullanci tarafindan ilk girilen sayi birinci basamak olarak kayit ediyoruz 
	birinci_basamak = sayi ; 
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4 ,  GPIO_PIN_SET );

}

else if ( artan == 2 ) {			// kullanci tarafindan ikinci girilen sayi ikinci basamak olarak kayit ediyoruz 
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5 ,  GPIO_PIN_SET );
	ikinci_basamak = sayi ; 
}

else if ( artan == 3 ) {			// kullanci tarafindan ucuncu girilen sayi ucuncu basamak olarak kayit ediyoruz 
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6 ,  GPIO_PIN_SET );
	ucuncu_basamak = sayi ; 
	artan = 0 ;

}




// sifre 1 2 3  sirasiyla

if ( birinci_basamak == 1 && ikinci_basamak  ==2 &&  ucuncu_basamak == 3 ){
	
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,  GPIO_PIN_RESET );	//1.sari
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5 ,  GPIO_PIN_RESET );//2.sari
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6 ,  GPIO_PIN_RESET );//3.sari
	
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7 ,  GPIO_PIN_SET );	// yesil led sifre dogru
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8 ,  GPIO_PIN_RESET );// kirmizi led kapali
	
}
else {
	
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5 ,  GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6 ,  GPIO_PIN_RESET );
	
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7 ,  GPIO_PIN_RESET ); // yesil led kapali sifre yanlis
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8 ,  GPIO_PIN_SET );		// kirmizi led acik sifre yanlis
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}


}
