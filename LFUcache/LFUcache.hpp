//
//  LFUcache.hpp
//  LFUcache
//
//  Created by Thao Nguyen on 26.07.22.
//

#ifndef LFUcache_hpp
#define LFUcache_hpp


#include <iostream>
#include <unordered_map>
#include <list>
#include "Exception.h"
class LFUcache{
  
private:
    struct Node{
        int value;
        int freq;
        std::list<int>::iterator itr; // store addresss
    };
    
    int m_cap{};
    int min_freq{};
    std::unordered_map<int, Node> u_m;
    std::unordered_map<int, std::list<int> > freq_map; // store the frequency of the list of elements e.g. <1 <2,3,4>> -> elements 2 3 4 appear 1 time
    
    
public:
    //constructor
    LFUcache(int capacity): m_cap(capacity){}
    
    
    /*Functions*/
    
    std::size_t cacheSize() const;
    
    int get(const int key);
    
    void put(const int& key, const int& value);
    void clear();
    
    void show();
    void setNewCapacity(const int new_cap);
    void remOldestEle();
      
};
#endif /* LFUcache_hpp */
