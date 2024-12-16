#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

// Defining region codes for line clipping (using integer values to represent binary)
const int WINDOW = 0; // If the line is inside the window
const int LEFT = 1; // Line extends past the left border of the window
const int RIGHT = 2; // Line extends past the right border of the window
const int BELOW = 4; // Line extends below the window
const int ABOVE = 8; // Line extends above the window

// Function to calculate the region code for a given point (x,y)
// This will be used to clip lines
int regionCode(float xBorder, float yBorder, double x, double y) {
	// Intitialising the code as being in the window
	int region = WINDOW;

	if (x < 0) {
		region |= LEFT;
	} else if (x > xBorder) {
		region |= RIGHT;
	}

	if (y < 0) {
		region |= BELOW;
	} else if (y > yBorder) {
		region |= ABOVE;
	}

	return region;
}

// Function to round off pixels
// This will be using in DDA line drawing
int rounder(float n) {
	if (n - (int)n < 0.5) {
		return (int)n;
	} else {
		return (int)(n + 1);
	}
}

// Edge function to calculate traingle edges and detrmine if a point is on the right or left side of that edge
// Counter-clockwise winding has been factored in
int edgeFunction(const Vec2f point0, const Vec2f point1, int x, int y) {
	return (x - point0.x) * (point1.y - point0.y) - (y - point0.y) * (point1.x - point0.x);
}

// Inspiration for Cohen-Sutherland found at:
// https://www.geeksforgeeks.org/line-clipping-set-1-cohen-sutherland-algorithm/
// Inspiration for DDA Line Drawing found at:
// https://www.youtube.com/watch?v=W5P8GlaEOSI
void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	// Getting window borders
	const int xBorder = aSurface.get_width() - 1;
	const int yBorder = aSurface.get_height() - 1;

	// Calculating the line's region codes for Cohen-Sutherland line clipping algorithm
	int region1 = regionCode(xBorder, yBorder, aBegin.x, aBegin.y);
	int region2 = regionCode(xBorder, yBorder, aEnd.x, aEnd.y);

	// Initialise line as existing outside the window
	bool allow = false;

	while (true) {
		if ((region1 == 0) && (region2 == 0)) {
			// If line is in the window
			allow = true;
			break;
		} else if (region1 & region2) {
			// If line is entirely outside the window
			break;
		} else {
			// Code to handle if line is partially outside the window
			int out_region;
			double x = 0;
			double y = 0;

			// Finding which point in the line is outside the window
			if (region1 != 0) {
				out_region = region1;
			} else {
				out_region = region2;
			}

			// Finding the point where the line intersects the window border
			if (out_region & ABOVE) { // Checking if it's at the top of the window
				x = aBegin.x + (aEnd.x - aBegin.x) * (aSurface.get_height() - 1 - aBegin.y) / (aEnd.y - aBegin.y);
				y = aSurface.get_height()-1;
			} else if (out_region & BELOW) { // Checking if it's below of the window
				x = aBegin.x + (aEnd.x - aBegin.x) * (0 - aBegin.y) / (aEnd.y - aBegin.y);
				y = 0;
			} else if (out_region & RIGHT) { // Checking if it's to the right of the window
				y = aBegin.y + (aEnd.y - aBegin.y) * (aSurface.get_width() - 1 - aBegin.x) / (aEnd.x - aBegin.x);
				x = aSurface.get_width()-1;
			} else if (out_region & LEFT) { // Checking if it's at the top of the window
				y = aBegin.y + (aEnd.y - aBegin.y) * (0 - aBegin.x) / (aEnd.x - aBegin.x);
				x = 0;
			}

			// Now that we found the intersection point, we want to replace the endpoint that is outside the rectangle
			// with the intersection point at the window border
			if (out_region == region1) {
				aBegin.x = x;
				aBegin.y = y;
				region1 = regionCode(xBorder, yBorder, aBegin.x, aBegin.y);
			} else {
				aEnd.x = x;
				aEnd.y = y;
				region2 = regionCode(xBorder, yBorder, aEnd.x, aEnd.y);
			}
		}
	}

	// If the line is clipped and within the window, draw the line
	if (allow) {
		// Code to draw solid lines
		// To draw solid lines, I will be using the DDA Line Drawing Algorithm

		int step = 0; // Tracks how many 'steps' / iterations needed to draw the line

		int dx = aEnd.x - aBegin.x; // Calculating the derivative of x
		int dy = aEnd.y - aBegin.y; // Calculating the derivative of y

		// Determining if the line is more horizontal or vertical
		if (abs(dx) > abs (dy)) {
			step = abs(dx); // If more horizontal, increment along x-axis
		} else {
			step = abs(dy); // If more vertical, increment along y-axis
		}

		// Calculating the increments in x and y for each step
		float xInc = (float)dx / step;
		float yInc = (float)dy / step;

		float x = aBegin.x;
		float y = aBegin.y;

		// Drawing one pixel at each step along the line until the line is fully drawn
		for (int i = 0; i <= step; i++) {
			aSurface.set_pixel_srgb(rounder(x), rounder(y), aColor); // Setting pixel to specified colour
			x = x + xInc; // Incrementing along the x-coordinates
			y = y + yInc; // Incrementing along the y-coordinates
		}
	}
}

