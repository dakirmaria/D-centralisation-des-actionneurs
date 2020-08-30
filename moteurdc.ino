
int moteur=6,choix=2;
char recu;
String messagerecu="";
String idMode="9w";
String idModeread="9r";
int temps;
void setup() {
Serial.begin(9600);
pinMode(choix,OUTPUT);
digitalWrite(choix,0);
pinMode(moteur,OUTPUT);
}

void loop() {
 while(Serial.available())
 {
 delay(3);
 char c = Serial.read();//lectur de trame reçu
 messagerecu += c; 
 }
  if (messagerecu.length()==4)
 {
  String firstTwo = messagerecu.substring(0,2); //prise des deux premiers caractères 
  firstTwo.toLowerCase();
  if(firstTwo==idMode){
    if(isDigital(messagerecu.substring(2,4))== true){//vérification si la donnée est numérique
      digitalWrite(choix,1);//changer au mode TX
      delay(200);
      Serial.print('A');//envoie d'acquittement positif
      delay(200);
      digitalWrite(choix,0); //mode RX
      //répondre au besoin du maitre
     temps=messagerecu.substring(2,4).toInt();
     if(temps>0&&temps<60){ 
      int milisec=temps*60000;//convertir la durée en miliS
      digitalWrite(moteur,1);
      
      delay(milisec);
      digitalWrite(moteur,0);//arret de moteur 
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
  //verification si les données sont numérque 
  boolean isDigital (String verification){
  int ret=0;
  for(int i=0;i<2;i++)
    if(isDigit(verification.charAt(i))) ret++;
    if (ret==2)return true;
    else return false;
  
}
      
