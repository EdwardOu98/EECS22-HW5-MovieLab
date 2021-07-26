/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include "IterativeFilter.h"
#include <assert.h>

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{
    assert(image);
    assert(filter);
    float x;
    IMAGE *copy = NULL;
    MOVIE *movie = NULL;
    movie = CreateMovie();
    ILIST *list = movie->Frames;

    if(start < end)
    {
        for(x = start; x <= end; x += change)
        {
            copy = CopyImage(image);
            assert(copy);
            copy = filter(copy, x);
            AppendRGBImage(list, copy);
        }
    }
    else if(start > end)
    {
        for(x = start; x >= end; x -= change)
        {
            copy = CopyImage(image);
            assert(copy);
            copy = filter(copy, x);
            AppendRGBImage(list, copy);
        }
    }
    RGB2YUVMovie(movie);

    return movie;
}
