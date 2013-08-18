#include <allegro.h>

int set_graphic_mode(int depth)
{
    int retVal = 0;
    set_color_depth(depth);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) >= 0)
    {
        retVal = 1;
    }
    return retVal;
}

int main(int argc, char **argv)
{
    // initialize allegro
    allegro_init();
    
    // init keyboard
    install_keyboard();
    
    // set graphic mode and exit if set graphic mode failed
    if (!set_graphic_mode(16))
    {
        allegro_message("Error: Unable to set graphic mode");
        exit(0);
    }
    
    // load default allegro logo
    BITMAP* logo = load_tga("../allegro.tga", NULL);
    if (logo == NULL) 
    {
        allegro_message("Error: Unable to load logo");
        exit(0);
    }
    
    // aquire screen and dislpay loaded logo
    acquire_screen();
    clear(screen);
    blit(logo, screen, 
         0 , 0,
         (SCREEN_W - logo->w)/2,
         (SCREEN_H - logo->h)/2,
         logo->w, logo->h);
    
    // release screen and wait for key event
    release_screen();
    while(!keypressed());
    return 0;
} END_OF_MAIN()
