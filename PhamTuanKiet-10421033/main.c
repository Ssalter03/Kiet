#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

/**
 * Create a new 1-dimensional array with the given size
 * @param[in] _size the size of the array
 * @param[out] _ empty 1-dimensional array filled with 0
 */
unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *mask_image(unsigned char *image1,unsigned char *image2, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for (int i = 0; i < height*width*channel; i=i+1)
    {   
            temp_array[i] = image1[i]; 
    }
    for (int i = 0; i < height*width*channel; i=i+3)
    {
        if((image1[i] >= 50  &&  image1[i] <= 180 ) &&
        (image1[i+1] <= 255 && image1[i+1] >= 180 ) && 
        (image1[i+2] >= 0 && image1[i+2] <= 100 ))
        {
            temp_array [i] = image2[i];
            temp_array [i+1] = image2[i+1];
            temp_array [i+2] = image2[i+2];
        }
    }   
    return temp_array;
}

int main()
{
    int width, height, channel;
    char path_img1[] = "./foreground.png";
    char path_img2[] = "./back.jpg";
    char save_path[] = "./Res.jpg";

    unsigned char *imagefore = stbi_load(path_img1, &width, &height, &channel, 3);
    if (imagefore == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    unsigned char *imagenewback = stbi_load(path_img2, &width, &height, &channel, 3);
    if (imagenewback == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    unsigned char *mimage = mask_image(imagefore, imagenewback, width, height, channel);
    stbi_write_png(save_path, width, height, channel, mimage, width * channel);
    printf("New image saved to %s\n", save_path);
}