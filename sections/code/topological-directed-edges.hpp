struct face_adjacency_id {
  uint32_t face : 30;
  uint32_t location : 2;
};

struct edge : array<vertex_id, 2> {
  struct info {
    bool oriented() const noexcept { return face[1] == invalid; }
    void add_face(uint32 f, uint16 l);
    uint32 face[2]{invalid, invalid};
    uint16 location[2];
  };

  struct hasher {
    auto operator()(const edge &e) const noexcept -> size_t {
      return (size_t(e[0]) << 7) ^ size_t(e[1]);
    }
  };
};

unordered_map<edge, edge::info, edge::hasher> edges{};

void generate_edges() {
  edges.clear();
  for (size_t i = 0; i < faces.size(); ++i) {
    const auto &f = faces[i];
    edges[edge{topological_vertex_map(f[0]), //
               topological_vertex_map(f[1])}]
        .add_face(i, 0);
    edges[edge{topological_vertex_map(f[1]), //
               topological_vertex_map(f[2])}]
        .add_face(i, 1);
    edges[edge{topological_vertex_map(f[2]), //
               topological_vertex_map(f[0])}]
        .add_face(i, 2);
  }
}
