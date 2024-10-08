/*************************************************************
  project: <Accessories>
  author: <Thierry PARIS>
  description: <Source for Locoduino Accessories/Commander Demonstrator.>
*************************************************************/

#include "Commanders.h"
#include "Accessories.h"

// DCC codes
#define AIGUILLE    20 //DCCINT(20,0)
#define DECOUPLAGE    21 //DCCINT(21,0)

#define ANIMLEDS    1
#define ANIMLEDSPOS   100

#define LED1      2
#define LED2      3
#define LED3      4
#define LED4      5
#define LED5      8
#define LED6      7

#define FEU       2
#define FEUPOS      200

#define SERVOPOS    300

#define DEMOSWITCH  400
#define FEUSWITCH	401
#define AIG1PUSH	402
#define AIG2PUSH	403

const EventsSequencerItem animationEvents[] PROGMEM =
{
	// mouvement une led depuis la droite lent
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 0, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 1, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 2, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 3, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 4, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 5, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 6, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 5, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 4, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 3, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 2, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 1, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 0, 300, NULL},

	// mouvement une led depuis la gauche rapide
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 6, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 5, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 4, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 3, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 2, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 1, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 0, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 1, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 2, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 3, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 4, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 5, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 6, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 0, 300, NULL},

	// barre progressive lente depuis la droite
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  1, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  7, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  8, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  9, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 10, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 11, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 10, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  9, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  8, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  7, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  1, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  0, 300, NULL},

	// barre progressive rapide depuis la gauche
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  6, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 15, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 14, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 13, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 12, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 11, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 12, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 13, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 14, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 15, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  6, 100, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  0, 100, NULL},

	// mouvement deux leds lent depuis la droite
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  1, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  7, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 16, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 17, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 18, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 19, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  1, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  7, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 16, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 17, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 18, 300, NULL },
	{ ANIMLEDSPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX, 0, 300, NULL},

	// Fin de la liste
	{ UNDEFINED_ID, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_NONE, 0, 0, NULL}
};

const MovingPosition animationPositions[] PROGMEM =
{
  { ANIMLEDSPOS + 0, B00000000 },
  { ANIMLEDSPOS + 1, B00000001 },
  { ANIMLEDSPOS + 2, B00000010 },
  { ANIMLEDSPOS + 3, B00000100 },
  { ANIMLEDSPOS + 4, B00001000 },
  { ANIMLEDSPOS + 5, B00010000 },
  { ANIMLEDSPOS + 6, B00100000 },
  { ANIMLEDSPOS + 7, B00000011 },
  { ANIMLEDSPOS + 8, B00000111 },
  { ANIMLEDSPOS + 9, B00001111 },
  { ANIMLEDSPOS + 10, B00011111 },
  { ANIMLEDSPOS + 11, B00111111 },
  { ANIMLEDSPOS + 12, B00111110 },
  { ANIMLEDSPOS + 13, B00111100 },
  { ANIMLEDSPOS + 14, B00111000 },
  { ANIMLEDSPOS + 15, B00110000 },
  { ANIMLEDSPOS + 16, B00000110 },
  { ANIMLEDSPOS + 17, B00001100 },
  { ANIMLEDSPOS + 18, B00011000 },
  { ANIMLEDSPOS + 19, B00100001 },
  { -1, 0 },	// fin de liste
};

const byte anims[] PROGMEM =
{
	B00000000,  // 0
	B00000001,
	B00000010,
	B00000100,
	B00001000,
	B00010000,  // 5
	B00100000,
	B00000011,
	B00000111,
	B00001111,
	B00011111,  // 10
	B00111111,
	B00111110,
	B00111100,
	B00111000,
	B00110000,  // 15
	B00000110,
	B00001100,
	B00011000,
	B00100001   // 19
};

#define NBANIMS   sizeof(anims) / sizeof(byte)

const EventsSequencerItem feuEvents[] PROGMEM =
{
	{ FEUPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  0, 4000, NULL },
	{ FEUPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  1, 4000, NULL },
	{ FEUPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  2, 4000, NULL },
	{ FEUPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  3, 4000, NULL },
	{ FEUPOS, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  4, 4000, NULL },
	{ UNDEFINED_ID, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_NONE, 0, 0, NULL }
};

