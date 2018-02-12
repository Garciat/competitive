#include <algorithm>
#include <iostream>

#define MAX_SETTLEMENTS 20
#define PRESIDENT_TERM_DAYS 1825

struct Settlement {
    int solarDayLength;
    int sunriseHour;
    int sunsetHour;

    bool isNight(int hour) const {
        if (sunriseHour < sunsetHour) {
            return hour <= sunriseHour || hour >= sunsetHour;
        } else {
            return hour <= sunriseHour && hour >= sunsetHour;
        }
    }
};

int postIncrementMod(int &x, int m) {
    int v = x;
    x = (x + 1) % m;
    return v;
}

int getLongestSolarDay(Settlement *settlements, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        result = std::max(result, settlements[i].solarDayLength);
    }
    return result;
}

int getHoursUntilDarkness(Settlement *settlements, int n) {
    int hours[MAX_SETTLEMENTS] = {0};

    int presidentTermHours = PRESIDENT_TERM_DAYS * getLongestSolarDay(settlements, n);

    for (int i = 0; i < presidentTermHours; ++i) {
        bool okay = true;
        for (int j = 0; j < n; ++j) {
            okay &= settlements[j].isNight(postIncrementMod(hours[j], settlements[j].solarDayLength));
        }
        if (okay) {
            return i;
        }
    }

    return -1;
}

int main() {
    int n;
    std::cin >> n;

    Settlement settlements[MAX_SETTLEMENTS];

    for (int i = 0; i < n; ++i) {
        Settlement &s = settlements[i];
        std::cin >> s.solarDayLength >> s.sunriseHour >> s.sunsetHour;
    }

    int ans = getHoursUntilDarkness(settlements, n);

    if (ans == -1) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }

    return 0;
}
