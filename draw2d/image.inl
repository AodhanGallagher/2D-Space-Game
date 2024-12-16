inline
ColorU8_sRGB_Alpha ImageRGBA::get_pixel( Index aX, Index aY ) const
{
	assert( aX < mWidth && aY < mHeight ); // Leave this at the top of the function.

	// Calculating the linear memory index of the image
	std::uint32_t linIndex = get_linear_index(aX, aY);

	// Creating an RGBA value for the pixel data
	ColorU8_sRGB_Alpha pixel;

	// Getting the individual RGBA values from the image
	pixel.r = mData[linIndex];
    pixel.g = mData[linIndex + 1];
    pixel.b = mData[linIndex + 2];
    pixel.a = mData[linIndex + 3];

	// Returning the colour data of the pixel (in RGBA format)
	return pixel;
}

inline
auto ImageRGBA::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto ImageRGBA::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
std::uint8_t* ImageRGBA::get_image_ptr() noexcept
{
	return mData;
}
inline
std::uint8_t const* ImageRGBA::get_image_ptr() const noexcept
{
	return mData;
}

inline
ImageRGBA::Index ImageRGBA::get_linear_index( Index aX, Index aY ) const noexcept
{
	std::uint32_t linIndex = aY * get_width() + aX; // Getting the linear memory index for the given coordinates
	return linIndex * 4; // Multiplying the linear index by 4 to handle the pixel data in 32-bit format
}
