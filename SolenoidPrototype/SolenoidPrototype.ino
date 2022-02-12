// Bunch of constants in the form of definitions
// 1 = output debug to serial port, 0 = no debug
#define debug 1 
// define the buffer size... 
#define serialbufferSize 50 
// End of Constants

char inputBuffer[serialbufferSize]   ; 
int serialIndex = 0; // keep track of where we are in the buffer
// End of real variables

void setup() 
{ 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // do other setup here as needed
  
  // Print some instructions
  Serial.println("Hello, please ask me something");
  Serial.println("type \"one\", \"two\", \"three\" or \"four\" or make up your own command");
  Serial.println();
}

void loop() 
{
  
  if (CheckSerial()) DoCommand(inputBuffer); 
  
}

boolean DoCommand(char * commandBuffer)
{
  // ARRAY ONE ONLY
  if (strstr(commandBuffer, "one")){
    digitalWrite(3, LOW); // turn the relay on to start
    digitalWrite(4, HIGH); // turn the relay off to start
    digitalWrite(5, HIGH); // turn the relay off to start
    digitalWrite(6, LOW); // turn the relay on to start
 delay(3000); // wait for 3 seconds
 
  }  
   //ARRAY TWO ONLY
  else if (strstr(commandBuffer, "two")){
    digitalWrite(3, HIGH); // turn the relay off to start
    digitalWrite(4, LOW); // turn the relay on to start
    digitalWrite(5, HIGH); // turn the relay off to start
    digitalWrite(6, HIGH); // turn the relay off to start
  }
   //ARRAY ONE AND TWO
  else if (strstr(commandBuffer, "three")){
    digitalWrite(3, LOW); // turn the relay on to start
    digitalWrite(4, HIGH); // turn the relay off to start
    digitalWrite(5, LOW); // turn the relay on to start
    digitalWrite(6, HIGH); // turn the relay off to start
  
  }
    //ALL VALVES CLOSED
  else if (strstr(commandBuffer, "four")){
      digitalWrite(3, HIGH); // turn the relay off to start
    digitalWrite(4, HIGH); // turn the relay off to start
    digitalWrite(5, HIGH); // turn the relay off to start
    digitalWrite(6, HIGH); // turn the relay off to start
    //    Do some other work here
    //    and here
    //    and here
  }
  else {
    Serial.print("I dont understand you \nYou said: ");
    Serial.println(commandBuffer);
    //    Do some other work here
    //    and here
    //    and here
  }
  
  
  // debug code after here
#if debug
  Serial.print("Free Ram = "); Serial.println(freeRam(), DEC);
#endif  
return true;
}


boolean CheckSerial()
{
  boolean lineFound = false;
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    //Read a character as it comes in:
    //currently this will throw away anything after the buffer is full or the \n is detected
    char charBuffer = Serial.read(); 
      if (charBuffer == '\n') {
           inputBuffer[serialIndex] = 0; // terminate the string
           lineFound = (serialIndex > 0); // only good if we sent more than an empty line
           serialIndex=0; // reset for next line of data
         }
         else if(charBuffer == '\r') {
           // Just ignore the Carrage return, were only interested in new line
         }
         else if(serialIndex < serialbufferSize && lineFound == false) {
           /*Place the character in the string buffer:*/
           inputBuffer[serialIndex++] = charBuffer; // auto increment index
         }
  }// End of While
  return lineFound;
}// End of CheckSerial()

#if debug
// check free ram
int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
#endif


 
