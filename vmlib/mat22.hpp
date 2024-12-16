#ifndef MAT22_HPP_1F974C02_D0D1_4FBD_B5EE_A69C88112088
#define MAT22_HPP_1F974C02_D0D1_4FBD_B5EE_A69C88112088

#include <cmath>

#include "vec2.hpp"

/** Mat22f : 2x2 matrix with floats
 *
 * See comments for Vec2f for some discussion.
 *
 * The matrix is stored in row-major order.
 *
 * Example:
 *   Mat22f identity{ 
 *     1.f, 0.f,
 *     0.f, 1.f
 *   };
 */
struct Mat22f
{
	float _00, _01;
	float _10, _11;
};

// Common operators for Mat22f.
// Note that you will need to implement these yourself.


// Inspiration for matrix mutliplication gained from:
// https://www.statology.org/matrix-multiplication-2x2-by-2x2/
constexpr
Mat22f operator*( Mat22f const& aLeft, Mat22f const& aRight ) noexcept
{
	// Implementing matrix-matrix multiplication

	// Calculating the individual values for the multiplied 2x2 matrix
	float topLeft = (aLeft._00 * aRight._00) + (aLeft._01 * aRight._10);
	float topRight = (aLeft._00 * aRight._01) + (aLeft._01 * aRight._11);
	float bottomLeft = (aLeft._10 * aRight._00) + (aLeft._11 * aRight._10);
	float bottomRight = (aLeft._10 * aRight._01) + (aLeft._11 * aRight._11);

	// Returning the final matrix
	return Mat22f{ topLeft, topRight, bottomLeft, bottomRight };
}

constexpr
Vec2f operator*( Mat22f const& aLeft, Vec2f const& aRight ) noexcept
{
	// Implementing matrix-vector multiplication

	// Calculating the new vector values
	float topValue = (aLeft._00 * aRight.x) + (aLeft._01 * aRight.y);
	float bottomValue = (aLeft._10 * aRight.x) + (aLeft._11 * aRight.y);

	// Assigning the values to a new vector variable
	Vec2f finalVector = { topValue, bottomValue };

	// Returning the new vector
	return finalVector;
}

// Learning how to handle a 2d rotation matrix from:
// https://en.wikipedia.org/wiki/Rotation_matrix
inline
Mat22f make_rotation_2d( float aAngle ) noexcept
{
	// Implementing a 2d rotation matrix

	// Calculating the individual values for the rotation matrix (adjusted for coordinates beginning at bottom left)
	float topLeft = cos(aAngle);
	float topRight = -sin(aAngle);
	float bottomLeft = sin(aAngle);
	float bottomRight = cos(aAngle);

	// Returning the rotation matrix
	return Mat22f{ topLeft, topRight, bottomLeft, bottomRight };
}

#endif // MAT22_HPP_1F974C02_D0D1_4FBD_B5EE_A69C88112088
