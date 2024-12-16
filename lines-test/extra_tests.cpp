#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


// Extra Lines Test 1 - Lines connect with no gaps.
// The test is done here as a means of validation, 
// but the main visual test is written and shown in lines-sandbox
TEST_CASE( "Connected Lines - No Gap", "[extra]") {
    Surface surface( 600, 600 );
    surface.clear();

    SECTION( "Connected Lines (Line from p0 - p1 & p1 - p2)" ) {
        draw_line_solid( surface,
			{ 10.0f, 170.0f },
			{ 140.0f, 250.0f },
			{ 255, 255, 255 }
		);
        draw_line_solid( surface,
			{ 140.0f, 250.0f },
			{ 230.0f, 310.0f },
			{ 255, 255, 255 }
		);

        auto const counts = count_pixel_neighbours( surface );

        REQUIRE( 2 == counts[1] ); // There should be two pixels with one neighbour - endpoints
        REQUIRE( counts[2] > 0 ); // Line should contain non-zero amount of pixels with two neighbours
        REQUIRE( 0 == counts[0] ); // No pixels should have zero neighbours

		for( std::size_t i = 3; i < counts.size(); i++ )
			REQUIRE( 0 == counts[i]  ); // There should be no pixels with more than two neighbours
    }
}

// Extra Lines Test 2 - Line clipping when the line extends beyond 2 diagonal bounds
TEST_CASE( "Line clipping beyond 2 bounds", "[extra]") {
    Surface surface( 600, 600 );
	surface.clear();

    // Drawing the extended line
    SECTION( "Diagonal extended line" ) {
        draw_line_solid( surface,
            { -200.0f, -200.0f },
            { 1000.0f, 1000.0f },
            { 255, 255, 255 }
        );

        auto const pixels = max_col_pixel_count( surface );
		REQUIRE( 1 == pixels ); // There should only be one column of pixels
    }
}

// Extra Lines Test 3 - Intersecting lines and ensuring the connecting pixel is drawn
// Once again, this is better visually shown in lines-sandbox
TEST_CASE( "Intersecting lines", "[extra]") {
    Surface surface( 600, 600 );
    surface.clear();

    SECTION( "Intersected lines" ) {
        draw_line_solid( surface,
            { 140.0f, 250.0f },
            { 500.0f, 350.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { 260.0f, 370.0f },
            { 200.0f, 100.0f },
            { 255, 255, 255 }
        );

        auto const counts = count_pixel_neighbours( surface );

        REQUIRE( 4 == counts[1] ); // There should be four pixels with one neighbour - endpoints
        REQUIRE( counts[2] > 0 ); // Line should contain non-zero amount of pixels with two neighbours
        REQUIRE( 0 == counts[0] ); // No pixels should have zero neighbours

		for( std::size_t i = 3; i < counts.size(); i++ )
			REQUIRE( 18 >= counts[i]  ); // There should be at most eighteen pixels with more than two neighbours
    }
}

// Extra Lines Test 4 - Multiple lines, multiple clipping, multiple intersection (stress test)
TEST_CASE( "Multiple lines, multilpe clipping", "[extra]") {
    Surface surface( 600, 600 );
    surface.clear();

    SECTION( "Multiple lines and clipping" ) {
        draw_line_solid( surface,
            { -200.0f, -200.0f },
            { 1000.0f, 1000.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { -200.0f, 300.0f },
            { 1000.0f, 300.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { 300.0f, -200.0f },
            { 300.0f, 1000.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { 1000.0f, -200.0f },
            { -200.0f, 1000.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { 450.0f, -200.0f },
            { 450.0f, 1000.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { 550.0f, -200.0f },
            { 550.0f, 1000.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { -200.0f, 150.0f },
            { 1000.0f, 150.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { -200.0f, 500.0f },
            { 1000.0f, 500.0f },
            { 255, 255, 255 }
        );

        auto const counts = count_pixel_neighbours( surface );
        auto const pixelCol = max_col_pixel_count( surface );
        auto const pixelRow = max_row_pixel_count( surface );

		REQUIRE( 600 == pixelCol ); // There should be 600 columns containing pixels
        REQUIRE( 600 == pixelRow ); // There should be 600 rows containing pixels

        REQUIRE( 16 == counts[1] ); // There should be 16 pixels with one neighbour - endpoints & instersections
        REQUIRE( counts[2] > 0 ); // Line should contain non-zero amount of pixels with two neighbours
        REQUIRE( 0 == counts[0] ); // No pixels should have zero neighbours

		for( std::size_t i = 3; i < counts.size(); i++ )
			REQUIRE( 57 >= counts[i]  ); // There should be at most 57 pixels with more than two neighbours
    }
}

// Extra Lines Test 5 - Parallel lines, ensuring both lines are the same
// Once again, this is better visually shown in lines-sandbox
TEST_CASE( "Parallel", "[extra]") {
    Surface surface( 600, 600 );
    surface.clear();

    SECTION( "Parallel lines" ) {
        draw_line_solid( surface,
            { 40.0f, 40.0f },
            { 240.0f, 240.0f },
            { 255, 255, 255 }
        );
        draw_line_solid( surface,
            { 40.0f, 100.0f },
            { 240.0f, 300.0f },
            { 255, 255, 255 }
        );

        auto const counts = count_pixel_neighbours( surface );
        auto const pixelCol = max_col_pixel_count( surface );
        auto const pixelRow = max_row_pixel_count( surface );

		REQUIRE( 2 == pixelCol ); // There should be 2 columns containing pixels
        REQUIRE( 2 == pixelRow ); // There should be 2 rows containing pixels

        REQUIRE( 4 == counts[1] ); // There should be four pixels with one neighbour - endpoints & instersection
        REQUIRE( counts[2] > 0 ); // Line should contain non-zero amount of pixels with two neighbours
        REQUIRE( 0 == counts[0] ); // No pixels should have zero neighbours

		for( std::size_t i = 3; i < counts.size(); i++ )
			REQUIRE( 57 >= counts[i]  ); // There should be at most 57 pixels with more than two neighbours
    }
}