#ifndef UTILITY_UUID_HH__
#define UTILITY_UUID_HH__


#include <cstdint>    // std:uint64_t
#include <stdexcept>  // std::out_of_range
#include <new>        // std::nothrow_t


namespace utility {
	template <class UUID> class uuid_generator;
} // utility


namespace utility
{


template <class T>
struct LigthIdComparator
{
		using is_transparent = void;
		using uuid_t = typename T::uuid;

		bool operator()(T const & a, T const & b) const;
		bool operator()(T const & a, uuid_t b) const;
		bool operator()(uuid_t a, T const & b) const;
		bool operator()(uuid_t a, uuid_t b) const;
};

template <class T>
struct LigthIdComparator<T*>
{
		using is_transparent = void;
		using uuid_t = typename T::uuid;

		bool operator()(T const * a, T const * b) const;
		bool operator()(T const * a, uuid_t b) const;
		bool operator()(uuid_t a, T const * b) const;
		bool operator()(uuid_t a, uuid_t b) const;
};



//                                   _     __
//                      __  ____  __(_)___/ /
//                     / / / / / / / / __  /
//                    / /_/ / /_/ / / /_/ /
//                    \__,_/\__,_/_/\__,_/
//                    


/**
 * @brief Scopped id type, associated with a type.
 * 
 * This class represent a simple ID. The Tag associated with it allow
 * to restrict cross usage of ID. Specificaly, uuid width different Tag can't
 * be mixed.
 * 
 * @code{.cpp}
 * uuid<A> a;
 * uuid<B> b;
 * 
 * a = b; // compilation error.
 * @endcode
 * 
 * To construct an ID, you must use uuid_generator.
 *
 * @note An uuid set to 0 is an invalid or unsetted ID.
 * 
 * @tparam Tag To differienciate between id type.
 * @tparam T   Internal type for id representation.
 * 
 * @see uuid_generator
 */
template <class Tag, class T = std::uint64_t>
class uuid
{
public:
	using tag_t  = Tag;
	using type_t = T;

	/**
	 * @brief To get the default ID.
	 * @bug Find a way to make this a static value, not a function.
	 */
	static uuid<Tag, T> no_id() noexcept;

	///@name Default ctor/dtor.
	/// Default constructible, copyable, movable, assignable and destructible.
	///@{
	explicit uuid() noexcept                     = default;
	uuid(uuid<Tag, T> const & oth) : _id(oth._id) {}
	uuid(uuid<Tag, T> &&) noexcept               = default;
	~uuid() noexcept                             = default;

	uuid<Tag, T> & operator=(uuid<Tag, T> const &) noexcept = default;
	uuid<Tag, T> & operator=(uuid<Tag, T> &&) noexcept      = default;
	///@}

	/// Used by uuid_generator.
	explicit uuid(type_t i) noexcept;

	///@name internal value
	/// To get the id as the internal type. Read only.
	///@{
	type_t id() const noexcept;
	explicit operator type_t () const noexcept;
	///@}


	///@name validity
	///@details An ID is valid if not 0. 
	///@{
	bool valid() const noexcept;
	explicit operator bool () const noexcept;
	/// Set the id to no_id.
	void reset() noexcept;
	///@}

	///@name comparaison
	///@{
	bool operator==(uuid<Tag, T> const & o) const noexcept;
	bool operator!=(uuid<Tag, T> const & o) const noexcept;
	bool operator> (uuid<Tag, T> const & o) const noexcept;
	bool operator< (uuid<Tag, T> const & o) const noexcept;
	bool operator>=(uuid<Tag, T> const & o) const noexcept;
	bool operator<=(uuid<Tag, T> const & o) const noexcept;
	///@}

private:

	type_t _id = (type_t)(0);

	friend class uuid_generator<uuid<Tag, T>>;
};


//                _     __                                      __
//   __  ____  __(_)___/ /    ____ ____  ____  ___  _________ _/ /_____  _____
//  / / / / / / / / __  /    / __ `/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/
// / /_/ / /_/ / / /_/ /    / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /
// \__,_/\__,_/_/\__,_/_____\__, /\___/_/ /_/\___/_/   \__,_/\__/\____/_/
//                   /_____/____/
// 


/**
 * @brief To generate uuid.
 * 
 * @tparam UUID Type of generated ID
 * 
 * @see uuid
 * 
 * @todo refactor and do not use std::nothrow
 */
template <class UUID>
class uuid_generator
{
public:
	using tag_t  = typename UUID::tag_t;
	using type_t = typename UUID::type_t;

	///@name Default ctor/dtor.
	/// Default constructible, copyable, movable, assignable and destructible.
	///@{
	explicit uuid_generator()                             = default;
	explicit uuid_generator(uuid_generator<UUID> const &) = default;
	explicit uuid_generator(uuid_generator<UUID> &&)      = default;
	~uuid_generator()                                     = default;

	/// Initialise at a specified last_id
	explicit uuid_generator(type_t last) noexcept : _last_uuid(last) {}

	uuid_generator<UUID> & operator=(uuid_generator<UUID> const &) = default;
	uuid_generator<UUID> & operator=(uuid_generator<UUID> &&)      = default;
	///@}


	///@name ID generation
	/// Generate uuid
	///@{

	/// Generate next uuid
	UUID gen() noexcept;

	/**
	 * @brief Generate a specific Id.
	 * 
	 * If i is greater than the last_id generated, update the internal counter.
	 */
	UUID gen(type_t i, std::nothrow_t) noexcept;

	/**
	 * @brief Generate a specific Id.
	 * 
	 * If i is greater than the last_id generated, update the internal counter.
	 * 
	 * @throw Throw std::out_of_range if internal counter is greater or equal to i.
	 */
	UUID gen(type_t i);

	/// Same as uuid_generator::gen
	UUID operator() () noexcept;

	/// Same as uuid_generator::gen(type_t)
	UUID operator() (type_t i) noexcept;

	/// Same as uuid_generator::gen(type_t, std::nothrow_t)
	UUID operator() (type_t i, std::nothrow_t) noexcept;
	///@}

	///@name Getter/Setter for Internal ID
	///@{
	/// Return internal last id.
	type_t last() const noexcept;

	/// Set internal last id in hard
	void set_last(type_t i) noexcept;

	/**
	 * @brief Set internal last id if the newer is greater or equal.
	 * @return true if internal counter is updated, false if i is already used.
	 * @throw Throw std::out_of_range if i is lesser than internal counter.
	 */
	bool set_or_throw(type_t i);

	/**
	 * @brief Set internal last id if the newer is greater or equal.
	 * @return true if internal counter is updated, false if i is already used.
	 */
	bool set_or_throw(type_t i, std::nothrow_t) noexcept;
	///@}

private:
	type_t _last_uuid = (type_t)(0);
};


#include "uuid.ipp"


} // utility


#endif // UTILITY_UUID_HH__
