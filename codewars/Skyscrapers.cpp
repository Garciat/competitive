#include <cassert>
#include <climits>
#include <cstdlib>

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using std::begin;
using std::end;
using std::rbegin;
using std::rend;

template <typename Container, typename Pred>
void erase_if(Container &cont, Pred pred) {
    cont.erase(
        std::remove_if(begin(cont), end(cont), pred),
        end(cont)
    );
}

template <int N>
struct Skyscrapers {

    enum { SIDES = 4, PERIMETER = SIDES * N };

    using Rank = int;
    using Height = int;
    using Strip = std::array<Height, N>;

    using StripsByRank = std::array<std::vector<Strip>, N+1>;
    using Clues = std::array<Rank, PERIMETER>;
    using Choices = std::array<std::vector<Strip>, PERIMETER>;
    using City = std::vector<std::vector<int>>;

    Skyscrapers(Clues clues)
        : clues(clues)
        , stripsByRank(makeRankedStrips())
    {}

    Clues clues;
    StripsByRank stripsByRank;
    Choices answer;

    City makeCity() {
        Choices choices = makeInitialChoices();
        work(choices);

        // this->answer is now set

        City city(N, std::vector<int>(N));
        for (int i = 0; i < N; ++i) {
            // Use last N choices because these have these are left-to-right heights
            // that match the target matrix's shape.
            auto& choice = answer[PERIMETER - N + i];
            assert(choice.size() >= 1);
            std::copy(begin(choice[0]), end(choice[0]), begin(city[N-i-1]));
        }

        return city;
    }

    bool done[PERIMETER]{};

    bool work(Choices &choices) {
        int target = -1;

        for (int i = 0; i < PERIMETER; ++i) {
            if (done[i]) {
                continue;
            }
            if (choices[i].size() == 1) {
                target = i;
                break;
            }
            if (target == -1) {
                target = i;
            } else if (choices[i].size() < choices[target].size()) {
                target = i;
            }
        }

        if (target == -1) {
            answer = choices;
            return true;
        }

        done[target] = true;

        for (Strip strip : choices[target]) {
            Choices nextChoices(choices);
            if (constrain(target, strip, nextChoices)) {
                if (work(nextChoices)) {
                    return true;
                }
            }
        }

        done[target] = false;

        return false;
    }

    bool constrain(int i, Strip strip, Choices &choices) {
        int a = i / N;
        int c = i % N;

        for (int j = 0; j < PERIMETER; ++j) {
            if (done[j] && j != i) {
                continue;
            }
            
            auto& level = choices[j];
            int b = j / N;
            int d = j % N;

            if (i == j) {
                level = {strip};
            } else if (std::abs(a-b) == 2 && std::abs(c-d) == N-1) {
                erase_if(level, [&strip] (Strip s) {
                    return !std::equal(begin(strip), end(strip), rbegin(s), rend(s));
                });
            } else if ((a + 1) % SIDES == b) {
                erase_if(level, [&strip, a, b, c, d] (Strip s) {
                    return strip[d] != rbegin(s)[c];
                });
            } else if ((SIDES + a - 1) % SIDES == b) {
                erase_if(level, [&strip, a, b, c, d] (Strip s) {
                    return rbegin(strip)[d] != s[c];
                });
            } else {
                // do nothing
            }

            if (level.size() == 0) {
                return false;
            }
        }

        return true;
    }

    Choices makeInitialChoices() {
        Choices choices;
        for (int i = 0; i < PERIMETER; ++i) {
            new(&choices[i]) std::vector<Strip>(stripsByRank[clues[i]]);;
        }
        return choices;
    }

    static StripsByRank makeRankedStrips() {
        StripsByRank result{};

        Strip strip;
        std::iota(begin(strip), end(strip), 1);

        do {
            result[0].push_back(strip);
            result[stripRank(strip)].push_back(strip);
        } while (std::next_permutation(begin(strip), end(strip)));

        return result;
    }

    static Rank stripRank(const Strip &strip) {
        Height tallest = strip[0];
        Rank rank = 0;

        for (Height height : strip) {
            if (height >= tallest) {
                rank += 1;
                tallest = height;
            }
        }

        assert(1 <= rank && rank <= N);

        return rank;
    }
};

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &clues) {
    const int N = 7;
    Skyscrapers<N>::Clues input;
    std::copy(begin(clues), end(clues), begin(input));
    Skyscrapers<N> sky(input);
    return sky.makeCity();
}

int main() {
    auto city = SolvePuzzle({ 0, 2, 3, 0, 2, 0, 0,
    5, 0, 4, 5, 0, 4, 0,
    0, 4, 2, 0, 0, 0, 6,
    5, 2, 2, 2, 2, 4, 1 });
    for (auto row : city) {
        for (auto height : row) {
            std::cout << height << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
