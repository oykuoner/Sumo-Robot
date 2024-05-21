#define CizgiSensorSol A0
#define CizgiSensorSag A1

#define Motor_R_Hiz 11
#define Motor_R_Yon 13

#define Motor_L_Hiz 3
#define Motor_L_Yon 12

#define CisimSagSensor A2
#define CisimSolSensor A4
#define CisimOrtaSensor A3


int mesafe_sag;
int mesafe_sol;
int mesafe_orta;

int cizgi_sol;
int cizgi_sag;




void setup() {

  // Cisim algılama sensörleri
  pinMode (CisimSagSensor,INPUT);
  pinMode (CisimSolSensor,INPUT);
  pinMode (CisimOrtaSensor,INPUT);

  
  //Çizgi algılama sensörleri
  pinMode (CizgiSensorSol,INPUT);
  pinMode (CizgiSensorSag,INPUT);

  // Motor hız ve yön sensörleri
  pinMode (Motor_R_Hiz,OUTPUT);
  pinMode (Motor_R_Yon,OUTPUT);

  pinMode (Motor_L_Hiz,OUTPUT);
  pinMode (Motor_L_Yon,OUTPUT);

  
  Serial.begin(9600);


}

void loop() {

  // Çigi sensörlerinde veri okuyoruz.
  cizgi_sol = analogRead(CizgiSensorSol);
  cizgi_sag = analogRead(CizgiSensorSag);
  
  /*Rakip testip etmeyi while içinde yapıyoruz. Eğer çizgi sensörlerinde herhangi bir çizgi sinyali
  almışsa zaten öncelik kendini kurtarmak olacak ve while içine girmeyecek. */

  while ((cizgi_sol <= 220) && (cizgi_sag <= 220 )){
        Serial.println("Çizgiye basmıyorum ringin içindeyim cisim aramaya başla.");
        mesafe_sag = digitalRead(CisimSagSensor); // Sag sensörden ölçüm alıyoruz.
        mesafe_sol = digitalRead(CisimSolSensor); // Sol sensörden ölçüm alıyoruz.
        mesafe_orta = digitalRead(CisimOrtaSensor); // Orta sensörden ölçüm alıyoruz.

        // 3X MR45 sensörler cisim görünce 1 çıkışı verir.
        while(mesafe_orta == 0){ // Orta sensörde cisim algılamış ise..
            // Önce çizgiye basıp basmadığını kontrol edelim. Basıyorsa hiçbirşey yapmayıp döngüden çıkacak.
            cizgi_sol = analogRead(CizgiSensorSol);
            cizgi_sag = analogRead(CizgiSensorSag);
              if((cizgi_sol <= 220) || (cizgi_sag <= 220 )){
                break;
            }

            // Eğer çizgiye basmıyorsa orta sensör algıladığı için rakibe saldıracak.
            Serial.println("Hedefe git");
            mesafe_orta = digitalRead(CisimOrtaSensor);
            // while da sonsuz dönmesin diye tekrar ön sensörde algılama olup olmadığını kontrol ediyoruz.
        }
        // sadece sağdan bilgi alıyor sağa dönecek
        while((mesafe_sag == 1 && mesafe_orta == 0)){
          // Çizgi kontrolü
          cizgi_sol = analogRead(CizgiSensorSol);
          cizgi_sag = analogRead(CizgiSensorSag);
             if((cizgi_sol <= 220) || (cizgi_sag <= 220 )){
                break;
            }

            // Çizgi yok sağa dönecek.
            yerindesag();
            delay(200); // Bu değer robotun 90 derece dönmesini sağlayacak şekilde ayarlanmalı.
            Serial.println("sağa dön");
            mesafe_sag = digitalRead(CisimSagSensor); // Sag sensörden ölçüm alıyoruz.
            mesafe_sol = digitalRead(CisimSolSensor); // Sol sensörden ölçüm alıyoruz.
            mesafe_orta = digitalRead(CisimOrtaSensor); // Orta sensörden ölçüm alıyoruz.
          
        }

        // sadece soldan bilgi alıyor sola dönecek sağ kısmının aynısı
        while ((mesafe_sol == 1 && mesafe_orta == 0)){
          // Çizgi kontrolü
          cizgi_sol = analogRead(CizgiSensorSol);
          cizgi_sag = analogRead(CizgiSensorSag);
          if((cizgi_sol <= 220) || (cizgi_sag <= 220 )){
                break;
            }
            yerindesol();
            delay(200);      
            Serial.println("sola dön");
            mesafe_sag = digitalRead(CisimSagSensor); // Sag sensörden ölçüm alıyoruz.
            mesafe_sol = digitalRead(CisimSolSensor); // Sol sensörden ölçüm alıyoruz.
            mesafe_orta = digitalRead(CisimOrtaSensor); // Orta sensörden ölçüm alıyoruz.           

          
        }

        //hiçbir sensörde cisim yok ne yapalım?

        while((mesafe_sag == 0) && (mesafe_orta == 0) && (mesafe_sol == 0)){ // mesafe sol 1 di 0 a çektim
              // Çizgi kontrolü
          cizgi_sol = analogRead(CizgiSensorSol);
          cizgi_sag = analogRead(CizgiSensorSag);
          if((cizgi_sol <= 220) || (cizgi_sag <= 220 )){
                break;
            } 
            ileri();
            // cisim görmediğinde yapılacak şey bize kalmış biz düz ileri gitmesini istedik.
            // Yerinde dönmede yaptırılabilir.
            Serial.println("cisim bulunamadı ileri git");
            mesafe_sag = digitalRead(CisimSagSensor); // Sag sensörden ölçüm alıyoruz.
            mesafe_sol = digitalRead(CisimSolSensor); // Sol sensörden ölçüm alıyoruz.
            mesafe_orta = digitalRead(CisimOrtaSensor); // Orta sensörden ölçüm alıyoruz. 
        }
        
          
         // Çizgi kontrolü
          cizgi_sol = analogRead(CizgiSensorSol);
          cizgi_sag = analogRead(CizgiSensorSag);
    
  } // İlk while çıkışı.

  if(cizgi_sol <= 220){ // Sol çizgi sensörü çizgi algılıyorsa geri gidecek. Sagada döndürebiliriz.
    Serial.println(" Sol çizgi tespit edildi geri gidiyorum"); 
    geri();
    delay(400); // Delay değerleri ring boyutuna göre tekrar ayarlanabilir
    yerindesag();
    delay(300); // Delay değerleri ring boyutuna göre tekrar ayarlanabilir

  }
  else if(cizgi_sag <= 220){
    Serial.println(" Sag çizgi tespit edildi geri gidiyorum"); 
    geri();
    delay(400); // Delay değerleri ring boyutuna göre tekrar ayarlanabilir
    yerindesol();
    delay(300); // Delay değerleri ring boyutuna göre tekrar ayarlanabilir
  }
  
} // Loop sonu


