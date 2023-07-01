
#include "stm32f4xx.h"
#include "clockconfig.h"
#include "HTTP.h"

#define GSM_RX 7
#define GSM_TX 6

#define SERIAL_RX 9
#define SERIAL_TX 8

#define GSM_BAUDRATE 9600
#define SERIAL_BAUDRATE 9600

char URL_GET[] = "http://predict-data-api.herokuapp.com/data/real-time";
char URL_POST[] = "http://predict-data-api.herokuapp.com/data/jj0qlj6x09j";
char PAYLOAD[] = "{\"xClockWise\":\"56\",\"xAntiClockWise\":\"90\",\"yClockWise\":\"56\",\"yAntiClockWise\":\"40\",\"vibration\":\"223\",\"noise\":\"0\"}";

char RECEIVE_BUFFER[BUFFER_SIZE];

custom_libraries::clock_config system_clock;
custom_libraries::HTTP GSM(USART1,GPIOB,custom_libraries::_DMA2,DMA2_Stream2,GSM_RX,GSM_TX,GSM_BAUDRATE);
custom_libraries::HTTP Serial(USART3,GPIOD,custom_libraries::_DMA1,DMA1_Stream1,SERIAL_RX,SERIAL_TX,SERIAL_BAUDRATE);

int main(void) {
  
  system_clock.initialize();
  Serial.initialize();
   /* Enable Serial reception from GSM */
  //GSM.enable_sms_reception();
  //GSM.post_http_json(URL,PAYLOAD);
  GSM.get_http_json(URL_GET);


  while(1){
  
    /* ------------START GSM RECPTION----------------------*/
    /* Check if data has been received in USART data register */
    if(USART1->SR & USART_SR_RXNE){
      /* Short delay */
      for(volatile int i = 0; i < 100000; i++){}
      /* Print out data in the receive buffer */
      Serial.println(GSM.receive_buffer);
      /*Clear serial buffer */
      GSM.flush_buffer();
      /* clear flag */
      USART1->SR &= ~USART_SR_RXNE;
    }
    /* ------------END GSM RECPTION----------------------*/
   
  }
}
