vector<vertex_id> inverse_topological_vertex_offset{};
vector<vertex_id> inverse_topological_vertex_index{};

void generate_inverse_toplogical_vertex_map() {
  const auto &labels = topological_vertex_index;
  const auto count = topological_vertex_count;
  auto &inverse_offset = inverse_topological_vertex_offset;
  auto &inverse = inverse_topological_vertex_index;

  // Get the count of elements per equivalence class.
  //
  inverse_offset.assign(count + 1, 0);
  for (auto y : labels)
    ++inverse_offset[y + 1];

  // Calculate cumulative sum of counts to get the offsets.
  //
  for (size_t i = 2; i < inverse_offset.size(); ++i)
    inverse_offset[i] += inverse_offset[i - 1];

  // Generate equivalence classes by using offsets as indices.
  //
  inverse.resize(labels.size());
  for (size_t x = 0; x < labels.size(); ++x)
    inverse[inverse_offset[labels[x]]++] = x;

  // Repair the inverse offsets after using them in the previous step.
  //
  for (size_t i = inverse_offset.size() - 1; i > 0; --i)
    inverse_offset[i] = inverse_offset[i - 1];
  inverse_offset[0] = 0;
}
