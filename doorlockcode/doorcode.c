#include<reg51.h>
#include<string.h>
//Keypad connections
sbit r1=P1^0;
sbit r2=P1^1;
sbit r3=P1^2;
sbit r4=P1^3;
sbit c1=P1^4;
sbit c2=P1^5;
sbit c3=P1^6;
sbit c4=P1^7;
//LCD control lines
sbit RS = P3^0;
sbit EN = P3^1;
//Motor connections
sbit IN1 =P3^2;
sbit IN2 =P3^3;
sbit IN3 =P3^4;
sbit IN4 =P3^5;
//user defined functions
void lcdcmd(unsigned char); //LCD commands
void lcddat(unsigned char); 
void lcddisplay(unsigned char*); //LCD display
unsigned char password[5]; 
int x=0;
int beep=0;
unsigned char correctpassword[5]="02349"; //this is the correct password
void delay(int);
void check();
void delay (int a){
    int i,j;
    for(i=0;i<a;i++){
        for(j=0;j<1275;j++);
    }
}
void lcdstart(){
    lcdcmd(0x01); //clear screen
	  lcdcmd(0x38); // 5*7 matrix
	  lcdcmd(0x0E); //display on, cursor blinking
	  lcdcmd(0x80); //force cursor to beginning of first line
    lcddisplay("DOOR LOCK");
    lcdcmd(0xc0); //force cursor to beginning of second line
    lcddisplay("   SYSTEM");
	  delay(1);
	  lcdcmd(0x01); //clear screen
	  lcddisplay("Enter Password");
	  lcdcmd(0xc0); //force cursor to beginning of second line	
}
void solve(){
	  lcdstart();
	  while(1){        
        r1=0;r2=1;r3=1;r4=1;        
        if(c1==0){            
            password[x]='1';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);     //shift cursor to right        
            x++;
        }
        if(c2==0){
            password[x]='2';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);     //shift cursor to right  
            x++;
        }
        if(c3==0){
            password[x]='3';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);      //shift cursor to right      
            x++;
        }
        r1=1;r2=0;r3=1;r4=1;
        if(c1==0){
            password[x]='4';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);      //shift cursor to right      
            x++;
        }
        if(c2==0){
            password[x]='5';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);      //shift cursor to right      
            x++;
        }
        if(c3==0){
            password[x]='6';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);   //shift cursor to right         
            x++;
        }
        r1=1;r2=1;r3=0;r4=1;
        if(c1==0){
            password[x]='7';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);       //shift cursor to right     
            x++;
        }
        if(c2==0){
            password[x]='8';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);       //shift cursor to right     
            x++;
        }
        if(c3==0){
            password[x]='9';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);      //shift cursor to right      
            x++;
        }
        r1=1;r2=1;r3=1;r4=0;
        if(c2==0){
            password[x]='0';
            lcddat('*');  
					  delay(100);
					  lcdcmd(0x06);         //shift cursor to right   
            x++;
        }
        if(x==5){
            check();
            delay(100);
					  lcdcmd(0x06);       //shift cursor to right
        }
        r4=1;
    }
}
void main(){
	  solve();
}
void check(){
    if(password[0]==correctpassword[0]&&
       password[1]==correctpassword[1]&&
       password[2]==correctpassword[2]&&            //if entered password matches to set password
       password[3]==correctpassword[3]&&
       password[4]==correctpassword[4]){
           IN1=1;
           IN2=0;
           lcdcmd(0x01);
           lcdcmd(0x80);
           lcddisplay("Password");
           lcdcmd(0xc0);
           lcddisplay("Matched");
           delay(500);
				   IN1=0;
				   IN2=0;
				   x=0;
				   solve();
       }
       else{                                        //if password doesnt match
           IN1=0;
           IN2=0;
           lcdcmd(0x01);
           lcdcmd(0x80);
           lcddisplay("Wrong");
           lcdcmd(0xc0);
           lcddisplay("Password");				   
				   for(beep=0;beep<3;beep++){						 
				   IN3=1;
				   IN4=0;
           delay(200);
				   IN3=0;
				   IN4=0;
				   delay(10);
					 }
				   x=0;
				   solve();
       }
}
void lcdcmd(unsigned char cmd){
    P2=cmd;
    RS=0;
    EN=1;
    delay(1);
    EN=0;
}
void lcddat(unsigned char dat){
    P2=dat;
    RS=1;
    EN=1;
    delay(1);
    EN=0;
}
void lcddisplay(unsigned char *c){
  int k;  
	for(k=0;c[k]!='\0';k++){
        lcddat(c[k]);
    }
    delay(100);
}



