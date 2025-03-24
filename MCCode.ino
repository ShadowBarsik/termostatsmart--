//Программа для микроконтроллера в новом модуле автоматической поддержки микроклимата в террариумах. Автор: Дмитрий. Версия:0.0
// Определение пинов для подключения к 7-ми сегментному индикатору
const int segPin[] = {PC1,PC2,PC3,PC4,PC5, PC6, PC7};
const int digitPins[] = {PB0,PB1,PB2};
#define EULER_CONST 2.718281828459045235
unsigned long previousMillis = 0;   
unsigned long previousmillis = 0;   
double nat_log(double x) {
    if (x <= 0) {
        return 0.0/0.0;
    }
    int power_adjust = 0;
    while (x > 1.0) {
        x /= EULER_CONST;
        power_adjust++;
    }
    while (x < .25) {
        x *= EULER_CONST;
        power_adjust--;
    }
    x -= 1.0;
    double t = 0.0, s = 1.0, z = x;
    for (int k=1; k<=20; k++) {
        t += z * s / k;
        z *= x;
        s = -s;
    }
    return t + power_adjust;
}
int num=0;
int COUNT=0;
int sgm=0;
// Определение символов для каждой цифры (a, b, c, d, e, f, g)
int dig0=0,dig1=0,dig2=0;
int ThermistorPin = PB3;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = -0.08263077828e-03, c2 = 4.274733946e-04, c3 = -6.385940625e-07;
void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPin[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}
 void displayNumber(int number) {
  unsigned long currentMillis = millis();
   switch (COUNT){
case 0: //”0” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], LOW);
digitalWrite(segPin[5], LOW);
digitalWrite(segPin[6], HIGH);
break;
case 1: //”1” на дисплее
digitalWrite(segPin[0], HIGH);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], HIGH);
digitalWrite(segPin[4], HIGH);
digitalWrite(segPin[5], HIGH);
digitalWrite(segPin[6], HIGH);
break;
case 2: //”2” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], HIGH);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], LOW);
digitalWrite(segPin[5], HIGH);
digitalWrite(segPin[6], LOW);
break;
case 3: //”3” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], HIGH);
digitalWrite(segPin[5], HIGH);
digitalWrite(segPin[6], LOW);
break;
case 4: //”4” на дисплее
digitalWrite(segPin[0], HIGH);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], HIGH);
digitalWrite(segPin[4], HIGH);
digitalWrite(segPin[5], LOW);
digitalWrite(segPin[6], LOW);
break;
case 5: //”5” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], HIGH);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], HIGH);
digitalWrite(segPin[5], LOW);
digitalWrite(segPin[6], LOW);
break;
case 6: //”6” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], HIGH);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], LOW);
digitalWrite(segPin[5], LOW);
digitalWrite(segPin[6], LOW);
break;
case 7: //”7” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], HIGH);
digitalWrite(segPin[4], HIGH);
digitalWrite(segPin[5], HIGH);
digitalWrite(segPin[6], HIGH);
break;
case 8: //”8” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], LOW);
digitalWrite(segPin[5], LOW);
digitalWrite(segPin[6], LOW);
break;
case 9: //”9” на дисплее
digitalWrite(segPin[0], LOW);
digitalWrite(segPin[1], LOW);
digitalWrite(segPin[2], LOW);
digitalWrite(segPin[3], LOW);
digitalWrite(segPin[4], HIGH);
digitalWrite(segPin[5], LOW);
digitalWrite(segPin[6], LOW);
break;
break;
   }
COUNT=10;
dig0=number/100;
dig1=(number/10)%10;
dig2=number%10;
if (currentMillis - previousmillis >= 5) {
    previousmillis = currentMillis;
if (sgm<3){
sgm++;
}
if (sgm==3){
sgm=0; //сброс
}
 }
if (sgm==0){
digitalWrite(digitPins[1], LOW);
digitalWrite(digitPins[2], LOW);
digitalWrite(digitPins[0], HIGH);
COUNT=dig0;
}
if (sgm==1){
digitalWrite(digitPins[0], LOW);
digitalWrite(digitPins[2], LOW);
digitalWrite(digitPins[1], HIGH);
COUNT=dig1;
}
if (sgm==2){
digitalWrite(digitPins[0], LOW);
digitalWrite(digitPins[1], LOW);
digitalWrite(digitPins[2], HIGH);
COUNT=dig2;
}
}
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 500) { //обновление данных в миллисекундах 
    previousMillis = currentMillis;
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = nat_log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;//273.15
  }
displayNumber(Tc*10);
}
 
