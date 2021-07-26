/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
    MOVIE *m;

    m = malloc(sizeof(MOVIE));
    if(m == NULL)
    {
        printf("Memory Allocation for the movie frame failed!\n");
        printf("Exiting the program...\n");
        exit(10);
    }
    m->Frames = CreateImageList();

    return m;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);

    DeleteImageList(movie->Frames);
    movie->Frames = NULL;
    free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
    assert(movie);
    IMAGE *image = NULL;
    ILIST *list = NULL;
    IENTRY *curr = NULL;
    IENTRY *next = NULL;
    unsigned int movWidth, x;
    unsigned int movHeight, i;
    int c, d, e;
    int tmp;
    int y, u, v;

    list = movie->Frames;
    curr = list->First;
    movWidth = MovieWidth(movie);
    movHeight = MovieHeight(movie);
    while(curr != NULL)
    {
        assert(curr);
        assert(curr->YUVImage);
        next = curr->Next;
        image = CreateImage(movWidth, movHeight);

        for(i = 0; i < movHeight; i++)
        {
            for(x = 0; x < movWidth; x++)
            {
                y = GetPixelY(curr->YUVImage, x, y);
                u = GetPixelU(curr->YUVImage, x, y);
                v = GetPixelV(curr->YUVImage, x, y);

                c = y - 16;
                d = u - 128;
                e = v - 128;

                tmp = (298 * c + 409 * e + 128) >> 8;
                if(tmp > 255){
                    SetPixelR(image, x, y, 255);
                }
                else if(tmp < 0){
                    SetPixelR(image, x, y, 0);
                }
                else
                {
                    SetPixelR(image, x, y, tmp);
                }

                tmp = (298 * c - 100 * d - 208 * e + 128) >> 8;
                if(tmp > 255){
                    SetPixelG(image, x, y, 255);
                }
                else if(tmp < 0){
                    SetPixelG(image, x, y, 0);
                }
                else
                {
                    SetPixelG(image, x, y, tmp);
                }

                tmp = (298 * c + 516 * d + 128) >> 8;
                if(tmp > 255){
                    SetPixelB(image, x, y, 255);
                }
                else if(tmp < 0){
                    SetPixelB(image, x, y, 0);
                }
                else
                {
                    SetPixelB(image, x, y, tmp);
                }
            }
        }
        curr->RGBImage = image;
        DeleteYUVImage(curr->YUVImage);
        curr->YUVImage = NULL;
        curr = next;
    }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
    assert(movie);
    YUVIMAGE *YUVimage = NULL;
    ILIST *list = NULL;
    IENTRY *curr = NULL;
    IENTRY *next = NULL;
    unsigned int Width, x;
    unsigned int Height, y;
    int tmp;
    int r, g, b;

    list = movie->Frames;
    curr = list->First;
    Width = ImageWidth(curr->RGBImage);
    Height = ImageHeight(curr->RGBImage);

    while(curr != NULL)
    {
        assert(curr);
        assert(curr->RGBImage);
        next = curr->Next;
        YUVimage = CreateYUVImage(Width, Height);

        for(y = 0; y < Height; y++)
        {
            for(x = 0; x < Width; x++)
            {
                r = GetPixelR(curr->RGBImage, x, y);
                g = GetPixelG(curr->RGBImage, x, y);
                b = GetPixelB(curr->RGBImage, x, y);
                
                tmp = ((66 * r + 129 * g + 25 * b + 128) >> 8) + 16;
                if(tmp > 255){
                    SetPixelY(YUVimage, x, y, 255);
                }
                else if(tmp < 0){
                    SetPixelY(YUVimage, x, y, 0);
                }
                else
                {
                    SetPixelY(YUVimage, x, y, tmp);
                }

                tmp = ((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
                if(tmp > 255){
                    SetPixelU(YUVimage, x, y, 255);
                }
                else if(tmp < 0){
                    SetPixelU(YUVimage, x, y, 0);
                }
                else
                {
                    SetPixelU(YUVimage, x, y, tmp);
                }

                tmp = ((112 * r - 94 * g - 18 * b + 128) >> 8) + 128;
                if(tmp > 255){
                    SetPixelV(YUVimage, x, y, 255);
                }
                else if(tmp < 0){
                    SetPixelV(YUVimage, x, y, 0);
                }
                else
                {
                    SetPixelV(YUVimage, x, y, tmp);
                }
            }
        }
        curr->YUVImage = YUVimage;
        DeleteImage(curr->RGBImage);
        curr->RGBImage = NULL;
        curr = next;
    }
}

int MovieLength(const MOVIE *movie)
{
    assert(movie);
    return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
    assert(movie);
    return movie->Frames->First->YUVImage->H;
}

int MovieWidth(const MOVIE *movie)
{
    assert(movie);
    return movie->Frames->First->YUVImage->W;
}

/* EOF */
