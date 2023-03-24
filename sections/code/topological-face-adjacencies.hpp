struct face_adjacency : array<face_adjacency_id, 3> {};

vector<face_adjacency> face_adjacencies{};

void generate_face_adjacencies() {
  face_adjacencies.resize(faces.size());
  for (const auto &[e, info] : edges) {
    if (info.oriented()) {
      const auto it = edges.find(edge{e[1], e[0]});
      if (it == end(edges))
        face_adjacencies[info.face[0]][info.location[0]] = invalid;
      else {
        const auto &[e2, info2] = *it;
        face_adjacencies[info.face[0]][info.location[0]] =
            uint32(info2.face[0] << 2) | uint32(info2.location[0]);
      }
    } else {
      face_adjacencies[info.face[0]][info.location[0]] =
          uint32(info.face[1] << 2) | uint32(info.location[1]);
      face_adjacencies[info.face[1]][info.location[1]] =
          uint32(info.face[0] << 2) | uint32(info.location[0]);
    }
  }
}
