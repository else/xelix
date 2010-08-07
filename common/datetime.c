#include <common/datetime.h>

int date(char dateStr)
{
  int whatDate;
  int nowDate;
  switch(dateStr)
  {
    case 's':
      whatDate = 0;
      break;
    case 'm':
      whatDate = 0x02;
      break;
    case 'h':
      whatDate = 0x04;
      break;
    case 'd':
      whatDate = 0x07;
      break;
    case 'M':
      whatDate = 0x08;
      break;
    case 'y':
      whatDate = 0x09;
      break;
  }
  outb(0x70, whatDate);
  nowDate = inb(0x71);
  switch(dateStr)
  {
    case 's':
    case 'm':
    case 'h':    
    case 'y':
      nowDate = (nowDate & 0xf) + 10 * (nowDate >> 4);
  }
  if(dateStr == 'y') nowDate += 2000;
  return nowDate;
}

char* monthToString(int month, int shortVersion)
{
  char* monthString;
  char* longNames[12];
  
  longNames[0] = "January";
  longNames[1] = "February";
  longNames[2] = "March";
  longNames[3] = "April";
  longNames[4] = "May";
  longNames[5] = "June";
  longNames[6] = "July";
  longNames[7] = "August";
  longNames[8] = "September";
  longNames[9] = "October";
  longNames[10] = "November";
  longNames[11] = "December";
  
  --month;
  monthString = longNames[month];
  if(shortVersion) monthString = substr(monthString, 0, 3);
  return monthString;
}

void registerTick()
{
//dummy
}

void sleep(time_t timeout)
{
  timeout = timeout * 50; //PIT is running @ 50Hz
  int startTick = pit_getTickNum();
  while(1)
  {
    //display_printDec(pit_getTickNum() / 50);
    if(pit_getTickNum() > startTick + timeout) break;
  }
}
