#pragma once
#include <random>



struct Random
{
    static std::mt19937& Generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    static float RandomFloat(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(Generator());  // Generator ‚ğg‚¤
    }

    static int RandomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(Generator());  // Generator ‚ğg‚¤
    }

    static float RandomAngle() {
        std::uniform_real_distribution<float> dist(0.0f, 2.0f * 3.14159265f);
        return dist(Generator());
    }
};