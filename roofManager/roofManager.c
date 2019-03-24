/*
 *
 *  roofManager.c: Roof Manager for the onion omega uses roofServer
 *                 
 */

#include <roofServer.h>
#include <cmdParser.h>

int main (int argc, char **argv)
{
    unsigned char mycmd;    
    server_setup();
   
    while (1) 
    {   // forever
        server_run(&mycmd);

        // This where cmd is executed add code here for desired action
        // write the string to file
        if (cmdParser(mycmd, fd_log) != 1)
            error ("write: logfile");

    }
}