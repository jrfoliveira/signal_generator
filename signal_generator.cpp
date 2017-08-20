// Do not remove the include below
#include "signal_generator.h"

const int W_CLK_PIN = 8;
const int FQ_UD_PIN = 9;
const int DATA_PIN = 10;
const int RESET_PIN = 11;
const int LED = 13;

double trimFreq = 125000000;

int phase = 0;

//everytime that we connect the usb in ubuntu is needed to issue the following commands
// $ sudo chmod a+rw /dev/ttyACM0
// $ sudo usermod -a -G dialout <user>

static hc_sr08::ad9850 dds;

//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	pinMode(LED, OUTPUT);
	digitalWrite(LED,LOW);
	Serial.begin(9600);
	Serial.println(" Signal Generator - jrfo ");
	dds.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
	dds.calibrate(trimFreq);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	static int state=0;
	static bool needPrompt=true;
	char* userInput;

	if (needPrompt)
	{
		Serial.println("Please enter frequency in Hz: ");
		needPrompt=false;
	}
	userInput= serialString();
	if (userInput!=NULL)
	{
		digitalWrite(LED,HIGH);
		dds.setfreq(atof(userInput),phase);
		Serial.print("adjusting frequency: ");
		Serial.print(userInput);
		Serial.println(" Hz");
		needPrompt=true;
		digitalWrite(LED,LOW);
	}

	if(!needPrompt)
	{
		delay(200);
		digitalWrite(LED,HIGH);
		delay(200);
		digitalWrite(LED,LOW);
	}
}

char* serialString(void)
{
  static char str[21]; // For strings of max length=20
  if (!Serial.available()) return NULL;
  delay(64); // wait for all characters to arrive
  memset(str,0,sizeof(str)); // clear str
  byte count=0;
  while (Serial.available())
  {
    char c=Serial.read();
    if (c>=32 && count<sizeof(str)-1)
    {
      str[count]=c;
      count++;
    }
  }
  str[count]='\0'; // make it a zero terminated string
  return str;
}
