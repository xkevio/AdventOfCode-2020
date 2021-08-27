#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::int64_t find_wrong_number(std::vector<std::int64_t> nums, int preamble) {
    std::int64_t num = -1;
    int t = 0;
    for (std::size_t i = preamble; i < nums.size(); i++) {
        bool add = false;
        std::int64_t cur_num = nums[i];

        for (std::size_t j = t; j < preamble + t; j++) {
            int test = 0;
            if (!add) {
                std::int64_t look_for = cur_num - nums[j];
                auto new_num = nums;

                if (t != 0) {
                    new_num.erase(new_num.begin(), new_num.begin() + t);
                }
                new_num.erase(new_num.begin() + test);
                test++;
                new_num.erase(new_num.begin() + preamble - 1, new_num.end());

                if (std::find(new_num.begin(), new_num.end(), look_for) != new_num.end()) {
                    add = true;
                }
            }
        }
        t++;
        if (!add) {
            num = cur_num;
            break;
        }
    }

    return num;
}

std::vector<std::int64_t> find_contiguous_sum(const std::vector<std::int64_t>& nums, std::int64_t sum) {
    std::vector<std::int64_t> sums;

    for (std::size_t i = 0; i < nums.size(); i++) {
        std::int64_t temp_sum = nums[i];
        sums.push_back(temp_sum);
        for (size_t j = i + 1; j < nums.size(); j++) {
            if (temp_sum < sum) {
                temp_sum += nums[j];
                sums.push_back(nums[j]);
            } else if (temp_sum > sum) {
                sums.clear();
            } else {
                return sums;
            }
        }
    }

    return sums;
}

int main() {
    std::ifstream file("input.txt");
    std::string cur;
    std::vector<std::int64_t> nums;

    while (std::getline(file, cur)) {
        nums.push_back(stoll(cur));
    }

    std::cout << "Part 1: " << find_wrong_number(nums, 25) << std::endl;

    auto sums = find_contiguous_sum(nums, find_wrong_number(nums, 25));
    std::sort(sums.begin(), sums.end());

    std::cout << "Part 2: " << sums[0] + sums[sums.size() - 1] << std::endl;

    return EXIT_SUCCESS;
}