#ifndef TESTS_BASE_H
#define TESTS_BASE_H

#include <iostream>
#include <stdexcept>
#include <string>

namespace ezPano{

#define EZPANO_ASSERT_EQUAL(x,y)                                  \
{                                                                 \
	if (x!=y)                                                     \
	{                                                             \ 
		throw std::runtime_error(std::string( __FILE__ )            \
							+ std::string(" : ")                    \
							+ std::to_string( __LINE__ )            \
							+ std::string(" in ")                   \
							+ std::string( __PRETTY_FUNCTION__ )    \
							+ std::string(" : ")                    \
							+ std::to_string((x))                 \
							+ std::string(" != ")                   \
							+std::to_string((y))                  \
		);                                                        \
	}                                                             \
}



#define EZPANO_ASSERT_THROW( condition )                             \
{                                                                   \
  if( !( condition ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
    );                                                              \
  }                                                                 \
}



#define EZPANO_EXPECT_EXCEPTION( expression, exception )             \
{                                                                   \
  try                                                               \
  {                                                                 \
    ( expression );                                                 \
  }                                                                 \
  catch( exception& e )                                             \
  {                                                                 \
  }                                                                 \
  catch( ... )                                                      \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
    );                                                              \
  }                                                                 \
}



#define EZPANO_TEST_BEGIN(name)                              \
{                                                            \
	std::cerr << "-- Running test \"" << name << "\"....";   \
}




#define EZPANO_TEST_END()       \
{                               \
	std::cerr << "finished\n";  \
}

}

#endif
