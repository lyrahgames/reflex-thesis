auto geodesic_unfolding(const vec3& l, const vec3& r,    //
                        const vec3& v1, const vec3& v2,  //
                        float t) {
  const auto p = r - v1;
  const auto q = l - v1;
  const auto v = v2 - v1;
  const auto vl = length(v);
  const auto ivl = 1 / vl;
  const auto vn = ivl * v;

  const auto py = dot(p, vn);
  const auto qy = dot(q, vn);
  const auto px = -length(p - py * vn);
  const auto qx = length(q - qy * vn);

  const auto w = (py * qx - qy * px) / (qx - px) * ivl;
  return clamp(w, 0.0f, 1.0f);
};
