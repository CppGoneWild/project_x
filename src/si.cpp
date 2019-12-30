#include "si.hh"



////////////////////////////////////////////////////////////////////////////////
/////                                 angle                                /////
////////////////////////////////////////////////////////////////////////////////



template <>
si::radians si::si_cast<si::radians, float, si::degree_tag, std::ratio<1>>(si::degrees s)
{
	return (radians(s.count() * M_PI / 180.0));
}

template <>
si::degrees si::si_cast<si::degrees, float, si::radian_tag, std::ratio<1>>(si::radians s)
{
	return (degrees(s.count() * 180.0 / M_PI));
}



////////////////////////////////////////////////////////////////////////////////
/////                         angular speed                                /////
////////////////////////////////////////////////////////////////////////////////



template <>
si::rad_per_second si::si_cast<si::rad_per_second, float, si::deg_speed_tag, std::ratio<1>>(si::deg_per_second s)
{
	return (rad_per_second(s.count() * M_PI / 180.0));
}

template <>
si::deg_per_second si::si_cast<si::deg_per_second, float, si::rad_speed_tag, std::ratio<1>>(si::rad_per_second s)
{
	return (deg_per_second(s.count() * 180.0 / M_PI));
}


////////////////////////////////////////////////////////////////////////////////
/////                              position                                /////
////////////////////////////////////////////////////////////////////////////////



// cast from polar/carthesian to polar/carthesian



template <>
si::carth_coord si::si_cast<si::carth_coord, si::polar_coord::type_t, si::polar_coord::tag_t, si::polar_coord::ratio_t>(si::polar_coord s)
{
	carth_coord res(to_carthesian<si::carth_coord::type_t::type_t>(s.count()));
	return (res);
}

template <>
si::polar_coord si::si_cast<si::polar_coord, si::carth_coord::type_t, si::carth_coord::tag_t, si::carth_coord::ratio_t>(si::carth_coord s)
{
	assert(false);

	polar_coord res(to_polar<si::polar_coord::type_t::rtype_t, si::polar_coord::type_t::atype_t>(s.count()));
	return (res);
}
