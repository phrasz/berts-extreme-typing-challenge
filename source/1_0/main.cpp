#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_ttf.h>

//#include "common.c"

int main(int argc, const char *argv[])
{


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  Variables


    //const char *filename;
   // int num_adapters = al_get_num_video_adapters();
   // if(al_get_num_video_adapters()<=0){
       // al_set_new_display_flags(ALLEGRO_FULLSCREEN);
   // }
   // log_printf("%d adapters found...\n", num_adapters);
//while(1){}
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *membitmap;//, *bitmap;

   //BITMAP *background;
    ALLEGRO_BITMAP *allegmap, *powered, *PPlogo, *gimp, *presents, *menuscreen, *extreme, *typing; //loading
    ALLEGRO_BITMAP *bg, *opt1,*opt2, *opt3, *credits, *cred1, *cred2, *cred3, *cred4, *cred5, *cred6, *cred7, *cred8, *cred9; //Main menu and Credits
    ALLEGRO_BITMAP *diffea, *diffme, *diffha, *diffex, *diff1, *diff2, *diff3, *diff4;//difficulty

    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    bool redraw = true;
    //double zoom = 1;
    //double t0;
    //double t1;
    //bool done=0;
    //int x,y=0;
    float dx, dy;
    int gamestate=1;//This is the "case" statement for the while loop
    int fadespeed, globespeed=0;
    int startload=1; //The value to indicate to start and show loading screen;
    int round=0;
    int song_start=0;
    bool runthisgame=1; //keeps the while loop alive

    ALLEGRO_BITMAP *gbg, *notice, *black, *black_smlft, *black_smrght, *notice_blank, *winning;
    int pts,ptso,tot_time=0;
    int wpm,wordc,strikes,letterspressed,tot_keys;


    ALLEGRO_FONT *f, *f2;
char pear[]="   pear   ";
char kiwi[]="   kiwi   ";
char apple[]="   apple  ";
char grape[]="   grape  ";
char lemon[]="   lemon  ";
char banana[]="  banana  ";
char orange[]="  orange  ";
char strawberry[]="strawberry";
char buffer [33];
char reportletter[2];
//char buffer [33];


    //GS3
//    bool mainmenu, arrowdir; //if sub menus are up then no animation can be performed.
    int credcount=0;
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                 Allegro Bootup
//Return if allegro cannot start
    if (!al_init()) {
      printf("\nCould not init Allegro.\n");
      // abort_example("Could not init Allegro.\n");
    }
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  I/O Devices Installation
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//



//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  Front Creation

    f = al_load_ttf_font("data/Oran.ttf", 138, 0); //name, //int size, int flags ALLEGRO_TTF_NO_KERNING &_MONOCHROME
    if (!f) {
        //abort_example("Failed to load keys.ttf\n");
        return 1;
    }
    f2 = al_load_ttf_font("data/256bytes.ttf", 47, 0); //name, //int size, int flags ALLEGRO_TTF_NO_KERNING &_MONOCHROME
    if (!f2) {
        //abort_example("Failed to load keys.ttf\n");
        return 1;
    }
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//



//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  Display Creation

    display = al_create_display(1280, 720);
    if (!display) {
        printf("Error creating display\n");
       //abort_example("Error creating display\n");
    }

    al_set_window_title(display, "Bert's EXTREME Typing Challenge");
    al_set_window_position(display, 0, 0);
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//



//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                      BITMAP LAODING
    /* We load the bitmap into a memory bitmap, because creating a
     * display bitmap could fail if the bitmap is too big to fit into a
     * single texture.
     * FIXME: Or should A5 automatically created multiple display bitmaps?
     */
    //ALLEGRO_BITMAP *black, *powered, *PPlogo, *gimp, *presents, *menuscreen;

    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
    membitmap = al_load_bitmap("images/bg.png");
    if (!membitmap) {
       //abort_example("%s not found or failed to load\n");
    }
    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
    bg =al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);


    membitmap = al_load_bitmap("images/powered.bmp");
    if (!membitmap) {
      // abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    powered = al_clone_bitmap(membitmap); //#1
    al_destroy_bitmap(membitmap);


    membitmap = al_load_bitmap("images/PPlogo.tga");
    if (!membitmap) {
       //abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    PPlogo = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);


    membitmap = al_load_bitmap("images/gimp.bmp");
    if (!membitmap) {
       //abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    gimp = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);


    membitmap = al_load_bitmap("images/presents.bmp");
    if (!membitmap) {
       //abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    presents = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);



    membitmap = al_load_bitmap("images/menuscreen.png");
    if (!membitmap) {
       //abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    menuscreen = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);



    membitmap = al_load_bitmap("images/allegro.bmp");
    if (!membitmap) {
      // abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    allegmap = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);



        membitmap = al_load_bitmap("images/extreme.png");
    if (!membitmap) {
      // abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    extreme = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);

        membitmap = al_load_bitmap("images/typing.png");
    if (!membitmap) {
      // abort_example("%s not found or failed to load\n", filename);
    }
    else
        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );

    typing = al_clone_bitmap(membitmap);
    al_destroy_bitmap(membitmap);
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  Audio Function Variables

ALLEGRO_VOICE* voice;
ALLEGRO_MIXER* mixer;

  al_init_acodec_addon();

   if (!al_install_audio()) {
      //abort_example("Could not init sound!\n");
      return 1;
   }

   if (!al_reserve_samples(1)) {
      //abort_example("Could not set up voice and mixer.\n");
      return 1;
   }

    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    if (!voice) {
        //printf(stderr, "Could not create ALLEGRO_VOICE.\n"); return 1;
    }

    #ifndef BYPASS_MIXER
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    if (!mixer) {
        //printf(stderr, "Could not create ALLEGRO_MIXER.\n");
        return 1;
    }
    //printf(stderr, "Mixer created.\n");
    if (!al_attach_mixer_to_voice(mixer, voice)){
        //printf(stderr, "al_attach_mixer_to_voice failed.\n");
        return 1;
    }
    #endif
    ALLEGRO_AUDIO_STREAM *stream, *stream2;
    //bool playing = true;

    stream = al_load_audio_stream("music/01_loadsong.ogg", 4, 2048);//music/01_loadsong.ogg
    //al_attach_audio_stream_to_mixer(stream, mixer);
    stream2 = al_load_audio_stream("music/Page_null.ogg", 4, 2048);
    //al_attach_audio_stream_to_mixer(stream2, mixer);


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//

////-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
////                  Audio Function Variables
//ALLEGRO_SAMPLE *sample;
//ALLEGRO_SAMPLE_INSTANCE *sample_inst;
//
//   al_init_acodec_addon();
//
//   if (!al_install_audio()) {
//      //abort_example("Could not init sound!\n");
//      return 1;
//   }
//
//   if (!al_reserve_samples(1)) {
//      //abort_example("Could not set up voice and mixer.\n");
//      return 1;
//   }
//
//   sample = al_load_sample("music/01_loadsong.ogg");
//   if (!sample) {
//      //abort_example("Could not load sample from '%s'!\n", argv[1]);
//   }
//
//      /* Loop the sample. */
//   //sample_inst = al_create_sample_instance(sample);
//   sample_inst = al_create_sample_instance(sample);
//   al_set_sample_instance_playmode(sample_inst, ALLEGRO_PLAYMODE_LOOP);
//   al_attach_sample_instance_to_mixer(sample_inst, al_get_default_mixer());
//
////-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//



//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  Timer Function Variables
    timer = al_create_timer(1.0 / 60); //60 FPS
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//





///-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~///
///                  THE MAGIC WHILE LOOP
/// Here's the start of the execution of the game
       // x=al_get_display_width(display)/2;
       // y=al_get_display_height(display)/2;
        dx=640.0;
        dy=360.0;
        //printf("\nX=%i, Y=%i", x, y);
       //x=1280;
       //y=720;
    while (runthisgame==1){//runthisgame) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //User closes the window
            break;
        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                if(gamestate==1){//Game is loading...user wishes to skip start seqeunce
                    if(startload==1){
                        fadespeed=255; //set fade to out
                        startload=0; //stop the start sequence, and proceed to presents
                    }
                    //printf("\n\n\n\nESC PRESSED. QUITING STARTLOAD\n\n\n\n"); //Debugging
                }
                else if (gamestate==2){
                    runthisgame=0;
                }
                else if (gamestate==3){
                    if (round==1){
                        runthisgame=0;
                    }
                    else if (round==2){
                        credcount=99;
                        fadespeed=0;
                    }
                    else if (round ==6){//End credits...
                        credcount=99;
                        fadespeed=0;
                    }
                }
                else if (gamestate==4){
                    if(round>0)round=99;
                }

            }
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                //printf("\nSpace bar was Pressed.");
                if(gamestate==1){//Game is loading...user wishes to skip start seqeunce
                    if(startload==1){
                        fadespeed=255; //set fade to out
                        startload=0; //stop the start sequence, and proceed to presents
                    }
                    //printf("\n\n\n\nESC PRESSED. QUITING STARTLOAD\n\n\n\n"); //Debugging
                }
                else if(gamestate==2){
                   //if(startload==1){//reuse variable. One time load
                        round=2; //press on to main menu (round 1 blinks enter
                        fadespeed=-200; //set fade to out
                   // }
                }
                else if (gamestate==3){
                     if(round==6){//End credits...
                        credcount=99;
                        fadespeed=0;
                    }
                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_UP){
                //printf("\nLeft was Pressed.");
                if(gamestate==3){
                   if(round==1){//reuse variable. One time load
                       if (credcount==1){
                            credcount=3; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if (credcount==2){
                            credcount=1; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if(credcount==3){
                            credcount=2; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }

                   }
                   else if(round==2){//reuse variable. One time load
                       if (credcount==1){
                            credcount=4; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if (credcount==2){
                            credcount=1; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if(credcount==3){
                            credcount=2; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if(credcount==4){
                            credcount=3; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }

                   }

                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                //printf("\nLeft was Pressed.");
                if(gamestate==3){
                  if(round==1){//reuse variable. One time load
                       if (credcount==1){
                            credcount=2; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if (credcount==2){
                            credcount=3; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if(credcount==3){
                            credcount=1; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }

                   }

                   if(round==2){//reuse variable. One time load
                       if (credcount==1){
                            credcount=2; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if (credcount==2){
                            credcount=3; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if(credcount==3){
                            credcount=4; //finish current animations if needed
                            fadespeed=0; //set fade to out
                       }
                       else if(credcount==4){
                            credcount=1;//finish current animations if needed
                            fadespeed=0; //set fade to out
                       }

                   }
                }
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_A){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"A");
                        round=6; //Strike
                        credcount=2; //Wrong key
                        //strikes++;


                        if(wordc==0){//Prove it's not a strike
                            if(letterspressed==2){
                             round=5;
                             //strikes--;
                            }
                        }
                        else if(wordc==2){
                            if(letterspressed==0){
                             round=5;
                             //strikes--;
                            }
                        }
                        if(wordc==3){
                            if(letterspressed==2){
                            round=5;
                            //strikes--;
                            }
                        }
                        if(wordc==5){
                            if(letterspressed==1 || letterspressed==3 || letterspressed ==5){
                             round=5;
                             //strikes--;
                            }
                        }
                        if(wordc==6){
                            if(letterspressed==2){
                             round=5;
                             //strikes--;
                            }
                        }
                        if(wordc==7){
                            if(letterspressed==3){
                             round=5;
                             //strikes--;
                            }
                        }
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }


                }


            }

            if (event.keyboard.keycode == ALLEGRO_KEY_B){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"B");
                        round=6;
                        credcount=2;
                        if(wordc==5){if(letterspressed==0){round=5;}} //B -ANANA
                        if(wordc==7){if(letterspressed==5){round=5;}} //STRAW - B - ERRY
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_C){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"C");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_D){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"D");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_E){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"E");
                        round=6;
                        credcount=2;
                        if(wordc==0){if(letterspressed==1){round=5;}} //P -E- AR
                        if(wordc==2){if(letterspressed==4){round=5;}} /// APPL -E
                        if(wordc==3){if(letterspressed==4){round=5;}} ///GRAP -E
                        if(wordc==4){if(letterspressed==1){round=5;}} //L -E- MON
                        if(wordc==6){if(letterspressed==5){round=5;}} ///ORANG -E
                        if(wordc==7){if(letterspressed==6){round=5;}} //STRAWB -E- RRY
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_F){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"F");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_G){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"G");
                        round=6;
                        credcount=2;
                        if(wordc==3){if(letterspressed==0){round=5;}} //-G- RAPE
                        if(wordc==6){if(letterspressed==4){round=5;}} //ORAN -G -E
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_H){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"H");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_I){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"I");
                        round=6;
                        credcount=2;
                        if(wordc==1){if(letterspressed==1 || letterspressed ==3){round=5;}}///K -I- W -I-
                        //if(wordc==1){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_J){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"J");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_K){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"K");
                        round=6;
                        credcount=2;
                        if(wordc==1){if(letterspressed==0){round=5;}}//-K- IWI
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_L){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"L");
                        round=6;
                        credcount=2;
                        if(wordc==2){if(letterspressed==3){round=5;}}//APP -L- E
                        if(wordc==4){if(letterspressed==0){round=5;}}//-L- EMON
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_M){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"M");
                        round=6;
                        credcount=2;
                        if(wordc==4){if(letterspressed==2){round=5;}}//LE -M- ON
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_N){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"N");
                        round=6;
                        credcount=2;
                        if(wordc==4){if(letterspressed==4){round=5;}}///LEMO -N-
                        if(wordc==5){if(letterspressed==2 || letterspressed==4){round=5;}}//BA -N- A -N- A
                        if(wordc==6){if(letterspressed==3){round=5;}}//ORA -N- GE
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_O){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"O");
                        round=6;
                        credcount=2;
                        if(wordc==4){if(letterspressed==3){round=5;}}//LEM -O- N
                        if(wordc==6){if(letterspressed==0){round=5;}}//-O- RANGE
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_P){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"P");
                        round=6;
                        credcount=2;
                        if(wordc==0){if(letterspressed==0){round=5;}}//-P- EAR
                        if(wordc==2){if(letterspressed==1 || letterspressed==2){round=5;}} //A -P- -P- LE
                        if(wordc==3){if(letterspressed==3){round=5;}}//GRA -P- E
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_Q){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"Q");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_R){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"R");
                        round=6;
                        credcount=2;
                        if(wordc==0){if(letterspressed==3){round=5;}}///PEA -R-
                        if(wordc==3){if(letterspressed==1){round=5;}}//G -R- APE
                        if(wordc==6){if(letterspressed==1){round=5;}}//O -R- ANGE
                        if(wordc==7){if(letterspressed==2 ||letterspressed==7 ||letterspressed==8){round=5;}} //ST -R- AWBE -R- -R- Y
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_S){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"S");
                        round=6;
                        credcount=2;
                        if(wordc==7){if(letterspressed==0){round=5;}}//-S- TRAWBERRY
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_T){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"T");
                        round=6;
                        credcount=2;
                        if(wordc==7){if(letterspressed==1){round=5;}} //S -T- RAWBERRY
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_U){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"U");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_V){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"V");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_W){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"W");
                        round=6;
                        credcount=2;
                        if(wordc==1){if(letterspressed==2){round=5;}}//KI -W- I
                        if(wordc==7){if(letterspressed==4){round=5;}}//STRA -W- BERRY
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_X){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"X");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_Y){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"Y");
                        round=6;
                        credcount=2;
                        if(wordc==7){if(letterspressed==9){round=5;}}///STRAWBERR -Y-
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }if (event.keyboard.keycode == ALLEGRO_KEY_Z){
                if(gamestate==4){ //game is playing
                    if(round ==5){
                        strcpy(reportletter,"Z");
                        round=6;
                        credcount=2;
                        //if(wordc==0){if(letterspressed==0){round=5;}}
                        if(round==6){ptso=-2500;strikes++;}
                        letterspressed++; //indicate a key change
                    }
                }
            }


                //done=0;
        }


        if(event.type == ALLEGRO_EVENT_KEY_UP){

            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                //printf("\nEnter was Pressed.");
                if(gamestate==1){//Game is loading...user wishes to skip start seqeunce
                    if(startload==1){
                        fadespeed=255; //set fade to out
                        startload=0; //stop the start sequence, and proceed to presents
                    }
                    //printf("\n\n\n\nESC PRESSED. QUITING STARTLOAD\n\n\n\n"); //Debugging
                }

                else if(gamestate==2){
                   //if(startload==1){//reuse variable. One time load
                        round=2; //press on to main menu (round 1 blinks enter
                        fadespeed=-75; //set fade to out
                   // }
                }

                else if(gamestate==3){
                    if(round==1){
                        if(credcount==1){
                            round=2; //Difficulty Select
                            fadespeed=-750; //transistion audio delay...
                            credcount=0;
                            //al_stop_sample_instance(sample_inst);
                            //al_set_sample(sample_inst, al_load_sample("music/07_fruity.ogg"));
                            //al_play_sample_instance(sample_inst);
                        }

                        else if(credcount==2){//Start credits...
                            round=6;
                            fadespeed=-600; //transistion audio delay...
                            credcount=0;
                            //al_stop_sample_instance(sample_inst);
                            //al_set_sample(sample_inst, al_load_sample("music/08_pushups.ogg"));
                           // al_play_sample_instance(sample_inst);

                        }
                        else if(credcount==3){
                            runthisgame=0;
                        }

                    }

                    else if(round==2){ //Difficulty select
                        if(credcount==1){//Easy
                            wpm=10;
                        }
                        if(credcount==2){//Med
                             wpm=5;
                        }
                        if(credcount==3){//Hard
                             wpm=3;
                        }
                        if(credcount==4){//EXT
                             wpm=1;
                        }

                        gamestate=4;//start game
                        round=0;
                        fadespeed=-200;
                        credcount=0;
                       // al_stop_sample_instance(sample_inst);
                        //al_set_sample(sample_inst, al_load_sample("music/09_gamestart.ogg"));
                        //al_play_sample_instance(sample_inst);
                    }

                    else if(round==6){ //End credits...
                        fadespeed=0;
                        credcount=99;
                    }
                }

                else if(gamestate==4){
                    if(round==2){ //standby round ... start the game.
                        round=3;

                    }
                    else if (round==6){
                        if (credcount==3){//GAME OVER
                        round =99;
                        }
                        else round=3;
                    }
                    else if(round==8){
                        round =99;
                    }


                }
            }
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
    //GAMESTATES:
        //Start Loading -1
        //Main Splash -2
        //Main Menu -3
        //Game Menus (Campagin -4, Arcade -5, Extras -6, Options -7)


        if(gamestate==1){//Start Loading -1
                //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
                //                  Start Screen
                //These Screens fade in and out to show the "basic" credits
                if (startload==0){ //Clean up from start sequence --- fade out regardless of animation



                if(round<=4){

                    if(fadespeed>255&&fadespeed<512){ //FADE OUT

                        //IF condition for each possible interupt:
                        if(round==1)al_draw_tinted_bitmap(powered,al_map_rgba_f(1*(fadespeed-256),1*(fadespeed-256),1*(fadespeed-256),(fadespeed-256)/255.0),(dx-288.0),(dy-48.0),0);
                        if(round==2)al_draw_tinted_bitmap(allegmap,al_map_rgba_f(1*(fadespeed-256),1*(fadespeed-256),1*(fadespeed-256),(fadespeed-256)/255.0),(dx-359.0),(dy-98.0),0);
                        if(round==3)al_draw_tinted_bitmap(gimp,al_map_rgba_f(1*(fadespeed-256),1*(fadespeed-256),1*(fadespeed-256),(fadespeed-256)/255.0),(dx-347.0),(dy-303.0),0);
                        if(round==4)al_draw_tinted_bitmap(PPlogo,al_map_rgba_f(1*(fadespeed-256),1*(fadespeed-256),1*(fadespeed-256),(fadespeed-256)/255.0),0,0,0); //full screen image
                        al_flip_display();
                    }

                    fadespeed+=12; //speed up total transition.
                    if(fadespeed>=512){
                        round=5; //Finish the current animation, then press on to the presents.
                        fadespeed=0;
                    }
                }

                if(round==5){//Presents
                    if(fadespeed<256){ //FADE IN
                            if(song_start==1){ //stop into song, preload theme song
                               //al_stop_sample_instance(sample_inst);
                               //al_set_sample(sample_inst, al_load_sample("music/02_themesong.ogg"));
                               al_destroy_audio_stream(stream);
                               stream = al_load_audio_stream("music/02_themesong.ogg", 4, 2048);
                               //al_attach_audio_stream_to_mixer(stream, mixer);
                               song_start=0; //stop music
                            }
                            al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(presents,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-379.0),(dy-88.0),0);
                            al_flip_display();
                            fadespeed+=1;
                    }

                    if(fadespeed>255 && fadespeed<512){ //FADE OUT
                            al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                            al_draw_tinted_bitmap(presents,al_map_rgba_f(1*(fadespeed-255),1*(fadespeed-255),1*(fadespeed-255),(fadespeed-255)/255.0),(dx-379.0),(dy-88.0),0);//when values re set to 256 a fade "pop" occurs...
                            al_flip_display();
                            fadespeed+=16; //fade out twice as fast as in;
                    }


                }

                if(round==6){//MenuScreen
                    if(fadespeed<256){ //FADE IN
                            if(song_start==0){//Play Theme Song
                               //al_play_sample_instance(sample_inst);
                               //al_destroy_audio_stream(stream);
                               //stream = al_load_audio_stream("music/02_themesong.ogg", 4, 2048);
                               al_attach_audio_stream_to_mixer(stream, mixer);
                               song_start=1; //start music
                            }

                            al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(menuscreen,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),0,0,0);
                            al_flip_display();
                            fadespeed+=32;
                    }
                    if(fadespeed>=256)fadespeed=512;//If the animation is done, set to condition for round 7

                }


                    if (fadespeed>=512){
                        round++;
                        fadespeed=0;
                        if(round==7){ //End of intro sequence...remove gfx
                            al_destroy_bitmap(powered);
                            al_destroy_bitmap(PPlogo);
                            al_destroy_bitmap(gimp);
                            al_destroy_bitmap(allegmap);
                            gamestate=2; round=0; fadespeed=0;
                        }
                        ///KILL MUSIC
                    } //Done with load switch to main screen presentation

                    //fadespeed+=11; //speed up total transition.
                }

                if (startload==1){ //THIS LOOP IS THE STARTING SCREEN SEQUENCE
                    //printf("\nLoop #%i!", fadespeed); //Debugging
                    if(song_start==0){
                           //al_play_sample_instance(sample_inst);
                           //stream = al_load_audio_stream("music/00_DADReader.ogg", 4, 2048);
                           al_attach_audio_stream_to_mixer(stream, mixer);
                           song_start=1;
                    }
                    if(round==1){ //Powered by
                       if(fadespeed<256){ //FADE IN
                            al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(powered,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-288.0),(dy-48.0),0);
                            al_flip_display();
                            fadespeed+=2;
                      }

                        if(fadespeed>255 && fadespeed<512){ //FADE OUT
                            al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                            al_draw_tinted_bitmap(powered,al_map_rgba_f(1*(fadespeed-255),1*(fadespeed-255),1*(fadespeed-255),(fadespeed-255)/255.0),(dx-288.0),(dy-48.0),0);//when values re set to 256 a fade "pop" occurs...
                            al_flip_display();
                            fadespeed+=3; //fade out twice as fast as in;
                        }
                    }

                    if(round==2){ //Allegro
                       if(fadespeed<256){ //FADE IN
                            al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(allegmap,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-359.0),(dy-98.0),0);
                            al_flip_display();
                            fadespeed+=2;
                      }

                        if(fadespeed>255 && fadespeed<512){ //FADE OUT
                            al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                            al_draw_tinted_bitmap(allegmap,al_map_rgba_f(1*(fadespeed-255),1*(fadespeed-255),1*(fadespeed-255),(fadespeed-255)/255.0),(dx-359.0),(dy-98.0),0);//when values re set to 256 a fade "pop" occurs...
                            al_flip_display();
                            fadespeed+=3;
                        }
                    }


                    if(round==3){ //gimp
                       if(fadespeed<256){ //FADE IN
                            al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(gimp,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-347.0),(dy-303.0),0);
                            al_flip_display();
                            fadespeed+=2;
                      }

                        if(fadespeed>255 && fadespeed<512){ //FADE OUT
                            al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                            al_draw_tinted_bitmap(gimp,al_map_rgba_f(1*(fadespeed-255),1*(fadespeed-255),1*(fadespeed-255),(fadespeed-255)/255.0),(dx-347.0),(dy-303.0),0);//when values re set to 256 a fade "pop" occurs...
                            al_flip_display();
                            fadespeed+=3;
                        }
                    }


                    if(round==4){ //PPlogo
                       if(fadespeed<256){ //FADE IN
                            al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(PPlogo,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),0,0,0);
                            al_flip_display();
                            fadespeed+=2;
                      }

                        if(fadespeed>255 && fadespeed<512){ //FADE OUT
                            al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                            al_draw_tinted_bitmap(PPlogo,al_map_rgba_f(1*(fadespeed-255),1*(fadespeed-255),1*(fadespeed-255),(fadespeed-255)/255.0),0,0,0);//when values re set to 256 a fade "pop" occurs...
                            al_flip_display();
                            fadespeed+=3;
                        }
                    }

                    if(fadespeed>=512){//round completed increment...
                        fadespeed=0;
                        round++;
                        if(round>4) startload=0;//The fourth round is completed. Load the presents and menu splash
                    }

                }

                //                  Start Screen END
                //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
        }

        if(gamestate==2){//Main Splash -2
            if(round==0){

                fadespeed+=2;

                if(fadespeed>=256){
                    fadespeed=0;
                    globespeed=0;
                    round++;
                }
            }
            if(round==1){

                    if(fadespeed<128 &&globespeed==0){ //FADE IN
                            //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(extreme,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),0,0,0);
                            al_flip_display();

                      }

                    if(fadespeed<128&&globespeed==1){ //FADE IN
                            //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                            al_draw_tinted_bitmap(typing,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),0,0,0);
                            al_flip_display();
                           // fadespeed+=2;
                      }
                fadespeed+=2;

                if(fadespeed>=256&&globespeed<2){
                    fadespeed=0;
                    globespeed++;
                    //round++;
                }
            }

            if(round==2){//clean up stuff
                    if(song_start==1){ //stop into song, preload theme song
                        //al_stop_sample_instance(sample_inst);
                        //al_set_sample(sample_inst, al_load_sample("music/03_transistion.ogg"));
                        //al_play_sample_instance(sample_inst);
                        al_destroy_audio_stream(stream);
                        stream = al_load_audio_stream("music/03_transistion.ogg", 4, 2048);
                        al_attach_audio_stream_to_mixer(stream, mixer);
                        song_start=0; //start music
                    }

                    if(fadespeed>255&&fadespeed<512){ //FADE OUT
                        al_draw_tinted_bitmap(menuscreen,al_map_rgba_f(1*(fadespeed-256),1*(fadespeed-256),1*(fadespeed-256),(fadespeed-256)/255.0),0,0,0); //full screen image
                        al_flip_display();
                    }

                    fadespeed+=2; //speed up total transition.
                    if(fadespeed>=512){
                        gamestate=3;//Finish the current animation, then press on to the presents.
                        fadespeed=0;
                        //startload=1;
                        round=0; //first fade in
                        al_destroy_bitmap(extreme);
                        al_destroy_bitmap(typing);
                    }
            }
        }

