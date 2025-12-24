#include <LedControl.h>

const int DIN = 11;
const int CS = 7;
const int   CLK = 13;
const int trigPin = 10;
const int echoPin = 9;
float duration, distance;

LedControl lc=LedControl(DIN, CLK, CS,0);




// 1. dance left
const byte dance1[8] = {
  B00000000, 
  B01000010, 
  B01111110, 
  B01011010, 
  B01111110, 
  B00111100,
  B01101100,  
  B00000000 
};

// 2. dance center
const byte dance2[8] = {
  B00000000, 
  B01000010, 
  B01111110, 
  B01011010, 
  B01111110, 
  B00111100, 
  B00100100,  
  B00100100 
};

// 3. dance right
const byte dance3[8] = {
  B00000000, 
  B01000010, 
  B01111110, 
  B01011010, 
  B01111110, 
  B00111100, 
  B00110110, 
  B00000000 

};
// 2. JUMPING CAT
const byte jumpCrouch[8] = {
  B00000000, 
  B00000000, 
  B01000010,
  B01111110, 
  B01011010, 
  B01111110, 
  B00111100,  
  B00100100

};

// 2. MIDAIR (High up)
const byte jumpMid[8] = {
  B01000010, 
  B01111110, 
  B01011010, 
  B01111110, 
  B00111100, 
  B00100100, 
  B00100100,
  B00000000  
};

// 3. LANDING (Impact)
const byte jumpLandHigh[8] = {
  B00000000, 
  B01000010, 
  B01111110,
  B01011010,
  B01111110,
  B00111100,
  B00100100,  
  B00100100 

};
const byte jumpLandLow[8] = {
  B00000000,
  B00000000,
  B01000010, 
  B01111110, 
  B01011010, 
  B01111110,
  B00111100,
  B00100100  
};


const byte heartBig[8] = {
  B00000000,
  B01100110, 
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000 
};

// Frame 2: Small Heart
const byte heartSmall[8] = {
  B00000000,
  B00000000,
  B00100100, 
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};
// Frame 3: Tiny Heart
const byte heartTiny[8] = {
  B00000000,
  B00000000,
  B00000000, 
  B00100100,
  B00111100,
  B00011000,
  B00000000,
  B00000000
};



void setup() {
	Serial.begin(9600);  
  lc.shutdown(0, false);      
  lc.setIntensity(0, 8);      
  lc.clearDisplay(0);          
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  //Serial.print("Distance: ");
  //Serial.println(distance);
  if(distance <= 20) {
    showHeart();
  } else if(distance <= 50) {
    danceCat();
  }
  else {
    jumpCat();
  }
  delay(100);

  }




void jumpCat() {
  // Sequence 2: The Jump (Crouch -> Jump -> Land)
  displayFrame(jumpCrouch); delay(500); 
  displayFrame(jumpMid);    delay(200); 
  displayFrame(jumpLandHigh);   delay(200); 
  displayFrame(jumpLandLow);   delay(200); 
  displayFrame(jumpCrouch); delay(500); 
}

void danceCat() {
  for(int i=0; i<1; i++) {
    displayFrame(dance1); delay(250);
    displayFrame(dance2); delay(250);
    displayFrame(dance3); delay(250);
    displayFrame(dance2); delay(250);
  }
}

void showHeart() {
  // show heart
  displayFrame(heartTiny); delay(500);
  displayFrame(heartSmall); delay(500);
  displayFrame(heartBig); delay(500);
}
// Helper function to draw the frame
void displayFrame(const byte frame[]) {
  for (int i = 0; i < 8; i++) {
    // We use '7-i' to reverse the order of the columns
    lc.setColumn(0, 7 - i, frame[i]); 
  }
}


    