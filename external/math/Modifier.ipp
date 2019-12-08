/*
                    ___   __  __       _ __          __
                   /   | / /_/ /______(_) /_  __  __/ /____
                  / /| |/ __/ __/ ___/ / __ \/ / / / __/ _ \
                 / ___ / /_/ /_/ /  / / /_/ / /_/ / /_/  __/
                /_/  |_\__/\__/_/  /_/_.___/\__,_/\__/\___/
*/


template <typename T>
static T _compute_attribute_value(T base, Modifier<T> const & modifs)
{
	double flat = 0.0;
	double ratio = 1.0;
	for (auto it = modifs.cbegin(); it != modifs.cend(); ++it) {
		if (it->type() == Modifier<T>::Flat)
			flat += static_cast<double>(it->value());
		else
			ratio += static_cast<double>(it->value());
	}
	double result = (static_cast<double>(base) + flat) * ratio;
	return (T(result));
}

template <typename T>
Attribute<T>::~Attribute()
{
	for (auto it = _auto_removers.begin(); it != _auto_removers.end(); ++it)
		it->_attr = nullptr;
}

// template <typename T>
// Attribute<T>::Attribute(Attribute<T> const & oth)
// : _base_attribute(oth._base_attribute),
//   _computed_attribute(oth._computed_attribute),
//   _modifiers(oth._modifiers),
//   _auto_removers()
// {}

template <typename T>
Attribute<T>::Attribute(Attribute<T> && oth)
: _base_attribute(oth._base_attribute),
  _computed_attribute(oth._computed_attribute),
  _modifiers(std::move(oth._modifiers)),
  _auto_removers(std::move(oth._auto_removers))
{
	for (auto it = _auto_removers.begin(); it != _auto_removers.end(); ++it)
		it->_attr = this;
}

// template <typename T>
// Attribute<T> & Attribute<T>::operator=(Attribute<T> const & oth)
// {
// 	if (this != &oth) {
// 		_base_attribute = oth._base_attribute;
// 		_computed_attribute = oth._computed_attribute;
// 		_modifiers = oth._modifiers;
// 	}
// 	return (*this);
// }

template <typename T>
Attribute<T> & Attribute<T>::operator=(Attribute<T> && oth)
{
	if (this != &oth) {
		_base_attribute = oth._base_attribute;
		_computed_attribute = oth._computed_attribute;
		_modifiers = std::move(oth._modifiers);
		_auto_removers = std::move(oth._auto_removers);
		for (auto it = _auto_removers.begin(); it != _auto_removers.end(); ++it)
			it->_attr = this;
	}
	return (*this);
}

template <typename T>
Attribute<T>::Attribute(T v)
: _base_attribute(v),
  _computed_attribute(v),
  _modifiers(),
  _auto_removers()
{}

template <typename T>
T Attribute<T>::base_attribute() const
{
	return (_base_attribute);
}

template <typename T>
T & Attribute<T>::base_attribute()
{
	return (_base_attribute);
}

template <typename T>
typename Attribute<T>::Container_t const & Attribute<T>::modifiers() const
{
	return (_modifiers);
}

template <typename T>
typename Attribute<T>::Container_t & Attribute<T>::modifiers()
{
	return (_modifiers);
}

template <typename T>
T Attribute<T>::value() const
{
	return (_base_attribute);
}

template <typename T>
typename Attribute<T>::Modifier_id Attribute<T>::add_modifier(Modifier_t const & m)
{
	_modifiers.push_front(m);
	return (_modifiers.begin());
}

template <typename T>
typename Attribute<T>::Modifier_id Attribute<T>::add_modifier(Modifier_t && m)
{
	_modifiers.push_front(m);
	return (_modifiers.begin());
}

template <typename T>
void Attribute<T>::del_modifier(Modifier_id it)
{
	_modifiers.erase(it);
}

template <typename T>
void Attribute<T>::replace(Modifier_id id, Modifier_t const & m)
{
	*id = m;
}

template <typename T>
void Attribute<T>::replace(Modifier_id id, Modifier_t && m)
{
	*id = m;
}

template <typename T>
AutoRemover_Modifier<T> Attribute<T>::add_modifier_auto(Modifier_t const & m)
{
	AutoRemover_Modifier<T> res;
	res._attr = this;
	res._modifier_id = add_modifier(m);
	return (res);
}

template <typename T>
AutoRemover_Modifier<T> Attribute<T>::add_modifier_auto(Modifier_t && m)
{
	AutoRemover_Modifier<T> res;
	res._attr = this;
	res._modifier_id = add_modifier(m);
	return (res);
}



