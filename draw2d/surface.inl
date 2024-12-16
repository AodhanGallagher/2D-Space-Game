/* Inline functions need to have a definition that is visible to the compiler
 * whenever the function is used. THey could be define in the header that
 * declares the function. However, to keep the definitions and declarations
 * somewhat apart, it is a common practice to move them to an "inline" file
 * such as this one (*.inl extension). This file is then #include:ed at the end
 * of the header, to ensure that whoever includes the header also automatically
 * includes the inline file.
 *
 * Inlining allows us to avoid any overheads related to call (when building in
 * "release mode" / with optimizations enabled). This makes functions like
 * set_pixel_srgb() zero overhead abstractions.
 *
 */
inline
void Surface::set_pixel_srgb( Index aX, Index aY, ColorU8_sRGB const& aColor )
{
	assert( aX < mWidth && aY < mHeight ); // IMPORTANT! This line must remain the first line in this function!

	int pixel = get_linear_index(aX, aY); // Getting the linear index of the given coordinates and storing them in 'pixel'

	mSurface[pixel+0] = aColor.r; // Setting the red value of the chosen pixel
	mSurface[pixel+1] = aColor.g; // Setting the green value of the chosen pixel
	mSurface[pixel+2] = aColor.b; // Setting the blue value of the chosen pixel
	mSurface[pixel+3] = 0; // Setting the x value of RGBx value to 0 for padding / 32 bit format
}

inline 
auto Surface::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto Surface::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
Surface::Index Surface::get_linear_index( Index aX, Index aY ) const noexcept
{
	std::uint32_t linIndex = aY * get_width() + aX; // Getting the linear memory index for the given coordinates
	return linIndex * 4; // Multiplying the linear index by 4 to handle the pixel data in 32-bit format
}
