using face_id = uint32_t;

// Face Adjacencies not only store a face reference
// but also the location to determine at which side
// of the triangle the adjacent edge or face lies.
// As there will never be more than 2^30 faces,
// two bits of the face id will be used to store
// the location that is only allowed to contain the
// values 0, 1, and 2.
// The value 4 is used as invalidation mark for boundaries.
//
struct face_adjacency_id {
  constexpr bool valid() const noexcept { return loc != 4; }
  face_id fid : 30 {};
  face_id loc : 2 = 4;
};

// A directed edge only references
// two topological vertices in a specific order.
//
struct edge : array<vertex_id, 2> {
  // To generate intermediate directed edges in a hash map,
  // a structure to map values onto needs to be provided.
  // Each info structure store the face adjacencey
  // of the face that generated the edge.
  // Not forbidding unoriented surfaces, at most two
  // triangles are allowed to provide the same directed edge.
  // In all other case, the surface would no longer
  // be a 2D manifold and an exception is thrown.
  //
  struct info {
    constexpr bool oriented() const noexcept { //
      return data[1].valid() == invalid;
    }
    void add_face(face_adjacency_id nid) {
      if (!data[0].valid())
        data[0] = nid;
      else if (!data[1].valid())
        data[1] = nid;
      else
        throw runtime_error(                         //
            "Failed to add face adjacency to edge. " //
            "Additional face would violate violate " //
            "the requirements for a 2D manifold.");
    }
    face_adjacency_id data[2];
  };

  // As before, a custom hash function needs to be provided
  // to be able to add edges to a hash map.
  //
  struct hasher {
    auto operator()(const edge &e) const noexcept -> size_t {
      return (size_t(e[0]) << 7) ^ size_t(e[1]);
    }
  };
};

// The hash map that contains an intermediate
// representation of all directed edges.
// After the generation of face adjacencies,
// it is no longer needed and can be destroyed.
//
unordered_map<edge, edge::info, edge::hasher> topological_edges{};

// Iterate through all oriented faces and
// add their directed edges with their
// respective locations to the hash map.
//
void generate_topological_edges() {
  topological_edges.clear();
  for (face_id fid = 0; fid < faces.size(); ++fid) {
    const auto &f = faces[fid];
    topological_edges[edge{topological_vertex_index[f[0]], //
                           topological_vertex_index[f[1]]}]
        .add_face({fid, 0});
    topological_edges[edge{topological_vertex_index[f[1]], //
                           topological_vertex_index[f[2]]}]
        .add_face({fid, 1});
    topological_edges[edge{topological_vertex_index[f[2]], //
                           topological_vertex_index[f[0]]}]
        .add_face({fid, 2});
  }
}
