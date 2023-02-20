// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/serialization.hpp>

struct X
{
    int a, b;

    template<class Ar> void serialize( Ar& ar, unsigned /*v*/ )
    {
        ar & boost::core::make_nvp( "a", a );
        ar & boost::core::make_nvp( "b", b );
    }
};

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/core/lightweight_test.hpp>
#include <sstream>
#include <string>

int main()
{
    std::ostringstream os;

    X x1 = { 7, 11 };

    {
        boost::archive::xml_oarchive ar( os );
        ar << boost::core::make_nvp( "x1", x1 );
    }

    std::string s = os.str();

    X x2 = { 0, 0 };

    {
        std::istringstream is( s );
        boost::archive::xml_iarchive ar( is );
        ar >> boost::make_nvp( "x2", x2 );
    }

    BOOST_TEST_EQ( x1.a, x2.a );
    BOOST_TEST_EQ( x1.b, x2.b );

    return boost::report_errors();
}