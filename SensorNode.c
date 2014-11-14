// DUEM - Solar Car 2014-2015 
// sensor node programme
// when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
// 

#include <SPI.h>
#include "mcp_can.h"
/* 
could also define if the last 3 bits are 111 then its some sort of recalibration message.
*/


MCP_CAN CAN(10);                                            // Set CS to pin 10

unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
unsigned char message[8] 				// message to be sent
INT32U send_message_id;						// send id to message
INT32U recieved_message_id;					// message id recieved
INT8U remote_frame;					// whether the message is a remote frame or not


char str[20];

void send_data() //get it to return something to check if it succeeds. give it an input for the data and node to send

void setup()
{
    Serial.begin(115200);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
    
    /*
     * set mask, set both the mask to 0x3ff
     */
    CAN.init_Mask(0, 0, 0x3FF);                         // there are 2 mask in mcp2515, you need to set both of them
    CAN.init_Mask(1, 0, 0x3FF); 
    /*
     * set filter, we can receive id from 0x04 ~ 0x09
     */
    CAN.init_Filt(0, 0, 0x04);                          // there are 6 filter in mcp2515
    CAN.init_Filt(1, 0, 0x05);                          // there are 6 filter in mcp2515
    
    CAN.init_Filt(2, 0, 0x06);                          // there are 6 filter in mcp2515
    CAN.init_Filt(3, 0, 0x07);                          // there are 6 filter in mcp2515
    CAN.init_Filt(4, 0, 0x08);                          // there are 6 filter in mcp2515
    CAN.init_Filt(5, 0, 0x09);                          // there are 6 filter in mcp2515

}

void send_data()
{
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(send_message_id, 0, 8, message);
    delay(100);                       // send data per 100ms
}


void loop()
{
     if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
    
        Flag_Recv = 0;                // clear flag
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
		
	remote_frame = CAN.isRemoteRequest(void) //checking if a remote frame is recieved 	
	recieved_message_id = CAN.getCanId(void); // getting message id.
		
	if(remote_frame == 1){
		
	}
		
       /* Serial.println("\r\n------------------------------------------------------------------");
        Serial.print("Get Data From id: ");
        Serial.println(CAN.getCanId());
      
	   for(int i = 0; i<len; i++)    // print the data for debugging purposes
        {
            Serial.print("0x");
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();	
		*/
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
