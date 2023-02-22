struct polyhedral_surface {
  static constexpr uint32_t invalid = -1;

  struct vertex {
    vec3 position{};
    vec3 normal{};
  };
  using vertex_id = uint32_t;

  struct edge : std::array<vertex_id, 2> {};

  struct face : std::array<vertex_id, 3> {};
  using face_id = uint32_t;

  struct face_neighbors : std::array<face_id, 3> {};

  std::vector<vertex> vertices{};
  std::vector<face> faces{};
  std::vector<face_neighbors> dual_graph{};
};
