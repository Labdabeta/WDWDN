#ifndef LAB_GUI_H
#define LAB_GUI_H 1.0 //Version

typedef unsigned int Colour;
typedef void *Surface;

void guiInit(int,int,const char*);
void guiQuit(void);

void guiFill(Colour);
void guiFlip(void);
void guiSleep(int);

Surface guiLoadSurface(const char*);
void guiCloseSurface(Surface);
void guiRenderSurface(Surface,int,int);//top-left specified

int main(int argc, char *argv[])
{
    LABMain();
}

#endif
