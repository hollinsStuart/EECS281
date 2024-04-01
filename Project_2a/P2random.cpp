// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#include <iostream>
#include "P2random.h"

P2random::MersenneTwister P2random::mt;
std::vector<std::string> P2random::ZOMBIE_NAMES = {
        "paoletti",
        "darden",
        "garcia",
        "cris",
        "bing",
        "will",
        "fee",
        "noah",
        "potatobot",
};


P2random::GenState P2random::genState;
uint32_t P2random::zombieCounter;
uint32_t P2random::maxRandDist;
uint32_t P2random::maxRandSpeed;
uint32_t P2random::maxRandHealth;


void P2random::initialize(uint32_t seed, uint32_t maxDist, uint32_t maxSpeed, uint32_t maxHealth) {
    genState = GenState::GenName;
    zombieCounter = 0;
    maxRandDist = maxDist;
    maxRandSpeed = maxSpeed;
    maxRandHealth = maxHealth;
    mt.init_genrand(seed);
}


std::string P2random::getNextZombieName() {
    if (genState != GenState::GenName) {
        std::cerr << "Zombie functions called out of order" << std::endl;
        exit(1);
    } // if

    genState = GenState::GenDistance;
    uint32_t index = zombieCounter++;

    const auto& name = ZOMBIE_NAMES[index % ZOMBIE_NAMES.size()];
    return name + std::to_string(index);
}


uint32_t P2random::getNextZombieDistance() {
    if (genState != GenState::GenDistance) {
        std::cerr << "Zombie functions called out of order" << std::endl;
        exit(1);
    } // if

    genState = GenState::GenSpeed;
    return getNextInt(maxRandDist);
}


uint32_t P2random::getNextZombieSpeed() {
    if (genState != GenState::GenSpeed) {
        std::cerr << "Zombie functions called out of order" << std::endl;
        exit(1);
    } // if

    genState = GenState::GenHealth;
    return getNextInt(maxRandSpeed);
}


uint32_t P2random::getNextZombieHealth() {
    if (genState != GenState::GenHealth) {
        std::cerr << "Zombie functions called out of order" << std::endl;
        exit(1);
    } // if

    genState = GenState::GenName;
    return getNextInt(maxRandHealth);
}


uint32_t P2random::getNextInt(uint32_t maxValue) {
    return (mt.genrand_uint32_t() % maxValue) + 1;
}


/**
* C++ Mersenne Twister wrapper class written by
* Jason R. Blevins <jrblevin@sdf.lonestar.org> on July 24, 2006.
* Based on the original MT19937 C code by
* Takuji Nishimura and Makoto Matsumoto.
*/

/*
A C-program for MT19937, with initialization improved 2002/1/26.
Coded by Takuji Nishimura and Makoto Matsumoto.

Before using, initialize the state by using init_genrand(seed).

Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The names of its contributors may not be used to endorse or promote
products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Any feedback is very welcome.
http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/


/**
* Constructor
*/
P2random::MersenneTwister::MersenneTwister(void) :
        mt_(new uint32_t[N]), mti_(N + 1) {
    init_genrand(0);
}


/**
* Destructor
*/
P2random::MersenneTwister::~MersenneTwister(void) {
    delete[] mt_;
    mt_ = nullptr;
}


/**
* Initializes the Mersenne Twister with a seed.
*
* \param s seed
*/
void P2random::MersenneTwister::init_genrand(uint32_t s) {
    mt_[0] = s & 0xffffffffU;
    for (mti_ = 1; mti_ < N; mti_++) {
        mt_[mti_] =
                (1812433253U * (mt_[mti_ - 1] ^ (mt_[mti_ - 1] >> 30)) + static_cast<uint32_t>(mti_));
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt_[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt_[mti_] &= 0xffffffffU;
        /* for >32 bit machines */
    }
}


/**
* Generates a random number on [0,0xffffffff]-interval
*
* \return random number on [0, 0xffffffff]
*/
uint32_t P2random::MersenneTwister::genrand_uint32_t(void) {
    uint32_t y;
    static uint32_t mag01[2] = { 0x0U, MATRIX_A };
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti_ >= N) { /* generate numStats words at one time */
        uint32_t kk;

        if (mti_ == N + 1)   /* if init_genrand() has not been called, */
            init_genrand(5489U); /* a default initial seed is used */

        for (kk = 0; kk < N - M; kk++) {
            y = (mt_[kk] & UPPER_MASK) | (mt_[kk + 1] & LOWER_MASK);
            mt_[kk] = mt_[kk + M] ^ (y >> 1) ^ mag01[y & 0x1U];
        }
        for (; kk < N - 1; kk++) {
            y = (mt_[kk] & UPPER_MASK) | (mt_[kk + 1] & LOWER_MASK);
            mt_[kk] = mt_[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1U];
        }
        y = (mt_[N - 1] & UPPER_MASK) | (mt_[0] & LOWER_MASK);
        mt_[N - 1] = mt_[M - 1] ^ (y >> 1) ^ mag01[y & 0x1U];

        mti_ = 0;
    }

    y = mt_[mti_++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680U;
    y ^= (y << 15) & 0xefc60000U;
    y ^= (y >> 18);

    return y;
}
