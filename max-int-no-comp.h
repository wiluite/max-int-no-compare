#pragma once

namespace mi_ns {

    namespace detail {
        enum class max {
            IN_PROGRESS = 0,
            FIRST,
            SECOND
        };
    }

    auto max_int_nocmp(int a, int b) -> int {
        auto const constexpr sign_bit = 1u << 31u;

        if (!(sign_bit & a) && sign_bit & b) 
            return a;
        if (!(sign_bit & b) && sign_bit & a)
            return b;

        auto const a_orig{a}; 
        auto const b_orig{b};
        
        auto const neg = (sign_bit & a && sign_bit & b) && (a = std::abs(a), b = std::abs(b), true);

        #define TERNARY_RETURN(condition, first, second)  { if (condition) return first; else return second; }

        for (auto cmp_bit = sign_bit >> 1u; cmp_bit; cmp_bit >>= 1u) {
            using namespace detail;
            auto _ = [&](auto f, auto s) {
                if (cmp_bit & f && !(cmp_bit & s))
                    TERNARY_RETURN(neg, max::SECOND, max::FIRST)
                return max::IN_PROGRESS;
            };
            if (auto res = static_cast<int>(_(a, b)))
                TERNARY_RETURN(res & static_cast<int>(max::FIRST), a_orig, b_orig)
            else
                if ((res = static_cast<int>(_(b, a))))
                    TERNARY_RETURN(res & static_cast<int>(max::FIRST), b_orig, a_orig)
        }
        #undef TERNARY_RETURN
        return a_orig; // on equality
    }

}
