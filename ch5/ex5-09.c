#include <assert.h>
#include <stdint.h>

#define leap_year(y) (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))

#define days_per_year(y) (leap_year(y) ? 366 : 365)


uint8_t day_table[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


int32_t day_of_year(int32_t year, int32_t month, int32_t day) {
    /* day_of_year: return the day of year from month & day */
    uint8_t *p = day_table[leap_year(year)];
    uint8_t *q = p+month;

    if ((year <= 0) || (month < 1 || month > 12) || (day < 1 || day > *q)) {
        return -1;
    }

    for (; p != q; p++) {
        day += *p;
    }

    return day;
}


int32_t month_day(int32_t year, int32_t year_day, int32_t *pmonth, int32_t *pday) {
    /* month_day: set the month, day from day of year */
    if (year <= 0 || year_day < 1 || year_day > days_per_year(year)) {
        return -1;
    }
    uint8_t *p, *q;
    for (p = q = day_table[leap_year(year)]; year_day > *p; p++) {
        year_day -= *p;
    }

    *pmonth = p - q;
    *pday = year_day;

    return 0;
}


int32_t main() {
    assert(day_of_year(0, 1, 31) == -1);
    assert(day_of_year(-2001, 1, 31) == -1);
    assert(day_of_year(2025, 6, 31) == -1);
    assert(day_of_year(2025, 0, 30) == -1);
    assert(day_of_year(2025, 6, 30) == 181);
    assert(day_of_year(1776, 7, 4) == 186);
    assert(day_of_year(1999, 12, 31) == 365);
    assert(day_of_year(2000, 12, 30) == 365);

    int32_t res, month, day;
    assert(month_day(0, 31, &month, &day) == -1);
    assert(month_day(-2001, 31, &month, &day) == -1);
    assert(month_day(1700, 366, &month, &day) == -1);
    assert(month_day(1999, 366, &month, &day) == -1);
    res = month_day(2025, 181, &month, &day);
    assert(res == 0 && month == 6 && day == 30);
    res = month_day(1776, 186, &month, &day);
    assert(res == 0 && month == 7 && day == 4);
    res = month_day(1999, 365, &month, &day);
    assert(res == 0 && month == 12 && day == 31);
    res = month_day(2000, 365, &month, &day);
    assert(res == 0 && month == 12 && day == 30);

    return 0;
}

