/*
 *  Utility.cpp
 *  NFSpace
 *
 *  Source: http://www.ogre3d.org/wiki/index.php/CropImage
 *
 *  Created by Steven Wittens on 20/08/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Utility.h"

namespace NFSpace {
    
/**
 * Little utility function that crops an image
 * (Doesn't alter the source image, returns a cropped representation)
 *
 * @param   source   The source image
 * @param   offsetX   The X offset from the origin
 * @param   offsetY   The Y offset from the origin
 * @param   width   The width to crop to
 * @param   height   The height to crop to
 *
 * @return   Returns the cropped representation of the source image if the parameters are valid,
 *         otherwise, returns the source image.
 */
Ogre::Image cropImage(const Ogre::Image& source, size_t offsetX, size_t offsetY, size_t width, size_t height)
{
    if(offsetX + width > source.getWidth())
        return source;
    else if(offsetY + height > source.getHeight())
        return source;
    
    size_t bpp = Ogre::PixelUtil::getNumElemBytes(source.getFormat());
    
    const unsigned char *srcData = source.getData();
    unsigned char *dstData = OGRE_ALLOC_T(uchar, width * height * bpp, MEMCATEGORY_RENDERSYS);
    
    size_t srcPitch = source.getRowSpan();
    size_t dstPitch = width * bpp;
    
    for(size_t row = 0; row < height; row++)
    {
        for(size_t col = 0; col < width * bpp; col++)
        {
            dstData[(row * dstPitch) + col] = srcData[((row + offsetY) * srcPitch) + (offsetX * bpp) + col];
        }
    }
    
    Ogre::Image croppedImage;
    croppedImage.loadDynamicImage(dstData, width, height, 1, source.getFormat(), true);
    
    return croppedImage;
}

};