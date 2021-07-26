/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
    IENTRY *entry = NULL;

    entry = malloc(sizeof(IENTRY));
    if(entry == NULL)
    {
        printf("Memory allocation for image entry failed!\n");
        printf("Exiting the program...\n");
        exit(10);
    }
    entry->RGBImage = NULL;
    entry->YUVImage = NULL;
    entry->Next = NULL;
    entry->Prev = NULL;
    entry->List = NULL;

    return entry;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
    assert(entry);
    if(entry->RGBImage)
    {
        DeleteImage(entry->RGBImage);
        entry->RGBImage = NULL;
    }
    else if(entry->YUVImage)
    {
        DeleteYUVImage(entry->YUVImage);
        entry->YUVImage = NULL;
    }
    entry->List = NULL;
    entry->Prev = NULL;
    entry->Next = NULL;
    free(entry);
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
    ILIST *l;
    l = malloc(sizeof(ILIST));
    if(l == NULL)
    {
        printf("Memory allocation for image list failed!\n");
        printf("Exiting the program...\n");
        exit(10);
    }

    l->First = NULL;
    l->Last = NULL;
    l->length = 0;

    return l;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    IENTRY *a, *s;

    assert(list);
    a = list->First;
    while(a)
    {
        s = a->Next;
        DeleteImageEntry(a);
        a = s;
    }
    free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
    assert(list);
    assert(RGBimage);
    IENTRY *entry = NULL;
    entry = CreateImageEntry();
    entry->RGBImage = RGBimage;
    if(list->Last)
    {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = list->Last;
        list->Last->Next = entry;
        list->Last = entry;
    }
    else
    {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = NULL;
        list->First = entry;
        list->Last = entry;
    }
    list->length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
    assert(list);
    assert(YUVimage);
    IENTRY *entry = NULL;
    entry = CreateImageEntry();
    entry->YUVImage = YUVimage;
    if(list->Last)
    {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = list->Last;
        list->Last->Next = entry;
        list->Last = entry;
    }
    else
    {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = NULL;
        list->First = entry;
        list->Last = entry;
    }
    list->length++;
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
    assert(list);
    IENTRY *curr = NULL;
    IENTRY *next = NULL;
    IENTRY *prev = NULL;
    IENTRY *first = NULL;
    
    curr = list->First;
    first = list->First;
    while(curr != NULL)
    {
        next = curr->Next;
        prev = curr->Prev;
        if(curr == list->First)
        {
            curr->Prev = next;
            curr->Next = NULL;
        }
        else if(curr == list->Last)
        {
            curr->Next = prev;
            curr->Prev = NULL;
        }
        else
        {
            curr->Next = prev;
            curr->Prev = next;
        }

        curr = next;
    }
    list->First = list->Last;
    list->Last = first;
}























/* EOF */
