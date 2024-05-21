#define SensorSol A0 // Sol
#define SensorSag A1 // Sag

#define MotorR1Hiz 11 // Sag motor Hızı
#define MotorR2Yon 13 // Sag motor dönüş yönü

#define MotorL1Hiz 3//Sol motor Hızı
#define MotorL2Yon 12 // Sol motor dönüş yönü

int degerA0, degerA1;

void setup()
{

  //Kullanılacak pinlerin giriş çıkış olup olmadığını belirtmek.

  pinMode(SensorSol,INPUT);
  pinMode(SensorSag,INPUT);

  pinMode(MotorR1Hiz, OUTPUT);
  pinMode(MotorR2Yon, OUTPUT);
  
  pinMode(MotorL1Hiz  , OUTPUT);
  pinMode(MotorL2Yon, OUTPUT);
  Serial.begin(9600);

 
}
// Motorhız değişkenindeki değeler eğer sıfır olursa motor dönmez . 
// Renk rensörü analog oldugundan 0-1023 arasında değer almaktadır.
// 220 değer altını siyaha yakın üstünü ise beyaza yakın kabul ettik.
// Algroritma sahanın beyaz , sahayı sınırlayan çizgileri siyah kabul ettik.
void loop(){
 degerA0 = analogRead(SensorSol);
 degerA1 = analogRead(SensorSag);
  if(analogRead(degerA0) >= 220  && analogRead(degerA1  )>= 220 ){// İki sensörde beyaz renkli zemini okuyor ileri yönde devam etsin
      ileri();      
  }
  else if(analogRead(degerA0)<=220  && analogRead(degerA1  )>= 220 ){// Sol sensör Siyah renkli çizgiyi okursa eğer sola dön
      sol();      }
  //Robotun sola dönme durumus
  else if(analogRead(degerA0)>= 220&& analogRead(degerA1  )<=220 ){// Sag sensör Siyah renkli çizgiyi okursa eğer sağa dön
      sag();      
      } 



  void ileri (){
  analogWrite(MotorL1Hiz,150);
  digitalWrite(MotorL2Yon,HIGH);
  analogWrite(MotorR1Hiz,150);
  digitalWrite(MotorR2Yon,HIGH); 

 
}


void sag (){

  analogWrite(MotorL1Hiz,100);
  digitalWrite(MotorL2Yon,HIGH);

  analogWrite(MotorR1Hiz,0);
  digitalWrite(MotorR2Yon,HIGH); 
 
}


void sol (){

  analogWrite(MotorL1Hiz,0);
  digitalWrite(MotorL2Yon,HIGH);

  analogWrite(MotorR1Hiz,100);
  digitalWrite(MotorR2Yon,HIGH); 
 
}
