#include "spaceship.hpp"

#include <cstdio>

#include "../draw2d/shape.hpp"

/* Instructions - CUSTOM SPACESHIP DESIGNS
 *
 *  0. If you are OK with your space ship design being included in future
 *     computer graphics exercises and/or courseworks, please indicate this by
 *     placing a 'X' in the space between the [ ] on the following line:
 *     [X] I give permission for my space ship shape to be used in future
 *         computer graphics exercises and/or courseworks.
 *
 *     If you do not wish for your shape to be used, leave the line as is.
 *     Your decision will not affect the marking of Task 2.7 in CW1.
 *
 *     If you wish to be credited (name + year when you took the computer
 *     graphics mdoule) in a CREDITS.txt or similar file with future exercises
 *     and/or courseworks, please indicate this by ticking the following box
 *     [X] I wish to have my name + year listed with assignments that use my
 *         space ship shape.
 *
 *     If you do not wish to be credited, leave the [ ] empty.
 *
 *     Many thanks if you do permit the use of your cool space ship designs! It
 *     will help us to make future computer graphics exercises and courseworks
 *     more interesting.
 *
 *  1. Change the line
 *     #	define SPACESHIP SPACESHIP_DEFAULT
 *     to
 *     #	define SPACESHIP SPACESHIP_CUSTOM
 *
 *  2. Define your custom space ship design in the now active code section.
 *     (Look for the line that says '// TODO: YOUR DESIGN GOES HERE')
 */

#define SPACESHIP_DEFAULT 1
#define SPACESHIP_CUSTOM 2

#ifndef SPACESHIP
#	define SPACESHIP SPACESHIP_CUSTOM
#endif

LineStrip make_spaceship_shape()
{
#	if SPACESHIP == SPACESHIP_DEFAULT
	static constexpr float xs[] = { 250.f, 200.f, 150.f, 100.f, 000.f, 040.f, -50.f, -140.f, -170.f };
	static constexpr float ys[] = { 190.f, 180.f, 70.f, 50.f, 30.f, 20.f };

	LineStrip spaceship{ { 
		{ 0.2f * xs[0], 0.2f * +ys[5] }, // upper half. starts at front, goes towards the back
		{ 0.2f * xs[1], 0.2f * +ys[3] },
		{ 0.2f * xs[2], 0.2f * +ys[3] },
		{ 0.2f * xs[3], 0.2f * +ys[4] }, 
		{ 0.2f * xs[4], 0.2f * +ys[4] },
		{ 0.2f * xs[4], 0.2f * +ys[2] },
		{ 0.2f * xs[5], 0.2f * +ys[1] },
		{ 0.2f * xs[6], 0.2f * +ys[0] },
		{ 0.2f * xs[8], 0.2f * +ys[2] },
		{ 0.2f * xs[7], 0.2f * +ys[3] },

		{ 0.2f * xs[7], 0.2f * -ys[3] }, // lower half, starts at the back and goes towards the front
		{ 0.2f * xs[8], 0.2f * -ys[2] }, // this is essentially the same as the upper half, except in  reverse.
		{ 0.2f * xs[6], 0.2f * -ys[0] },
		{ 0.2f * xs[5], 0.2f * -ys[1] },
		{ 0.2f * xs[4], 0.2f * -ys[2] },
		{ 0.2f * xs[4], 0.2f * -ys[4] },
		{ 0.2f * xs[3], 0.2f * -ys[4] }, 
		{ 0.2f * xs[2], 0.2f * -ys[3] },
		{ 0.2f * xs[1], 0.2f * -ys[3] },
		{ 0.2f * xs[0], 0.2f * -ys[5] }, 

		{ 0.2f * xs[0], 0.2f * +ys[5] } // link back to beginning (connects both sides at the "front")
	} };
#	elif SPACESHIP == SPACESHIP_CUSTOM

	LineStrip spaceship{ {

		// Drawing a custom spaceship by plotting the individual vertex coordinates

		// Top half of the ship
		{ 47.5f, 0.0f },
		{ 42.5f, -5.0f },
		{ 22.5f, -12.5f },
		{ 2.5f, -25.0f },
		{ 17.5f, -25.0f },
		{ 17.5f, -40.0f },
		{ -2.5f, -40.0f },
		{ -22.5f, -70.0f },
		{ -37.5f, -70.0f },
		{ -37.5f, -40.0f },
		{ -47.5f, -40.0f },
		{ -47.5f, -25.0f },
		{ -37.5f, -25.0f },
		{ -40.0f, -12.5f },
		{ -47.5f, -7.5f },

		// Bottom half of ship (reverse due to symmetry)
		{ -47.5f, 7.5f },
		{ -40.0f, 12.5f },
		{ -37.5f, 25.0f },
		{ -47.5f, 25.0f },
		{ -47.5f, 40.0f },
		{ -37.5f, 40.0f },
		{ -37.5f, 70.0f },
		{ -22.5f, 70.0f },
		{ -2.5f, 40.0f },
		{ 17.5f, 40.0f },
		{ 17.5f, 25.0f },
		{ 2.5f, 25.0f },
		{ 22.5f, 12.5f },
		{ 42.5f, 5.0f },
		{ 47.5f, 0.0f }

	
	} };
#	endif

	if( spaceship.vertex_count() > 32 )
	{
		std::fprintf( stderr, "WARNING: you must use at most 32 points for your custom spaceship design. You are currently using %zu\n", spaceship.vertex_count() );
	}

	return spaceship;
}
