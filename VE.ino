#include <TimerOne.h>
// Variables para la interrupción
volatile float Time = 0;
const int trigPin = 7;
const int echoPin = 6;
float distance_setpoint = 10; // Distancia deseada
// Define variables
volatile double duration;
volatile double distance1 = 0;
volatile int voltajebits = 0;
int in3 = 2; // Pin que controla el sentido de giro Motor B
int in4 = 4; // Pin que controla el sentido de giro Motor B
int EnB = 3; // Pin que controla la velocidad del Motor A PWM
float ultrasonicRead(); // Declaración de la función para leer la distancia

const double k_1 = 0.027210960048911, k_2 = -0.023528895559911, l = 0.633817350032687;
const double gt = 0.6, ga = 0.146473059986925, pe = 176.6386912825946, c1 = 0.002804770356280, c2 = 0.002856503471888;
volatile double x_1 = 0, x_2 = 0, xa = 0, xb = 0, f = 0, peq = 0,  u =0;
volatile double f_1=0;

void setup() {
  Serial.begin(115200);  // Iniciamos la comunicación serial a 9600 baudios
  Timer1.initialize(5000); // Configura el TIMER en 20 milisegundos = 20000 microsegundos
  Timer1.attachInterrupt(Temporizador); // Configura la interrupción del Timer 1
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(2, OUTPUT); // Salidas del motor
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT); 
  analogWrite(EnB, 0); // Inicializa la velocidad del motor a cero
  delay(5000);
}
void loop() {
  if(Serial.available()>0){
  char seleccion = Serial.read();
  if(seleccion=='A'){
 // Serial.print(Time);
 // Serial.print(" ");
 // Serial.print(u);
 // Serial.print(" ");
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print(distance_setpoint);
  Serial.print(" ");
  Serial.print(xa);
  Serial.print(" ");
  Serial.println(xb);  
  };
    if(seleccion == 'D'){
      while (Serial.available()==0);
      int data = Serial.read();
      distance_setpoint = data;
      }
    }
}
void Temporizador(void) {
  Time = Time + 0.01; // Incrementa el temporizador
    distance1 = ultrasonicRead();
    xa = (distance1-(c1*xb))/c2 ;
    xb = f_1 + (l*xa);
    peq = distance_setpoint*pe;
    x_1 = xa - peq;
    x_2 = xb - peq;
    u = -(k_1*x_1+k_2*x_2);
    f=-(u*l)+(f_1*gt)+(xa*ga);  
    f_1 = f;
  if (u > 0) {    // Cambia la dirección del motor según el signo del error
    digitalWrite(in3, HIGH); // Giro ADELANTE
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW); // Giro ATRÁS
    digitalWrite(in4, HIGH);
  }
  voltajebits = (abs(u)*255)/5.58; // Ajusta la velocidad del motor dentro de los límites
  if (voltajebits < 50) voltajebits = 50;
  if (voltajebits > 255) voltajebits = 255;
  analogWrite(EnB, voltajebits);
}
float ultrasonicRead() { // Función para leer la distancia
  digitalWrite(trigPin, LOW);// Clears the trigPin
  digitalWrite(trigPin, HIGH);   // Sets the trigPin on HIGH state for 10 micro seconds
  //delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);   // Reads the echoPin, returns the sound wave travel time in microseconds
  double distance = duration * 0.034 / 2.0;   // Calcula la distancia
  return distance;
}
