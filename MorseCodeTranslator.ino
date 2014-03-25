  /* 
 Morse code translator.
 
 For the Arduino Leonardo and Micro.
 
 Translates button presses in morse code into keyboard characters
 
 The circuit:
 * pushbutton attached from pin 2 to +5V
 * 10-kilohm resistor attached from pin 4 to ground
 */

const int button = 2;              // input pin for pushbutton
//const int dahTime = 10;          // number of milliseconds for a dah
const int maxMorseCharSize = 25;   // the maximum size of a sequence of morse chars
char morseChar[maxMorseCharSize];  // the string of dits and dahs used to represent a character
int morseCharSize = 0;
const int timeUnit = 100;           // time unit for beats in milliseconds

void appendMorseChar(char c)
{ 
  //TODO: Check if morseCharSize is too large. Maybe print an error
  morseChar[morseCharSize] = c;  // add a dit to the end of the string
  ++morseCharSize;                 // increment the string size
}

void appendDitOrDah(int held) 
// determines whether dit, dah, or space and appends
{
  if (held <= 2)           
  {
    appendMorseChar('.');                   // append a dit to the morseChar string
  }
  else                             // a second has passed, note that the button may still be down
  {
    appendMorseChar('-');                   // append a dah to the morseChar string
  } 
}

void handleGap(int unheld)
// Handles gap behavior appropriately
{
    if (unheld >= 7) // if word gap
    {
       Keyboard.write(' ');  // send a keyboard space char 
    }
    else if (unheld >= 3 && unheld < 7) // if letter gap
    {
        Keyboard.write(translateMorse());  // translate morse code to keyboard char
    }
}

char translateMorse()
// translates dits and dahs to ascii chars
{
    if (morseChar[0] == '.')
    {
        if (morseChar[1] == '.')
        {

        }
        else if (morseChar[1] == '-')
        {

        }
        else
        {
            return 'e';
        }
    }
}

void setup() 
{
  pinMode(button, INPUT);          // make the pushButton pin an input:
  Keyboard.begin();                // initialize control over the keyboard:
}

void loop() 
{
  int held = 0;                            // counter for number of time units button is held
  int unheld = 0;                          // counter for number of time units button is unheld

  while (digitalRead(button) == HIGH)
  {
    delay(timeUnit);                       // count out one time unit
    ++held;
  }
  appendDitOrDah(held);                   // determines whether dit, dah, or space and appends

  // count the number of unheld beats
  while (digitalRead(button) != HIGH && unheld < 30)
  {
    delay(timeUnit);                       // count out one time unit
    ++unheld;
  } 
  handleGap(unheld);
}


