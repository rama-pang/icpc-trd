#define W(f) apply([](auto&&... a) { return f; }, i)
#define D(x) W(iterator<decltype(x(a))...>({x(a)...}))
template <class... A>
struct zip_view : R::view_interface<zip_view<A...>> {
  template <class... B> struct iterator {
    tuple<B...> i;
    using iterator_category = input_iterator_tag;
    using value_type = tuple<R::range_value_t<A>...>;
    using reference = tuple<R::range_reference_t<A>...>;
    using difference_type = ptrdiff_t;
    iterator& operator++() { W(((++a), ...)); return *this; }
    void operator++(int) { ++*this; }
    reference operator*() const { return W(reference(*a...)); }
    bool operator==(auto&& o) const {
      return [&]<size_t... I>(index_sequence<I...>) {
        return ((get<I>(i) == get<I>(o.i)) | ...);
      }(index_sequence_for<B...>{});
    } };
  auto begin() { return D(R::begin); }
  auto end() { return D(R::end); }
  zip_view(A&&... a) : i(forward<A>(a)...) {}
  tuple<A...> i; };
#undef W
#undef D
template <R::input_range... A>
auto zip(A&&... a) {
  return zip_view<A...>(forward<A>(a)...);
}
template <R::input_range A>
auto enumerate(A&& a) {
  return zip(V::iota(0), forward<A>(a));
}