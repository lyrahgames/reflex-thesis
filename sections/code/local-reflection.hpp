auto reflect(face_node p, face_node q) {
  const auto src = p.fid;
  const auto dst = q.fid;
  vector<face_node> face_strip{};

  // Return an empty face strip if the
  // original path returns to the first face.
  //
  if (src == dst) return face_strip;

  // The first face node only needs to change
  // the next location pointer by negating 'rot'.
  //
  face_strip.push_back({p.fid, p.loc, (p.rot + 1) % 2});

  // Run through the fan of faces with the
  // opposite rotation and add the face nodes
  // to the strip until 'dst' is reached.
  //
  auto f = face_adjacencies[p.fid][p.loc + (p.rot + 1) % 2];
  while (f.fid != dst) {
    face_strip.push_back({f.fid, f.loc, p.rot});
    f = face_adjacencies[f.fid][(f.loc + 1 + p.rot) % 3];
  }

  // The last face node keeps its next location
  // but needs to change its previous location and 'rot'.
  //
  const auto qloc2 = (q.loc + 1 + rot) % 3;
  face_strip.push_back({q.fid, (3 + qloc2 - 1 - q.rot) % 3,  //
                        (q.rot + 1) % 2});

  return face_strip;
}
