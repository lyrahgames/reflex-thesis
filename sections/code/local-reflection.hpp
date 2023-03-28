auto reflect(face_node p, face_node q) {
  const auto src = p.fid;
  const auto dst = q.fid;
  vector<face_node> face_strip{};
  if (src == dst) return face_strip;

  face_strip.push_back({p.fid, p.loc, (p.rot + 1) % 2});

  auto f = face_adjacencies[p.fid][p.loc + (p.rot + 1) % 2];
  while (f.fid != dst) {
    face_strip.push_back({f.fid, f.loc, p.rot});
    f = face_adjacencies[f.fid][(f.loc + 1 + p.rot) % 3];
  }

  const auto qloc2 = (q.loc + 1 + rot) % 3;
  face_strip.push_back({q.fid, (3 + qloc2 - 1 - q.rot) % 3, (q.rot + 1) % 2});

  return face_strip;
}
