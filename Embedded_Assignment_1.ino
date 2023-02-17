// setting up the pins
const int button_1 = 2; // pin 2 assigned to button 1
const int button_2 = 4; // pin 4 assigned to button 2

const int signal_A = 3; // pin 3 will be as signal A or LED 1
const int signal_B = 5; // pin 5 will be as signal B or LED 2

// variables to read from switches
int read_button_1 = 0; // declaring a variable to read from button 1 initially set as LOW
int read_button_2 = 0; // declaring a variable to read from button 2 initially set as LOW

// setting up the parameters
int a = 1300;       // parameter 'a' calculated as first letter*100 = 13*100 = 1300
const int b = 100;  // parameter 'b' calculated as second letter*100 = 1*100 = 100
const int c = 13;   // parameter 'c' calculated as third letter+4 = 9+4=13
const int d = 2500; // parameter 'd' calculated as fourth letter*500 = 5*500 = 2500

int r = 1950; // parameter used in mode '1' where we reverse the signal, hence highest value is a+(c-1)*b = 1950
// mode is calculated as rem(fifth letter/4) + 1 = rem(4/4) + 1 = 1. Hence the mode is 1

void setup()
{
  // put your setup code here, to run once:
  pinMode(button_1, INPUT);  // setting button_1 pin(button 1) as INPUT
  pinMode(button_2, INPUT);  // setting button_2 pin(button 2) as INPUT
  pinMode(signal_A, OUTPUT); // setting signal_A pin(LED 1/signal A) as OUTPUT
  pinMode(signal_B, OUTPUT); // setting signal_B pin(LED 2/signal B) as OUTPUT
}

void run_mode(int x, int increment)
{
  digitalWrite(signal_B, HIGH);
  delay(50);
  digitalWrite(signal_B, LOW);

  for (int i = 0; i < c; i++)
  {
    digitalWrite(signal_A, HIGH);
    delay(x);
    digitalWrite(signal_A, LOW);
    delay(b);

    x = x + increment;
  }
  digitalWrite(signal_A, LOW);
  delay(d);
}

void loop()
{
  // put your main code here, to run repeatedly:
  read_button_1 = digitalRead(button_1); // reading from button_1 and storing it in read_button_1
  read_button_2 = digitalRead(button_2); // reading from button_2 and storing it in read_button_2

  if (read_button_1 == HIGH) // using if else to
  {
    digitalWrite(signal_A, LOW);
    digitalWrite(signal_B, LOW);
  }
  else
  {
    if (read_button_2 == LOW)
    {
      run_mode(a, 50);
    }
    else
    {
      run_mode(r, -50);
    }
  }
}
