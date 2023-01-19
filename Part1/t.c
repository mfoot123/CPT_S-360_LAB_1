#include <stdio.h>

typedef unsigned int u32;

char *ctable = "0123456789ABCDEF";
int  BASE = 10;

void rpu(u32 x)
{
        char c;
        if (x) {
                c = ctable[x % BASE];
                rpu(x / BASE);
                putchar(c);
        }
}

// prints an unsigned (positive) integer
int printu(u32 x)
{
   (x==0)? putchar('0') : rpu(x);
   putchar(' ');
}

// uses putchar to display a char to display
void prints(char *s)
{
   // identify out starting index
   //int index = 0;
   // make sure we dont keep going past NULL
   while(*s)
   {
      // loop through our character array
      // printing each character to the screen
      putchar(*s);
      // increase out index by one
      s++;
   }
}

// prints x in hex
int  printx(u32 x)
{
   // hex is base 16 NOT base 10
   // so lets change out BASE variable
   BASE = 16;
   
   // first lets check if x is negative
   if(x < 0)
   {
      // since we know its a negative, lets print a -
      putchar('-');
      // next lets convert it to positive
      // this will allow us to call print u
      x = -1 * x;
   }
   // now we need to print 0 and x
   // per the requiremements in the instructions
   putchar('0');
   putchar('x');
   // now we can call printu to do our zero check and call rpu
   printu(x);
}

// prints an integer
void printd(int x)
{
   BASE = 10;
   // first we need to determine if the integer is negative
   if (x < 0) 
   {
      // if the number is negative we need
      // to print a - in front of it
      putchar('-');
      // lets x positive now
      x = -1 * x;
   }
   // we now know x is not negative, but dont know two things:
   // 1) if x = 0
   // OR 2) if x > 0
   // printu will check for us so call printu
   printu(x);
}

int myprintf(char *fmt, ...)
{
   // set our current pointer
   char *cp = fmt;
   // set our initial pointer to the address of fmt + 1

   /*
                   char *cp -> "...%c ..%s ..%u .. %d\n"
   HIGH               |                                              LOW 
 --------------------------- --|------------------------------------------
   | d | c | b | a | fmt |retPC| ebp | locals
 ----------------|----------------|---------------------------------------
                 |                | 
            int *ip            CPU.ebp
   */

  // if we just set ip = to the address of fmt it will not be pointing
  // to the first thing we need to have printed
   int *ip = &fmt + 1; 

   // run until CP is null
   while(*cp != '\0')
   {
        // check our string to see if we have a percent sign
        // this will help us determine which x to print
        if(*cp == '%')
        {
            // move to the next index of cp
            // this will be the letter that determines
            // what print function we use
            cp++;
            if (*cp == 'c')
            {
               // if its a character use put char
               putchar(*ip);
               putchar('\r');
               putchar('\n');
            }

            else if (*cp == 's')
            {
               // if its an s print the string
               prints((char*)(*ip));
               putchar('\r');
               putchar('\n');
            }

            else if(*cp == 'u')
            {
               // if u print an unsigned integer
               printu(*ip);
               putchar('\r');
               putchar('\n');
            }

            else if (*cp == 'x')
            {
               // if x print in hex
               printx(*ip);
               putchar('\r');
               putchar('\n');
            }

            else if (*cp == 'd')
            {
               // if d print an integer
               printd(*ip);
               putchar('\r');
               putchar('\n');
            }

            // increase the initial pointer
            ip++;
        }
        // if it is not a % but instead a new line
        // print a new line then move the character back to the left
        else if (*cp == '\n')
        {
            // if our character is a new line,
            // print a new line to the screen
            putchar('\n');
            // and a extra \r per the instructions
            putchar('\r');
        }
        // if its anything else just print it
        else 
        {
            // we know our character is not \n or %
            // therefore we can safely print it, no extra check needed
            putchar(*cp);
        }
        // move our index by one
        cp++;
    }
}

/* int  printx(u32 x) which print x in HEX   (prefixed with 0x ) */
/* int  printd(int x) which print an integer (x may be negative!!!) */

int main(int argc, char *argv[ ], char *env[ ])
{
// test case
/*WARNING: compile and print using WSL if you are using a 64 bit OS, will cause errors if run through vscode*/
myprintf("char = %c string = %s dec %u hex = %x neg = %d\n", 'A', "Test", 100, 100, -100);
}
