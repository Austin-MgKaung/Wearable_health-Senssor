/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/
#define samp_siz 20
#define rise_threshold 5
int REDLed = 3;
int IRLed = 4;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(REDLed,OUTPUT);
  pinMode(IRLed,OUTPUT);

  // turn off leds
  digitalWrite(REDLed,LOW);
  digitalWrite(IRLed,LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  
	  float reads[samp_siz], sum; 
	  long int now, ptr; 
	  float last, reader, start; 
	  float first, second, third, before, print_value; 
	  bool rising; 
	  int rise_count; 
	  int n; 
	  long int last_beat; 
	  for (int i = 0; i < samp_siz; i++) 
	    reads[i] = 0; 
	  sum = 0; 
	  ptr = 0; 
	  while(1) 
	  { 
	    // calculate an average of the sensor 
	    // during a 20 ms period (this will eliminate 
	    // the 50 Hz noise caused by electric light 
	    n = 0; 
	    start = millis(); 
	    reader = 0.; 
	    do 
	    { 
	      reader += analogRead (A0); 
	      n++; 
	      now = millis(); 
	    } 
	    while (now < start + 20);   
	    reader /= n;  // we got an average 
	    // Add the newest measurement to an array 
	    // and subtract the oldest measurement from the array 
	    // to maintain a sum of last measurements 
	    sum -= reads[ptr]; 
	    sum += reader; 
	    reads[ptr] = reader; 
	    last = sum / samp_siz; 
	    // now last holds the average of the values in the array 
	    // check for a rising curve (= a heart beat) 
	    if (last > before) 
	    { 
	      rise_count++; 
	      if (!rising && rise_count > rise_threshold) 
	      { 
	        // Ok, we have detected a rising curve, which implies a heartbeat. 
	        // Record the time since last beat, keep track of the two previous 
	        // times (first, second, third) to get a weighed average. 
	        // The rising flag prevents us from detecting the same rise  
	        // more than once. 
	        rising = true; 
	        first = millis() - last_beat; 
	        last_beat = millis(); 
	        // Calculate the weighed average of heartbeat rate 
	        // according to the three last beats 
	        print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third); 
	        Serial.print(print_value); 
	      
	        third = second; 
	        second = first; 
	      } 
	    } 
	    else 
	    { 
	      // Ok, the curve is falling 
	      rising = false; 
	      rise_count = 0; 
	    } 
	    before = last; 
	    ptr++; 
	    ptr %= samp_siz; 

    }
}