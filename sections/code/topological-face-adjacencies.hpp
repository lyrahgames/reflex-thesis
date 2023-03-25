// A triangle at most can have three adjacent faces.
// So, a simple static array with three values
// will be used to represent face adjacencies.
//
struct face_adjacency : array<face_adjacency_id, 3> {};

// All the face adjacencies are stored in a contiguous array
// that is dynamically allocated and managed on the heap.
//
vector<face_adjacency> topological_face_adjacencies{};

// Generating the actual face adjacencies then only
// consists of iterating over all directed edges
// and copying their mapped information.
//
void generate_topological_face_adjacencies() {
  const auto& edges = topological_edges;
  auto& adjacencies = topological_face_adjacencies;
  adjacencies.assign(faces.size(), face_adjacency_id{});

  for (const auto& [e, info] : topological_edges) {
    if (!info.data[1].valid()) {
      // In this case, the edge is oriented
      // as only a single triangle provides it.
      // So, the reverse edge also needs to be evaluated.
      const auto it = edges.find(edge{e[1], e[0]});
      // If it does not exist, it is a boundary edge.
      if (it == end(edges)) continue;
      const auto& [e2, info2] = *it;
      adjacencies[info.data[0].fid][info.data[0].loc] = info2.data[0];
    } else {
      // In this case, the directed edge is unoriented
      // as two triangles provide the same directed edge.
      adjacencies[info.data[0].fid][info.data[0].loc] = info.data[1];
      adjacencies[info.data[1].fid][info.data[1].loc] = info.data[0];
    }
  }
}
