#define BLYNK_TEMPLATE_ID "TMPLtkah7fhW"
#define BLYNK_TEMPLATE_NAME "Home automation"
#define BLYNK_AUTH_TOKEN "PAuNoIM7bW4SQPoz5cZ9pCxwTBS-Ngbu"
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Balish";
char pass[] = "518616gepp";

BlynkTimer timer;
int pinValue=0;
#define switch1 D5
#define switch2 D6
#define switch3 D7
#define pir D3
#define fire D2
#define buzzer D4
#define redlight D0
#define greenlight_for_pir D1
#define greenlight_for_fire D8
int fire_Val = 0;
//switch1=d5----V0
//switch2=d6----V1
//switch3=d7-----V2
//pir=d3--------V3
//fame=d2-------V4
//buzzer=d4
//redlight=d0
//greenlight=d1
//greenlight=d8

void setup()
  {
    Serial.begin(9600);
    pinMode(switch1,OUTPUT);
    pinMode(switch2,OUTPUT);
    pinMode(switch3,OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(redlight, OUTPUT);
    pinMode(greenlight_for_pir, OUTPUT);
    pinMode(greenlight_for_fire, OUTPUT);
    pinMode(pir, INPUT);
    pinMode(fire, INPUT);
    Blynk.begin(auth, ssid, pass);
    timer.setInterval(1000L,notification);
  }

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(switch1, HIGH);
    Serial.println("ROOM_1 LED ON");
  }
  if(value == 0)
  {
     digitalWrite(switch1, LOW);
     Serial.println("ROOM_1 LED OFF");
  }
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(switch2, HIGH);
    Serial.println("ROOM_2 LED ON");
  }
  if(value == 0)
  {
     digitalWrite(switch2, LOW);
     Serial.println("ROOM_2 LED OFF");
  }
}
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(switch3, HIGH);
    Serial.println("ROOM_3 LED ON");
  }
  if(value == 0)
  {
     digitalWrite(switch3, LOW);
     Serial.println("ROOM_3 LED OFF");
  }
}

BLYNK_WRITE(V3)
{
 pinValue = param.asInt();
}

BLYNK_WRITE(V4)
{
 fire_Val = param.asInt();
}
/////////////////////PIR CODE PART////////////////////

void notification()
{
  int sensor=digitalRead(pir);
  int fire_sensor=digitalRead(fire);
  if(pinValue==1)
  {
    Serial.println("System is ON");
    if(sensor==1)
    {
      Blynk.logEvent("PIR_SEN","WARNING! Please check door security");//event code
      digitalWrite(buzzer,HIGH);
      digitalWrite(greenlight_for_pir, HIGH);
    }
    else if(sensor==0)
    {
      digitalWrite(buzzer,LOW);
      digitalWrite(greenlight_for_pir, LOW);
    }
  }else if(pinValue==0)
  {
    Serial.println("System is OFF");
  }



///////////////////////////////////////////////
  if(fire_Val==1)
  {
    Serial.println("System is ON");
    if(fire_sensor==1)
    {
      Blynk.logEvent("FIRE_SEN","WARNING! Fire! Fire!");//event code
      digitalWrite(greenlight_for_fire, LOW);
      digitalWrite(redlight, HIGH);
      digitalWrite(buzzer,HIGH);
    }
    else if(fire_sensor==0)
    {
      digitalWrite(greenlight_for_fire, HIGH);
      digitalWrite(redlight, LOW);
      digitalWrite(buzzer,LOW);
    }
  }else if(fire_Val==0)
  {
    Serial.println("System is OFF");
  }
}
void loop()
  {
    Blynk.run();
    timer.run();
  }
