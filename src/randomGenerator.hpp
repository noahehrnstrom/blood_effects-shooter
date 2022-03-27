#ifndef randomGenerator_hpp
#define randomGenerator_hpp

#include <random>
#define PI 3.14159265359

namespace randomGenerator
{
    template<typename T>
    T getRandom(int min, int max)
    {
        std::random_device rng;

        std::mt19937 dev( rng() );
        
        std::uniform_int_distribution<> rand(min, max);
        
        return rand(rng);
    }
};

#endif /* randomGenerator_hpp */
