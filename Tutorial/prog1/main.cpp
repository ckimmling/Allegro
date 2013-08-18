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
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 1;
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
         x,
         y,
         logo->w, logo->h);
    
    // release screen and wait for key event
    release_screen();
    
    BITMAP* doubleBuffer = create_bitmap(SCREEN_W, SCREEN_H);
    while(!keypressed())
    {
        // check if position x reach left border
        if (x + dx < 0)
        {
            // change direction of logo
            dx *= -1;
        }
        // check if position x reach rigth border
        else if (x + logo->w >= SCREEN_W)
        {
            // change direction of logo
            dx *= -1;
        }
        
        // check if position y reach top border
        if (y + dy < 0)
        {
            dy *= -1;
        }
        // check if position y reach bottom border
        else if (y + logo->h >= SCREEN_H)
        {
            dy *= -1;
        }
        x+=dx;
        y+=dy;
        
        // first load logo into a second buffer
        acquire_bitmap(doubleBuffer);
        clear(doubleBuffer);
        blit(logo, doubleBuffer, 0 , 0, x, y, logo->w, logo->h);
        release_bitmap(doubleBuffer);
        
        // draw logo on next calculated position
        acquire_screen();
        blit(doubleBuffer, screen, 0 , 0, 0, 0, SCREEN_W, SCREEN_H);
        release_screen();
    }
    return 0;
} END_OF_MAIN()
