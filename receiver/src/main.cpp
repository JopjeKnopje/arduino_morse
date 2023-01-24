#include <Arduino.h>
#include "SimpleTimer.hpp"


#define PIN_LDR A0
#define PIN_MORSE 10
#define MORSE_COUNT 36

const int TIME_UNIT = 250;
const int DOT = TIME_UNIT;
const int DASH = 3 * TIME_UNIT;
const int SYMBOL_SP = TIME_UNIT;
const int LETTER_SP = TIME_UNIT * 3 - SYMBOL_SP;
const int WORD_SP = TIME_UNIT * 6 - SYMBOL_SP;
const int TOLERANCE = -50;



typedef struct s_morse_letter
{
    char morse[6];
    char letter;
}	t_morse_letter;

#ifdef __cplusplus
static t_morse_letter lookup_table[] = {
#endif
	{"-----", '0'},
	{".----", '1'},
	{"..---", '2'},
	{"...--", '3'},
	{"....-", '4'},
	{".....", '5'},
	{"-....", '6'},
	{"--...", '7'},
	{"---..", '8'},
	{"----.", '9'},
	{".-", 'A'},
	{"-...", 'B'},
	{"-.-.", 'C'},
	{"-..", 'D'},
	{".", 'E'},
	{"..-.", 'F'},
	{"--.", 'G'},
	{"....", 'H'},
	{"..", 'I'},
	{".---", 'J'},
	{"-.-", 'K'},
	{".-..", 'L'},
	{"--", 'M'},
	{"-.", 'N'},
	{"---", 'O'},
	{".--.", 'P'},
	{"--.-", 'Q'},
	{".-.", 'R'},
	{"...", 'S'},
	{"-", 'T'},
	{"..-", 'U'},
	{"...-", 'V'},
	{".--", 'W'},
	{"-..-", 'X'},
	{"-.--", 'Y'},
	{"--..", 'Z'},
	{"", '\0'}
#ifdef __cplusplus
};
#endif

void setup()
{
    Serial.begin(9600);
    pinMode(PIN_LDR, INPUT);
    pinMode(PIN_MORSE, INPUT);
}



void iterate_table()
{
    for (size_t i = 0; i < MORSE_COUNT; i++)
    {
        Serial.print(lookup_table[i].letter);
        Serial.print(" | ");
        Serial.print(lookup_table[i].morse);
        Serial.println();
        delay(100);
    }
}



SimpleTimer pulseDurationTimer("pulse timer");
bool first_pulse_init = false;

char morse_buf[6];
int symbol_count = 0;


void loop()
{
    if (digitalRead(PIN_MORSE))
    {
        if (!first_pulse_init || pulseDurationTimer.delta() > WORD_SP)
        {
            pulseDurationTimer.start();
            first_pulse_init = true;
            Serial.println("encounterd high");
        }
    }
    else
    {
        pulseDurationTimer.stop(); 
        Serial.println("encounterd low");
    }
    if (pulseDurationTimer.delta()) 
    {
        Serial.print("pulse delta ");
        Serial.println(pulseDurationTimer.delta());
    }
    // check if symbol
    if (pulseDurationTimer.delta() > SYMBOL_SP + TOLERANCE && pulseDurationTimer.delta() < SYMBOL_SP -+ TOLERANCE)
    {
        morse_buf[symbol_count] = 'a';
        symbol_count++;
    }
}