// ------------------------------------------------------------------------------------------------------------------------ //
// This Project is to make a Clock which shows the weather conditions of the surrounding area using Arduino //
// ------------------------------------------------------------------------------------------------------------------------ //
// Modules Used:
//         RTC DS3231: It is a Real Time Clock which is used to maintain the time even when the power supply if off
//         DHT11: A Temperature and Humidity Module to provide info on the surrounding weather conditions
//         Keypad Shield: It is used to display the info and the buttons to make changes to it
// ------------------------------------------------------------------------------------------------------------------------ //
// Wirings:
//         RTC DS3231:
//                    GND -> GND
//                    VCC -> 5V
//                    SDA -> A4
//                    SCL -> A5
//         DHT11:
//                    GND -> GND
//                    VCC -> 3V
//                    DATA -> D2
//         Keypad Shield:
//                    Fixes on top of the Arduino Board
// ------------------------------------------------------------------------------------------------------------------------ //
// Button Configuration:
//         Left:  Change Date and Time
//         Up:    Increase Counter
//         Right: Next Selection
// ------------------------------------------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------------------------------------------ //

#include <DS3231.h>
#include <ErriezLCDKeypadShield.h>
#include <SimpleDHT.h>
DS3231  rtc(SDA, SCL);
LCDKeypadShield shield;

String DOW, Date, Cur_Time;
const int pinDHT11 = 2;
byte temperature = 0;
byte humidity = 0;
int err = SimpleDHTErrSuccess;
SimpleDHT11 dht11(pinDHT11);
int d = 1, m = 1, y = 2000, day = 1, h = 0, mn = 0, menu = 0;

void setup() 
{
  Serial.begin(9600);
  rtc.begin();
  //  Initialise Date and Time for the first use then comment it back
  //  rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(12, 26, 0);     // Set the time to 12:00:00 (24hr format)
  //  rtc.setDate(22, 03, 2020);   // Set the date to January 1st, 2014
  shield.backlightOn();
  shield.clear(); 
}

void loop() 
{

  // ---------- Get Date & Time and Print ---------- //
  get_date_time();
  print_date_time();

  // ---------- Get Temperature & Humidity and Print ---------- //
  print_temp_hum();

  // ---------- Change Date & Time ---------- //
  if(shield.getButtons() == ButtonLeft)
    change_date();

  // ---------- Delay of 1s ---------- //
  delay(1000);
}

void get_date_time()
{
  //---------- Send Day-of-Week ---------- //
  DOW = String(rtc.getDOWStr()).substring(0, 3);

  // ---------- Send date ---------- //  
  Date = rtc.getDateStr();
  Date.replace(".", "/");

  // ---------- Send time ---------- //
  Cur_Time = rtc.getTimeStr();
  Cur_Time = Cur_Time.substring(0, 5); //Uncomment after all works
}

void print_date_time()
{

  // ---------- Set Cursor & Print Day of the Week ---------- //
  shield.setCursor(0, 0);
  shield.print(DOW);
  
  //   Serial.print(DOW); Serial.print(" "); // Testing on Serial Monitor

  // ---------- Set Cursor & Print Date ---------- //
  shield.setCursor(6, 0);
  shield.print(Date);
  //Serial.print(Date); Serial.print(" -- ");

  // ---------- Set Cursor & Print Time ---------- //  
  //Serial.println(Cur_Time);
  shield.setCursor(0, 1);
  shield.print(Cur_Time);  
}

void print_temp_hum()
{
  // ---------- Set Cursor & Print Temperature & Humidity ---------- //  
  shield.setCursor(8, 1);
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);
    return;
  } 

  shield.print(temperature); shield.print((char)223); shield.print("C "); // T °C
  shield.print(humidity); shield.println("%"); // H%

  //  Testing With RTC In-built temperature sensor
  //  Serial.print("Temperature (from RTC): "); Serial.print(rtc.getTemp()); 
  // Serial.println(" C");
}

void change_date()
{
  initialise_vars();
  while(true)
  {
    shield.clear();
    shield.setCursor(0, 0);
    switch(menu)
    {
      case 0:
        set_day();
        break;

      case 1:
        set_month();
        break;

      case 2:
        set_year();
        break;  

      case 3:
        set_date();
        break;

      case 4:
        set_hour();
        break;

      case 5:
        set_min();
        break;

      default:
        store();
        return;
        break;
    }
  }
}

void set_day()
{
  shield.print("Change Day:");
  shield.setCursor(0, 1);
  shield.print("Monday = 1: ");
  while(shield.getButtons() != ButtonLeft)
  {
    shield.setCursor(14, 1);
    shield.print(day);
    delay(500);
    if(shield.getButtons() == ButtonUp)
      ++day;
    else if(shield.getButtons() == ButtonRight)
    {
      menu++;
      return;
    }

    day = day % 8;
  }
}