const byte PROGMEM animsFeu[][2]
{
	{ B00, B00 },
	{ B10, B00 },
	{ B01, B00 },
	{ B11, B00 },
	{ B11, B11 },
	{ -1, 0 },	// fin de liste
};

#define NBANIMSFEU    sizeof(animsFeu) / sizeof(byte) / 2

const EventsSequencerItem servoEvents[] PROGMEM =
{
	{ SERVOPOS + 0, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  0, 10000, NULL },
	{ SERVOPOS, (COMMANDERS_EVENT_TYPE)ACCESSORIES_EVENT_TYPE::ACCESSORIES_EVENT_SETDURATION,  0, 10, NULL },
	{ SERVOPOS + 1, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  1, 2000, NULL },
	{ SERVOPOS + 2, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVEPOSITIONINDEX,  2, 2000, NULL },
	{ SERVOPOS, (COMMANDERS_EVENT_TYPE)ACCESSORIES_EVENT_TYPE::ACCESSORIES_EVENT_SETDURATION,  50, 10, NULL },
	{ UNDEFINED_ID, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_NONE, 0, 0, NULL }
};

const EventsSequencerItem moteursEvents[] PROGMEM =
{
	{ AIGUILLE, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVE, COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_LEFT, 2000, NULL },
	{ AIGUILLE, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVE, COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_RIGHT, 2000, NULL },
	{ DECOUPLAGE, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVE, COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_LEFT, 2000, NULL },
	{ UNDEFINED_ID, COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_NONE, 0, 0, NULL }
};

//SERIAL_COMMANDER(Serial)

EventsSequencer moteursSeq;
EventsSequencer animationLumineuse;
EventsSequencer feuSeq;
EventsSequencer servoSeq;

// Accessories

AccessoryMotorTwoWays aiguille;
AccessoryMotorOneWay decouplage;

AccessoryLightMulti animation;
AccessoryLightMulti feu;

AccessoryServo servo;

// Ports

PortTwoPins portAiguille;
PortOnePin portDecouplage;

PortOnePin portLed1;
PortOnePin portLed2;
PortOnePin portLed3;
PortOnePin portLed4;
PortOnePin portLed5;
PortOnePin portLed6;

PortOnePin portFeuRouge;
PortOnePin portFeuVert;

PortServo portServo;

ButtonsCommanderSwitchOnePin demo;
ButtonsCommanderSwitchOnePin switchFeu;
ButtonsCommanderPush aigDroit, aigDevie;

void ReceiveEvent(unsigned long inId, COMMANDERS_EVENT_TYPE inEventType, int inEventData)
{
	//Commanders::printEvent(inId, inEventType, inEventData);
	switch (inId)
	{
	case DEMOSWITCH:
		if (inEventType == COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVE)
		{
			if (inEventData == COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_ON)
			{	
				moteursSeq.Continue();
				animationLumineuse.Continue();
				feuSeq.Continue();
				servoSeq.Continue();
			}
			if (inEventData == COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_OFF)
			{
				moteursSeq.Pause();
				animationLumineuse.Pause();
				feuSeq.Pause();
				servoSeq.Pause();
			}
		}
		return;

	case FEUSWITCH:
		if (inEventType == COMMANDERS_EVENT_TYPE::COMMANDERS_EVENT_MOVE)
		{
			if (inEventData == COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_ON)
			{
				Accessories::ReceiveEvent(FEUPOS + 1, ACCESSORIES_EVENT_TYPE::ACCESSORIES_EVENT_MOVEPOSITIONID, 0);
			}
			if (inEventData == COMMANDERS_MOVE_TYPE::COMMANDERS_MOVE_OFF)
			{
				Accessories::ReceiveEvent(FEUPOS + 2, ACCESSORIES_EVENT_TYPE::ACCESSORIES_EVENT_MOVEPOSITIONID, 0);
			}
		}
		return;

	case AIG1PUSH:
		Accessories::ReceiveEvent(AIGUILLE, ACCESSORIES_EVENT_TYPE::ACCESSORIES_EVENT_MOVE, ACCESSORIES_MOVE_TYPE::ACCESSORIES_MOVE_LEFT);
		return;

	case AIG2PUSH:
		Accessories::ReceiveEvent(AIGUILLE, ACCESSORIES_EVENT_TYPE::ACCESSORIES_EVENT_MOVE, ACCESSORIES_MOVE_TYPE::ACCESSORIES_MOVE_RIGHT);
		return;
	}

	Accessories::ReceiveEvent(inId, (ACCESSORIES_EVENT_TYPE)inEventType, inEventData);
}

