
#include "HTTP.h"

namespace custom_libraries
{
    HTTP::HTTP(USART_TypeDef *_USART,
				GPIO_TypeDef *GPIO,
				_DMA ACTUAL_DMA,
				DMA_Stream_TypeDef *DMA_STREAM,
				uint8_t RX_PIN,
				uint8_t TX_PIN,
				int baudrate): USART(_USART,
                                    GPIO,
                                    ACTUAL_DMA,
                                    DMA_STREAM,
                                    RX_PIN,
                                    TX_PIN,
                                    baudrate){
        /* Initialize serial communication */
        initialize();
     }
    
    void HTTP::pseudo_delay(uint64_t duration){
        for(volatile uint64_t i = 0; i < duration; i++){}
    }

    void HTTP::send_sms(char* phone_number, char* payload){
        char sms_mode[] = "AT+CMGF=1\r";
        char config_number[] = "AT+CMGS=\"";
        char recipient_number[15];
        char command_termination[] = "\"\r";
        char send_payload[1024];
        char term = (char)26;
        strcpy(recipient_number,phone_number);
        strcat(config_number,recipient_number);
        strcat(config_number,command_termination);
        strcpy(send_payload,payload);
        print(sms_mode);
        pseudo_delay(100000); //The delay value of 100,000 was arrived at by experimentation
        print(config_number);
        pseudo_delay(100000);
        print(send_payload);
        pseudo_delay(100000);
        print(&term);
    }

    void HTTP::enable_sms_reception(){
        char sms_mode[] = "AT+CMGF=1\r\n";
        char delete_sms_from_storage[] = "AT+CMGDA=1\r\n";
        char notify_of_new_messages[] = "AT+CNMI=2,2,0,0,0\r\n";
        print(sms_mode);
        pseudo_delay(100000);
        print(delete_sms_from_storage);
        pseudo_delay(100000);
        print(notify_of_new_messages);
        pseudo_delay(100000);
    }

        /* Convert an Integer value to a character array */
    void HTTP::tostring(char str[], int num)
    {
        int i, rem, len = 0, n;
        n = num;
        while (n != 0)
        {
            len++; //get length for string/digits in int
            n = n / 10;
        }
        //convert and store in string
        for (i = 0; i < len; i++)
        {
            rem = num % 10;                 //last digit fetched first
            num = num / 10;                 //continue fetching rest of the digits
            str[len - (i + 1)] = rem + '0'; //start storing string with max-1 index first
        }
        str[len] = '\0'; //null to end the string[max]
    }

    int HTTP::get_size(char *bytes){
        int size = 0;
        for(;*bytes;bytes++){
            size++;
        }
        return size;
    }

    void HTTP::post_http_json(char* url, char* data){

        char server_address[512] = "AT+HTTPPARA=\"URL\",\"";
        char address_termination[] = "\"";
        char target_url[100];
        strcpy(target_url,url);
        strcat(server_address,target_url);
        strcat(server_address,address_termination);

        char data_size_command[512] = "AT+HTTPDATA=";
        char data_size[5];
        tostring(data_size,get_size(data));
        char data_size_command_termination[] = ",100000";

        strcat(data_size_command,data_size);
        strcat(data_size_command,data_size_command_termination);

        char command_1[] = "AT";
        char command_2[] = "AT+SAPBR=3,1,\"Contype\",\"GPRS\""; //setting the SAPBR,connection type is GPRS
        char command_3[] = "AT+SAPBR=3,1,\"APN\",\"internet\""; //setting the APN,2nd parameter empty works for all networks
        char command_4[] = "AT+SAPBR=1,1";
        char command_5[] = "AT+SAPBR=2,1";
        char command_6[] = "AT+HTTPINIT";
        char command_7[] = "AT+HTTPPARA=\"CID\",1";
        char command_8[] = "AT+HTTPPARA=\"CONTENT\",\"application/json\"";
        char command_9[] = "AT+HTTPACTION=1";
        char command_10[] = "AT+HTTPREAD";
        char command_11[] = "AT+HTTPTERM";
        println(command_1);
        pseudo_delay(100000);
        println(command_2);
        pseudo_delay(100000);
        println(command_3);//APN
        pseudo_delay(100000);
        println(command_4);
        pseudo_delay(100000);
        println(command_5);
        pseudo_delay(100000);
        println(command_6);
        pseudo_delay(100000);
        println(command_7);
        pseudo_delay(100000);
        println(server_address); //Server address
        pseudo_delay(100000);
        println(command_8);
        pseudo_delay(100000);
        println(data_size_command);
        pseudo_delay(100000);
        println(data);
        pseudo_delay(100000);
        println(command_9);
        pseudo_delay(100000);
        println(command_10);
        pseudo_delay(100000);
        println(command_11);
        pseudo_delay(100000);
    }

    void HTTP::get_http_json(char* url){
         char server_address[512] = "AT+HTTPPARA=\"URL\",\"";
        char address_termination[] = "\"";
        char target_url[100];
        strcpy(target_url,url);
        strcat(server_address,target_url);
        strcat(server_address,address_termination);

        char command_1[] = "AT";
        char command_5[] = "AT+CGATT=1";
        char command_2[] = "AT+SAPBR=3,1,\"Contype\",\"GPRS\"";
        char command_3[] = "AT+SAPBR=3,1,\"APN\",\"internet\"";
        char command_4[] = "AT+SAPBR=1,1";
        char command_6[] = "AT+HTTPINIT";
        char command_7[] = "AT+HTTPPARA=\"CID\",1";
        char command_9[] = "AT+HTTPACTION=0";
        char command_10[] = "AT+HTTPREAD";
        char command_11[] = "AT+HTTPTERM";
        char command_12[] = "AT+CFUN?";

        println(command_1);
        pseudo_delay(100000);
        println(command_12);
        pseudo_delay(100000);
        println(command_5);
        pseudo_delay(100000);
        println(command_2);
        pseudo_delay(100000);
        println(command_3);//APN
        pseudo_delay(100000);
        println(command_4);
        pseudo_delay(100000);
        println(command_6);
        pseudo_delay(100000);
        println(command_7);
        pseudo_delay(100000);
        println(server_address); //Server address
        pseudo_delay(100000);
        println(command_9);
        pseudo_delay(40000000);
        flush_buffer();
        println(command_10);
        pseudo_delay(100000);
        println(command_11);
        pseudo_delay(100000);
    }

    HTTP::~HTTP(){
         /* Implement destructor here */
     }
    
} // namespace custom_libaries
