#include <vector>

template <class S, S (*op)(S, S), S (*e)()>
struct Segtree {
    std::vector<S> Tree;
    int n;
    int depth = 1, width = 1;
    Segtree(int N = 0) : n(N) {
        while (width < n) depth++, width <<= 1;
        Tree.resize(width * 2);
        for (int i = width; i < width * 2; i++) Tree[i] = e();
        for (int i = width-1; i >= 0; i--) Tree[i] = op(Tree[i<<1], Tree[i<<1|1]);
    }
    Segtree(std::vector<S> v) {
        n = v.size();
        while (width < n) depth++, width <<= 1;
        Tree.resize(width * 2);
        for (int i = width; i < width * 2; i++) Tree[i] = (i < width + n ? v[i - width] : e());
        for (int i = width-1; i >= 0; i--) Tree[i] = op(Tree[i<<1], Tree[i<<1|1]);
    }
    void set(int pos, S val) {
        pos += width;
        Tree[pos] = val;
        for (int c = (pos >> 1); c > 0; c >>= 1) Tree[c] = op(Tree[c<<1], Tree[c<<1|1]);
        return;
    }
    S get(int pos) { return Tree[width + pos]; }
    S all_prod() { return Tree[1]; }
    S prod(int l, int r) {
        S x = e(), y = e();
        l += width, r += width;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) x = op(x, Tree[l++]);
            if (r & 1) y = op(Tree[--r], y);
        }
        return op(x, y);
    }
};
