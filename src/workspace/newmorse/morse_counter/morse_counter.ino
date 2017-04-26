
int ambientLight = 0;
long startTime = 0;
byte state = 0;

int LIGHT_CHANGE_THRESHOLD = 40;
void setup()
{
    Serial.begin(9600);
    Serial.println("__________________________");
    pinMode(13, OUTPUT);
    pinMode(A1, INPUT);
    digitalWrite(13, LOW);
    initialize();
}



void initialize()
{
    delay(100);
    pinMode(13, OUTPUT);
    pinMode(A1,INPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    
    Serial.begin(9600);
}



void loop()
{
    doPhotocellThings();
    


    
}

void doPhotocellThings()
{
  //Serial.println(analogRead(A1));
    long lightDelta = analogRead(A1) - ambientLight;
    long timeDelta = millis() - startTime;
    if (millis() > 500 && ambientLight == 0) {
        ambientLight = analogRead(A1);
    }
    else {
        if (lightDelta > LIGHT_CHANGE_THRESHOLD && state != 2) {
            if (state == 1) {
               Serial.print("off   ");
               Serial.println(timeDelta);
            }
            state = 2;
            startTime = millis();
        }
        else if (!(lightDelta > LIGHT_CHANGE_THRESHOLD) && state == 2) {
            state = 1;
            startTime = millis();
             Serial.print("on    ");
               Serial.println(timeDelta);
        }
    }
}


