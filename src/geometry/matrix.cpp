#include "geometry/matrix.hpp"

#include <cmath>

namespace geo {
	matrix operator*(const matrix& lhs, const matrix& rhs) {
		matrix result;

	    for (unsigned i = 0; i < 4; ++i) {
	        for (unsigned j = 0; j < 4; ++j) {
	            result[i][j] = 0;
	            for (unsigned k = 0; k < 4; ++k) {
	                result[i][j] += lhs[i][k] * rhs[k][j];
	            }
	        }
	    }

	    return result;
	}

    matrix operator*(const matrix& lhs, const float n) {
    	matrix result = lhs;

    	for (int i = 0; i < 4; ++i) {
	        for (int j = 0; j < 4; ++j) {
	            result[i][j] *= n;
	        }
	    }

	    return result;
    }

    matrix operator+(const matrix& lhs, const matrix& rhs) {
    	matrix result = lhs;

	    for (int i = 0; i < 4; ++i) {
	        for (int j = 0; j < 4; ++j) {
	            result[i][j] += rhs[i][j];
	        }
	    }

	    return result;
    }


    matrix translation(float x, float y, float z) {
    	return matrix(1, 0, 0, 0,
                  	  0, 1, 0, 0,
                  	  0, 0, 1, 0,
                  	  x, y, z, 1);
    }

    matrix scaling(float x, float y, float z) {
    	return matrix(x, 0, 0, 0,
                  	  0, y, 0, 0,
                  	  0, 0, z, 0,
                  	  0, 0, 0, 1);
    }

    matrix rotation(float angle, float x, float y, float z) {
    	matrix I(1, 0, 0, 0,
	             0, 1, 0, 0,
	             0, 0, 1, 0,
	             0, 0, 0, 1);

	    matrix C( 0, -z,  y,  0,
	              z,  0, -x,  0,
	             -y,  x,  0,  0,
	              0,  0,  0,  1);

	    matrix T(x * x, x * y, x * z, 0,
	             y * x, y * y, y * z, 0,
	             z * x, z * y, z * z, 0,
	             0,     0,     0,     1);

	    return I * cosf(angle) + C * sinf(angle) + T * (float(1) - cosf(angle));
    }
}
