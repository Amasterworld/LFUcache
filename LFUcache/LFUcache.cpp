//
//  LFUcache.cpp
//  LFUcache
//
//  Created by Tnguyen on 26.07.22.
//

#include "LFUcache.hpp"


    
    int LFUcache:: get(const int key){
        // if key is not present in cache
        if(u_m.count(key) == 0){
            return -1;
        }
        
        // if the key is found in u_m map, then remove it in freq_map by its frequency and iter
        // for example in freq_map =  <1 <1 2 3>>, now key ==2  that mean in u_m[2] ={?, 1, iter}
        
        freq_map[u_m[key].freq].erase(u_m[key].itr);
        //update the frequency  in u_m
        u_m[key].freq++;
        
        
         /*if all eles having min_freq are deleted, keep putting the new eles hence, should increase min_freq, in order to delete the eles having  new min_freq
         . that means if freq_map[min_freq].size() == 0≠
         */
        if (!freq_map[min_freq].size()){
            min_freq++;
        }
        
        //after deleting key (lines 39), now update its frequency and itself, note that  <int, list> that means all elements having the same frequency are added to the same list,  the closer to the top the more LRU elements(because of using emplace_back).
        
        /* if you want to make the back of the list to be LRU hence use emplace_front */
        freq_map[u_m[key].freq].emplace_back(key);
        u_m[key].itr = std::prev(freq_map[u_m[key].freq].end());
        //std::cout<<"key "<< key<<" freq "<<u_m[key].freq<<std::endl;
        return u_m[key].value;
               
    }
    
    void LFUcache:: put(const int& key, const int& value){
        constexpr int init_freq = 1;//
        if (m_cap <= 0){
            return;
        }
         // if the key is available in cache
        int curr_value = get(key);
        //std::cout<<"key "<<key<<" "<<value <<std::endl;
        if (curr_value != -1){
            // just update value, because update the its frequency and the others has done by get() method
            u_m[key].value = value;
            return;
        }
        // If the key is not present in cache, then check the current u_m size
        if(u_m.size() >= m_cap){
            /*freq_map[min_freq]access to the list<int>
             .front() return the top elements
             above we use emplace_back
             hence front() return the 1st element was inserted ->LRU with min_fr eq     */
            u_m.erase(freq_map[min_freq].front());
            /*also need to delete it in freq_map it is the 1st element of the list correspoding with  min_freq*/
            freq_map[min_freq].pop_front();
        }
        // when the key is not available in the cache
        // then add it with init_freq
        freq_map[init_freq].emplace_back(key);
        u_m[key].value = value;
        u_m[key].freq = init_freq;
        u_m[key].itr = std::prev(freq_map[init_freq].end());
        /* or we can,
         u_m[key] = {value, 1, std::priv(freq_map[1].end())}
         */
        
        // this key and value has the default min_freq
        min_freq = init_freq;
    }
    
    void LFUcache:: show(){
        for(auto&& [key, value] : u_m){
            std::cout<<"key "<<key<<" : "<<"value " <<value.value <<std::endl;
        }
    }

    void LFUcache::clear(){
    u_m.clear();
    freq_map.clear();
        
    }

    std::size_t LFUcache::cacheSize() const{
        
        return u_m.size(); //O(1)
    }


void LFUcache::setNewCapacity(const int new_cap){
    // if doest not change anything hence return
    if (new_cap == m_cap){
        return;
    }
    
    if (m_cap <new_cap){
        m_cap = new_cap;
        return;
    }
    
    /*disallow to put 0 or negativ new_cap*/
    if (new_cap <= 0){
        //throw ZeroCapacityException();
        throw ZeroCapacityException() ;
    }
    
    /*to solve the problem: new_cap , m_cap carefully we also should move the res = m_cap - new_cap, LFU in a cache and move them to the file (or delete),  m*/
    size_t numItemsRem = m_cap - new_cap;
    for(int i = 0; i < numItemsRem; ++i){
        remOldestEle();
        
    }
    
    m_cap = new_cap;
}

void LFUcache::remOldestEle(){
           
        if(freq_map[min_freq].size() > 0)
            {
              
                u_m.erase(freq_map[min_freq].front());
            
                freq_map[min_freq].pop_front();
                
        }
        else{
            min_freq++;
            u_m.erase(freq_map[min_freq].front());
            freq_map[min_freq].pop_front();
        }
    }
    

