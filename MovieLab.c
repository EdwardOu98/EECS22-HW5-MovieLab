/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                                                            */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

void PrintUsage(char *ProgramName);

int main(int argc, char *argv[])
{
    int i;
    float start, end, step;
    int ftype = 0, rev = 0;
    int Width, Height, frameNUM;
    char *InFileName = NULL, *OutFileName = NULL;
    iterableFilter Filter = NULL;
    MOVIE *movie = NULL;
    IMAGE *image = NULL;
    for(i = 1; i < argc; i++)
    {
        if(0 == strcmp(argv[i], "-h"))
        {
            PrintUsage(argv[0]);
            exit(10);}
        else if(0 == strcmp(argv[i], "-i"))
        {   i++;
            if(i < argc)
            { InFileName = argv[i];
              ftype = 1; }
            else
            { fputs("Missing argument for -i\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-m"))
        {   i++;
            if(i < argc)
            { InFileName = argv[i];
              ftype = 2; }
            else
            { fputs("Missing argument for -m\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-o"))
        {   i++;
            if(i < argc)
            { OutFileName = argv[i]; }
            else
            { fputs("Missing argument for -o\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-s"))
        {   i++;
            if(i < argc)
            { sscanf(argv[i], "%dx%d", &Width, &Height); }
            else
            { fputs("Missing argument for -s\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-f"))
        {   i++;
            if(i < argc)
            { sscanf(argv[i], " %d", &frameNUM); }
            else
            { fputs("Missing argument for -f\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-start="))
        {   i++;
            if(i < argc)
            { sscanf(argv[i], " %f", &start); }
            else
            { fputs("Missing argument for -start=\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-end="))
        {   i++;
            if(i < argc)
            { sscanf(argv[i], " %f", &end); }
            else
            { fputs("Missing argument for -end=\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-step="))
        {   i++;
            if(i < argc)
            { sscanf(argv[i], " %f", &step); }
            else
            { fputs("Missing argument for -step=\n", stderr);
              PrintUsage(argv[0]);
              exit(10);}
        }
        else if(0 == strcmp(argv[i], "-hue"))
        {
            Filter = &HueRotate;
        }
        else if(0 == strcmp(argv[i], "-reverse"))
        {
            rev = 1;
        }
        else
        {   fprintf(stderr, "Unknown Option %s!\n", argv[i]);
            PrintUsage(argv[0]);
            exit(10);}
    }

    if(ftype == 1)
    {
        image = LoadImage(InFileName);
        if(image == NULL)
        {
            printf("Load Image Failed! \n");
            printf("Exiting the program... \n");
            exit(10);
        }
        movie = doIterativeFilter(image, Filter, start, end, step);
        SaveMovie(OutFileName, movie);
        DeleteMovie(movie);
        movie = NULL;
        DeleteImage(image);
        image = NULL;
    }
    else if((ftype == 2) && (rev == 1))
    {
        movie = LoadMovie(InFileName, frameNUM, Width, Height);
        if(movie == NULL)
        {
            printf("Load Movie Failed! \n");
            printf("Exiting the program... \n");
            exit(10);
        }
        ReverseImageList(movie->Frames);
        SaveMovie(OutFileName, movie);
        DeleteMovie(movie);
        movie = NULL;
    }

    return 0;
}

void PrintUsage(char *ProgramName)
{
    fprintf(stderr, "Usage: %s [option...]\n"
                "Option:             Function: \n" 
                "-h                  Print usage info\n" 
                "-i <file.ppm>       Import image\n"
                "-m <file.yuv>       Import movie\n" 
                "-o <file.yuv>       Export movie\n" 
                "-f <frameNUM>       Number of Frames in the imput movie\n"
                "-s <WxH>            Size of a movie frame\n"
                "-start= <startVal>  Set start parameter\n"
                "-end= <endVal>      Set end parameter\n"
                "-step= <stepVal>    Set step parameter\n" 
                "-hue                Use hue filter\n"
                "-reverse            Use reverse filter\n", ProgramName);             
}

/* EOF */
