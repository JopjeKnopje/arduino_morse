const int LED = 7;
const int TIME_UNIT = 250;
const int DOT = TIME_UNIT;
const int DASH = 3 * TIME_UNIT;
const int SYMBOL_SP = TIME_UNIT;
const int LETTER_SP = TIME_UNIT * 3 - SYMBOL_SP;
const int WORD_SP = TIME_UNIT * 6 - SYMBOL_SP;
const int MORSE_CODE = 26 + 10;

char c;
int LED_ON = 0;

typedef struct s_morse_letter
{
    char morse[6];
    char letter;
}	t_morse_letter;

#ifdef __cplusplus
const static t_morse_letter lookup_table[] = {
#endif
    {"-----",'0'},
    {".----",'1'},
    {"..---",'2'},
    {"...--",'3'},
    {"....-",'4'},
    {".....",'5'},
    {"-....",'6'},
    {"--...",'7'},
    {"---..",'8'},
    {"----.",'9'},
    {".-",'A'},
    {"-...",'B'},
    {"-.-.",'C'},
    {"-..",'D'},
    {".",'E'},
    {"..-.",'F'},
    {"--.",'G'},
    {"....",'H'},
    {"..",'I'},
    {".---",'J'},
    {"-.-",'K'},
    {".-..",'L'},
    {"--",'M'},
    {"-.",'N'},
    {"---",'O'},
    {".--.",'P'},
    {"--.-",'Q'},
    {".-.",'R'},
    {"...",'S'},
    {"-",'T'},
    {"..-",'U'},
    {"...-",'V'},
    {".--",'W'},
    {"-..-",'X'},
    {"-.--",'Y'},
    {"--..",'Z'}
#ifdef __cplusplus
};
#endif

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter your message.\n");
}

void loop() {
  if (Serial.available())
  {
    c = Serial.read();
    if (c >= 'a' && c <= 'z')
      c -= 32;
    else if (c >= 'A' && c <= 'Z')
    {
      Serial.println(c);
      signal_led(lookup_table[c - 'A'].morse);
      delay(LETTER_SP);
    }
    else if (c >= '0' && c <= '9')
    {
      Serial.println(c);
      signal_led(lookup_table[c].morse);
      delay(LETTER_SP);
    }
    else if (c == ' ')
    {
      Serial.println(c);
      delay(WORD_SP);
    }
  }
}

void  signal_led(char *morse_string)
{
  size_t  i;

  i = 0;
  while (morse_string[i])
  {
    dot_dash(morse_string[i]);
    delay(SYMBOL_SP);
    i++;
  }
}

void  dot_dash(char c)
{
  digitalWrite(LED, HIGH);
  if (c == '.')
    delay(DOT);
  else
    delay(DASH);
  digitalWrite(LED, LOW);
}
