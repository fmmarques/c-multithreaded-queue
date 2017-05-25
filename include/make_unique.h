#ifndef MAKE_UNIQUE_H_INCLUDED
#define MAKE_UNIQUE_H_INCLUDED

#include <memory>
#include <utility>
  
#if __cplusplus == 201402L // C++14

#else // C++11
namespace std
{

        template < typename T, typename... CONSTRUCTOR_ARGS >
        std::unique_ptr<T> make_unique( CONSTRUCTOR_ARGS&&... constructor_args )
        { return std::unique_ptr<T>( new T( std::forward<CONSTRUCTOR_ARGS>(constructor_args)... ) ); }

}
    #endif // __cplusplus == 201402L


#endif // MAKE_UNIQUE_H_INCLUDED 
