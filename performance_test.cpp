#include "unsafe_ipow.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <execution>
#include <iostream>

struct performance_test
{
    template <typename _Vector>
    static double average(const _Vector& items)
    {
        return std::accumulate<typename _Vector::const_iterator, double>(items.begin(), items.end(), 0.0) / double(items.size());
    }

    template <typename _Integer>
    void run(std::uint16_t times) const
    {
        using limits = std::numeric_limits<_Integer>;

        constexpr _Integer max_integer = std::min<std::int64_t>(1000, limits::max());
        constexpr std::uint8_t max_exponent = 64u;

        using duration_vector = std::vector<std::uint64_t>;
        duration_vector ipow_durations {};
        duration_vector pow_durations {};

        const auto raw_estimation = times * max_integer / 2;
        ipow_durations.reserve(raw_estimation);
        pow_durations.reserve(raw_estimation);

        while (times--)
        {
            for (_Integer base = 2; base < max_integer; ++base)
            {
                for (std::uint8_t exponent = 0u; exponent < max_exponent; ++exponent)
                {
                    using clock = std::chrono::high_resolution_clock;

                    const auto start1 = clock::now();
                    const auto result1 = stdext::unsafe_ipow(base, exponent);
                    const auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - start1).count();

                    const auto start2 = clock::now();
                    const auto result2 = std::pow(base, exponent);
                    const auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - start2).count();

                    if (static_cast<decltype(result2)>(result1) == result2) // consider only duration computing non-overflow values
                    {
                        ipow_durations.push_back(duration1);
                        pow_durations.push_back(duration2);
#if 0
                        std::cout << std::int64_t(base) << '^' << int(exponent) << "  :   "
                                  << "ipow -> " << std::int64_t(result1) << "  pow -> " << std::int64_t(result2) << '\n';
#endif
                    }
                }
            }
        }

        const auto ipow_average = average(ipow_durations);
        const auto pow_average = average(pow_durations);
        std::cout << "size " << sizeof(_Integer) << "\tunsafe_ipow avg: " << ipow_average << " ns\t pow avg: " << pow_average << " ns\t"
                  << (ipow_average / pow_average - 1) * 100 << "%\n";
    }
};

int main()
{
    constexpr std::uint16_t repetition = 100u;
    const performance_test test {};
    const std::vector<std::function<void()>> tasks {
        [&test]() { test.run<std::uint8_t>(repetition); },  [&test]() { test.run<std::uint16_t>(repetition); },
        [&test]() { test.run<std::uint32_t>(repetition); }, [&test]() { test.run<std::int8_t>(repetition); },
        [&test]() { test.run<std::int16_t>(repetition); },  [&test]() { test.run<std::int32_t>(repetition); }};
    std::for_each(std::execution::par_unseq, tasks.begin(), tasks.end(), [](const auto& f) { f(); });
}
