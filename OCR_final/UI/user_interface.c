#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "../Preprocessing/grayscale.h"
#include "../Preprocessing/display.h"
#include "../Segmentation/hough.h"
#include "../Segmentation/segment.h"
#include "../Preprocessing/drawsudoku.h"
#include "../Preprocessing/sdl.h"

//Global variable

//Main containers
GtkWidget   *main_window;
GtkWidget   *main_panel;

//Button Menu
GtkWidget   *button_grid;

//Buttons
GtkWidget   *open_file_button;
GtkButton*   quit_button;
GtkWidget   *execute_button;
GtkWidget   *spin_button;

//Containers
GtkWidget   *fixed0;
GtkWidget   *fixed1;
GtkWidget   *fixed2;
GtkWidget   *fixed3;

//Labels & Images
GtkWidget   *label_p0;
GtkWidget   *label_p1;
GtkWidget   *image_p1;
GtkWidget   *label_p2;
GtkWidget   *image_p2;

GtkWidget   *label_p01;

GtkWidget   *image0;
GtkWidget   *image1;
GtkWidget   *image2;
GtkWidget   *image3;
GtkWidget   *the1;
GtkWidget   *case1;

GtkBuilder  *builder;

SDL_Surface *img;

char* filename;  //link of the image


int main(){

    gtk_init(NULL,NULL);
    //link to glade
    builder = gtk_builder_new_from_file("interface.glade");

    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Connect signal with glade
    gtk_builder_connect_signals(builder,NULL);


    //Link all my widgets to the builder
    main_panel = GTK_WIDGET(gtk_builder_get_object(builder,"main_panel"));
    button_grid = GTK_WIDGET(gtk_builder_get_object(builder,"button_grid"));
    open_file_button = GTK_WIDGET(gtk_builder_get_object
            (builder,"open_file_button"));
    quit_button = GTK_BUTTON(gtk_builder_get_object(builder, "quit_button"));
    spin_button = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button"));

    fixed0 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed0"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));

    image_p1 = GTK_WIDGET(gtk_builder_get_object(builder, "image_p1"));
    image_p2 = GTK_WIDGET(gtk_builder_get_object(builder, "image_p2"));

    label_p0 = GTK_WIDGET(gtk_builder_get_object(builder, "label_p0"));
    label_p1 = GTK_WIDGET(gtk_builder_get_object(builder, "label_p1"));
    label_p2 = GTK_WIDGET(gtk_builder_get_object(builder, "label_p2"));

    label_p01 = GTK_WIDGET(gtk_builder_get_object(builder, "label_p01"));

/*
    grid1 = GTK_WIDGET(gtk_builder_get_object(builder, "grid1"));
    grid2 = GTK_WIDGET(gtk_builder_get_object(builder, "grid2"));
    grid3 = GTK_WIDGET(gtk_builder_get_object(builder, "grid3"));
    grid4 = GTK_WIDGET(gtk_builder_get_object(builder, "grid4"));
    grid5 = GTK_WIDGET(gtk_builder_get_object(builder, "grid5"));
    grid6 = GTK_WIDGET(gtk_builder_get_object(builder, "grid6"));
    grid7 = GTK_WIDGET(gtk_builder_get_object(builder, "grid7"));
    grid8 = GTK_WIDGET(gtk_builder_get_object(builder, "grid8"));
    grid9 = GTK_WIDGET(gtk_builder_get_object(builder, "grid9"));
*/

    g_signal_connect(quit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    //Change the color
    GdkRGBA color;
    color.red = color.green = color.blue = 000000;
    gtk_widget_override_background_color(main_window,GTK_STATE_NORMAL,&color);

    image0 = NULL;
    image1 = NULL;
    image2 = NULL;
    image3 = NULL;
    the1 = NULL;
    label_p01 = NULL;

    gtk_widget_show(main_window);

    gtk_main();

    return EXIT_SUCCESS;
}


//file button signal script
void on_open_file_button_file_set(GtkFileChooserButton *b){
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(b));
}

//spin button signal script for the rotate
void on_spin_button_value_changed(){
    int angle = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));


    SDL_Surface *img1 = IMG_Load("../cache/grayscale");
    SDL_Surface *rotated = rotate(img1,angle);
    gtk_container_remove(GTK_CONTAINER(fixed2),image2);
    SDL_SaveBMP(rotated, "../cache/rotated");
    image2 = gtk_image_new_from_file("../cache/rotated");

    //scale the rotated picture
    GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file_at_scale
        ("../cache/rotated",800,800,TRUE,NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), pixbuf2);
    gtk_container_add (GTK_CONTAINER(fixed2), image2);
    gtk_widget_show(image2);
}



//signal script of the execute button
void on_execute_button_clicked(){
    gtk_widget_hide(image_p1);
    gtk_widget_hide(image_p2);
    gtk_widget_hide(label_p0);

    gtk_container_add(GTK_CONTAINER(fixed0), label_p01);
    gtk_widget_show(label_p01);


    int i = 0;
    int len = 0;

    while (filename[i]){
        len+=1;
        i+=1;
    }
    
    //check if the file is a picture
    if(((filename[len-1] == 'g') && (filename[len-2] == 'n') &&
                (filename[len-3] == 'p')) || ((filename[len-1] == 'g') &&
                ((filename[len-2]) == 'p') && (filename[len-3] == 'j'))||
                ((filename[len-1] == 'p') && (filename[len-2] == 'm') &&
                 (filename[len-3] == 'b')))
    {

        if(image0){
            gtk_container_remove(GTK_CONTAINER(fixed0), image0);
        }
        if(image1){
            gtk_container_remove(GTK_CONTAINER(fixed1), image1);
        }
        if(image2){
            gtk_container_remove(GTK_CONTAINER(fixed2),image2);
        }
        if(image3){
            gtk_container_remove(GTK_CONTAINER(fixed3),image3);
        }

        //create a folder which will contain all the pictures
        mkdir("../cache", 0777);


        //Base picture
        img = IMG_Load(filename); //convert the image in SDL
        SDL_SaveBMP(img, "../cache/base");
        image0 = gtk_image_new_from_file("../cache/base");
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale
            ("../cache/base",800,800,TRUE,NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image0),pixbuf);
        gtk_container_add (GTK_CONTAINER(fixed0), image0);
        gtk_widget_show(image0);


        //Grayscale picture
        SDL_Surface *temp = IMG_Load(filename);
        SDL_Surface *grayscale_img = image(img,temp);

        SDL_SaveBMP(grayscale_img, "../cache/grayscale");
        image1 = gtk_image_new_from_file("../cache/grayscale");
        GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_scale
            ("../cache/grayscale",800,800,TRUE,NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image1),pixbuf1);
        gtk_container_add (GTK_CONTAINER(fixed1), image1);
        gtk_widget_show(image1);

        //int height = the1->h;
        //int width = the1->w;
       /* 
        int* matrice = matrice01("cache/grayscale");
        g_print("pas andrea");
        size_t w = 543;
        size_t h = 438;
        segment(matrice,w,h);
        */

        //Rotate auto


        g_print("ah");
        SDL_Surface *grille = load_image("../grid/grid.jpg");
        //Result Image
        grille = draw("../grid/grid_00.result",grille);
        //g_print("ah");
        SDL_SaveBMP(grille, "../cache/result");

        GdkPixbuf *pixbuf3 = gdk_pixbuf_new_from_file_at_scale
            ("../grid/grid.png",900,900,TRUE,NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image3),pixbuf3);
        gtk_container_add(GTK_CONTAINER(fixed3), image3);
        gtk_widget_show(image3);

    }
}

