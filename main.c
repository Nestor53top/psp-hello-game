#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psppower.h>
#include <pspgu.h>
#include <psptypes.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("Hello PSP Game", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define BUF_WIDTH 512
#define SCR_WIDTH 480
#define SCR_HEIGHT 272

static unsigned int __attribute__((aligned(16))) list[262144];
static unsigned int *fbp0 = (void *)0;
static unsigned int *zbp = (void *)0;

int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int CallbackThread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int SetupCallbacks(void) {
    int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, NULL);
    return thid;
}

void drawRect(int x, int y, int w, int h, unsigned int color) {
    struct Vertex {
        unsigned int color;
        short x, y, z;
    } __attribute__((packed));

    struct Vertex *vertices = sceGuGetMemory(sizeof(struct Vertex) * 2);

    vertices[0].color = color;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;

    vertices[1].color = color;
    vertices[1].x = x + w;
    vertices[1].y = y + h;
    vertices[1].z = 0;

    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, NULL, vertices);
}

int main(void) {
    SetupCallbacks();

    sceDebugScreenInit();
    sceDebugScreenSetBackColor(0xFF000000);
    sceDebugScreenSetTextColor(0xFFFFFFFF);
    sceDebugScreenClear();

    sceDebugScreenSetXY(5, 3);
    sceDebugScreenPrintf("=== Hello PSP Game ===");
    sceDebugScreenSetXY(5, 5);
    sceDebugScreenPrintf("A simple PSP homebrew");
    sceDebugScreenSetXY(5, 7);
    sceDebugScreenPrintf("Built with PSPSDK");
    sceDebugScreenSetXY(5, 10);
    sceDebugScreenPrintf("Press X to exit");
    sceDebugScreenSetXY(5, 13);
    sceDebugScreenPrintf("Press O to see colors!");

    sceDisplaySetMode(0, SCR_WIDTH, SCR_HEIGHT);
    sceDisplayWaitVblankStart();

    SceCtrlData pad;
    int showColors = 0;
    int running = 1;

    while (running) {
        sceCtrlReadBufferPositive(&pad, 1);

        if (pad.Buttons & PSP_CTRL_CROSS) {
            running = 0;
        }

        if (pad.Buttons & PSP_CTRL_CIRCLE) {
            showColors = !showColors;
        }

        sceDebugScreenClear();
        sceDebugScreenSetXY(5, 3);
        sceDebugScreenPrintf("=== Hello PSP Game ===");
        sceDebugScreenSetXY(5, 5);
        sceDebugScreenPrintf("A simple PSP homebrew");
        sceDebugScreenSetXY(5, 7);
        sceDebugScreenPrintf("Built with PSPSDK");
        sceDebugScreenSetXY(5, 10);
        sceDebugScreenPrintf("Press X to exit");
        sceDebugScreenSetXY(5, 13);
        sceDebugScreenPrintf("Press O: %s", showColors ? "COLORS ON" : "COLORS OFF");

        if (showColors) {
            sceGuStart(GU_DIRECT, list);
            sceGuDrawBuffer(GU_PSM_8888, fbp0, BUF_WIDTH);
            sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, (void *)0x88000, BUF_WIDTH);
            sceGuDepthBuffer((void *)0x110000, BUF_WIDTH);
            sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

            drawRect(20, 150, 80, 60, 0xFF0000FF);   // Red
            drawRect(120, 150, 80, 60, 0xFF00FF00);   // Green
            drawRect(220, 150, 80, 60, 0xFFFF0000);   // Blue
            drawRect(320, 150, 80, 60, 0xFF00FFFF);   // Yellow
            drawRect(420, 150, 60, 60, 0xFFFF00FF);   // Cyan

            sceGuFinish();
            sceGuSync(0, 0);
            sceDisplayWaitVblankStart();
            sceGuDisplay(GU_TRUE);
        }

        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
