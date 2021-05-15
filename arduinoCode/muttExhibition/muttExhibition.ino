class LDR
{
  int inputLDR;
  int outputLED;

public:
  LDR(int inputLDR, int outputLED) : inputLDR{inputLDR}, outputLED{outputLED}
  {
    pinMode(outputLED, OUTPUT);
  }

  void loop()
  {
    digitalWrite(outputLED, analogRead(inputLDR) <= 700 ? HIGH : LOW);
  }
};

class LDR_PIR
{
  int inputLDR;
  int inputPIR;
  int outputLED;
  int timeToOff = 7;
  int timer = timeToOff + 1;

public:
  LDR_PIR(int inputLDR, int inputPIR, int outputLED) : inputLDR{inputLDR}, inputPIR{inputPIR}, outputLED{outputLED}
  {
    pinMode(inputPIR, INPUT);
    pinMode(outputLED, OUTPUT);
  }

  void turnOff()
  {
    if (timer > timeToOff)
      digitalWrite(outputLED, LOW);
  }

  void turnOn()
  {
    digitalWrite(outputLED, HIGH);
    timer = 0;
  }

  void loop()
  {
    if (analogRead(inputLDR) > 700)
      turnOff();
    else if (digitalRead(inputPIR) == HIGH)
      turnOn();
    else
      turnOff();
    timer++;
  }
};

class Bluetooth
{
  int outputLED1;
  int outputLED2;

public:
  Bluetooth(int outputLED1, int outputLED2) : outputLED1{outputLED1}, outputLED2{outputLED2}
  {
    pinMode(outputLED1, OUTPUT);
    pinMode(outputLED2, OUTPUT);
  }

  void loop()
  {
    if (Serial.available() > 0)
    {
      switch (Serial.read())
      {
      case '0':
        digitalWrite(outputLED1, LOW);
        break;
      case '1':
        digitalWrite(outputLED1, HIGH);
        break;
      case '2':
        digitalWrite(outputLED2, LOW);
        break;
      case '3':
        digitalWrite(outputLED2, HIGH);
        break;
      }
    }
  }
};

LDR *ldr = new LDR(A0, 8);
LDR_PIR *ldrpir = new LDR_PIR(A1, 2, 9);
Bluetooth *bluetooth = new Bluetooth(10, 11);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  ldr->loop();
  ldrpir->loop();
  bluetooth->loop();
  delay(1000);
}
