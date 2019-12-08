


//     __    _       __  __    ____    ________                                       __
//    / /   (_)___ _/ /_/ /_  /  _/___/ / ____/___  ____ ___  ____  ____ __________ _/ /_____  _____
//   / /   / / __ `/ __/ __ \ / // __  / /   / __ \/ __ `__ \/ __ \/ __ `/ ___/ __ `/ __/ __ \/ ___/
//  / /___/ / /_/ / /_/ / / // // /_/ / /___/ /_/ / / / / / / /_/ / /_/ / /  / /_/ / /_/ /_/ / /
// /_____/_/\__, /\__/_/ /_/___/\__,_/\____/\____/_/ /_/ /_/ .___/\__,_/_/   \__,_/\__/\____/_/
//         /____/                                         /_/


template <class T>
bool LigthIdComparator<T>::operator()(T const & a, T const & b) const
{
	return (a.id() < b.id());
}

template <class T>
bool LigthIdComparator<T>::operator()(T const & a, uuid_t b) const
{
	return (a.id() < b);
}

template <class T>
bool LigthIdComparator<T>::operator()(uuid_t a, T const & b) const
{
	return (a < b.id());
}

template <class T>
bool LigthIdComparator<T>::operator()(uuid_t a, uuid_t b) const
{
	return (a < b);
}


template <class T>
bool LigthIdComparator<T*>::operator()(T const * a, T const * b) const
{
	return (a->id() < b->id());
}

template <class T>
bool LigthIdComparator<T*>::operator()(T const * a, uuid_t b) const
{
	return (a->id() < b);
}

template <class T>
bool LigthIdComparator<T*>::operator()(uuid_t a, T const * b) const
{
	return (a < b->id());
}

template <class T>
bool LigthIdComparator<T*>::operator()(uuid_t a, uuid_t b) const
{
	return (a < b);
}


//                                   _     __
//                      __  ____  __(_)___/ /
//                     / / / / / / / / __  /
//                    / /_/ / /_/ / / /_/ /
//                    \__,_/\__,_/_/\__,_/
//                    


template <class Tag, class T>
uuid<Tag, T> uuid<Tag, T>::no_id() noexcept
{
	return (uuid<Tag, T>((type_t)(0)));
}

template <class Tag, class T>
uuid<Tag, T>::uuid(type_t i) noexcept
: _id(i)
{}

template <class Tag, class T>
typename uuid<Tag, T>::type_t uuid<Tag, T>::id() const noexcept
{
	return (_id);
}

template <class Tag, class T>
uuid<Tag, T>::operator type_t () const noexcept
{
	return (id());
}

template <class Tag, class T>
bool uuid<Tag, T>::valid() const noexcept
{
	return (_id != (type_t)(0));
}

template <class Tag, class T>
uuid<Tag, T>::operator bool () const noexcept
{
	return (valid());
}

template <class Tag, class T>
void uuid<Tag, T>::reset() noexcept
{
	_id = (type_t)(0);
}

template <class Tag, class T>
bool uuid<Tag, T>::operator==(uuid<Tag, T> const & o) const noexcept
{
	return(_id == o._id);
}

template <class Tag, class T>
bool uuid<Tag, T>::operator!=(uuid<Tag, T> const & o) const noexcept
{
	return(_id != o._id);
}

template <class Tag, class T>
bool uuid<Tag, T>::operator> (uuid<Tag, T> const & o) const noexcept
{
	return(_id >  o._id);
}

template <class Tag, class T>
bool uuid<Tag, T>::operator< (uuid<Tag, T> const & o) const noexcept
{
	return(_id <  o._id);
}

template <class Tag, class T>
bool uuid<Tag, T>::operator>=(uuid<Tag, T> const & o) const noexcept
{
	return(_id >= o._id);
}

template <class Tag, class T>
bool uuid<Tag, T>::operator<=(uuid<Tag, T> const & o) const noexcept
{
	return(_id <= o._id);
}


//                _     __                                      __
//   __  ____  __(_)___/ /    ____ ____  ____  ___  _________ _/ /_____  _____
//  / / / / / / / / __  /    / __ `/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/
// / /_/ / /_/ / / /_/ /    / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /
// \__,_/\__,_/_/\__,_/_____\__, /\___/_/ /_/\___/_/   \__,_/\__/\____/_/
//                   /_____/____/
// 


template <class UUID>
UUID uuid_generator<UUID>::gen() noexcept
{
	return (UUID(++_last_uuid));
}

template <class UUID>
UUID uuid_generator<UUID>::gen(type_t i, std::nothrow_t) noexcept
{
	if (_last_uuid < i)
		_last_uuid = i;
	return (UUID(i));
}

template <class UUID>
UUID uuid_generator<UUID>::gen(type_t i)
{
	if (_last_uuid < i)
		_last_uuid = i;
	else
		throw std::out_of_range("Id already used.");			
	return (UUID(i));
}

template <class UUID>
UUID uuid_generator<UUID>::operator() () noexcept
{
	return (gen());
}

template <class UUID>
UUID uuid_generator<UUID>::operator () (type_t i) noexcept
{
	return (gen(i));
}

template <class UUID>
UUID uuid_generator<UUID>::operator () (type_t i, std::nothrow_t) noexcept
{
	return (gen(i, std::nothrow_t()));
}

template <class UUID>
typename uuid_generator<UUID>::type_t uuid_generator<UUID>::last() const noexcept
{
	return (_last_uuid);
}

template <class UUID>
void uuid_generator<UUID>::set_last(type_t i) noexcept
{
	_last_uuid = i;
}

template <class UUID>
bool uuid_generator<UUID>::set_or_throw(type_t i)
{
	if (_last_uuid <= i) {
		_last_uuid = i;
		return (true);
	}
	throw std::out_of_range("Id already used.");
	return (false);
}

template <class UUID>
bool uuid_generator<UUID>::set_or_throw(type_t i, std::nothrow_t) noexcept
{
	if (_last_uuid <= i) {
		_last_uuid = i;
		return (true);
	}
	return (false);
}
