#include <genesis.h>
#include <z80Test.h>

u16 psgTone;
u16 isPlaying;

//prototypes
void myJoyHandler( u16 joy, u16 changed, u16 state);
void playTone(u16 tone, u16 stop);

int main()
{
    //load Z80 test driver, reset z80 when done
    Z80_init();
    Z80_upload(0x0000, z80Test, 0x241, 1);

    //init gamepad
    JOY_init();
    JOY_setEventHandler( &myJoyHandler );

    //small greeting
    VDP_drawText("db Z80 custom driver test", 1, 10);

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

void playTone(u16 tone, u16 stop)
{
    Z80_requestBus(1);

    if (stop)
    {
        //issue command to stop tone
        Z80_write(0x0100, 0x00);

    }else
    {
        //write command to play tone
        Z80_write(0x0100, 0x80);
        //write tone value, big endian
        Z80_write(0x0102, (u8)(psgTone>>8));
        Z80_write(0x0103, (u8)(psgTone));
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
        }
        else if (state & BUTTON_DOWN)
        {
            psgTone--;
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
