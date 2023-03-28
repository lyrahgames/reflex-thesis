auto curvature_based_unfolding(const vec3& l, const vec3& r,    //
                               const vec3& v1, const vec3& v2,  //
                               float k) {
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

  const auto dx = qx - px;
  const auto sx = qx + px;
  const auto dy = qy - py;
  const auto sy = qy + py;

  const auto w0 = (sy - sx * dy / dx) / 2;

  const auto sink = sin(k);
  const auto cosk = cos(k);

  const auto tmp1 = sx * dy / dx * sink;
  const auto tmp2 = dx * cosk;
  const auto tmpr = sx * cosk + dy * sink;
  const auto tmp3 = sqrt(tmpr * tmpr - 4 * px * qx);

  const auto dw = (k == 0)  //
                      ? (0.0f)
                      : ((tmp1 + tmp2 - tmp3) / (2 * sink));
  const auto w = w0 + dw;
  return clamp(w, 0.0f, 1.0f);
};