///---------------------------------------------------------///
///                 Gamestate 3 vars
///

        if(gamestate==3){
                    if(round ==0){ //Load images



                           membitmap = al_load_bitmap("images/fruity.png");
                            if (!membitmap) {
                              // abort_example("%s not found or failed to load\n", filename);
                            }
                            else{
                                al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                            }
                            opt1 = al_clone_bitmap(membitmap); //#1
                            al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/questions.png");
                            if (!membitmap) {
                              // abort_example("%s not found or failed to load\n", filename);
                            }
                            else{
                                al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                            }
                            opt2 = al_clone_bitmap(membitmap); //#1
                            al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/exit.png");
                            if (!membitmap) {
                              // abort_example("%s not found or failed to load\n", filename);
                            }
                            else{
                                al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                            }
                            opt3 = al_clone_bitmap(membitmap); //#1
                            al_destroy_bitmap(membitmap);


                            al_destroy_bitmap(presents);
                            al_destroy_bitmap(menuscreen);


                            round=7;
                    }

                    if(round==1){ //Main Menu
                        if(fadespeed==0)al_draw_bitmap(bg,0,0,0);

                        if (credcount==1){ //fruity --opt1
                            if(fadespeed<128){ //FADE IN
                                //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                al_draw_tinted_bitmap(opt1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-191.0),(dy-109.0),0);
                                //al_draw_tinted_bitmap(belt1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-368.0),(dy-260.0),0);
                                //

                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(opt1,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-191.0),(dy-109.0),0);//when values re set to 256 a fade "pop" occurs...
                                    //al_flip_display();
                                    //(fadespeed-256)+=16; //fade out twice as fast as in;
                            }

                        }
                        else if (credcount==2){ //credits --opt2
                            if(fadespeed<128){ //FADE IN
                                //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                al_draw_tinted_bitmap(opt2,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-175.0),(dy+11.0),0);
                                //al_draw_tinted_bitmap(belt1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-368.0),(dy-260.0),0);
                                //

                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(opt2,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-175.0),(dy+11.0),0);//when values re set to 256 a fade "pop" occurs...
                                    //al_flip_display();
                                    //(fadespeed-256)+=16; //fade out twice as fast as in;
                            }

                        }
                        else if (credcount==3){ //fruity
                            if(fadespeed<128){ //FADE IN
                                //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                al_draw_tinted_bitmap(opt3,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-190.0),(dy+118.0),0);
                                //al_draw_tinted_bitmap(belt1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-368.0),(dy-260.0),0);
                                //

                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(opt3,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-190.0),(dy+118.0),0);//when values re set to 256 a fade "pop" occurs...
                                    //al_flip_display();
                                    //(fadespeed-256)+=16; //fade out twice as fast as in;
                            }

                        }

                           al_flip_display();
                           if(fadespeed>=512){
                               //round=2;
                               fadespeed=0;
                           }
                            fadespeed+=4;
                           //mainmenu=1;
                    }

                    if(round==2){//CREDIT SCREEN
                        if(credcount==0){
                            if(fadespeed>=0){ //add delay for audio transistion
                                if(song_start==1){//Play Theme Song
                                        //al_stop_sample_instance(sample_inst);
                                        //al_set_sample(sample_inst, al_load_sample("music/05_difficulty.ogg"));
                                        //al_play_sample_instance(sample_inst);
                                        al_destroy_audio_stream(stream);
                                        stream = al_load_audio_stream("music/05_difficulty.ogg", 4, 2048);
                                        al_attach_audio_stream_to_mixer(stream, mixer);
                                        song_start=0;
                                    }
                                membitmap = al_load_bitmap("images/diff1.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diff1 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/diff2.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diff2 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/diff3.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diff3 = al_clone_bitmap(membitmap); //#1

                                membitmap = al_load_bitmap("images/diff4.png");

                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diff4 = al_clone_bitmap(membitmap); //#1

                                membitmap = al_load_bitmap("images/diff_easy.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diffea = al_clone_bitmap(membitmap); //#1

                                membitmap = al_load_bitmap("images/diff_med.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diffme = al_clone_bitmap(membitmap); //#1

                                membitmap = al_load_bitmap("images/diff_hard.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diffha = al_clone_bitmap(membitmap); //#1

                                membitmap = al_load_bitmap("images/diff_ext.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                diffex = al_clone_bitmap(membitmap); //#1


                                al_draw_bitmap(diffea,0,0,0); //draw first screen for easy
                                al_flip_display();
                                fadespeed=1;
                                credcount++; //only load once

                                   //mainmenu=1;
                        } fadespeed++;


                        }
                     else {
                        if(fadespeed==0){ //Draw BG img
                            if(credcount==1){
                                al_draw_bitmap(diffea,0,0,0);
                            }
                            if(credcount==2){
                                al_draw_bitmap(diffme,0,0,0);
                            }
                            if(credcount==3){
                                al_draw_bitmap(diffha,0,0,0);
                            }
                            if(credcount==4){
                                al_draw_bitmap(diffex,0,0,0);
                            }
                        }
                    }

                        if (credcount==1){ //fruity --opt1
                            if(fadespeed<128){ //FADE IN
                                //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                al_draw_tinted_bitmap(diff1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-152.0),(dy-144.0),0);
                                //al_draw_tinted_bitmap(belt1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-368.0),(dy-260.0),0);
                                //

                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(diff1,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-152.0),(dy-144.0),0);//when values re set to 256 a fade "pop" occurs...
                                    //al_flip_display();
                                    //(fadespeed-256)+=16; //fade out twice as fast as in;
                            }

                        }
                        else if (credcount==2){ //credits --opt2
                            if(fadespeed<128){ //FADE IN
                                //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                al_draw_tinted_bitmap(diff2,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-152.0),(dy-63.0),0);
                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(diff2,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-152.0),(dy-63.0),0);//when values re set to 256 a fade "pop" occurs...

                            }

                        }
                        else if (credcount==3){ //fruity
                            if(fadespeed<128){ //FADE IN
                                al_draw_tinted_bitmap(diff3,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-152.0),(dy+26.0),0);
                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(diff3,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-152.0),(dy+26.0),0);//when values re set to 256 a fade "pop" occurs...

                            }

                        }
                        else if (credcount==4){ //fruity
                            if(fadespeed<128){ //FADE IN
                                //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                al_draw_tinted_bitmap(diff4,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-151.0),(dy+114.0),0);
                                //al_draw_tinted_bitmap(belt1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-368.0),(dy-260.0),0);
                                //

                           }
                           if((fadespeed-256)>128 && (fadespeed-256)<255){ //FADE OUT
                                   //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(diff4,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-151.0),(dy+114.0),0);//when values re set to 256 a fade "pop" occurs...
                                    //al_flip_display();
                                    //(fadespeed-256)+=16; //fade out twice as fast as in;
                            }

                        }

                        else if (credcount==99){ //DESTROY elements
                            al_destroy_bitmap(diff1);
                            al_destroy_bitmap(diff2);
                            al_destroy_bitmap(diff3);
                            al_destroy_bitmap(diff4);
                            al_destroy_bitmap(diffea);
                            al_destroy_bitmap(diffex);
                            al_destroy_bitmap(diffha);
                            al_destroy_bitmap(diffme);
                            round =7;
                        }

                        al_flip_display();
                           if(fadespeed>=512){
                               //round=2;
                               fadespeed=0;
                           }
                            fadespeed+=4;
                           //mainmenu=1;
                    }
                    if(round==6){ //CREDIT SCREEN
                        if(credcount==0){
                            if(fadespeed>=0){ //add delay for audio transistion
                                if(song_start==1){//Play Theme Song
//                                        al_stop_sample_instance(sample_inst);
//                                        al_set_sample(sample_inst, al_load_sample("music/06_credits.ogg"));
//                                        al_play_sample_instance(sample_inst);
                                        al_destroy_audio_stream(stream);
                                        stream = al_load_audio_stream("music/06_credits.ogg", 4, 2048);
                                        al_attach_audio_stream_to_mixer(stream, mixer);
                                        song_start=0;
                                    }
                                membitmap = al_load_bitmap("images/credits.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                credits = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/cred1.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred1 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);



                                membitmap = al_load_bitmap("images/cred2.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred2 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);



                                membitmap = al_load_bitmap("images/cred3.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred3 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);



                                membitmap = al_load_bitmap("images/cred4.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred4 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);



                                membitmap = al_load_bitmap("images/cred5.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred5 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);



                                membitmap = al_load_bitmap("images/cred6.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred6 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);



                                membitmap = al_load_bitmap("images/cred7.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred7 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/cred8.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred8 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);

                                membitmap = al_load_bitmap("images/cred9.png");
                                if (!membitmap) {
                                  // abort_example("%s not found or failed to load\n", filename);
                                }
                                else{
                                    al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                                }
                                cred9 = al_clone_bitmap(membitmap); //#1
                                al_destroy_bitmap(membitmap);




                                credcount++; //only load once
                                   //mainmenu=1;
                        } fadespeed++;
                        }


                        else if (credcount==1){
                            //if(fadespeed==0)

                            if(fadespeed<128){ //FADE IN
                                al_draw_tinted_bitmap(credits,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),0,0,0);
                                al_draw_tinted_bitmap(cred1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                            }
                           al_flip_display();
                        }


                        else if(credcount ==2){
                             // Always draw bg
        //                    if(fadespeed<256){ //FADE IN
        //                            //al_clear_to_color(al_map_rgb_f(0, 0, 0));
        //                            al_draw_tinted_bitmap(cred1,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
        //                            al_flip_display();
        //                            //fadespeed+=2;
        //                      }

                                if(fadespeed>255 && fadespeed<512){ //FADE OUT
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred1,al_map_rgba_f(1*(fadespeed-255),1*(fadespeed-255),1*(fadespeed-255),(fadespeed-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==3){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred2,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<768){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred2,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==4){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred3,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<768){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred3,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==5){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred4,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<768){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred4,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==6){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred5,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<768){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred5,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==7){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred6,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<768){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred6,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==8){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred7,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<608){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred7,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }
                        else if(credcount ==9){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred8,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<768){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred8,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }


                        else if(credcount ==10){

                                                 // Always draw bg
                            if(fadespeed<128){ //FADE IN -- correction to colors
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0));
                                    al_draw_tinted_bitmap(cred9,al_map_rgba_f(1*(255-fadespeed),1*(255-fadespeed),1*(255-fadespeed),(255-fadespeed)/255.0),(dx-245.0),(dy-130.0),0);
                                    al_flip_display();
                                    //fadespeed+=2;
                              }

                                if(fadespeed>512 && fadespeed<600){ //FADE OUT after 128 cycle pause
                                    //al_clear_to_color(al_map_rgb_f(0, 0, 0)); //exception handle fade glitch
                                    al_draw_tinted_bitmap(cred9,al_map_rgba_f(1*((fadespeed-256)-255),1*((fadespeed-256)-255),1*((fadespeed-256)-255),((fadespeed-256)-255)/255.0),(dx-245.0),(dy-130.0),0);//when values re set to 256 a fade "pop" occurs...
                                    al_flip_display();
                                    fadespeed+=1;
                                }

                        }


                        else if (credcount==99){ //DESTROY elements
                            al_destroy_bitmap(cred1);
                            al_destroy_bitmap(cred2);
                            al_destroy_bitmap(cred3);
                            al_destroy_bitmap(cred4);
                            al_destroy_bitmap(cred5);
                            al_destroy_bitmap(cred6);
                            al_destroy_bitmap(cred7);
                            al_destroy_bitmap(cred8);
                            al_destroy_bitmap(cred9);
                            al_destroy_bitmap(credits);
                            round =7;
                        }
                        fadespeed+=2;

                        if(fadespeed>=768){
                               //round=2;
                               fadespeed=0;
                               credcount++;
                        }

                    }

                    if(round==7){
//                        al_stop_sample_instance(sample_inst);
//                        al_set_sample(sample_inst, al_load_sample("music/04_menusong.ogg"));
//                        al_play_sample_instance(sample_inst);
                        al_destroy_audio_stream(stream);
                        stream = al_load_audio_stream("music/04_menusong.ogg", 4, 2048);
                        al_attach_audio_stream_to_mixer(stream, mixer);

                        fadespeed=0;
                        round=1;
                        credcount=1;
                        song_start =1;

                    }

                }

        if(gamestate==4){//Game Menu: Campagin -4
            if(round==0){
                if(fadespeed>=0){
                   // al_stop_sample_instance(sample_inst);
                    //al_set_sample(sample_inst, al_load_sample("music/10_game.ogg"));
                   // al_play_sample_instance(sample_inst);
                    al_destroy_audio_stream(stream);
                    stream = al_load_audio_stream("music/10_game.ogg", 4, 2048);
                    al_attach_audio_stream_to_mixer(stream, mixer);
                    membitmap = al_load_bitmap("images/gbg.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    gbg = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);

                    membitmap = al_load_bitmap("images/winning.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    winning = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);

                    membitmap = al_load_bitmap("images/notice.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    notice = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);

                    membitmap = al_load_bitmap("images/notice_blank.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    notice_blank = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);

                    membitmap = al_load_bitmap("images/black.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    black = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);

                    membitmap = al_load_bitmap("images/black_smlft.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    black_smlft = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);

                    membitmap = al_load_bitmap("images/black_smrght.png");
                    if (!membitmap) {
                    // abort_example("%s not found or failed to load\n", filename);
                    }
                    else{
                        al_convert_mask_to_alpha( membitmap, al_map_rgb(255,0,255) );
                    }
                    black_smrght = al_clone_bitmap(membitmap); //#1
                    al_destroy_bitmap(membitmap);


                    //al_draw_bitmap(diffea,0,0,0); //draw first screen for easy
                    //al_draw_bitmap(diffea,0,0,0); //draw first screen for easy
                    //al_flip_display();
                    //fadespeed=1;
                    credcount=0; //only load once


                    al_draw_bitmap(gbg,0,0,0); //draw first screen for easy
                    al_draw_bitmap(notice,0,0,0); //draw first screen for easy

                    al_flip_display();
                    fadespeed=1;
                    round++; //only load once


                //mainmenu=1;
                } fadespeed++;
            }

            else if(round==1){

                //LOAD GAME
//char pear[]="pear";
//char kiwi[]="kiwi";
//char apple[]="apple";
//char grape[]="grape";
//char lemon[]="lemon";
//char banana[]="banana";
//char orange[]="orange";
//char strawberry[]="strawberry";

///int pts,ptso,wpm,wordc,strikes=0;

            pts=0;
            ptso=0;
            wordc=0;
            strikes=0;
            credcount=0;
            round++;

            }

            else if (round==2){
            //standby ... wait for enter

                //else{ //DONE          }
                //credcount=0;
            }

            else if(round==3){ //transistion round
                pts+=ptso; //updates score
              //  if(credcount=0){
                al_draw_bitmap(gbg,0,0,0); //draw first screen (current values/words/strikes)

                if(wordc==0){ //no word, load pear
                    ptso=4000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, pear); //draw word
                    tot_keys=4; //Total amount of allowed key strokes
                   // strcpy(buffer, pear);
                }
                else if(wordc==1){ //kiwi
                    ptso=4000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, kiwi); //draw word
                    tot_keys=4; //Total amount of allowed key strokes
                    //strcpy(buffer, kiwi);
                }
                else if(wordc==2){ //apple
                    ptso=5000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, apple); //draw word
                    tot_keys=5; //Total amount of allowed key strokes
                    //strcpy(buffer, apple);
                }
                else if(wordc==3){ //grape
                    ptso=5000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, grape); //draw word
                    tot_keys=5; //Total amount of allowed key strokes
                    //strcpy(buffer, grape);
                }
                else if(wordc==4){ //lemon
                    ptso=5000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, lemon); //draw word
                    tot_keys=5; //Total amount of allowed key strokes
                   // strcpy(buffer, lemon);
                }
                else if(wordc==5){ //banana
                    ptso=6000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, banana); //draw word
                    tot_keys=6; //Total amount of allowed key strokes
                   // strcpy(buffer, banana);
                }
                else if(wordc==6){ //orange
                    ptso=6000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, orange); //draw word
                    tot_keys=6; //Total amount of allowed key strokes
                    //strcpy(buffer, orange);
                }
                else if(wordc==7){ //strawberry
                    ptso=10000;
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 130, 180, 0, strawberry); //draw word
                    tot_keys=10; //Total amount of allowed key strokes
                    //strcpy(buffer, strawberry);

                }

                if(strikes==1){
                    al_draw_textf(f2, al_map_rgb(255, 0, 0), 935, 595, 0, "X");

                }
                else if (strikes==2){
                    al_draw_textf(f2, al_map_rgb(255, 0, 0), 935, 595, 0, "XX");
                    //GAMEOVER if EXTREME
                    if(wpm==1){round=5;credcount=3;}
                }
                else if (strikes==3){
                    al_draw_textf(f2, al_map_rgb(255, 0, 0), 935, 595, 0, "XXX");
                    //GAMEOVER if hard
                    if(wpm==3){round=5;credcount=3;}
                }
                else if (strikes==4){
                    al_draw_textf(f2, al_map_rgb(255, 0, 0), 935, 595, 0, "XXXX");
                    //GAMEOVER if medium
                    if(wpm==5){round=5;credcount=3;}
                }
                else if (strikes==5){
                    al_draw_textf(f2, al_map_rgb(255, 0, 0), 935, 595, 0, "XXXXX");
                    //GAMEOVER if easy
                    if(wpm==10){round=5;credcount=3;}
                }
                ///Round =5, since it will hit the updated of round++ to make it 6.==>Game over



                    itoa(ptso,buffer,10);
                    al_draw_textf(f2, al_map_rgb(0,0,0), 716, 595, 0, buffer); //draw points offered

                    itoa(wpm,buffer,10);
                    al_draw_textf(f2, al_map_rgb(0,0,0), 463, 595, 0, buffer); //draw wpm/Seconds

                    itoa(pts,buffer,10);
                    al_draw_textf(f2, al_map_rgb(0,0,0), 950, 170, 0, buffer); //draw points offered

                    itoa(wordc,buffer,10);
                    al_draw_textf(f, al_map_rgb(0, 214, 11), 975, 60, 0, buffer); //draw points offered

                   // credcount++;
                //}


                al_flip_display();
                fadespeed=0;
                letterspressed=0;
                tot_time=wpm*60;
                round++;
            }

            else if (round==4){

                if(fadespeed>=0&&fadespeed<60){
                    al_draw_bitmap(black,155,385,0);
                    al_draw_textf(f, al_map_rgb(0, 211, 10), 165, 400, 0, "Get Ready!!!"); //draw word
                }
                if(fadespeed>=60&&fadespeed<120){
                    al_draw_bitmap(black,155,385,0);
                    al_draw_textf(f, al_map_rgb(0, 211, 10), 165, 400, 0, "     3      "); //draw word
                }
                if(fadespeed>=120&&fadespeed<180){
                    al_draw_bitmap(black,155,385,0);
                al_draw_textf(f, al_map_rgb(0, 211, 10), 165, 400, 0, "     2      "); //draw word
                }
                if(fadespeed>=180&&fadespeed<240){
                    al_draw_bitmap(black,155,385,0);
                al_draw_textf(f, al_map_rgb(0, 211, 10), 165, 400, 0, "     1      "); //draw word
                }
                if(fadespeed>=240&&fadespeed<300){
                    al_draw_bitmap(black,155,385,0);
                al_draw_textf(f, al_map_rgb(0, 211, 10), 165, 400, 0, "    GO!     "); //draw word
                }

                al_flip_display();

                if(fadespeed>=300){
                               //round=2;
                    fadespeed=0;
                    round++;
                    startload=ptso;
                }
                fadespeed+=1;

            }

            else if(round==5){
                if(tot_time>0){//run until time runs out
                    if(tot_keys>letterspressed){//ensure they only have pressed letters totaling the word length
                        al_draw_bitmap(black_smlft,440,585,0);


                        if(tot_time==600){
                            //itoa(wpm,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "10"); //draw wpm/Seconds
                        }
                        else if(tot_time>540&&tot_time<=600){
                            //itoa(wpm-1,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "9"); //draw wpm/Seconds
                        }
                        else if(tot_time>480&&tot_time<=540){
                            //toa(wpm-2,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "8"); //draw wpm/Seconds
                        }
                        else if(tot_time>420&&tot_time<=480){
                            //itoa(wpm-3,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "7"); //draw wpm/Seconds
                        }
                        else if(tot_time>360&&tot_time<=420){
                            //itoa(wpm-4,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "6"); //draw wpm/Seconds
                        }
                        else if(tot_time>300&&tot_time<=360){
                            //itoa(wpm-5,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "5"); //draw wpm/Seconds
                        }
                        else if(tot_time>240&&tot_time<=300){
                            //itoa(wpm-6,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "4"); //draw wpm/Seconds
                        }
                        else if(tot_time>180&&tot_time<=240){
                            //itoa(wpm-7,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "3"); //draw wpm/Seconds
                        }
                        else if(tot_time>120&&tot_time<=180){
                            //itoa(wpm-8,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "2"); //draw wpm/Seconds
                        }
                        else if(tot_time>60&&tot_time<=120){
                            //itoa(wpm-9,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "1"); //draw wpm/Seconds
                        }
                        else if(tot_time<=60){
                            //itoa(,buffer,10);
                            al_draw_textf(f2, al_map_rgb(255, 255, 255), 463, 595, 0, "0"); //draw wpm/Seconds
                        }

                    al_draw_bitmap(black_smrght,695,585,0);

                    itoa(ptso,buffer,10);
                    al_draw_textf(f2, al_map_rgb(255, 255, 255), 716, 595, 0, buffer); //draw points offered


                    }
                    else if(tot_keys==letterspressed){ //correct keys hit
                        round++;
                        credcount=6;
                        wordc++;
                        pts+=ptso;
                        if(wordc==8){//GAME==WON!
                            round=7;
                        }
                    }

                    else {  //tot_keys<letterspressed, aka TOO MANY keys
                        strikes++;
                        round++;

                        credcount=4;
                    }
                }

                else{ //round time done, check winner
                    if(tot_keys>letterspressed){strikes++;round++;credcount=1;}//ran out of time, not enough keystrokes
                }
                 al_flip_display();
                tot_time--;
                ptso-= (startload/(wpm*60))+0.5; //round it
                if(round==6 && credcount==1){ptso=-1500;}

                printf("\nGame: wpm(%i), letts.(%i), tot_keys(%i), tot_time(%i), ptso(%i)\n", wpm, letterspressed,tot_keys, tot_time, ptso);



            }

            else if (round==6){
                al_draw_bitmap(gbg,0,0,0); //draw first screen for easy
                al_draw_bitmap(notice_blank,116,113,0); //draw first screen for easy

                if(credcount==1){
                    al_draw_textf(f, al_map_rgb(222, 125, 0), 450, 300, 0, "Hello?");
                }
                if(credcount==2){
                    al_draw_textf(f, al_map_rgb(255, 0, 0), 350, 230, 0, "Wrong Key!");
                    al_draw_textf(f2, al_map_rgb(0, 214, 11), 280, 375, 0, "Next time watch out for the key:");
                    al_draw_textf(f2, al_map_rgb(0, 214, 11), 950, 375, 0, reportletter);
                }
                if(credcount==3){
                    al_draw_textf(f, al_map_rgb(255, 0, 0), 500, 300, 0, "GAME OVER!");
                }
                if(credcount==4){
                    al_draw_textf(f, al_map_rgb(255, 0, 0), 325, 230, 0, "Woah! Slow Down!");
                }
                if(credcount==6){
                    al_draw_textf(f, al_map_rgb(255, 0, 0), 430, 230, 0, "Alright!");
                    al_draw_textf(f2, al_map_rgb(0, 214, 11), 350, 375, 0, "Prepare for your next word!");
                }

                al_flip_display();
                printf("\nGame: wpm(%i), letts.(%i), tot_keys(%i), tot_time(%i), ptso(%i)\n", wpm, letterspressed,tot_keys, tot_time, ptso);
            }

            else if(round==7){//GAME WIN!!!!
//                al_stop_sample_instance(sample_inst);
//                al_set_sample(sample_inst, al_load_sample("music/11_win.ogg"));
//                al_play_sample_instance(sample_inst);
                al_destroy_audio_stream(stream);
                stream = al_load_audio_stream("music/11_win.ogg", 4, 2048);
                al_attach_audio_stream_to_mixer(stream, mixer);
                al_draw_bitmap(winning,0,0,0); //draw first screen for easy
                al_flip_display();
                round++;
            }

            else if(round==8){
                //paused
            }

            else if(round==9){
            //RECORD KEEPING

            }



            else if(round==99){
                al_destroy_bitmap(gbg);
                al_destroy_bitmap(notice);
                al_destroy_bitmap(notice_blank);
                al_destroy_bitmap(black);
                al_destroy_bitmap(black_smlft);
                al_destroy_bitmap(black_smrght);
                al_destroy_bitmap(winning);


                   fadespeed=0;
                   round=7;
                   gamestate=3;
                   credcount=0;
            }
        }

        if(gamestate==5){//Game Menu: Arcade -5
        }

        if(gamestate==6){//Game Menu: Extras -6
        }

        if(gamestate==7){//Game Menu: Options -7
        }





        printf("\nFlages: gamestate(%i), startload(%i), loop(%i), round(%i), credcount(%i),\n strikes(%i),totalpts(%i)", gamestate, startload,fadespeed, round, credcount,strikes, pts);
                //done=1;
        }
    }
///-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~///

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//
//                  DATA DESTRUCTION
   //BITMAP *black, *powered, *PPlogo, *gimp, *presents, *menuscreen;
    al_destroy_bitmap(membitmap);
   // al_destroy_bitmap(bitmap);
    al_destroy_bitmap(opt1);
    al_destroy_bitmap(opt2);
    al_destroy_bitmap(opt3);

    al_destroy_audio_stream(stream);
    al_destroy_audio_stream(stream2);
    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
    al_uninstall_audio();



//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~//


    return 0; //Program Completed Successfully
}