void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	// Using the previously implemented 'draw line' function to draw 3 lines, forming a triangle
	// NOTE: Doesn't appear to be used in program
	draw_line_solid(aSurface, aP0, aP1, aColor);
	draw_line_solid(aSurface, aP1, aP2, aColor);
	draw_line_solid(aSurface, aP2, aP0, aColor);
}

// Inspiration for triangle winding found at:
// https://www.geeksforgeeks.org/orientation-3-ordered-points/
// Inspiration for drawing triangles and half plane test found at:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage.html
void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	// Calculating slopes to determine winding of the triangle
	int firstSlope = (aP1.y - aP0.y) * (aP2.x - aP1.x);
	int secondSlope = (aP2.y - aP1.y) * (aP1.x - aP0.x);

	// Checking winding order and swapping vertices to make triangle clockwise
	if (firstSlope <= secondSlope) {
		std::swap(aP1.x, aP2.x);
		std::swap(aP1.y, aP2.y);
	}

	// Getting min and max values for rectangle surrounding the triangle
	int minX = std::min({aP0.x, aP1.x, aP2.x});
    int minY = std::min({aP0.y, aP1.y, aP2.y});
    int maxX = std::max({aP0.x, aP1.x, aP2.x});
    int maxY = std::max({aP0.y, aP1.y, aP2.y});

	// Getting max and min values of the window
	int maxWidth = aSurface.get_width();
	int maxHeight = aSurface.get_height();

	// Cutting to that the triangles / surrounding rectangles don't go out of bounds
	if (minX < 0) {
		minX = 0;
	}
	if (minY < 0) {
		minY = 0;
	}
	if (maxX >= maxWidth) {
		maxX = maxWidth - 1;
	}
	if (maxY >= maxHeight) {
		maxY = maxHeight - 1;
	}

	// Loop used to draw the triangle (loops through every pixel in the surrounding rectangle)
	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			// Calling the edge function 3 times to determine the area surrounding the triangle
			int edge1 = edgeFunction(aP1, aP2, x, y);
            int edge2 = edgeFunction(aP2, aP0, x, y);
            int edge3 = edgeFunction(aP0, aP1, x, y);

			// If every edge function is positive, then it is inside the triangle and a pixel should be placed
			if (edge1 >= 0 && edge2 >= 0 && edge3 >= 0) {
				aSurface.set_pixel_srgb(x, y, aColor);
			}
		}
	}
}

