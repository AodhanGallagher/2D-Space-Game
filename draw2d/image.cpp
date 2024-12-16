#include "image.hpp"

#include <memory>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <stb_image.h>

#include "surface.hpp"

#include "../support/error.hpp"

namespace
{
	struct STBImageRGBA_ : public ImageRGBA
	{
		STBImageRGBA_( Index, Index, std::uint8_t* );
		virtual ~STBImageRGBA_();
	};
}

ImageRGBA::ImageRGBA()
	: mWidth( 0 )
	, mHeight( 0 )
	, mData( nullptr )
{}

ImageRGBA::~ImageRGBA() = default;


std::unique_ptr<ImageRGBA> load_image( char const* aPath )
{
	assert( aPath );

	stbi_set_flip_vertically_on_load( true );

	int w, h, channels;
	stbi_uc* ptr = stbi_load( aPath, &w, &h, &channels, 4 );
	if( !ptr )
		throw Error( "Unable to load image \"%s\"", aPath );

	return std::make_unique<STBImageRGBA_>(
		ImageRGBA::Index(w),
		ImageRGBA::Index(h),
		ptr
	);
}

void blit_masked( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
	// Getting the width and height of the image to be blitted and the surface
	int imageWidth = aImage.get_width();
    int imageHeight = aImage.get_height();
	int surfaceWidth = aSurface.get_width();
    int surfaceHeight = aSurface.get_height();

	// Nested for loop to iterate through the image's pixels
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			// Getting the position on the surface to draw the pixel
			int surfaceXCoord = static_cast<int>(aPosition.x) + x;
			int surfaceYCoord = static_cast<int>(aPosition.y) + y;

			// If statement to ensure we do not draw pixels out of bounds
			if (surfaceXCoord >= 0 && surfaceXCoord < surfaceWidth && surfaceYCoord >= 0 && surfaceYCoord < surfaceHeight) {
				// Getting pixel data from the image
				ColorU8_sRGB_Alpha pixelData = aImage.get_pixel(x, y);

				// Discarding pixels with alpha value lower than 128
				if (pixelData.a >= 128) {
					// Setting the pixel on the surface
					aSurface.set_pixel_srgb(surfaceXCoord, surfaceYCoord, {pixelData.r, pixelData.g, pixelData.b});
				}
			}
		}
	}
}

namespace
{
	STBImageRGBA_::STBImageRGBA_( Index aWidth, Index aHeight, std::uint8_t* aPtr )
	{
		mWidth = aWidth;
		mHeight = aHeight;
		mData = aPtr;
	}

	STBImageRGBA_::~STBImageRGBA_()
	{
		if( mData )
			stbi_image_free( mData );
	}
}
