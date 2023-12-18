#include "SCServo.h"

#define S_RXD 18
#define S_TXD 19

SCSCL sc;
#define SERVO_TAG "Servo"
void servoPing()
{   
    ESP_LOGI(SERVO_TAG, "Post at 0");
    sc.WritePos(1, 0, 0, 600);//Servo(ID1) moves at max speed=1500, moves to position=20.
    delay(2000);//[(P1-P0)/V]*1000+100

    ESP_LOGI(SERVO_TAG, "Post at 500");
    sc.WritePos(1, 700, 0, 600);//Servo(ID1) moves at max speed=1500, moves to position=20.
    delay(2000);//[(P1-P0)/V]*1000+100
}

void servoPosTo(double rot){
	u16 pos = (rot/100) * 700;
	sc.WritePos(1, pos, 0, 600);//Servo(ID1) moves at max speed=1500, moves to position=1000.
  	delay(1000);//[(P1-P0)/V]*1000+100
}
