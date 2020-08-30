#include <Servo.h>
Servo myservo;
char recu;
String messagerecu="";
String idMode="5w";
String idModeread="5r";
int angleDegre;
int choix=2;
void setup() {
myservo.attach(11);
myservo.write(0);
Serial.begin(9600);
pinMode(choix,OUTPUT);
digitalWrite(choix,0);
} 
void loop() {
 
 while(Serial.available())
 {
 delay(3);
 char c = Serial.read();
 messagerecu += c;
 }
 //le message reçu doit forcement contenir 4 char sinon il est incomplet ou dépasse la 
 if (messagerecu.length()==4)
 {
  String firstTwo = messagerecu.substring(0,2);
  firstTwo.toLowerCase();
  if(firstTwo==idMode){
    if(isDigital(messagerecu.substring(2,4))== true){
      digitalWrite(choix,1);//changer au mode TX
      delay(200);
      Serial.print('A');
      delay(200);
      digitalWrite(choix,0); //mode RX
      //répondre au besoin du maitre
     angleDegre=messagerecu.substring(2,4).toInt();
     if(angleDegre>0&&angleDegre<99){
    myservo.write(angleDegre);
     }
    }else{
      //acquittement négatif
      digitalWrite(choix,1);//modeTX
      delay(200);
      Serial.print('N');
      delay(200);
      digitalWrite(choix,0); //mode RX
    }
  }else if(firstTwo==idModeread){
    //do nothing
  }else{
    //acquittement négatif
      digitalWrite(choix,1);//modeTX
      delay(200);
      Serial.print('N');
      delay(200);
      digitalWrite(choix,0); //mode RX
  }
  messagerecu="";
 }
}
 boolean isDigital (String verification){
  int ret=0;
  for(int i=0;i<2;i++)
    if(isDigit(verification.charAt(i))) ret++;
    if (ret==2)return true;
    else return false;
  
 }
 
