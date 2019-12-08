#ifndef UTILITY_MODIFIER_HH__
#define UTILITY_MODIFIER_HH__


#include <list>


namespace math {
	template <typename T> class Modifier;	
	template <typename T> class AutoRemover_Modifier;
} // math



namespace math
{


/**
 * @brief Attribute can have multiple modifier affecting his value.
 * @code{.cpp}
 * double flat = 0.0;
 * flat += accumulate_flat();
 * double ratio = 1.0;
 * ratio += accumulate_ratio();
 * return ((base + flat) * ratio);
 * @endcode
 * @see Modifier<T>
 */
template <typename T>
class Attribute
{
public:
	using type_t      = T;
	using Modifier_t  = Modifier<T>;
	using Container_t = std::list<Modifier<T>>;
	using Modifier_id = typename std::list<Modifier<T>>::iterator; //< used as key to remove a modifier

	Attribute() = default;
	~Attribute();

	Attribute(Attribute<T> &&);

	Attribute<T> & operator=(Attribute<T> &&);

	explicit Attribute(T);

	T base_attribute() const;
	T & base_attribute();

	Container_t const & modifiers() const;
	Container_t & modifiers();

	T value() const;

	Modifier_id add_modifier(Modifier_t const &);
	Modifier_id add_modifier(Modifier_t &&);

	void del_modifier(Modifier_id);

	void replace(Modifier_id, Modifier_t const &);
	void replace(Modifier_id, Modifier_t &&);

	AutoRemover_Modifier<T> add_modifier_auto(Modifier_t const &);
	AutoRemover_Modifier<T> add_modifier_auto(Modifier_t &&);

private:
	Attribute(Attribute<T> const &)                = delete;
	Attribute<T> & operator=(Attribute<T> const &) = delete;

	T _base_attribute;
	T _computed_attribute;
	Container_t _modifiers;
	std::list<AutoRemover_Modifier<T> *> _auto_removers;

	friend class AutoRemover_Modifier<T>;
};

/**
 * @brief Modifier can be applied to an Attribute
 * @detail Can be flat modifier, or by ratio.
 * @see Attribute<T>
 */
template <typename T>
class Modifier
{
public:
	enum Type { Flat, Ratio };

	Modifier()                    = default;
	Modifier(Modifier<T> const &) = default;
	Modifier(Modifier<T> &&)      = default;
	~Modifier()                   = default;

	Modifier<T> & operator=(Modifier<T> const &) = default;
	Modifier<T> & operator=(Modifier<T> &&)      = default;

	Modifier(Type, T);

	Type type() const;
	T value() const;

private:
	Type _type = Flat;
	T _value = 0;
};

/**
 * @brief Manage to remove modifier of his attribute when he died
 * @todo If Attribute<T> become invalid, segfault.
 * @bug If Attribute<T> become invalid, segfault.
 * 
 * @tparam T [description]
 */
template <typename T>
class AutoRemover_Modifier
{
public:

	AutoRemover_Modifier() = default;

	AutoRemover_Modifier(AutoRemover_Modifier<T> &&);
	~AutoRemover_Modifier();

	AutoRemover_Modifier<T> & operator=(AutoRemover_Modifier<T> &&);

	operator bool () const;
	bool is_valid() const;

	Modifier<T> const & operator*() const;
	Modifier<T> & operator*();

	Modifier<T> const & operator->() const;
	Modifier<T> & operator->();

	Modifier<T> const & modifier() const;
	Modifier<T> & modifier();

	Attribute<T> const & attribute() const;
	Attribute<T> & attribute();

	void replace(Modifier<T> const &);
	void replace(Modifier<T> &&);

	void remove();

private:
	AutoRemover_Modifier(AutoRemover_Modifier<T> const &)                = delete;
	AutoRemover_Modifier<T> & operator=(AutoRemover_Modifier<T> const &) = delete;

	Attribute<T> * _attr = nullptr;
	typename Attribute<T>::Modifier_id _modifier_id;

	friend class Attribute<T>;
};


#include "Modifier.ipp"


} // math



#endif // UTILITY_MODIFIER_HH__
