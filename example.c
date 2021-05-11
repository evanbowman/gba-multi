#include "multi.h"
#include </opt/devkitpro/libtonc/include/tonc_tte.h>
#include </opt/devkitpro/libtonc/include/tonc_video.h>
#include </opt/devkitpro/libtonc/include/tonc_irq.h>


static void text_init()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    tte_init_se(
                0,
                BG_CBB(0)|BG_SBB(31),
                0,
                CLR_YELLOW,
                14,
                NULL,
                NULL);

    pal_bg_bank[1][15]= CLR_RED;
    pal_bg_bank[2][15]= CLR_GREEN;
    pal_bg_bank[3][15]= CLR_BLUE;
    pal_bg_bank[4][15]= CLR_WHITE;
    pal_bg_bank[5][15]= CLR_MAG;
    pal_bg_bank[4][14]= CLR_GRAY;
}


static void text_put(const char* str)
{
    tte_write(str);
}


static void multi_connect_callback(multi_PlayerId player, int connected)
{
    switch (player) {
    case multi_PlayerId_host:
        if (connected) {
            text_put("host connected\n");
        } else {
            text_put("host disconnected\n");
        }
        break;

    case multi_PlayerId_p1:
        if (connected) {
            text_put("p1 connected\n");
        } else {
            text_put("p1 disconnected\n");
        }
        break;

    case multi_PlayerId_p2:
        if (connected) {
            text_put("p2 connected\n");
        } else {
            text_put("p2 disconnected\n");
        }
        break;

    case multi_PlayerId_p3:
        if (connected) {
            text_put("p3 connected\n");
        } else {
            text_put("p3 disconnected\n");
        }
        break;
    }
}


int main()
{
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);

    text_init();

    text_put("multiplayer test...\n");


    static volatile unsigned int* keys = (volatile unsigned int*)0x04000130;

    while (!(~(*keys) & 1)) { // wait for player to press A button
        // ...
    }

    multi_Status connect_result = multi_connect(multi_connect_callback);

    if (connect_result == multi_Status_failure) {
        return 1;
    }
}
