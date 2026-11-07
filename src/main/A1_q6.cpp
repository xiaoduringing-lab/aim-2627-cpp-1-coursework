#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw
int select_target(const std::vector<Target>& targets, int max_range) {
    if (max_range < 0) return -1;
    int best_id = -1;
    int best_hp = 0;
    long long best_distance = 0;
    long long range_squared = 1LL * max_range * max_range;
    for (const auto& target : targets) {
        long long distance = 1LL * target.x * target.x + 1LL * target.y * target.y;
        if (!target.visible || target.hp <= 0 || distance > range_squared) continue;
        if (best_id == -1 || target.hp < best_hp
            || (target.hp == best_hp && distance < best_distance)
            || (target.hp == best_hp && distance == best_distance && target.id < best_id)) {
            best_id = target.id;
            best_hp = target.hp;
            best_distance = distance;
        }
    }
    return best_id;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
