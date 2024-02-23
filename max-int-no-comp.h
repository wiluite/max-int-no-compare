#pragma once

#include <optional>

namespace mi_ns {

    namespace detail { 

        enum class max {
            FIRST=1,
            SECOND
        };
        using max_opt = std::optional<max>;
    }

    auto max_int_nocmp(int a, int b) -> int {
        auto const constexpr signbit = 1u << 31u;

        if (!(signbit & a) && signbit & b) 
            return a;
        if (!(signbit & b) && signbit & a)
            return b;

        auto const a_orig{a}; 
        auto const b_orig{b};
        
        auto const neg = (signbit & a && signbit & b) ? (a = std::abs(a), b = std::abs(b), true) : false;
        
        for (auto cmp_bit = signbit >> 1u; cmp_bit; cmp_bit >>= 1u) {
            using namespace detail;
            auto _ = [&](auto f, auto s) {
                if (cmp_bit & f && !(cmp_bit & s)) 
                    return neg ? max_opt{max::SECOND} : max_opt{max::FIRST};
                return max_opt{};
            };

            if (auto res = _(a, b))
                return (static_cast<unsigned>(*res) & static_cast<unsigned>(max::FIRST)) ? a_orig : b_orig;
            else if (auto res = _(b, a)) 
                return (static_cast<unsigned>(*res) & static_cast<unsigned>(max::FIRST)) ? b_orig : a_orig; 
        }
        return a_orig; // on equality
    }

}
