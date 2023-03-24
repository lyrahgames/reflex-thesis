struct vertex {
  vec3 position{};
  vec3 normal{};
};

using vertex_id = uint32_t;

struct face : array<vertex_id, 3> {};

vector<vertex> vertices{};
vector<face> faces{};
