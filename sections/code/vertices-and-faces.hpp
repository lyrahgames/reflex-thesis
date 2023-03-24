// Vertices store their position and
// a pseudo-normal to model additional attributes
// and improve rendering quality.
//
struct vertex {
  vec3 position{};
  vec3 normal{};
};

// In OpenGL and other standard applications,
// it is sufficient to use 32-bit unsigned integers
// to reference vertices.
//
using vertex_id = uint32_t;

// Each face is a contiguous array of three vertex indices.
//
struct face : array<vertex_id, 3> {};

// The vertex and face list are contiguous arrays
// which are dynamically allocated and managed on the heap.
//
vector<vertex> vertices{};
vector<face> faces{};
