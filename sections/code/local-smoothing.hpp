auto& curve = face_based_curve;

// Only the edge weights will be changed
// by the local smoothing transformation.
// Store all the new weights in a contiguous
// array of the same size.
//
vector<float> new_w(curve.w.size());

// Retrieve the first face node of the curve.
// A valid surface mesh curve,
// needs to provide at least one.
//
const auto fl = curve.face_strip[0];

// Determine the references and the actual
// positions of the first edge's vertices.
// Use the its edge weight to calculate
// the position of the first control point.
//
const auto pid1 = faces[fl.fid][fl.loc];
const auto pid2 = faces[fl.fid][(fl.loc + 1) % 3];
const auto p1 = vertices[pid1].position;
const auto p2 = vertices[pid2].position;
const auto pw = curve.w[0];
auto p = (1 - pw) * p1 + pw * p2;

// Determine the references and the actual
// positions of the first interior edge's vertices.
// Let it point to the right side of the curve.
//
const auto vid1 = faces[fl.fid][(fl.loc + 2 + fl.rot) % 3];
const auto vid2 = faces[fl.fid][(fl.loc + 1 + fl.rot) % 3];
const auto _v1 = vertices[vid1].position;
const auto _v2 = vertices[vid2].position;
auto v1 = _v1;
auto v2 = _v2;

// Iterate over all control points
// in the interior of the curve.
//
for (size_t i = 1; i < curve.w.size() - 1; ++i) {
  // Retrieve the face node on the right side.
  // Determine the references and the actual
  // positions of the next edge's vertices.
  // Use the next edge weight to calculate
  // the position of the next control point.
  //
  const auto fr = curve.face_strip[i];
  const auto qid1 = faces[fr.fid][(fr.loc + 2 + fr.rot) % 3];
  const auto qid2 = faces[fr.fid][(fr.loc + 1 + fr.rot) % 3];
  const auto q1 = vertices[qid1].position;
  const auto q2 = vertices[qid2].position;
  const auto qw = curve.w[i + 1];
  const auto q = (1 - qw) * q1 + qw * q2;

  // Compute the new weight for the current edge
  // by the application of an unfolding primitive.
  //
  const auto xw = curve.w[i];
  const auto xt = curve.t[i];
  new_w[i] = unfold(p, q, v1, v2, xt);

  // For the next iteration, overwrite the values
  // for the previous and current control points
  // to reuse old computations.
  //
  p = (1 - xw) * v1 + xw * v2;
  v1 = q1;
  v2 = q2;
}

// For a closed curve, the last face node points
// again to the first face node in the strip.
// The first and last edge weights will coincide
// and need to be updated accordingly.
//
if (curve.closed()) {
  // Retrieve positions of the first interior
  // edge's vertices from before and use its
  // edge weight to calculate the control point position.
  //
  const auto q1 = _v1;
  const auto q2 = _v2;
  const auto qw = curve.w[0];
  const auto q = (1 - qw) * q1 + qw * q2;

  // Compute the new weight for the first/last edge
  // by the application of an unfolding primitive.
  // Also update the last edge weight.
  //
  const auto xw = curve.w[0];
  const auto xt = curve.t[0];
  new_w[0] = unfold(p, q, v1, v2, xt);
  new_w.back() = new_w[0];
}

// After the computation of all new weights,
// swap the old weights with the new weights
// to update the surface mesh curve.
//
curve.w.swap(new_w);
