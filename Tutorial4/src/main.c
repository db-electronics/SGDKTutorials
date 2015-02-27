#include <genesis.h>
#include <z80Test.h>

#define PSGNOTEMIN      45
#define PSGNOTEMAX      116

u8 psgTone;
u16 isPlaying;

//prototypes
void myJoyHandler( u16 joy, u16 changed, u16 state);
void playTone(u8 tone, u16 stop);

int main()
{

    //lowest midi note on PSG is 45, max is 116
    psgTone = PSGNOTEMIN;

    //load Z80 test driver, reset z80 when done
    Z80_init();
    Z80_upload(0x0000, z80Test, 0x2000, 1);

    //init gamepad
    JOY_init();
    JOY_setEventHandler( &myJoyHandler );

    //small greeting
    VDP_drawText("db Z80 custom driver test", 1, 1);

    //main loop
    while(1)
    {

        if (isPlaying)
        {
            playTone(psgTone, 0);
        }else
        {
            playTone(0, 1);
        }

        VDP_waitVSync();
    }

    return 0;
}

void playTone(u8 tone, u16 stop)
{
    Z80_requestBus(1);

    if (stop)
    {
        //issue command to stop tone
        Z80_write(0x0100, 0x80);

    }else
    {
        //write command to play tone
        Z80_write(0x0100, psgTone);
    }

    Z80_releaseBus();
}

void myJoyHandler( u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_UP)
        {
            psgTone++;
            if (psgTone > PSGNOTEMAX)
            {
                psgTone = PSGNOTEMIN;
            }
        }
        else if (state & BUTTON_DOWN)
        {
            psgTone--;
            if (psgTone < PSGNOTEMIN)
            {
                psgTone = PSGNOTEMAX;
            }
        }
        else if (state & BUTTON_C)
        {
            isPlaying = 1;
        }
        else if (changed & BUTTON_UP)
        {

        }
        else if (changed & BUTTON_DOWN)
        {

        }
        else if (changed & BUTTON_C)
        {
            isPlaying = 0;
        }
    }
}
