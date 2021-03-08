#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

Display *dis;
int screen;
Window win;
GC gc;

XEvent event;
KeySym key;
char text[255];

unsigned long HEX(char v[8]) {
int r, g, b;
r = 16*(v[1] - 48 - (((v[1] - 48)>>4)*7)) + v[2] - 48 - (((v[2] - 48)>>4)*7);
g = 16*(v[3] - 48 - (((v[3] - 48)>>4)*7)) + v[4] - 48 - (((v[4] - 48)>>4)*7);
b = 16*(v[5] - 48 - (((v[5] - 48)>>4)*7)) + v[6] - 48 - (((v[6] - 48)>>4)*7);
return b + (g<<8) + (r<<16);
}

unsigned long RGB(int r, int g, int b) {
return b + (g<<8) + (r<<16);
}

void init_x() {
        dis=XOpenDisplay((char *)0);
        screen=DefaultScreen(dis);
        XSetWindowAttributes *attributes;

        win=XCreateWindow(dis,DefaultRootWindow(dis), 0, 0, 500, 500, 5, CopyFromParent, CopyFromParent, CopyFromParent, 0, attributes);
        XSetStandardProperties(dis,win,"PrimesOnHilbertCurve","hilbert",None,NULL,0,NULL);

        XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

        gc=XCreateGC(dis, win, 0,0);

        XSetBackground(dis,gc,HEX("#000000"));
        XSetForeground(dis,gc,HEX("#FFFFFF"));

        XClearWindow(dis, win);
        XMapRaised(dis, win);
}

void close_x() { // This doesn't get used. Not yet anyhow. If you're readin this you can delete it..
        XFreeGC(dis, gc);
        XDestroyWindow(dis,win);
        XCloseDisplay(dis);
        exit(1);
};

bool isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    } else {
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return 0;
            }
        }
        return 1;
    }
}

void move(int j,int pos[]){
pos[2]++;
if (isPrime(pos[2])) {
XSetForeground(dis,gc,HEX("#FF0000"));
XFillRectangle(dis,win,gc,pos[0]-3,pos[1]-3,7,7);
XSetForeground(dis,gc,HEX("#FFFFFF"));
};
if(j==1){
XDrawLine(dis,win,gc,pos[0],pos[1],pos[0],pos[1]-30);
pos[1]-=30;
};
if(j==2){
XDrawLine(dis,win,gc,pos[0],pos[1],pos[0]+30,pos[1]);
pos[0]+=30;
};
if(j==3){
XDrawLine(dis,win,gc,pos[0],pos[1],pos[0],pos[1]+30);
pos[1]+=30;
};
if(j==4){
XDrawLine(dis,win,gc,pos[0],pos[1],pos[0]-30,pos[1]);
pos[0]-=30;
};
};

void hilbert(int r, int d, int l, int u, int i, int pos[]){
if(i>0){
i--;
hilbert(d,r,u,l,i,pos);
move(r,pos);

hilbert(r,d,l,u,i,pos);
move(d,pos);

hilbert(r,d,l,u,i,pos);
move(l,pos);

hilbert(u,l,d,r,i,pos);
};
};

int main(){
int ev, n, pos[3];
ev = 0;
n = 7;
pos[0] = 10;
pos[1] = 10;
pos[2] = 0;
init_x();

while(1){
XNextEvent(dis,&event);
	if(event.type==KeyPress){
	break;
	};
};
XSetForeground(dis,gc,HEX("#000000"));
XFillRectangle(dis,win,gc,0,0,1000,1000);
XSetForeground(dis,gc,HEX("#FFFFFF"));

hilbert(2,3,4,1,n,pos);
while(1){
XNextEvent(dis,&event);
	if(event.type==KeyPress&&XLookupString(&event.xkey,text,255,&key,0)==1&&text[0]=='q'){
	break;
	};
	if(event.type==Expose) {
	ev+=1;
		if(ev%50==0){
		XSetForeground(dis,gc,HEX("#000000"));
		XFillRectangle(dis,win,gc,0,0,3000,3000);
		XSetForeground(dis,gc,HEX("#FFFFFF"));
		pos[0] = 10;
		pos[1] = 10;
		pos[2] = 0;
		hilbert(2,3,4,1,n,pos);
		};
	};
};

close_x();
return 0;
}
