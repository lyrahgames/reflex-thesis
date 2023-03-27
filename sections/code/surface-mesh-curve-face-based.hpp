struct face_based_node {
  face_id fid;

  // The location inside the adjacency of
  // the face given by the reference 'fid'
  // that points to the face adjacency
  // representing the previous face in the strip.
  //
  face_id loc : 16;

  // The amount that needs to be added to 'loc + 1'
  // to get the location inside the adjacency of
  // the face given by the reference 'fid'
  // that points to the face adjacency
  // representing the next face in the strip.
  //
  face_id rot : 16;
};

struct face_based_surface_mesh_curve {
  // The face strip is only a list face-based nodes
  // and handled by contiguous array that is
  // dynamically allocated and managed on the heap.
  //
  vector<face_based_node> face_strip{};

  // The edge weights and mapping parameters
  // need to be separated from the face strip
  // and will be stored as separate arrays.
  //
  vector<float> w{};
  vector<float> t{};
} face_based_curve{};
