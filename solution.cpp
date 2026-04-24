
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int get_month_days(int y, int m) {
    if (m == 2 && is_leap(y)) return 29;
    return month_days[m];
}

bool is_valid(int y, int m, int d) {
    if (y < 1) return false; // Though constraints say 1900-2030
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > get_month_days(y, m)) return false;
    return true;
}

class Date {
private:
    int _year;
    int _month;
    int _day;

    long long to_days() const {
        long long days = 0;
        for (int y = 1; y < _year; ++y) {
            days += is_leap(y) ? 366 : 365;
        }
        for (int m = 1; m < _month; ++m) {
            days += get_month_days(_year, m);
        }
        days += _day;
        return days;
    }

    static Date from_days(long long days) {
        int y = 1;
        while (true) {
            int dy = is_leap(y) ? 366 : 365;
            if (days <= dy) break;
            days -= dy;
            y++;
        }
        int m = 1;
        while (true) {
            int dm = get_month_days(y, m);
            if (days <= dm) break;
            days -= dm;
            m++;
        }
        return Date(y, m, (int)days, true);
    }

    Date(int y, int m, int d, bool skip_check) : _year(y), _month(m), _day(d) {}

public:
    Date() : _year(1900), _month(1), _day(1) {}
    Date(int y, int m, int d) {
        if (is_valid(y, m, d)) {
            _year = y;
            _month = m;
            _day = d;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }

    Date& operator++() {
        *this = from_days(to_days() + 1);
        return *this;
    }

    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }

    Date& operator--() {
        *this = from_days(to_days() - 1);
        return *this;
    }

    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }

    Date operator+(int days) const {
        return from_days(to_days() + days);
    }

    Date operator-(int days) const {
        return from_days(to_days() - days);
    }

    long long operator-(const Date& other) const {
        long long d1 = to_days();
        long long d2 = other.to_days();
        return d1 > d2 ? d1 - d2 : d2 - d1;
    }

    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }

    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test()
{
    int op;
    if (!(cin >> op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
    }
    if (op == 2 || op == 0)
    {
        if (cin >> yy >> mm >> dd) {
            Date d0(yy, mm, dd);
            for (int i=0;i<5;++i) cout << ++d0 << endl;
            for (int i=0;i<5;++i) cout << d0++ << endl;
            for (int i=0;i<5;++i) cout << d0-- << endl;
            for (int i=0;i<2;++i) cout << --d0 << endl;
            cout << d0 << endl;
        }
    }
    if (op == 3 || op == 0)
    {
        if (cin >> yy >> mm >> dd) {
            Date d0(yy, mm, dd);
            cout << d0 + 100 << endl;
            cout << d0 - 1000 << endl;
        }
    }
    if (op == 4 || op == 0)
    {
        if (cin >> yy >> mm >> dd) {
            Date d0(yy, mm, dd);
            Date d1(2020, 12, 21);
            cout << (d0 < d1) << endl;
        }
    }
    if (op == 5 || op == 0)
    {
        if (cin >> yy >> mm >> dd) {
            Date d0(yy, mm, dd);
            Date d1(1912, 6, 23);
            cout << d0 - d1 << endl;
        }
    }
}

int main()
{
    Test();
    return 0;
}