void setupAiguille()
{
	// ports begins

	portAiguille.begin(A3, A4, DIGITAL);

	// Accessories begin

	aiguille.begin(&portAiguille, AIGUILLE, 255, 300);

	Serial.println(F("Fin setupAiguille"));
}

void setupDecouplage()
{
	// ports begins

	portDecouplage.begin(A2, DIGITAL);

	// Accessories begin

	decouplage.begin(&portDecouplage, DECOUPLAGE, 255, 800);

	moteursSeq.begin(true);
	moteursSeq.AddEvents(moteursEvents);

	Serial.println(F("Fin setupDecouplage"));
}

void setupAnimation()
{
	portLed1.begin(LED1, DIGITAL_INVERTED);
	portLed2.begin(LED2, DIGITAL_INVERTED);
	portLed3.begin(LED3, DIGITAL_INVERTED);
	portLed4.begin(LED4, DIGITAL_INVERTED);
	portLed5.begin(LED5, DIGITAL_INVERTED);
	portLed6.begin(LED6, DIGITAL_INVERTED);

	animation.begin(ANIMLEDS, 6, 0);
	animation.beginLight(0, &portLed1);
	animation.beginLight(1, &portLed2);
	animation.beginLight(2, &portLed3);
	animation.beginLight(3, &portLed4);
	animation.beginLight(4, &portLed5);
	animation.beginLight(5, &portLed6);

	animation.AddMovingPositions(animationPositions);

	// Events Sequencer

	animationLumineuse.begin(true);
	animationLumineuse.AddEvents(animationEvents);
}

void setupFeu()
{
	portFeuRouge.begin(11, ANALOG);
	portFeuVert.begin(6, ANALOG);

	feu.begin(FEU, 2, 500);
	feu.beginLight(0, &portFeuVert);
	feu.SetFading(0, 12, 20);
	feu.beginLight(1, &portFeuRouge);
	feu.SetFading(1, 12, 20);

	feu.AdjustMovingPositionsSize(NBANIMSFEU);
	for (int i = 0; i < NBANIMSFEU; i++)
		feu.AddMovingPosition(FEUPOS + i, pgm_read_byte(&(animsFeu[i][0])), pgm_read_byte(&(animsFeu[i][1])));

	// Events Sequencer

	feuSeq.begin(true);
	feuSeq.AddEvents(feuEvents);

	Serial.println(F("Fin setupFeu"));
}

void setupServo()
{
	// ports begins

	portServo.begin(A5);

	// Accessories begin

	servo.begin(&portServo);
	servo.AddMovingPosition(SERVOPOS, 20);
	servo.AddMovingPosition(SERVOPOS + 1, 83);
	servo.AddMovingPosition(SERVOPOS + 2, 160);

	servoSeq.begin(true);
	servoSeq.AddEvents(servoEvents);

	Serial.println("Fin setupServo");
}

//////////////////////////////////
//
// Setup
//
void setup()
{
	Serial.begin(115200);
	//while (!Serial);    // For Leonardo only. No effect on other Arduino.

	Commanders::begin(ReceiveEvent, LED_BUILTIN);
	Accessories::begin();

	// Buttons

	demo.begin(DEMOSWITCH, A1);
	switchFeu.begin(FEUSWITCH, 12);
	aigDroit.begin(AIG1PUSH, 9);
	aigDevie.begin(AIG2PUSH, 10);

	// Accessories setups

	setupAiguille();
	setupDecouplage();
	setupAnimation();
	setupFeu();
	setupServo();

	// Events sequencers

	moteursSeq.Start();
	animationLumineuse.Start();
	feuSeq.Start();
	servoSeq.Start();
}

void loop()
{
	Accessories::loop();

	Commanders::loop();
}