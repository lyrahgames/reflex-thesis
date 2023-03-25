// Store the values of the quotient map for each vertex
// in a dynamically allocated contiguous array.
//
vector<vertex_id> topological_vertex_index{};
vertex_id topological_vertex_count = 0;

void generate_topological_vertex_map() {
  // Define whether two vertex references
  // are topologically equivalent.
  //
  const auto equivalent = [&](vertex_id vid1, vertex_id vid2) {
    return vertices[vid1].position == vertices[vid2].position;
  };
  using equivalence = decltype(equivalent);

  // For the most efficient pairwise comparison,
  // we use a hash map and need to define
  // a custom hash function for vertex references.
  //
  const auto hash = [&](vertex_id vid) -> size_t {
    const auto v = vertices[vid].position;
    return (size_t(bit_cast<uint32_t>(v.x)) << 11) ^
           (size_t(bit_cast<uint32_t>(v.y)) << 5) ^
           size_t(bit_cast<uint32_t>(v.z));
  };
  using hasher = decltype(hash);

  // The hash map itself is only needed during the construction
  // and directly represents the quotient map.
  //
  unordered_map<vertex_id, vertex_id, hasher, equivalence> //
      indices({},                                          //
              forward<decltype(hash)>(hash),               //
              forward<decltype(equal)>(equal));
  indices.reserve(vertices.size());

  topological_vertex_index.resize(vertices.size());
  topological_vertex_count = 0;

  // Iterate over all vertices and add them to the hash map.
  // The first-time insertion will also assign the index.
  // Toplogically equivalent vertices are automatically mapped
  // to the same index and filtered in linear time.
  //
  for (vertex_id vid = 0; vid < vertices.size(); ++vid) {
    const auto it = indices.find(vid);
    if (it != end(indices))
      topological_vertex_index[vid] = it->second;
    else {
      topological_vertex_index[vid] = topological_vertex_count;
      indices.emplace(vid, topological_vertex_count++);
    }
  }
}
