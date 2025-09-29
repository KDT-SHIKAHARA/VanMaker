#pragma once
#include<cmath>

class MathUtils {
public:
    // ƒTƒCƒ“”g‚ÅÀ•W‚ğ—h‚ç‚·
    // base: Šî€À•W
    // amplitude: —h‚ê•
    // frequency: ü”g”i1•b‚ ‚½‚è‚Ì—h‚ê‰ñ”j
    // time: Œo‰ßŠÔi•bj
    static float CalcSineWave(float base, float amplitude, float frequency, float time) {
        return base + amplitude * std::sinf(2.0f * PI * frequency * time);
    }
};