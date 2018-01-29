#if !defined(GENGINE_ENGINE_SHADER)
#define GENGINE_ENGINE_SHADER

namespace eng {
	class shader {
		unsigned handle;
		unsigned category;
		bool finalized;

	public:
		shader() :
	        handle(0),
	        category(0),
	        finalized(false)
	    { }

	    shader(const shader&) = default;
	    shader(shader&&) = default;
	    shader& operator=(const shader&) = default;
	    shader& operator=(shader&&) = default;
	    ~shader() noexcept = default;

		bool make(const char *source, unsigned type);

		inline operator unsigned() const {
	        return handle;
	    }
	};
}

#endif