void set_month()
{
  shield.print("Change Month:");
  shield.setCursor(0, 1);
  shield.print("January = 1: ");
  while(shield.getButtons() != ButtonLeft)
  {
    shield.setCursor(14, 1);
    shield.print(m);
    delay(500);
    if(shield.getButtons() == ButtonUp)
      ++m;
    else if(shield.getButtons() == ButtonRight)
    {
      menu++;
      return;
    }

    if(m == 13)
    {
      m == 1;
      shield.setCursor(15, 1);
      shield.print(" ");
    }
  }
}

void set_year()
{
  shield.print("Change Year:");
  shield.setCursor(0, 1);
  shield.print("Year: ");
  while(shield.getButtons() != ButtonLeft)
  {
    shield.setCursor(12, 1);
    shield.print(y);
    delay(500);
    if(shield.getButtons() == ButtonUp)
      ++y;
    else if(shield.getButtons() == ButtonRight)
    {
      menu++;
      return;
    }

    if(y == 2050)
      y = 2000;
  }
}

void set_date()
{
  shield.print("Change Date:");
  shield.setCursor(0, 1);
  shield.print("Date: ");
  while(shield.getButtons() != ButtonLeft)
  {
    shield.setCursor(14, 1);
    shield.print(d);
    delay(500);
    if(shield.getButtons() == ButtonUp)
      ++d;
    else if(shield.getButtons() == ButtonRight)
    {
      menu++;
      return;
    }

    if(d > 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12))
    {
      d = 1;
      shield.setCursor(15, 1);
      shield.print(" ");
    }
    if(d > 30 && (m == 4 || m == 6 || m == 9 || m == 11))
    {
      d = 1;
      shield.setCursor(15, 1);
      shield.print(" ");
    }
    if(d > 28 && m == 2 && ((y%4 == 0) || (y%400 == 0)))
      d = 29;
      
    else if(d > 28 && m == 2)
    {
      d = 1;
      shield.setCursor(15, 1);
      shield.print(" ");
    }
  }
}

void set_hour()
{
  shield.print("Change Hour:");
  shield.setCursor(0, 1);
  shield.print("Hour: ");
  while(shield.getButtons() != ButtonLeft)
  {
    shield.setCursor(14, 1);
    shield.print(h);
    delay(500);
    if(shield.getButtons() == ButtonUp)
      ++h;
    else if(shield.getButtons() == ButtonRight)
    {
      menu++;
      return;
    }

    if(h == 24)
    {
      h = 0;
      shield.setCursor(15, 1);
      shield.print(" ");
    }
  }
}

void set_min()
{
  shield.print("Change Minute:");
  shield.setCursor(0, 1);
  shield.print("Minute: ");
  while(shield.getButtons() != ButtonLeft)
  {
    shield.setCursor(14, 1);
    shield.print(mn);
    delay(500);
    if(shield.getButtons() == ButtonUp)
      ++mn;
    else if(shield.getButtons() == ButtonRight)
    {
      menu++;
      return;
    }

    if(mn == 60)
    {
      mn = 0;
      shield.setCursor(15, 1);
      shield.print(" ");
    }    
  }
}

void store()
{
  switch(day)
  {
    case 1: rtc.setDOW(MONDAY); break;
    case 2: rtc.setDOW(TUESDAY); break;
    case 3: rtc.setDOW(WEDNESDAY); break;
    case 4: rtc.setDOW(THURSDAY); break;
    case 5: rtc.setDOW(FRIDAY); break;
    case 6: rtc.setDOW(SATURDAY); break;
    case 7: rtc.setDOW(SUNDAY); break;
  }

  rtc.setTime(h, mn, 0);
  rtc.setDate(d, m, y);
  setup();
}

void initialise_vars()
{
  menu = 0;
  get_date_time();
  // ---------- Initialise Day of the Week ---------- //
  if (DOW == "MONDAY")
    day = 1;
  else if (DOW == "TUESDAY")
    day = 2;
  else if (DOW == "WEDNESDAY")
    day = 3;
  else if (DOW == "THURSDAY")
    day = 4;
  else if (DOW == "FRIDAY")
    day = 5;
  else if (DOW == "SATURDAY")
    day = 6;
  else if(DOW == "SUNDAY")
    day = 7;

  // ---------- Initialise Date ---------- //
  d = Date.substring(0, 2).toInt();
  m = Date.substring(3, 5).toInt();
  y = Date.substring(6, 10).toInt();

  //  ---------- Initialise Time  ---------- //
  h = Cur_Time.substring(0, 2).toInt();
  mn = Cur_Time.substring(3, 5).toInt();
}
