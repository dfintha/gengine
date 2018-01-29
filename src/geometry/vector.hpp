#if !defined(GENGINE_GEOMETRY_VECTOR)
#define GENGINE_GEOMETRY_VECTOR

#include <iosfwd>

namespace geo {
	struct vector {
		float x, y, z, w;

		vector(float cx = 0, float cy = 0, float cz = 0, float cw = 0) :
	        x(cx),
	        y(cy),
	        z(cz),
	        w(cw)
	    { }

	    vector(const vector&) = default;
	    vector(vector&&) = default;
	    vector& operator=(const vector&) = default;
	    vector& operator=(vector&&) = default;
	    ~vector() noexcept = default;

	    inline operator float *() {
	        return reinterpret_cast<float *>(this);
	    }

	    inline operator const float *() const {
	        return reinterpret_cast<const float *>(this);
	    }
	};

	vector operator+(const vector& lhs, const vector& rhs);
    vector operator-(const vector& lhs, const vector& rhs);
    vector operator*(const vector& lhs, double rhs);
    vector operator/(const vector& lhs, double rhs);
    vector operator*(double lhs, const vector& rhs);
    vector operator/(double lhs, const vector& rhs);
    vector operator*(const vector& lhs, const vector& rhs);
    vector operator/(const vector& lhs, const vector& rhs);

    bool operator==(const vector& lhs, const vector& rhs);
    bool operator!=(const vector& lhs, const vector& rhs);
    std::ostream& operator<<(std::ostream& os, const vector& vec);

    double length(const vector& v);
    vector normalize(const vector& v);
    double dot(const vector& v1, const vector& v2);
    vector cross(const vector& v1, const vector& v2);
}
#endif
