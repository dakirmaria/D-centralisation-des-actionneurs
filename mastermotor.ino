int BP1 = 11, BP2 = 9;
int choix = 6,erreur=0,erreur2=0;
char feedback,feedback2;
char slave1_ID='5',slave2_ID='9',mode='W';
int slave1_DATA=80,slave2_DATA=01,diz_angle,uni_angle,diz_dure,uni_dure;
void setup() {
  pinMode(BP1, INPUT);
  pinMode(BP2, INPUT);
  Serial.begin(9600);
  delay(100);
  pinMode(choix, OUTPUT);
  digitalWrite(choix,1);
}

void loop() { 
  // put your main code here, to run repeatedly:
  int etat1, etat2;
//controler l'état de boutton poussoir 1 
  if (digitalRead(BP1) == 1) {
    while(digitalRead(BP1)==1){
      // do nothing
    }
    //si le boutton est appuié on envoie la trame
    do{
    digitalWrite(choix,1);
    delay(200);
   diz_angle=slave1_DATA/10;//4
   uni_angle=slave1_DATA%10;//8
   char diz_angle_c =  diz_angle + 48;  // '4'
   char uni_angle_c =  uni_angle + 48;  // '8'
   Serial.print(slave1_ID);
   delay(3);
   Serial.print(mode);
   delay(3);
   Serial.print(diz_angle_c);
   delay(3);
   Serial.print(uni_angle_c);
   delay(3);
   delay(200);
   digitalWrite(choix,0);
   //attendre l'acquittement d'esclave 
  while(Serial.available()==0){
    //do nothing
  }
  //lecture du message reçu par l'esclave 1
  feedback=Serial.read();
  digitalWrite(choix,1); // retour au mode TX
  if (feedback=='A'){ //acquittement positif par lettre A
    //do nothing
  }else if(feedback=='N'){//acquittement négatif par lettre N
    erreur++; //incrémentation d'erreur
  }
  }while(erreur<3&&feedback=='N'); //si l'erreur est inf à 3 et l'acquittement est toujours négatif on renvoie le message 
  if(erreur==3){ //si l'acquittement est tjr négatif on arrete le communication définitivement avec cet esclace 
    Serial.end();
  }
  }


//controling the second slave

 if (digitalRead(BP2) == 1) { //control d'état de BP2
    while(digitalRead(BP2)==1){
      // do nothing
    }
    do{ //si le BP 2 est appuié envoie de la trame
    digitalWrite(choix,1);
    delay(200);
   diz_dure=slave2_DATA/10;//4
   uni_dure=slave2_DATA%10;//8
   char diz_dure_c =  diz_dure + 48;  // '4'
   char uni_dure_c =  uni_dure + 48;  // '8'
   Serial.print(slave2_ID);
   delay(3);
   Serial.print(mode);
   delay(3);
   Serial.print(diz_dure_c);
   delay(3);
   Serial.print(uni_dure_c);
   delay(3);
   delay(200);
   digitalWrite(choix,0);
  while(Serial.available()==0){ //attend de l'acquittement de l'esclave 2
    //do nothing
  }
  feedback2=Serial.read(); //lecture de l'acquittement 
  digitalWrite(choix,1); // retour au mode TX
  if (feedback2=='A'){ //acquittement positif
    //do nothing
  }else if(feedback2=='N'){ //acquittement négatif
    erreur2++; //incrémentation de l'erreur
  }
  }while(erreur2<3&&feedback2=='N'); //renvoie de la trame si l'erreur est inf à 3 est l'acquittement est négatif
  if(erreur2==3){
    Serial.end(); //si l'erreur égale à 3,o  arrete la communication avec l'esclve 2 définitivement
  }
  }

}
