// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef P2RANDOM_H
#define P2RANDOM_H

#include <vector>
#include <string>
#include <cstdint>

class P2random {
public:
    static void initialize(uint32_t seed, uint32_t maxDist, uint32_t maxSpeed, uint32_t maxHealth);
    static uint32_t rand();

    static std::string getNextZombieName();
    static uint32_t getNextZombieDistance();
    static uint32_t getNextZombieSpeed();
    static uint32_t getNextZombieHealth();

    //Don't need to read further than this, unless you want to learn about
    //Mersenne Twister implementation
private:
    enum class GenState : char { GenName, GenDistance, GenSpeed, GenHealth };
    static GenState genState;
    static uint32_t zombieCounter;
    static uint32_t maxRandDist, maxRandSpeed, maxRandHealth;
    static std::vector<std::string> ZOMBIE_NAMES;
    static uint32_t getNextInt(uint32_t);

    /**
    * mt.h: Mersenne Twister header file
    *
    * Jason R. Blevins <jrblevin@sdf.lonestar.org>
    * Durham, March  7, 2007
    */

    /**
    * Mersenne Twister.
    *
    * M. Matsumoto and T. Nishimura, "Mersenne Twister: A
    * 623-dimensionally equidistributed uniform pseudorandom number
    * generator", ACM Trans. on Modeling and Computer Simulation Vol. 8,
    * No. 1, January pp.3-30 (1998).
    *
    * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html.
    */
    class MersenneTwister {
    public:
        MersenneTwister(void);
        ~MersenneTwister(void);

        // The copy constructor and operator=() should never be used.
        MersenneTwister(const MersenneTwister&) = delete;
        MersenneTwister &operator=(const MersenneTwister&) = delete;

        void init_genrand(uint32_t s);
        uint32_t genrand_uint32_t(void);

    private:
        static const uint32_t N = 624;
        static const uint32_t M = 397;
        // constant vector a
        static const uint32_t MATRIX_A = 0x9908b0dfU;
        // most significant w-r bits
        static const uint32_t UPPER_MASK = 0x80000000U;
        // least significant r bits
        static const uint32_t LOWER_MASK = 0x7fffffffU;

        uint32_t *mt_;                  // the state vector
        uint32_t mti_;                  // mti == numStats+1 means mt not initialized
    };
    static MersenneTwister mt;
};

#endif 
