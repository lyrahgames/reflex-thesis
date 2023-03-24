using vertex_id = uint32_t;

struct face : array<vertex_id, 3> {};

vector<face> faces{};
