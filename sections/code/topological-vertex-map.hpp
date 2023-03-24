discrete_quotient_map<vertex_id, vertex_id> topological_vertex_map{};

void generate_topological_vertex_map() {
  const auto indices = views::iota(vertex_id(0), vertices.size());
  topological_vertex_map = {
      indices,
      [&](auto vid1, auto vid2) { return position(vid1) == position(vid2); },
      [&](auto vid) {
        const auto v = position(vid);
        return (size_t(bit_cast<uint32_t>(v.x)) << 11) ^
               (size_t(bit_cast<uint32_t>(v.y)) << 5) ^
               size_t(bit_cast<uint32_t>(v.z));
      }};
  assert(topological_vertex_map.valid());
}

auto topological_vertex_count() const noexcept {
  return topological_vertex_map.image_size();
}
auto topological_vertex(vertex_id vid) const noexcept {
  return topological_vertex_map(vid);
}
auto topological_vertex_vertex_ids(vertex_id vid) const noexcept {
  return topological_vertex_map[vid];
}
auto topological_vertex_vertices(vertex_id vid) const noexcept {
  return topological_vertex_vertex_ids(vid) |
         views::transform([&](auto vid) { return vertices[vid]; });
}
