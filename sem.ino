/**
 * Vancouver Maker Faire 2013
 * 
 */
 
 class CSEM 
 {
   private:
     int m_echoPin ;
     int m_trigPin ; 

     int   ReadInputs();    
     void  WriteOutputRGB( int value ); 
     
   public:
     void SetUp( int echo, int trig ); 
     void Loop(); 

 };
 
void CSEM::SetUp( int echo, int trig ) {
  // Record the pins
  this->m_echoPin = echo ; 
  this->m_trigPin = trig ;   

  // Set up the serial 
  Serial.begin (9600);
  
  // Set the pins up. 
  pinMode(this->m_trigPin, OUTPUT);
  pinMode(this->m_echoPin, INPUT);
  
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
    
  duration = pulseIn(this->m_echoPin, HIGH);
  distance = (duration/2) / 29.1;

  
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
  
  
  delay( 500 ); 
}




#define trigPin 13
#define echoPin 12

CSEM g_SDM; 
void setup() {
  g_SDM.SetUp( echoPin, trigPin ); 
}
void loop() {
  g_SDM.Loop();
}
