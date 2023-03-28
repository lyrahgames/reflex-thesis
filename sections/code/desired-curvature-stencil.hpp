const auto curve_stencil = [&]() {
  vector<float> curvature(smooth_curve.vertices.size());
  // curvature[0] = (smooth_curve.vertices[0].curvature +
  //                 smooth_curve.vertices[1].curvature) /
  //                2;
  curvature[0] = 0;
  for (size_t i = 1; i < curvature.size() - 1; ++i) {
    const auto l1 = length(smooth_curve.vertices[i].position -
                           smooth_curve.vertices[i - 1].position);
    const auto l2 = length(smooth_curve.vertices[i + 1].position -
                           smooth_curve.vertices[i].position);
    curvature[i] = (l2 * smooth_curve.vertices[i - 1].curvature +
                    l1 * smooth_curve.vertices[i + 1].curvature) /
                   (l1 + l2);
    curvature[i] = (curvature[i] + smooth_curve.vertices[i].curvature) / 2.0f;
  }
  curvature.back() = 0;
  // curvature.back() = (smooth_curve.vertices.back().curvature +
  //                     smooth_curve.vertices[curvature.size() -
  //                     2].curvature) /
  //                    2;
  for (size_t i = 0; i < curvature.size(); ++i)
    smooth_curve.vertices[i].curvature = curvature[i];
};

for (int i = 0; i < 5; ++i) curve_stencil();
float scale = 0.0f;
for (size_t i = 0; i < smooth_curve.vertices.size(); ++i)
  smooth_curve.vertices[i].curvature *= scale;
