struct quad_edge_algebra {
  using edge_id = uint32_t;

  struct alignas(2 * sizeof(edge_id)) edge {
    edge_id next{};
    edge_id data{};
  };

  static_assert(sizeof(edge) == 2 * sizeof(edge_id));
  static_assert(alignof(edge) == sizeof(edge));

  static constexpr edge_id type_mask = 0b11;
  static constexpr edge_id base_mask = ~type_mask;
  static_assert(sizeof(edge_id) == sizeof(ptrdiff_t));

  constexpr edge_id rotation(edge_id eid, ptrdiff_t n = 1) noexcept {  //
    const auto rid = static_cast<edge_id>(eid + n);
    return (eid & base_mask) | (rid & type_mask);
  }

  constexpr edge_id symmetric(edge_id eid) noexcept {  //
    return rotation(eid, 2);
  }

  constexpr edge_id next(edge_id eid) noexcept {  //
    return edges[eid].next;
  }

  constexpr edge_id previous(edge_id eid) noexcept {  //
    return rotation(next(rotation(eid)));
  }

  constexpr edge_id& origin(edge_id eid) noexcept {  //
    return edges[eid].data;
  }

  constexpr edge_id& destination(edge_id eid) noexcept {  //
    return origin(symmetric(eid));
  }

  constexpr edge_id& left(edge_id eid) noexcept {  //
    return origin(rotation(eid, -1));
  }

  constexpr edge_id& right(edge_id eid) noexcept {  //
    return origin(rotation(eid, 1));
  }

  constexpr edge_id rotl(edge_id eid) noexcept {  //
    return rotation(eid, 1);
  }

  constexpr edge_id rotr(edge_id eid) noexcept {  //
    return rotation(eid, -1);
  }

  constexpr edge_id sym(edge_id eid) noexcept {  //
    return symmetric(eid);
  }

  constexpr edge_id onext(edge_id eid) noexcept {  //
    return next(eid);
  }

  constexpr edge_id oprev(edge_id eid) noexcept {  //
    return rotl(onext(rotl(eid)));
  }

  constexpr edge_id dnext(edge_id eid) noexcept {  //
    return sym(onext(sym(eid)));
  }

  constexpr edge_id dprev(edge_id eid) noexcept {  //
    return rotr(onext(rotr(eid)));
  }

  constexpr edge_id lnext(edge_id eid) noexcept {  //
    return rotl(onext(rotr(eid)));
  }

  constexpr edge_id lprev(edge_id eid) noexcept {  //
    return sym(onext(eid));
  }

  constexpr edge_id rnext(edge_id eid) noexcept {  //
    return rotr(onext(rotl(eid)));
  }

  constexpr edge_id rprev(edge_id eid) noexcept {  //
    return onext(sym(eid));
  }

  constexpr edge_id& odata(edge_id eid) noexcept {  //
    return origin(eid);
  }

  constexpr edge_id& ddata(edge_id eid) noexcept {  //
    return destination(eid);
  }

  constexpr edge_id& ldata(edge_id eid) noexcept {  //
    return left(eid);
  }

  constexpr edge_id& rdata(edge_id eid) noexcept {  //
    return right(eid);
  }

  edge_id new_edge() {
    const auto eid = edges.size();
    edges.resize(eid + 4);
    edges[eid + 0].next = eid + 0;
    edges[eid + 1].next = eid + 3;
    edges[eid + 2].next = eid + 2;
    edges[eid + 3].next = eid + 1;
    return eid;
  }

  void splice(edge_id a, edge_id b) noexcept {
    const auto alpha = rotl(onext(a));
    const auto beta = rotl(onext(b));
    const auto t1 = onext(b);
    const auto t2 = onext(a);
    const auto t3 = onext(beta);
    const auto t4 = onext(alpha);
    edges[a].next = t1;
    edges[b].next = t2;
    edges[alpha].next = t3;
    edges[beta].next = t4;
  }

  edge_id connection(edge_id a, edge_id b) noexcept {
    auto e = new_edge();
    odata(e) = ddata(a);
    ddata(e) = odata(b);
    splice(e, lnext(a));
    splice(sym(e), b);
    return e;
  }

  void remove(edge_id e) noexcept {
    splice(e, oprev(e));
    splice(sym(e), oprev(sym(e)));
  }

  void swap(edge_id e) noexcept {
    auto a = previous(e);
    auto b = previous(symmetric(e));
    splice(e, a);
    splice(symmetric(e), b);
    splice(e, rotation(next(rotation(a, -1))));
    splice(symmetric(e), rotation(next(rotation(b, -1))));
    origin(e) = destination(a);
    destination(e) = destination(b);
  }

  std::vector<edge> edges;
};
