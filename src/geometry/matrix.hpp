#if !defined(GENGINE_GEOMETRY_MATRIX)
#define GENGINE_GEOMETRY_MATRIX

namespace geo {
	class matrix {
		float m[4][4];

	public:
		matrix() { }

	    matrix(float m00, float m01, float m02, float m03,
	           float m10, float m11, float m12, float m13,
	           float m20, float m21, float m22, float m23,
	           float m30, float m31, float m32, float m33)
	        : m {{m00, m01, m02, m03},
	             {m10, m11, m12, m13},
	             {m20, m21, m22, m23},
	             {m30, m31, m32, m33}}
	    { }

	    matrix(const matrix&) = default;
	    matrix(matrix&&) = default;
	    matrix& operator=(const matrix&) = default;
	    matrix& operator=(matrix&&) = default;
	    ~matrix() noexcept = default;

		inline float * as_uniform() {
		    return &m[0][0];
		}

		inline float * operator[](unsigned i) {
			return m[i];
		}

		inline const float * operator[](unsigned i) const {
			return m[i];
		}
	};

	matrix operator*(const matrix& lhs, const matrix& rhs) ;
    matrix operator*(const matrix& lhs, const float n);
    matrix operator+(const matrix& lhs, const matrix& rhs);

    matrix translation(float x, float y, float z);
    matrix scaling(float x, float y, float z);
    matrix rotation(float angle, float x, float y, float z);
}

#endif
