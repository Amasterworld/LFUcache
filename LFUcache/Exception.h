//
//  Exception.h
//  LFUcache
//
//  Created by Thao Nguyen on 26.07.22.
//

#ifndef Exception_h
#define Exception_h

#include <exception>
#include <string_view>


class BaseLRUCacheException: public std::exception{
private:
    std::string info_msg;
public:
    
    //constructor
    BaseLRUCacheException (std::string_view msg) : info_msg(msg){};
    
    /*virtual destructor to avoid Base * b = new Derived(); /../ delete b; ->destructor of class Base is called,
    -> then the instance of class Derived still exist -> mem leak
    
    */
    virtual ~BaseLRUCacheException() = default;
    
    virtual const char *what() const noexcept{
        return info_msg.c_str();
        
    }
};

class ZeroCapacityException : public BaseLRUCacheException{
    
private:
    std::string error_msg;
public:
    //constructor
    ZeroCapacityException() : BaseLRUCacheException("Attempt to give the size of a map to zero "){}
};

#endif /* Exception_h */
