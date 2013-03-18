/**
 * Vancouver Maker Faire 2013
 * 
 */
 
 class CSEM 
 {
   private:
     int m_echoPin ;
     int m_trigPin ; 
     
     int m_redLedPin ; 
     int m_greenLedPin ; 
     int m_blueLedPin ; 
     
     int m_servoPin ; 
 
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
  
  this->m_servoPin = servoPin ; 
 
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
 
  int red   = 255 ; 
  int green = 255 ; 
  int blue  = 255 ; 
  
  if( value <= 20 ) {
    Serial.println(" Red ");    
    red = 0 ; 
  } else if( value > 20 && value <= 50  ) {
    Serial.println(" Yellow ");    
    red   = 0 ; 
    green = 0 ; 
  } else if( value > 50  ) {
    Serial.println(" green ");    
    green = 0 ; 
  }
  
  analogWrite(this->m_redLedPin,   red);
  analogWrite(this->m_blueLedPin,  blue);
  analogWrite(this->m_greenLedPin, green);
 
}
 
 
void CSEM::Loop() {
  
  // Create an average betten several sensors. 
  int total = 0 ; 
  int count = 0 ; 
  for( ; count < 5; count ++ ) {
    total += this->ReadInputs() ; 
  }
  int value = total / count ;   
 
  // Write the value out to the outputs. 
  this->WriteOutputRGB( value ); 
  
}
 
 
 
 
#define trigPin 13
#define echoPin 12
 
#define redPin     8
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