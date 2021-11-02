#ifndef _STOPWATCH_HPP_
#define _STOPWATCH_HPP_

#include <chrono>
#include <iostream>
#include <vector>

class Stopwatch;
std::ostream &operator<<(std::ostream &os, const Stopwatch &sw);

class Stopwatch final
{
    friend std::ostream &operator<<(std::ostream &os, const Stopwatch &sw);

public:
    using time_pt = std::chrono::time_point<std::chrono::high_resolution_clock>;

    enum TimeFormat
    {
        NANOSECONDS,
        MICROSECONDS,
        MILLISECONDS,
        SECONDS
    };

    Stopwatch() : start_(), times_({})
    {
        start();
    }

    Stopwatch(const Stopwatch &) = delete;
    Stopwatch(Stopwatch &&) = delete;

    Stopwatch &operator=(const Stopwatch &) = delete;
    Stopwatch &operator=(Stopwatch &&) = delete;

    ~Stopwatch() = default;

    void start()
    {
        start_ = std::chrono::high_resolution_clock::now();
        times_ = {start_};
    }

    template <TimeFormat fmt = TimeFormat::MILLISECONDS>
    std::uint64_t elapsed() const
    {
        const auto end = std::chrono::high_resolution_clock::now();
        return tick<fmt>(start_, end);
    }

    template <TimeFormat fmt = TimeFormat::MILLISECONDS>
    std::uint64_t lapse()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto last = times_.back();
        times_.push_back(now);
        return tick<fmt>(last, now);
    }

    template <TimeFormat fmt_total = TimeFormat::MILLISECONDS, TimeFormat fmt_lap = fmt_total>
    std::pair<std::uint64_t, std::vector<std::uint64_t>> getLapses()
    {
        std::vector<std::uint64_t> lapses;
        lapses.reserve(times_.size() - 1);

        for (std::size_t i = 0; i <= lapses.size() - 2; ++i)
        {
            const auto end = lapses[i + 1];
            const auto start = lapses[i];
            lapses.push_back(tick<fmt_lap>(start, end));
        }

        return {tick<fmt_total>(start_, times_.back()), lapses};
    }

private:
    template <TimeFormat fmt = TimeFormat::MILLISECONDS>
    static std::uint64_t tick(const time_pt &start, const time_pt &end)
    {
        const auto duration = end - start;
        switch (fmt)
        {
        case TimeFormat::NANOSECONDS:
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        }
        case TimeFormat::MICROSECONDS:
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        }
        case TimeFormat::MILLISECONDS:
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        }
        case TimeFormat::SECONDS:
        {
            return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        }
        }
    }

    time_pt start_;
    std::vector<time_pt> times_;
};

std::ostream &operator<<(std::ostream &os, const Stopwatch &sw)
{
    os << sw.elapsed();
    return os;
}

#endif // !_STOPWATCH_HPP_