struct edge_based_control_point {
  // Directed edge pointing to the right side of the
  // curve with references to topological vertices
  //
  edge e{};

  // Edge weight parameter specifying the exact
  // location of the control point on the edge.
  //
  float w{};

  // Mapping parameter to be able to map values
  // from the original curve to the current one.
  //
  float t{};
};

// The surface mesh curve is then simply a list of
// control points represented by a contiguous array
// dynamically allocated and managed on the heap.
//
vector<control_point> edge_based_curve{};
