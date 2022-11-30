#include "number.h"
#include <string>
#include <iomanip>
#include <cstring>
#include <cmath>

uint2022_t from_uint(uint32_t i) {
    uint2022_t num;
    int count = 0;
    while (i > 0) {
        num.digits[count++] = i % uint2022_t::BASE;
        i /= uint2022_t::BASE;
    }
    return num;
}

uint2022_t from_string(const char* buff) {
    uint2022_t num;
    int i = strlen(buff) - 1, count = 0;
    while (i >= 0 ) {
        char digits_gap[9];  // количество разрядов у числа  10^9
        int count_clean = 0;
        while (count_clean < 9) {
            digits_gap[count_clean++] = ' ';
        }

        int size_gap = 8;
        while (size_gap >= 0 and i >= 0) {
            digits_gap[size_gap--] = buff[i--];
        }
        num.digits[count++] = atoi(digits_gap);
    }
    return num;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t num;
    int remainder = 0;
    for (int i = 0; i < uint2022_t::ORDER; i++) {
        num.digits[i] = (lhs.digits[i] + rhs.digits[i] + remainder) % uint2022_t::BASE;
        remainder = (lhs.digits[i] + rhs.digits[i] + remainder) / uint2022_t::BASE;
    }
    return num;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t num;
    uint2022_t lhs1 = lhs;
    for (int i = 0; i < uint2022_t::ORDER; ++i) {
        if (lhs1.digits[i] < rhs.digits[i]) {
            if (i + 1 == uint2022_t::ORDER) {
                throw std::runtime_error( "Input is not correct");
            }
            lhs1.digits[i + 1]--;
        }
        num.digits[i] = abs(lhs1.digits[i] - rhs.digits[i]);
    }
    return num;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t num;
    int remainder = 0;
    for (int rank_num = 0; rank_num < uint2022_t::ORDER; ++rank_num) {
        int rank_num_lfs = 0;
        int64_t multi = remainder;
        while (rank_num_lfs <= rank_num) {
            multi += int64_t(lhs.digits[rank_num_lfs]) * int64_t(rhs.digits[rank_num - rank_num_lfs]);
            rank_num_lfs++;
        }
        num.digits[rank_num] = (uint32_t)(multi % uint2022_t::BASE);
        remainder = int(multi / uint2022_t::BASE);
    }
    return num;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < uint2022_t::ORDER; i++) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    bool first_num = true;
    for (int i = uint2022_t::ORDER - 1; i >= 0; i--) {
        if (value.digits[i] != 0) {
            if (first_num == true) {
                stream << value.digits[i];
                first_num = false;
            } else {
                stream << std::setfill('0') << std::setw(9) << value.digits[i];
            }
        } else if (first_num == false){
            stream << std::setfill('0') << std::setw(9) << value.digits[i];
        }
    }
    return stream;
}
