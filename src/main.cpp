#include <Arduino.h>
#include <BfButton.h>
#include <NoDelay.h>

#define INITIAL_VALUE 0x0
#define LIMITS_MIN 0x0
#define LIMITS_MAX 0x9
#define DELAY_BETWEEN_ROLLS 1000
#define DELAY_SCROLL_5 5
#define DELAY_SCROLL_25 25
#define DELAY_SCROLL_50 50
#define DELAY_SCROLL_250 250
#define DELAY_SCROLL_500 500

#define PIN_BTN 4
#define PIN_A 13
#define PIN_B 12
#define PIN_C 14
#define PIN_D 16

unsigned int MODE = 0; // 0 = manual, 1 = auto

BfButton btn(BfButton::STANDALONE_DIGITAL, PIN_BTN);

void show_number(int value);
int generate_random_number_between(int min, int max);
void roll_dice();
void scroll_numbers(int value);
void auto_random_dice();
void set_mode(unsigned int mode);
void pressHandler(BfButton *btn, BfButton::press_pattern_t pattern);

noDelay auto_mode_time(DELAY_BETWEEN_ROLLS, auto_random_dice);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println();

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);

  pinMode(PIN_BTN, INPUT_PULLUP);

  show_number(INITIAL_VALUE);

  btn.onPress(pressHandler)
      .onDoublePress(pressHandler)     // default timeout
      .onPressFor(pressHandler, 1000); // custom timeout for 1 second

  Serial.println("Dice initialized!!!");
  Serial.println("Press the button to roll the dice.");
}

void loop()
{
  btn.read();
  auto_mode_time.update();
  
}

void show_number(int value)
{
  if (value < LIMITS_MIN || value > LIMITS_MAX)
  {
    digitalWrite(PIN_A, 0);
    digitalWrite(PIN_B, 0);
    digitalWrite(PIN_C, 0);
    digitalWrite(PIN_D, 0);
    return;
  }

  uint8_t a, b, c, d = INITIAL_VALUE;
  a = (value >> 3) & 1;
  b = (value >> 2) & 1;
  c = (value >> 1) & 1;
  d = (value >> 0) & 1;

  digitalWrite(PIN_A, a);
  digitalWrite(PIN_B, b);
  digitalWrite(PIN_C, c);
  digitalWrite(PIN_D, d);
}

int generate_random_number_between(int min, int max)
{
  min = min > LIMITS_MIN || min > LIMITS_MAX || min > max ? LIMITS_MIN : min;
  max = max < LIMITS_MIN || max > LIMITS_MAX || max < min ? LIMITS_MAX : max;

  return random(min, max);
}

void roll_dice()
{
  int value = generate_random_number_between(LIMITS_MIN, LIMITS_MAX);
  Serial.println("Dice value: " + String(value));
  scroll_numbers(value);
}

void scroll_numbers(int value)
{
  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_5);
  }

  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_25);
  }

  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_50);
  }

  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_250);
  }

  for (int i = INITIAL_VALUE; i <= value; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_500);
  }
}

void auto_random_dice()
{
  int value = generate_random_number_between(LIMITS_MIN, LIMITS_MAX);
  Serial.println("Dice value: " + String(value));
  show_number(value);
}

void pressHandler(BfButton *btn, BfButton::press_pattern_t pattern)
{  
  switch (pattern)
  {
  case BfButton::SINGLE_PRESS:    
    roll_dice();
    Serial.println("Press the button to roll the dice.");
    break;
  case BfButton::DOUBLE_PRESS:
    Serial.println("Manual mode selected.");
    set_mode(0);
    auto_mode_time.stop();    
    break;
  case BfButton::LONG_PRESS:
    Serial.println("Auto mode selected.");    
    set_mode(1);
    auto_mode_time.start();
    break;
  }
}

void set_mode(unsigned int mode)
{
  MODE = mode;
}