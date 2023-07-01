#ifndef _HTTP_H
#define _HTTP_H

#include "USART.h"
#include <string.h>

namespace custom_libraries
{
    class HTTP : public USART{
        private:
            bool is_available = false;
        private:
            void pseudo_delay(uint64_t duration);
        public:
        public:
            HTTP(USART_TypeDef *_USART,
				GPIO_TypeDef *GPIO,
				_DMA ACTUAL_DMA,
				DMA_Stream_TypeDef *DMA_STREAM,
				uint8_t RX_PIN,
				uint8_t TX_PIN,
				int baudrate);
            void send_sms(char* phone_number, char* payload);
            void enable_sms_reception();
            void post_http_json(char* url, char* data);
            void get_http_json(char* url);
            void tostring(char str[], int num);
            int get_size(char *bytes);
            ~HTTP();
    };

} // namespace custom_libaries




#endif //_HTTP_H