// Robotun saldırma hareketi için fonksiyon tanımlıyoruz.
void saldir(){

    analogWrite(Motor_R_Hiz,250);
    digitalWrite(Motor_R_Yon,HIGH);
  
    analogWrite(Motor_L_Hiz,250);
    digitalWrite(Motor_L_Yon,HIGH);      
}



// Robotun ileri yönlü hareketi için fonksiyon tanımlıyoruz.
void ileri (){
  analogWrite(Motor_R_Hiz,180);
  digitalWrite(Motor_R_Yon,HIGH);
  
  analogWrite(Motor_L_Hiz,180);
  digitalWrite(Motor_L_Yon,HIGH);

 
}

// Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.
void yerindesag (){

  analogWrite(Motor_R_Hiz,0);
  digitalWrite(Motor_R_Yon,HIGH);
  
  analogWrite(Motor_L_Hiz,200);
  digitalWrite(Motor_L_Yon,HIGH);
}


// Robotun sola dönme hareketi için fonksiyon tanımlıyoruz.
void yerindesol (){

  analogWrite(Motor_R_Hiz,200);
  digitalWrite(Motor_R_Yon,HIGH);
  
  analogWrite(Motor_L_Hiz,0);
  digitalWrite(Motor_L_Yon,HIGH);
}

// Robotun geri hareketi için fonksiyon tanımlıyoruz.
void geri (){

  analogWrite(Motor_R_Hiz,150);
  digitalWrite(Motor_R_Yon,LOW);
  
  analogWrite(Motor_L_Hiz,150);
  digitalWrite(Motor_L_Yon,LOW);
}


// Robotun durma dönme hareketi için fonksiyon tanımlıyoruz.
void dur (){

  analogWrite(Motor_R_Hiz,0);
  digitalWrite(Motor_R_Yon,HIGH);
  
  analogWrite(Motor_L_Hiz,0);
  digitalWrite(Motor_L_Yon,HIGH);
}
