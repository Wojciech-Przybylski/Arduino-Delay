//defining the output PWM parameters
#define PWM_FREQ 0x00FF // pwm frequency - 31.3KHz
#define PWM_MODE 0 // Fast (1) or Phase Correct (0)
#define PWM_QTY 2 // 2 PWMs in parallel

//other variables
int input;
unsigned int ADC_low, ADC_high;

#define MAX_DELAY 2000
byte DelayBuffer[MAX_DELAY];
unsigned int DelayCounter = 0;
unsigned int Delay_Depth = MAX_DELAY;

void setup() {
  // setup ADC
  ADMUX = 0x60; // left adjust, adc0, internal vcc
  ADCSRA = 0xe5; // turn on adc, ck/32, auto trigger
  ADCSRB = 0x07; // t1 capture for trigger
  DIDR0 = 0x01; // turn off digital inputs for adc0

  // setup PWM
  TCCR1A = (((PWM_QTY - 1) << 5) | 0x80 | (PWM_MODE << 1)); // first timer as pwm - phase correct 
  TCCR1B = ((PWM_MODE << 3) | 0x11); // ck/1
  TIMSK1 = 0x20; // interrupt on capture interrupt
  ICR1H = (PWM_FREQ >> 8);
  ICR1L = (PWM_FREQ & 0xff);
  DDRB |= ((PWM_QTY << 1) | 0x02); // turn on outputs
  sei(); // turn on interrupts -
}

void loop() {
  
}

ISR(TIMER1_CAPT_vect) 
{
  // get ADC data
  ADC_low = 0; // ADC_low always 0 to save space
  ADC_high = ADCH;

  //store the high bit only for
  DelayBuffer[DelayCounter] = ADC_high;

  //Increse/reset delay counter.
  DelayCounter++;
  if (DelayCounter >= Delay_Depth) DelayCounter = 0;

  input = (((DelayBuffer[DelayCounter] << 8) | ADC_low) + 0x8000) + (((ADC_high << 8) | ADC_low) + 0x8000); // make a signed 16b value

  //write the PWM signal
  OCR1AL = ((input + 0x8000) >> 8); // convert to unsigned, send out high byte
  OCR1BL = input; // send out low byte

}
