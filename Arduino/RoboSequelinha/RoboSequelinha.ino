#define MOTOR_DIREITO_TRAS 10 //a1a
#define MOTOR_DIREITO_FRENTE 11 //a1b
#define MOTOR_ESQUERDO_TRAS 6//b1a
#define MOTOR_ESQUERDO_FRENTE 5//b1b

#define SENSOR_01 2
#define SENSOR_02 3
#define SENSOR_03 4
#define SENSOR_04 7
#define SENSOR_05 8
#define SENSOR_CONTATO 9
#define SENSOR_PROXIMIDADE 13


int B1B = 10;  // esquedo frente
int B1A = 11;  // esquedo tras
int A1B = 6;   // direito frente
int A1A = 9;   // direito tras

int contdir = 0;
int contdirsaida = 0;
int timedir = 0;
int tempocego = 60;
float vel = 3.5;
int faixa = 0;
int faixaeqd = 0;

void setup() {

  pinMode(B1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(A1A, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if ((digitalRead(7) == 0) && (digitalRead(2) == 1) && (digitalRead(4) == 0) && (digitalRead(5) == 0)) {
    MotorDireita();
    Serial.println("direita 2");
  }

  if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(4) == 1) && (digitalRead(5) == 0)) {
    MotorEsquerda();
    Serial.println("esquerda 4");
  }

  if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(4) == 0) && (digitalRead(5) == 0) && (faixaeqd == 0)) {
    MotorFrente();
  }

  if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(4) == 0) && (digitalRead(5) == 0) && (digitalRead(3) == 0) && (faixaeqd == 1)) {
    timedir = 0;
    while (timedir < 50) {
      MotorFrenteReto();
      timedir++;
      delay(5);
      MotorFrente();
    }
    while ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(4) == 0) && (digitalRead(5) == 0) && (digitalRead(3) == 0) && (faixaeqd == 1)) {
    MotorParar();
    //Serial.println("parou final");
  }
  }
  if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(5) == 1) && (digitalRead(4) == 0)) {
    MotorEsquerda();
    Serial.println("squerda 5");
  }

  if ((digitalRead(7) == 1) && (digitalRead(2) == 0) && (digitalRead(4) == 0) && (digitalRead(5) == 0)) {
    MotorDireita();
    Serial.println("direita 7");
  }

  //inicio contagem rotatoria direita
  if ((((digitalRead(7) == 0) && (digitalRead(2) == 0)) || ((digitalRead(7) == 0) && (digitalRead(4) == 0))) && (digitalRead(5) == 1) && (digitalRead(3) == 1) && (contdirsaida == 0)) {
    Serial.println("sensor meio e canto ativos e o restante inativo");
    MotorFrenteLento();
    while ((((digitalRead(7) == 0) && (digitalRead(2) == 0)) || ((digitalRead(7) == 0) && (digitalRead(4) == 0))) && (digitalRead(5) == 1)) {
      Serial.println("sensor direita meio inativo, vira um loop");
      if (((digitalRead(5) == 1) && (digitalRead(3) == 1) && (digitalRead(2) == 0)) || ((digitalRead(5) == 1) && (digitalRead(3) == 1) && (digitalRead(4) == 0))) {
        Serial.println("sensores do meio e canto ativos e do meio inativo, vai contar mais um");
        MotorFrenteLento();
        contdir = contdir + 1;
        while (((digitalRead(5) == 1) && (digitalRead(2) == 0) && (digitalRead(3) == 1)) || ((digitalRead(5) == 1) && (digitalRead(4) == 0) && (digitalRead(3) == 1))) {
          Serial.println("loop infinito em cima do quadrado");
          delay(2);
          MotorFrenteLento();
        }
      }
      //Serial.println(contdir);
      contdirsaida = 0;
    }
  }


  if ((digitalRead(3) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1) && (contdir > 0)) {
    if ((digitalRead(3) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1) && (contdirsaida == 0)) {
      timedir = 0;
      if (faixa == 1){
        faixaeqd = 1;
      }
      while (timedir < tempocego) {
        MotorEsquerdaBrusco();
        timedir++;
        delay(70 / vel);
        if ((digitalRead(4) == 1) && (timedir > (tempocego / 3))) {
          timedir = tempocego;
        }
        while ((digitalRead(3) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1)) {
          Serial.println("Lendo uma saida");
          delay(2);
          MotorFrenteLento();
        }
      }
    }
    while ((digitalRead(3) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1)) {
      Serial.println("Lendo uma saida");
      delay(2);
      MotorFrenteLento();
    }
    contdirsaida++;

    Serial.println("if das condicoes para virar em uma saida");
    //Serial.println(contdir);
    //Serial.println(contdirsaida);

    if (contdir == contdirsaida) {
      timedir = 0;
      
      while (timedir < tempocego) {
        MotorEsquerdaBrusco();
        timedir++;
        delay(70 / vel);
        if ((digitalRead(4) == 1) && (timedir > (tempocego / 11))) {
          timedir = tempocego;
        }
      }

      //Serial.println("virou a direita");
      contdirsaida = 0;
      contdir = 0;
      
    }
  }

  //Serial.println("loop de toda programa");
  //termino contagem rotatoria direita


  // inicio para facha de pedestre
  if ((digitalRead(7) == 1) && (digitalRead(2) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1) && (digitalRead(3) == 0)) {
    while (digitalRead(7) == 1) {
      if ((digitalRead(7) == 1) && (digitalRead(2) == 0) && (digitalRead(4) == 1) && (digitalRead(5) == 1)) {
        MotorDireita();
        //Serial.println("direita");
      }

      if ((digitalRead(7) == 1) && (digitalRead(2) == 1) && (digitalRead(4) == 0) && (digitalRead(5) == 1)) {
        MotorEsquerda();
        //Serial.println("esquerda");
      }

      if ((digitalRead(7) == 1) && (digitalRead(2) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1) && (digitalRead(3) == 0)) {
        MotorFrente();
      }

      if ((digitalRead(7) == 1) && (digitalRead(2) == 1) && (digitalRead(5) == 0) && (digitalRead(4) == 1)) {
        MotorEsquerda();
        //Serial.println("sensor 3");
      }

      if ((digitalRead(7) == 0) && (digitalRead(2) == 1) && (digitalRead(4) == 1) && (digitalRead(5) == 1)) {
        MotorDireita();
        //Serial.println("sensor 2");
      }
    }
    timedir = 0;
    while (timedir < 400) {
      MotorFrenteReto();
      timedir++;
      delay(5);
      if ((digitalRead(7) == 0) && (digitalRead(2) == 1) && (digitalRead(4) == 0) && (digitalRead(5) == 0)) {
        MotorDireita();
        //Serial.println("direita");
      }

      if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(4) == 1) && (digitalRead(5) == 0)) {
        MotorEsquerda();
        //Serial.println("esquerda");
      }
   
      if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(5) == 1) && (digitalRead(4) == 0)) {
        MotorEsquerda();
        //Serial.println("sensor 3");
      }

      if ((digitalRead(7) == 1) && (digitalRead(2) == 0) && (digitalRead(4) == 0) && (digitalRead(5) == 0)) {
      MotorDireita();
      //Serial.println("sensor 2");
      }

      //Serial.println("andou 3 segundos");
      if ((digitalRead(7) == 0) && (digitalRead(2) == 0) && (digitalRead(3) == 0) && (digitalRead(4) == 0) && (digitalRead(5) == 0)) {
        timedir = 500;
      }
    }
    timedir = 0;
    while (timedir < 150) {
      MotorParar();
      timedir++;
      delay(5);
      //Serial.println("parou 5 segundos");
    }
    timedir = 0;
    while (timedir < 400) {
      MotorFrenteReto();
      timedir++;
      delay(5);
      //Serial.println("andou 3 segundos cego");
      faixa = 1;
    }
  }
  //Serial.println(faixa);
  //Serial.println(faixaeqd);
}

 