/*
                     __  ___          ___ _____
                    /  |/  /___  ____/ (_) __(_)__  _____
                   / /|_/ / __ \/ __  / / /_/ / _ \/ ___/
                  / /  / / /_/ / /_/ / / __/ /  __/ /
                 /_/  /_/\____/\__,_/_/_/ /_/\___/_/
*/


template <typename T>
Modifier<T>::Modifier(Type t, T v)
: _type(t),
  _value(v)
{}

template <typename T>
typename Modifier<T>::Type Modifier<T>::type() const
{
	return (_type);
}

template <typename T>
T Modifier<T>::value() const
{
	return (_value);
}







/*
    ___         __        ____                                        __  ___          ___ _____
   /   | __  __/ /_____  / __ \___  ____ ___  ____ _   _____  _____  /  |/  /___  ____/ (_) __(_)__  _____
  / /| |/ / / / __/ __ \/ /_/ / _ \/ __ `__ \/ __ \ | / / _ \/ ___/ / /|_/ / __ \/ __  / / /_/ / _ \/ ___/
 / ___ / /_/ / /_/ /_/ / _, _/  __/ / / / / / /_/ / |/ /  __/ /    / /  / / /_/ / /_/ / / __/ /  __/ /
/_/  |_\__,_/\__/\____/_/ |_|\___/_/ /_/ /_/\____/|___/\___/_/____/_/  /_/\____/\__,_/_/_/ /_/\___/_/
                                                            /_____/
*/


template <typename T>
AutoRemover_Modifier<T>::AutoRemover_Modifier(AutoRemover_Modifier<T> && oth)
: _attr(oth._attr),
  _modifier_id(oth._modifier_id)
{
	oth._attr = nullptr;
	if (!_attr) {
		auto found = std::find(_attr->_auto_removers.begin(),
		                       _attr->_auto_removers.end(),
		                       &oth);
		assert(found != _attr->_auto_removers.end());
		*found = this;
	}
}

template <typename T>
AutoRemover_Modifier<T>::~AutoRemover_Modifier()
{
	remove();
}

template <typename T>
AutoRemover_Modifier<T> & AutoRemover_Modifier<T>::operator=(AutoRemover_Modifier<T> && oth)
{
	if (&oth != this) {
		_attr = oth._attr;
		_modifier_id = oth._modifier_id;

		oth._attr = nullptr;
		if (!_attr) {
			auto found = std::find(_attr->_auto_removers.begin(),
			                       _attr->_auto_removers.end(),
			                       &oth);
			assert(found != _attr->_auto_removers.end());
			*found = this;
		}
	}
	return (*this);
}

template <typename T>
AutoRemover_Modifier<T>::operator bool () const
{
	return (_attr != nullptr);
}

template <typename T>
bool AutoRemover_Modifier<T>::is_valid() const
{
	return (_attr != nullptr);
}

template <typename T>
Modifier<T> const & AutoRemover_Modifier<T>::operator*() const
{
	assert(_attr);
	return (*_modifier_id);
}

template <typename T>
Modifier<T> & AutoRemover_Modifier<T>::operator*()
{
	assert(_attr);
	return (*_modifier_id);
}

template <typename T>
Modifier<T> const & AutoRemover_Modifier<T>::operator->() const
{
	assert(_attr);
	return (*_modifier_id);
}

template <typename T>
Modifier<T> & AutoRemover_Modifier<T>::operator->()
{
	assert(_attr);
	return (*_modifier_id);
}

template <typename T>
Modifier<T> const & AutoRemover_Modifier<T>::modifier() const
{
	assert(_attr);
	return (*_modifier_id);
}

template <typename T>
Modifier<T> & AutoRemover_Modifier<T>::modifier()
{
	assert(_attr);
	return (*_modifier_id);
}

template <typename T>
Attribute<T> const & AutoRemover_Modifier<T>::attribute() const
{
	assert(_attr);
	return (*_attr);
}

template <typename T>
Attribute<T> & AutoRemover_Modifier<T>::attribute()
{
	assert(_attr);
	return (*_attr);
}

template <typename T>
void AutoRemover_Modifier<T>::replace(Modifier<T> const & m)
{
	assert(_attr);
	_attr->replace(_modifier_id, m);
}

template <typename T>
void AutoRemover_Modifier<T>::replace(Modifier<T> && m)
{
	assert(_attr);
	_attr->replace(_modifier_id, m);
}

template <typename T>
void AutoRemover_Modifier<T>::remove()
{
	if (!_attr) {
		auto found = std::find(_attr->_auto_removers.begin(),
		                       _attr->_auto_removers.end(),
		                       this);
		assert(found != _attr->_auto_removers.end());
		_attr->_auto_removers.erase(found);
		_attr->del_modifier(_modifier_id);
	}
}
