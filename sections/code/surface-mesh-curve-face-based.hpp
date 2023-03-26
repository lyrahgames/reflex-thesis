struct face_point {
  face_id fid;
  face_id loc : 16;
  face_id rot : 16;
};

struct surface_mesh_curve {
  vector<face_point> face_strip{};
  vector<float> edge_weights{};
};
