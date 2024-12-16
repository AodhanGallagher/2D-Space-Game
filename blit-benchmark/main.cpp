#include <benchmark/benchmark.h>

#include <algorithm>

#include <cassert>

#include "../draw2d/image.hpp"
#include "../draw2d/surface.hpp"


// Image of phone - phone.png found at:
// https://mobirise.com/how-to/make-your-own-website/

// Image of moon - moon.png found at:
// https://pngfre.com/moon-png/

// Version of image blitting function with no alpha masking
void blit_no_mask( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
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

				// Setting the pixel on the surface
				aSurface.set_pixel_srgb(surfaceXCoord, surfaceYCoord, {pixelData.r, pixelData.g, pixelData.b});
			}
		}
	}
}


namespace
{
	// default earth blit
	void default_blit_earth_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/earth.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_masked( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	// no alpha mask blit on earth image
	void no_alpha_mask_blit_earth_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/earth.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_no_mask( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory();
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	// default blit on small image - phones.png
	void default_blit_small_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/phone.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_masked( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	// no alpha mask blit on small image - phone.png
	void no_alpha_mask_blit_small_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/phone.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_no_mask( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory();
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	// default blit on large image - moon.png
	void default_blit_large_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/moon.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_masked( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory(); 
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}

	// no alpha mask blit on small image - phone.png
	void no_alpha_mask_blit_large_( benchmark::State& aState )
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		Surface surface( width, height );
		surface.clear();

		auto source = load_image( "assets/moon.png" );
		assert( source );

		for( auto _ : aState )
		{
			blit_no_mask( surface, *source, {0.f, 0.f} );

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory();
		}

		// The following enables the benchmarking library to print information
		// about the memory bandwidth. The total number of bytes processed is
		// *approximatively* two times the total number of bytes in the blit,
		// accounding for both reading and writing. ("Approximatively" since
		// not all pixels are written.)
		auto const maxBlitX = std::min( width, source->get_width() );
		auto const maxBlitY = std::min( height, source->get_height() );

		aState.SetBytesProcessed( 2*maxBlitX*maxBlitY*4 * aState.iterations() );
	}
}

// Default blitting on the earth
BENCHMARK( default_blit_earth_ )
	->Args( { 320, 240 } ) // Small framebuffer
	->Args( { 1280, 720 } ) // Default framebuffer
	->Args( { 1920, 1080 } ) // Full HD framebuffer
	->Args( { 7680, 4320 } ) // 8k framebuffer
;

// Blitting with no alpha mask on the earth
BENCHMARK( no_alpha_mask_blit_earth_ )
	->Args( { 320, 240 } ) // Small framebuffer
	->Args( { 1280, 720 } ) // Default framebuffer
	->Args( { 1920, 1080 } ) // Full HD framebuffer
	->Args( { 7680, 4320 } ) // 8k framebuffer
;

// Default blitting on small image
BENCHMARK( default_blit_small_ )
	->Args( { 320, 240 } ) // Small framebuffer
	->Args( { 1280, 720 } ) // Default framebuffer
	->Args( { 1920, 1080 } ) // Full HD framebuffer
	->Args( { 7680, 4320 } ) // 8k framebuffer
;

// Blitting with no alpha mask on small image
BENCHMARK( no_alpha_mask_blit_small_ )
	->Args( { 320, 240 } ) // Small framebuffer
	->Args( { 1280, 720 } ) // Default framebuffer
	->Args( { 1920, 1080 } ) // Full HD framebuffer
	->Args( { 7680, 4320 } ) // 8k framebuffer
;

// Default blitting on large image
BENCHMARK( default_blit_large_ )
	->Args( { 320, 240 } ) // Small framebuffer
	->Args( { 1280, 720 } ) // Default framebuffer
	->Args( { 1920, 1080 } ) // Full HD framebuffer
	->Args( { 7680, 4320 } ) // 8k framebuffer
;

// Blitting with no alpha mask on large image
BENCHMARK( no_alpha_mask_blit_large_ )
	->Args( { 320, 240 } ) // Small framebuffer
	->Args( { 1280, 720 } ) // Default framebuffer
	->Args( { 1920, 1080 } ) // Full HD framebuffer
	->Args( { 7680, 4320 } ) // 8k framebuffer
;

BENCHMARK_MAIN();