// Inspiration for barycentric interpolation found at:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage.html
void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	// Calculating slopes to determine winding of the triangle
	int firstSlope = (aP1.y - aP0.y) * (aP2.x - aP1.x);
	int secondSlope = (aP2.y - aP1.y) * (aP1.x - aP0.x);

	// Checking winding order and swapping vertices to make triangle clockwise
	if (firstSlope <= secondSlope) {
		std::swap(aP1, aP2);
		std::swap(aC1, aC2);
	}

	// Getting min and max values for rectangle surrounding the triangle
	int minX = std::min({aP0.x, aP1.x, aP2.x});
    int minY = std::min({aP0.y, aP1.y, aP2.y});
    int maxX = std::max({aP0.x, aP1.x, aP2.x});
    int maxY = std::max({aP0.y, aP1.y, aP2.y});

	// Getting max and min values of the window
	int maxWidth = aSurface.get_width();
	int maxHeight = aSurface.get_height();

	// Cutting so that the triangles / surrounding rectangles don't go out of bounds
	if (minX < 0) {
		minX = 0;
	}
	if (minY < 0) {
		minY = 0;
	}
	if (maxX >= maxWidth) {
		maxX = maxWidth - 1;
	}
	if (maxY >= maxHeight) {
		maxY = maxHeight - 1;
	}

	// Loop used to draw the triangle (loops through every pixel in the surrounding rectangle)
	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			// Calling the edge function 3 times to determine the area surrounding the triangle
			int edge1 = edgeFunction(aP1, aP2, x, y);
            int edge2 = edgeFunction(aP2, aP0, x, y);
            int edge3 = edgeFunction(aP0, aP1, x, y);

			// If every edge function is positive, then it is inside the triangle and a pixel should be placed
			if (edge1 >= 0 && edge2 >= 0 && edge3 >= 0) {
				// Calculating barycentric coordinates
				float alpha = ((aP1.y - aP2.y) * (x - aP2.x) + (aP2.x - aP1.x) * (y - aP2.y)) / ((aP1.y - aP2.y) * (aP0.x - aP2.x) + (aP2.x - aP1.x) * (aP0.y - aP2.y));
				float beta = ((aP2.y - aP0.y) * (x - aP2.x) + (aP0.x - aP2.x) * (y - aP2.y)) / ((aP1.y - aP2.y) * (aP0.x - aP2.x) + (aP2.x - aP1.x) * (aP0.y - aP2.y));
				float gamma = 1.0f - alpha - beta;

				// Interplating colour values using the barycentric coordinates
				ColorF interpolatedColor;
				interpolatedColor.r = alpha * aC0.r + beta * aC1.r + gamma * aC2.r;
				interpolatedColor.g = alpha * aC0.g + beta * aC1.g + gamma * aC2.g;
				interpolatedColor.b = alpha * aC0.b + beta * aC1.b + gamma * aC2.b;

				// Converting linear colour back to sRGB format
				ColorU8_sRGB finalColor = linear_to_srgb(interpolatedColor);

				// Drawing the pixel on the surface
				aSurface.set_pixel_srgb(x, y, finalColor);
			}
		}
	}
}


void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	for (int i = aMinCorner.x; i < aMaxCorner.x; i++) {
		for (int j = aMinCorner.y; j < aMaxCorner.y; j++) {
			aSurface.set_pixel_srgb(i, j, aColor);
		}
	}
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	for (float i = 0; i < aMaxCorner.x - aMinCorner.x; i++) {
		aSurface.set_pixel_srgb(aMinCorner.x + i, aMinCorner.y, aColor);
		aSurface.set_pixel_srgb(aMinCorner.x + i, aMaxCorner.y, aColor);
	}

	for (float i = 0; i < aMaxCorner.y - aMinCorner.y; i++) {
		aSurface.set_pixel_srgb(aMinCorner.x, aMinCorner.y + i, aColor);
		aSurface.set_pixel_srgb(aMaxCorner.x, aMaxCorner.y - i, aColor);
	}
}
