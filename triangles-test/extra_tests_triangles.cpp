#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

// Extra Triangle Test 1 - Drawing overlapping triangles with diferent colour coordinates
// Testing is added here for validation
// Visual testing in triangles-sandbox shows results better
TEST_CASE( "Overlapping triangles", "[extra]" ) {
    Surface surface( 1200, 800 );
	surface.clear();

    SECTION( "Overlapping" ) {
        draw_triangle_interp( surface, 
            { 100.0f, 100.0f },
            { 300.0f, 300.0f },
            { 500.0f, 100.0f},
            { 1.f, 1.f, 0.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );
        draw_triangle_interp( surface, 
            { 400.0f, 100.0f },
            { 600.0f, 300.0f },
            { 800.0f, 100.0f},
            { 0.f, 1.f, 1.f },
            { 1.f, 0.f, 1.f },
            { 1.f, 1.f, 0.f }
        );
        draw_triangle_interp( surface, 
            { 250.0f, 200.0f },
            { 450.0f, 400.0f },
            { 650.0f, 200.0f},
            { 0.f, 1.f, 1.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );

        // Ensure the triangles have been drawn
		auto const col = find_most_red_pixel( surface );
		REQUIRE( 255 == int(col.r) );
		REQUIRE( 255 == int(col.g) );
		REQUIRE( 0 == int(col.b) );
    }
}

// Extra Triangle Test 2 - One large triangle that clips at all 3 vertices
// Testing is added here for validation
// Visual testing in triangles-sandbox shows results better
TEST_CASE( "Clipping all three vertices", "[extra]" ) {
    Surface surface( 1200, 800 );
	surface.clear();

    SECTION( "Clipping at all three vertices" ) {
        draw_triangle_interp( surface, 
            { -100.0f, 100.0f },
            { 650.0f, 800.0f },
            { 1350.0f, 100.0f},
            { 1.f, 1.f, 0.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );

        // Ensure the traingle has been drawn
		auto const col = find_most_red_pixel( surface );
		REQUIRE( 255 == int(col.r) );
		REQUIRE( 14 == int(col.g) );
		REQUIRE( 255 == int(col.b) );
    }
}

// Extra Triangle Test 3 - A range of irregular triangle shapes
// Testing is added here for validation
// Visual testing in triangles-sandbox shows results better
TEST_CASE( "Irregular triangles", "[extra]" ) {
    Surface surface( 1200, 800 );
	surface.clear();

    SECTION( "Drawing a range of irregular triangles" ) {
        draw_triangle_interp( surface, 
            { 100.0f, 100.0f },
            { 276.0f, 423.0f },
            { 130.0f, 52.0f},
            { 1.f, 1.f, 0.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );
        draw_triangle_interp( surface, 
            { 476.0f, 300.0f },
            { 523.0f, 574.0f },
            { 700.0f, 432.0f},
            { 0.f, 1.f, 1.f },
            { 1.f, 0.f, 1.f },
            { 1.f, 1.f, 0.f }
        );
        draw_triangle_interp( surface, 
            { 900.0f, 200.0f },
            { 1023.0f, 253.0f },
            { 978.0f, 296.0f},
            { 0.f, 1.f, 1.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );
        draw_triangle_interp( surface, 
            { 500.0f, 254.0f },
            { 673.0f, 10.0f },
            { 824.0f, 296.0f},
            { 0.f, 1.f, 1.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );
        draw_triangle_interp( surface, 
            { 967.0f, 498.0f },
            { 1144.0f, 685.0f },
            { 1256.0f, 328.0f},
            { 0.f, 1.f, 1.f },
            { 1.f, 0.f, 1.f },
            { 0.f, 1.f, 1.f }
        );

        // Ensuring traingles have been drawn
		auto const col = find_most_red_pixel( surface );
		REQUIRE( 255 == int(col.r) );
		REQUIRE( 0 == int(col.g) );
		REQUIRE( 255 == int(col.b) );
    }
}