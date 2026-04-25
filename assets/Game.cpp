#include <allegro.h>
#define W 800
#define H 600

int main(){
    allegro_init();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, W, H, 0, 0);

    BITMAP *ball = load_bitmap("ball.bmp", NULL);
    SAMPLE *hit  = load_sample("hit.wav");
    if(!ball) return 1;

    int p1=W/4, p2=3*W/4, s1=0, s2=0;
    int bx=W/2, by=H/2, dx=4, dy=-4;

    while(!key[KEY_ESC]){
        clear_to_color(screen, makecol(20,20,40));

        if(key[KEY_A]) p1-=6;
        if(key[KEY_D]) p1+=6;
        if(key[KEY_LEFT]) p2-=6;
        if(key[KEY_RIGHT]) p2+=6;

        if(p1<50) p1=50; if(p1>W-50) p1=W-50;
        if(p2<50) p2=50; if(p2>W-50) p2=W-50;

        rectfill(screen,p1-50,H-30,p1+50,H-10,makecol(0,255,0));
        rectfill(screen,p2-50,10,p2+50,30,makecol(0,0,255));

        draw_sprite(screen,ball,bx-ball->w/2,by-ball->h/2);

        bx+=dx; by+=dy;
        if(bx<=0||bx>=W) dx=-dx;

        if(by>=H-40 && bx>=p1-50 && bx<=p1+50){
            dy=-dy; dx=(bx-p1)/10;
            if(hit) play_sample(hit,255,128,1000,0);
        }

        if(by<=40 && bx>=p2-50 && bx<=p2+50){
            dy=-dy; dx=(bx-p2)/10;
            if(hit) play_sample(hit,255,128,1000,0);
        }

        if(by>H){ s2++; bx=W/2; by=H/2; dy=-4; }
        if(by<0){ s1++; bx=W/2; by=H/2; dy=4; }

        textprintf_ex(screen,font,10,H-50,makecol(0,255,0),-1,"P1:%d",s1);
        textprintf_ex(screen,font,10,20,makecol(0,0,255),-1,"P2:%d",s2);

        rest(16);
    }

    destroy_bitmap(ball);
    if(hit) destroy_sample(hit);
    return 0;
}
END_OF_MAIN();