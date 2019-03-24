#include <string.h>
#include "roofClient.h"
#include "roofCMD.h"

char buf [128];
unsigned char ucmd;

unsigned char getCmd(char* mybuf);

void setup()
{
  client_setup();
  printf ("Please type a command: ");
}

void loop()
{
  ucmd = getCmd(buf);
  client_push_cmd(ucmd);
  printf ("Please type a command: ");
}

int main(int argc, char* argv[])
{
  setup();
  while(fgets(buf, 126, stdin))
  {
    int length = strlen (buf);
	  if (buf [length - 1] == '\n')
	    buf [length - 1] = '\0';
    loop();
  }
  return 0;
}

unsigned char getCmd(char* mybuf)
{
  unsigned char mcmd;
  int length = strlen (mybuf);
  if( length > 0)
  {
    if( strncmp(mybuf, "open", length)==0 )
      mcmd = CMD_OPEN;
    else if ( strncmp(mybuf, "close", length)==0 )
      mcmd = CMD_CLOSE;
    else if ( strncmp(mybuf, "none", length)==0 )
      mcmd = CMD_NONE;
    else if ( strncmp(mybuf, "state", length)==0 )
      mcmd = CMD_STATE_CHECK;
    else 
      mcmd = CMD_UNKNOWN;
    
    return mcmd;
  }
}