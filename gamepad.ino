#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_G 9
#define BUTTON_F 8
#define BUTTON_E 3
#define BUTTON_D 4
#define BUTTON_JOYSTICK 5
#define JOYSTICK_X 1
#define JOYSTICK_Y 0

int joystickX;
int joystickY;

int statusA = 0;
int statusB = 0;
int statusG = 0;
int statusF = 0;
int statusE = 0;
int statusD = 0;
int statusJOYSTICK = 0;
int direction = 0;
int lastDirection = 0;

/*

    Directions

    -----------------
    |8      1      2|
    |               |
    |7      0      3|
    |               |
    |6      5      4|
    -----------------
*/

void setup() {
    Serial.begin(9600);
    // to enable pull up resistors first write pin mode
    // and then make that pin HIGH
    pinMode(BUTTON_A, INPUT);
    digitalWrite(BUTTON_A, HIGH);
    pinMode(BUTTON_B, INPUT);
    digitalWrite(BUTTON_B, HIGH);
    pinMode(BUTTON_G, INPUT);
    digitalWrite(BUTTON_G, HIGH);
    pinMode(BUTTON_F, INPUT);
    digitalWrite(BUTTON_F, HIGH);
    pinMode(BUTTON_E, INPUT);
    digitalWrite(BUTTON_E, HIGH);
    pinMode(BUTTON_D, INPUT);
    digitalWrite(BUTTON_D, HIGH);
    pinMode(BUTTON_JOYSTICK, INPUT);
    digitalWrite(BUTTON_JOYSTICK, HIGH);
}

int sendKey(int digitalInput, int status, char key) {
    if(digitalRead(digitalInput) == LOW) {
        // button not pressed before --> start keypress
        if(status == 0) {
            Serial.print('P');
            Serial.print(key);
            Serial.print('\n');
        }
        return 1;
    } else {
        // button not pressed anymore
        if(status == 1) {
            Serial.print('R');
            Serial.print(key);
            Serial.print('\n');
        }
        return 0;
    }
}

int getDirection() {
    joystickX = analogRead(JOYSTICK_X);
    joystickY = analogRead(JOYSTICK_Y);

    // analog to digital
    if(joystickX > 600) {
        if(joystickY > 600) {
            //Serial.println("RIGHT UP is pressed");
            return 2;
        } else if(joystickY < 400) {
            //Serial.println("RIGHT DOWN is pressed");
            return 4;
        } else {
            //Serial.println("RIGHT is pressed");
            return 3;
        }
    }

    else if(joystickX < 400) {
        if(joystickY > 600) {
            //Serial.println("LEFT UP is pressed");
            return 8;
        } else if(joystickY < 400) {
            //Serial.println("LEFT DOWN is pressed");
            return 6;
        } else {
            //Serial.println("LEFT is pressed");
            return 7;
        }
    }

    else if(joystickY < 400) {
        if(joystickX < 600 && joystickX > 400 ) {
            //Serial.println("DOWN is pressed");
            return 5;
        }
    }

    else if(joystickY > 600) {
        if(joystickX < 600 && joystickX > 400 ) {
            //Serial.println("UP is pressed");
            return 1;
        }
    }

    return 0;
}

void sendDirection() {
    switch (direction) {
    case 1:
        if(lastDirection != 1) {
            //Keyboard.release(KEY_DOWN_ARROW);
            //Keyboard.release(KEY_LEFT_ARROW);
            //Keyboard.release(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_UP_ARROW);
            Serial.println("UP is pressed");
        }
        break;
    case 2:
        if(lastDirection != 2) {
            //Keyboard.release(KEY_DOWN_ARROW);
            //Keyboard.release(KEY_LEFT_ARROW);
            //Keyboard.press(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_UP_ARROW);
            Serial.println("RIGHT UP is pressed");
        }
        break;
    case 3:
        if(lastDirection != 3) {
            //Keyboard.release(KEY_DOWN_ARROW);
            //Keyboard.release(KEY_LEFT_ARROW);
            //Keyboard.release(KEY_UP_ARROW);
            //Keyboard.press(KEY_RIGHT_ARROW);
            Serial.println("RIGHT is pressed");
        }
        break;
    case 4:
        if(lastDirection != 4) {
            //Keyboard.release(KEY_UP_ARROW);
            //Keyboard.release(KEY_LEFT_ARROW);
            //Keyboard.press(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_DOWN_ARROW);
            Serial.println("RIGHT DOWN is pressed");
        }
        break;
    case 5:
        if(lastDirection != 5) {
            //Keyboard.release(KEY_UP_ARROW);
            //Keyboard.release(KEY_LEFT_ARROW);
            //Keyboard.release(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_DOWN_ARROW);
            Serial.println("DOWN is pressed");
        }
        break;
    case 6:
        if(lastDirection != 6) {
            //Keyboard.release(KEY_UP_ARROW);
            //Keyboard.release(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_DOWN_ARROW);
            //Keyboard.press(KEY_LEFT_ARROW);
            Serial.println("LEFT DOWN is pressed");
        }
        break;
    case 7:
        if(lastDirection != 7) {
            //Keyboard.release(KEY_DOWN_ARROW);
            //Keyboard.release(KEY_UP_ARROW);
            //Keyboard.release(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_LEFT_ARROW);
            Serial.println("LEFT is pressed");
        }
        break;
    case 8:
        if(lastDirection != 8) {
            //Keyboard.release(KEY_DOWN_ARROW);
            //Keyboard.release(KEY_RIGHT_ARROW);
            //Keyboard.press(KEY_LEFT_ARROW);
            //Keyboard.press(KEY_UP_ARROW);
            Serial.println("LEFT UP is pressed");
        }
        break;
    case 0:
        if(lastDirection != 0) {
            Serial.println("J0");
        }
        break;
  }
  lastDirection = direction;
}

void outputRawJoystickData() {
  joystickX = analogRead(JOYSTICK_X);
  joystickY = analogRead(JOYSTICK_Y);

  Serial.print("x:");
  Serial.print(joystickX);
  Serial.print(" ");

  Serial.print("y:");
  Serial.print(joystickY);
  Serial.println(" ");
}


void loop() {

    statusA = sendKey(BUTTON_A, statusA, 'a');
    statusB = sendKey(BUTTON_B, statusB, 'b');
    statusG = sendKey(BUTTON_G, statusG, 'g');
    statusF = sendKey(BUTTON_F, statusF, 'f');
    statusE = sendKey(BUTTON_E, statusE, 'e');
    statusD = sendKey(BUTTON_D, statusD, 'd');
    statusJOYSTICK = sendKey(BUTTON_JOYSTICK, statusJOYSTICK, 'j');

    //outputRawJoystickData();

}
