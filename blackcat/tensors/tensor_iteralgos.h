
	self_type& fill(value_type value) {
		bc::algorithms::fill(
				this->get_stream(), cw_begin(), cw_end(), value);
		return *this;
	}

	self_type& zero() { return fill(0); }
	self_type& ones() { return fill(1); }

	template<class Function>
	void for_each(Function func) const {
		*this = this->un_expr(func);
	}

	template<class Function>
	void for_each(Function func) {
		*this = this->un_expr(func);
	}

	self_type& sort()
	{
		bc::algorithms::sort(
				this->get_stream(), cw_begin(), cw_end());
		return *this;
	}

	void randomize(value_type lb=0, value_type ub=1)
	{
		static_assert(
				expression_type::tensor_iterator_dim == 0 ||
				expression_type::tensor_iterator_dim == 1,
				"randomize not available to non-continuous tensors");

		using Random = bc::random::Random<system_tag>;
		Random::randomize(
				this->get_stream(),
				this->expression_template(), lb, ub);
	}

#define BC_FORWARD_ITER(suffix, iter, access)              \
	auto suffix##iter() const {                            \
		return iterators::iter_##suffix##iter(access);     \
	}                                                      \
	auto suffix##iter() {                                  \
		return iterators::iter_##suffix##iter(access);     \
	}                                                      \
	auto suffix##c##iter() const {                         \
		return iterators::iter_##suffix##iter(access);     \
	}                                                      \
	auto suffix##r##iter() const {                         \
		return iterators::iter_##suffix##r##iter(access);  \
	}                                                      \
	auto suffix##r##iter() {                               \
		return iterators::iter_##suffix##r##iter(access);  \
	}                                                      \
	auto suffix##cr##iter() const {                        \
		return iterators::iter_##suffix##r##iter(access);  \
	}

	BC_FORWARD_ITER(,begin, *this)
	BC_FORWARD_ITER(,end, *this)
	BC_FORWARD_ITER(cw_, begin, this->expression_template())
	BC_FORWARD_ITER(cw_, end, this->expression_template())

#undef BC_FORWARD_ITER


#define BC_ITERATOR_DEF(suffix, iterator_name, begin_func, end_func)     \
                                                                         \
    template<class Tensor>                                               \
    struct iterator_name {                                               \
                                                                         \
        using size_t = bc::size_t;                                       \
        Tensor& tensor;                                                  \
                                                                         \
        using begin_t = decltype(tensor.begin_func ());                  \
        using end_t = decltype(tensor.end_func ());                      \
                                                                         \
        begin_t m_begin = tensor.begin_func();                           \
        end_t m_end = tensor.end_func();                                 \
                                                                         \
        iterator_name(Tensor& tensor) :                                  \
                tensor(tensor) {}                                        \
                                                                         \
        iterator_name(Tensor& tensor, size_t start):                     \
            tensor(tensor)                                               \
        {                                                                \
            m_begin += start;                                            \
        }                                                                \
                                                                         \
        iterator_name(Tensor& tensor, size_t start, size_t end):         \
                tensor(tensor)                                           \
        {                                                                \
            m_begin += start;                                            \
            m_end = end;                                                 \
        }                                                                \
                                                                         \
        auto begin() {                                                   \
            return m_begin;                                              \
        }                                                                \
                                                                         \
        const begin_t& cbegin() const {                                  \
            return m_begin;                                              \
        }                                                                \
                                                                         \
        const end_t& end() const {                                       \
            return m_end;                                                \
        }                                                                \
    };                                                                   \
                                                                         \
                                                                         \
template<class... params> auto suffix##iter(params... ps) const {        \
    return iterator_name<const self_type>(*this, ps...);                 \
}                                                                        \
                                                                         \
template<class... params> auto suffix##iter(params... ps) {              \
    return iterator_name<self_type>(*this, ps...);                       \
}                                                                        \
                                                                         \
template<class... params> auto suffix##const_iter(params... ps) const {  \
    return iterator_name<const self_type>(*this, ps...);                 \
}                                                                        \

BC_ITERATOR_DEF(,nd_iterator_type, begin, end)
BC_ITERATOR_DEF(reverse_, nd_reverse_iterator_type, rbegin, rend)
BC_ITERATOR_DEF(cw_, cw_iterator_type, cw_begin, cw_end)
BC_ITERATOR_DEF(cw_reverse_, cw_reverse_iterator_type, cw_rbegin, cw_rend)

#undef BC_ITERATOR_DEF