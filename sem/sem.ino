/**
 * Vancouver Maker Faire 2013
 * 
 */

#include <Servo.h> 

 
 class CSEM 
 {
   private:
     int m_echoPin ;
     int m_trigPin ; 
     
     int m_redLedPin ; 
     int m_greenLedPin ; 
     int m_blueLedPin ; 
     
     Servo m_servo ; 

     int   ReadInputs();    
     void  WriteOutputRGB( int value ); 
     
   public:
     void SetUp( int echo, int trig, int redLed, int greenLed, int blueLed,  int servoPin  ); 
     void Loop(); 

 };
 
void CSEM::SetUp( int echo, int trig, int redLed, int greenLed, int blueLed, int servoPin ) {
  // Record the pins
  this->m_echoPin = echo ; 
  this->m_trigPin = trig ;   

  this->m_redLedPin   = redLed ; 
  this->m_greenLedPin = greenLed ; 
  this->m_blueLedPin  = blueLed ; 
  
  this->m_servo.attach( servoPin ) ; 

  // Set up the serial 
  Serial.begin (9600);
  
  // Set the pins up. 
  pinMode(this->m_trigPin, OUTPUT);
  pinMode(this->m_echoPin, INPUT);
  
  pinMode(this->m_redLedPin,   OUTPUT);
  pinMode(this->m_greenLedPin, OUTPUT);
  pinMode(this->m_blueLedPin,  OUTPUT);  
  
  // debug, Print pins
  Serial.print("Trig Pin: ");  
  Serial.print( this->m_trigPin );  
  Serial.print(" Echo Pin: ");  
  Serial.print( this->m_echoPin );  
  Serial.println( "" ) ; 
  
}
 
 
int CSEM::ReadInputs() {
  
  long duration, distance;
  digitalWrite(this->m_trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(this->m_trigPin, HIGH);
  delayMicroseconds(10);   
  digitalWrite(this->m_trigPin, LOW);

  /** 
   * Instead of using the Speed of Sound, we can also use the "Pace of Sound".
   * The Pace of Sound = 1 / Speed of Sound = 1 / 0.03435 = 29.1 ųs/cm
   * In this case the equation to calculate the distance become: D = (Δt/2) / Pace of sound
   * and for the example above: D = 250 / 29.1 = 8.6 cm   
   */    
  duration = pulseIn(this->m_echoPin, HIGH);
  distance = (duration/2) / 29.1;

  // This sensors has a max of 200 cm 
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
    return 0; 
  } 
  
  // Returnt the distance. 
  Serial.print(distance);
  Serial.println(" cm");
  return distance ; 
}

void CSEM::WriteOutputRGB( int value ) {
/*     int m_redLedPin ; 
     int m_greenLedPin ; 
     int m_blueLedPin ; 
*/

  if( value <= 10 ) {
    Serial.println(" Red ");    
  } else if( value > 10 && value <= 20  ) {
    Serial.println(" Blue ");    
  } else if( value > 20 && value <= 50  ) {
    Serial.println(" green ");    
  }
}
 

void CSEM::Loop() {
  int ret = this->ReadInputs() ; 
  this->WriteOutputRGB( ret ); 

  int servo = ret;
  if (servo == 0) // out of range
    servo = 180;
  this->m_servo.write(90 - map(servo, 0, 180, 0, 90));
  
  delay( 50 ); 
}




#define trigPin 13
#define echoPin 12

#define redPin    11
#define greenPin  10
#define bluePin    9

#define servoPin   14


CSEM g_SDM; 
void setup() {
  g_SDM.SetUp( echoPin, trigPin, redPin, greenPin, bluePin, servoPin ); 
}
void loop() {
  g_SDM.Loop();
}
