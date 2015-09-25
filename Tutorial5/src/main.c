#include <genesis.h>
#include <map.h>
#include <pal.h>
#include <tiles.h>

int main()
{
    Z80_init();
    VDP_setPlanSize(64,64);
    VDP_setScreenHeight240();
    VDP_setScreenWidth320();
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);

    VDP_setPalette(PAL1, (const u16 *)palDat);
    VDP_loadTileData((const u32 *)tileDat, TILE_USERINDEX, 191, 1);

    VDP_setTileMapData(VDP_PLAN_A, (const u16 *)mapDat, TILE_USERINDEX, (40*16), 1);

    VDP_waitVSync();
    while(TRUE)
    {


        VDP_waitVSync();
    }
}
