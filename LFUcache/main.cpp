/*

 
 Design and implement a data structure for a Least Frequently Used (LFU) cache.
 Implement the LFUCache class:
    
    -LFUCache(int capacity) Initializes the object with the capacity of the data structure.
    -int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
    -void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.

 To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

 When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

 The functions get and put must each run in O(1) average time complexity.
 
  Created by TNguyen on 22.07.22.
*/

#include "LFUcache.hpp"
#import <gtest/gtest.h>

class LFUCacheTests : public ::testing::Test {
protected:

    LFUCacheTests() = default;
    ~LFUCacheTests() override = default;
    void SetUp() override {}
    void TearDown() override {}

};



   

    TEST_F(LFUCacheTests, TestClear) {

        LFUcache  testCache(2);

        testCache.put(1, 10);
        testCache.put(2, 20);
        ASSERT_EQ(testCache.get(1), 10);
        ASSERT_EQ(testCache.get(2), 20);
        testCache.clear();
        ASSERT_TRUE(testCache.get(1) == -1);
        ASSERT_EQ(testCache.cacheSize(), 0);
        
        testCache.setNewCapacity(3);
        testCache.put(1, 10);
        testCache.put(2, 20);
        testCache.put(3, 30);
        
        ASSERT_EQ(testCache.cacheSize(), 3);
    }

TEST_F(LFUCacheTests, TestPutLogic) {
    
    //LFUcache::LFUcache<int, int> testCache(3); // keep it here for future when implement a template
    LFUcache  testCache(2);

    testCache.put(1, 10);
    testCache.put(1, 100);
    testCache.put(2, 1);
    testCache.put(2, 2);
    testCache.get(1); // to make sure that the frequency of key == 1 is highest now, == (3)
    testCache.put(4, 3); // key == 2 should be deleted
    ASSERT_EQ(testCache.get(2), -1); // == -1 that means, it doest not exist in the map
    ASSERT_EQ(testCache.get(1), 100);
    ASSERT_EQ(testCache.get(4), 3);
    
    testCache.clear();
    //test when the both keys have the same frequency but the the LRU should be deleted to insert the new key
    
    testCache.put(10, 2);
    testCache.put(10, 3);
    testCache.put(2, 100);
    testCache.put(2, 200);
    // the both keys = 10 and 2 are the same frequency now
    testCache.get(2); // but the key == 2 is called that means it is used (+ freq)
    
    testCache.put(50, 70); // the key == 50 is inserted then  the key = 10 should be deleted because it is LRU
    
    ASSERT_EQ(testCache.cacheSize(), 2); // assert that cache size ==2
    ASSERT_TRUE(testCache.get(10) == -1); // should return true because key == 10 is deleted
    ASSERT_EQ(testCache.get(2), 200);   //
    ASSERT_EQ(testCache.get(50), 70);
        
}
TEST_F(LFUCacheTests, TestCapacityException) {
    // test with 10 element and min_freq = 1
    LFUcache  testCache(10);
    
    testCache.put(10, 2);
    testCache.put(9, 3);
    testCache.put(8, 100);
    testCache.put(7, 200);
    testCache.put(6, 2);
    testCache.put(5, 3);
    testCache.put(4, 100);
    testCache.put(3, 200);
    testCache.put(2, 2);
    testCache.put(1, 3);
    
    ASSERT_EQ(testCache.cacheSize(), 10);
    
    testCache.setNewCapacity(7);
    
    ASSERT_EQ(testCache.cacheSize(), 7);
    
    //// test with 10 elements and  2 min_freq = 1 and the other elements > 1 so min_freq should increase in order to keep deleting
    // we do not clear the  the cache, insead using get method to increase their frequency, now from 1  to 5 freq ==2, 6 and 7 is 1, but key ==5 should be deleted, if we set new cap = 4(reduce 3 elements), because key ==5 is LRU
   
      
    testCache.get(5);
    testCache.get(4);
    testCache.get(3);
    testCache.get(2);
    testCache.get(1);
    testCache.setNewCapacity(4);
    ASSERT_EQ(testCache.cacheSize(), 4);
       
    
    ASSERT_THROW(testCache.setNewCapacity(-1), ::ZeroCapacityException);
                
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