void MotorDireita() {
  analogWrite(B1B, (vel * 20));
  digitalWrite(A1A, LOW);
  analogWrite(A1B, (vel * 1));
  digitalWrite(B1A, LOW);
  delay(2);
  //Serial.println("motor direita");
}

void MotorEsquerda() {
  analogWrite(A1B, (vel * 20));
  digitalWrite(B1A, LOW);
  analogWrite(B1B, (vel * 1));
  digitalWrite(A1A, LOW);
  delay(2);
  //Serial.println("motor esquerda");
}


void MotorEsquerdaBrusco() {
  analogWrite(A1B, (vel * 15));
  analogWrite(B1A, (vel * 12));
  digitalWrite(B1B, LOW);
  digitalWrite(A1A, LOW);
  delay(2);
  //Serial.println("motor esquerda brusco");
}

void MotorFrente() {
  digitalWrite(B1A, LOW);
  digitalWrite(A1A, LOW);
  analogWrite(A1B, (vel * 19.5));
  analogWrite(B1B, (vel * 17));
  //Serial.println("motor frente");
}

void MotorParar() {
  digitalWrite(A1B, LOW);
  digitalWrite(B1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(A1A, LOW);
  delay(2);
  //Serial.println("motor parar");
}

void MotorFrenteLento() {
  digitalWrite(B1A, LOW);
  digitalWrite(A1A, LOW);
  analogWrite(A1B, (vel * 11));
  analogWrite(B1B, (vel * 10));
  //Serial.println("motor frente lento");
}

void MotorFrenteReto() {
  digitalWrite(B1A, LOW);
  digitalWrite(A1A, LOW);
  analogWrite(A1B, (vel * 11));
  analogWrite(B1B, (vel * 10));
  //Serial.println("motor frente lento");
}