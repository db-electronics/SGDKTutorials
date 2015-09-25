#include <genesis.h>
#include <map.h>
#include <pal.h>
#include <tiles.h>

int main()
{
    int i = 0;

    Z80_init();
    VDP_setPlanSize(64,64);
    VDP_setScreenHeight240();
    VDP_setScreenWidth320();
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);

    //VDP_setPalette(PAL0, (const u16 *)palDat);
    VDP_loadTileData((const u32 *)tileDat, 0, 191, 1);

    for (i=0;i<16;i++)
    {
       VDP_setTileMapData(VDP_PLAN_A, (const u16 *)(&mapDat[i*40*2]), i*64, 40, 1);
    }

    VDP_fadePalIn(PAL0,(const u16 *)palDat, 30, 0);

    i = 0;
    while(i<120)
    {
        i++;
        VDP_waitVSync();
    }
    VDP_fadePalOut(PAL0, 30, 0);

    while(TRUE)
    {
        VDP_waitVSync();
    }
}
