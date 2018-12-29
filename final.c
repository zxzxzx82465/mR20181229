#include <stdio.h>
#include <stdlib.h>

//**************ADD***************//
#include <sys/select.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <wiringPi.h>
#define MIDDLE	28
#define LEFT	26
#define RIGHT	27
#define BUFSIZE 512

#define MOTOR_GO_FORWARD   digitalWrite(1,HIGH);digitalWrite(16,LOW);digitalWrite(12,HIGH);digitalWrite(22,LOW)
#define MOTOR_GO_BACK	   digitalWrite(1,LOW);digitalWrite(16,HIGH);digitalWrite(12,LOW);digitalWrite(22,HIGH)
#define MOTOR_GO_LEFT	   digitalWrite(1,HIGH);digitalWrite(16,LOW);digitalWrite(12,LOW);digitalWrite(22,HIGH)
#define MOTOR_GO_RIGHT	   digitalWrite(1,LOW);digitalWrite(16,HIGH);digitalWrite(12,HIGH);digitalWrite(22,LOW)
#define MOTOR_GO_STOP	   digitalWrite(1, LOW);digitalWrite(16,LOW);digitalWrite(12, LOW);digitalWrite(22,LOW)

#define INT1 1
#define INT2 16
#define INT3 12
#define INT4 22

#define ENA 29
#define ENB 6



int main(int argc, char *argv[])
{

    float dis;
    int count_run = 0; 
    int count = 0;
    int flag = 0, flag2 = 0;
   // char buf[BUFSIZE]={0xff,0x00,0x00,0x00,0xff};

	int SR;
	int SL;
	int SM;
    /*RPI*/
    wiringPiSetup();
    /*WiringPi GPIO*/
    pinMode (INT1, OUTPUT);	//IN1
    pinMode (INT2, OUTPUT);	//IN2
    pinMode (INT3, OUTPUT);	//IN3
    pinMode (INT4, OUTPUT);	//IN4
	pinMode (INT5, INPUT); // 變數確認
    pullUpDnControl(INT1, PUD_DOWN);
    pullUpDnControl(INT2, PUD_DOWN);
    pullUpDnControl(INT3, PUD_DOWN);
    pullUpDnControl(INT4, PUD_DOWN);
	pullUpDnControl(INT4, PUD_UP);		//變數確認
	
    pinMode(ENB, OUTPUT);
    softPwmCreate(ENB,1,50);
    pinMode(ENA, OUTPUT);
    softPwmCreate(ENA,1,50);
	
	struct timeval tv;
	fd_set readfds;
	tv.tv_sec = 0;
	tv.tv_usec = 500;

 while(1)
  {
	
	// input 
  FD_ZERO(&readfds);
  FD_SET(STDIN, &readfds);
  
  
	
  int ret = select(STDIN + 1, &rdfds, NULL, NULL, &tv);

  if (ret>0) 
  {
	  printf("STOP");
	  MOTOR_GO_STOP
  }
  
 


	
  //有信号为LOW  没有信号为HIGH
  SR = digitalRead(RIGHT);//有信号表明在白色区域，车子底板上L亮；没信号表明压在黑线上，车子底板上L灭
  SL = digitalRead(LEFT);//有信号表明在白色区域，车子底板上L亮；没信号表明压在黑线上，车子底板上L灭
  SM = digitalRead(MIDDLE);
   //softPwmWrite(ENA,25); //rotate
   //softPwmWrite(ENB,25);	
	//MOTOR_GO_FORWARD;   
	//MOTOR_GO_BACK;	   
	//MOTOR_GO_RIGHT;	   
	//MOTOR_GO_LEFT;	   
	//MOTOR_GO_STOP;
	
  //forward
  if (SL == LOW && SM == HIGH && SR==LOW){//2
   printf("GO");
   softPwmWrite(ENA,30);
   softPwmWrite(ENB,30);
   MOTOR_GO_FORWARD;
   //run();
   count_run++;
   flag2  = 1;
   
  }
  // forward
  else if (SL == LOW && SM == LOW && SR == LOW){//0
   printf("GO");
   softPwmWrite(ENA,30);
   softPwmWrite(ENB,30);
   MOTOR_GO_FORWARD;
   //run();
   count_run++;
   flag2  = 1;
	  
  }
  //fast right(little angle)
  else if (SL == LOW && SM == HIGH && SR == HIGH){ //3
   printf("FR");
   softPwmWrite(ENA,35);
   softPwmWrite(ENB,25);
   MOTOR_GO_FORWARD;   
  }
  // slow right(big angle)
  else if (SL == LOW && SM == LOW && SR == HIGH){ //1
   printf("SR");
   softPwmWrite(ENA,45);
   softPwmWrite(ENB,45);
   MOTOR_GO_RIGHT;
  }
  //fast left(little angle)
  else if (SL == HIGH && SM == HIGH && SR == LOW){ //6
   printf("FL");
   softPwmWrite(ENA,35);
   softPwmWrite(ENB,25);
   MOTOR_GO_FORWARD;   
  }
  // slow left(big angle)
  else if (SL == HIGH && SM == LOW && SR == LOW){ // 4
   printf("SL");
   softPwmWrite(ENA,45);
   softPwmWrite(ENB,45);
   MOTOR_GO_LEFT;
  }

  else {// 都是白色, 停止
  printf("STOP");
  MOTOR_GO_STOP;
  
  
  
/*
  flag++;
  if(flag%2==1)
   {
      for(count = 0;count<5;count++)
       {
           left(); 
       }
      if(SR == LOW && SL == LOW)
       {
          for(count = 0;count<5;count++)
           {
           right(); 
           }
       }
   }
  else
  {
      for(count = 0;count<5;count++)
       {
           right();
            
       }
     flag = 0;
     if(SR == LOW && SL == LOW)
       {
          for(count = 0;count<5;count++)
           {
           left(); 
           }
       }
  }
*/
 }

  }

 
  return 0;

}



