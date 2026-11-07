#define main public_q1
#include "../src/main/A1_q1.cpp"
#undef main
#define main public_q2
#include "../src/main/A1_q2.cpp"
#undef main
#define main public_q3
#include "../src/main/A1_q3.cpp"
#undef main
#define main public_q4
#include "../src/main/A1_q4.cpp"
#undef main
#define main public_q5
#include "../src/main/A1_q5.cpp"
#undef main
#define main public_q6
#include "../src/main/A1_q6.cpp"
#undef main
#define main public_q7
#include "../src/main/A1_q7.cpp"
#undef main
#define main public_q8
#include "../src/main/A1_q8.cpp"
#undef main

int main() {
    try {
        CHECK(aim::q1::ratio(999999999999LL,1000000000000LL)==99);
        CHECK(aim::q1::ratio(-1,10)==0);
        CHECK(aim::q1::report(0,1,0,60)=="ID=0;HP=INVALID;BAT=60;STATE=OK");
        CHECK(aim::q2::edit_labels("a,b,a",{{"a",""},{"a",""},{"b",""},{"","c"}})=="c");
        CHECK(aim::q2::edit_labels("cam2,cam",{{"cam","long_name"},{"cam2",""}})=="long_name");
        CHECK(aim::q2::edit_labels("A,a",{{"a","x"}})=="A,x");
        CHECK((aim::q3::alarms({-4,-3,-2},2,-6)==std::vector<int>{2}));
        CHECK(aim::q3::alarms({2,2},2,4).empty());
        CHECK(aim::q3::alarms({1},0,0).empty());
        CHECK((aim::q3::alarms({1000000000,1000000000,1000000000},3,2999999999LL)==std::vector<int>{2}));
        auto command=aim::q4::execute({"SET 5","RESET x","ADD 12x","ADD +2","SET 1000000","ADD 1","RESET","add 5","","ADD 999999999999999999999999"});
        CHECK(command.value==0 && command.accepted==4 && command.rejected==6);
        CHECK((aim::q5::risk({"#." ,".."})==std::vector<std::vector<int>>{{-1,1},{1,0}}));
        EXPECT_INVALID(aim::q5::risk({""}));
        EXPECT_INVALID(aim::q5::risk({"..",".x"}));
        EXPECT_INVALID(aim::q5::risk({"..","."}));
        CHECK(aim::q6::select_target({{8,1000000,0,1,true},{2,0,0,2,true}},1000000)==8);
        CHECK(aim::q6::select_target({{9,0,0,3,true},{1,0,0,3,true}},0)==1);
        CHECK(aim::q6::select_target({{1,0,0,1,true}},-1)==-1);
        auto fire=aim::q7::simulate(0,50,10,20,{1});
        CHECK(fire.shots==0 && fire.rejected==1 && fire.ammo==0 && fire.heat==40);
        fire=aim::q7::simulate(4,80,10,30,{});
        CHECK(fire.heat==80 && fire.ammo==4);
        fire=aim::q7::simulate(1,100,0,0,{1});
        CHECK(fire.shots==1 && fire.heat==100);
        auto summary=aim::q8::summarize({{1,-1001},{1,30},{1,1001},{1,40},{9999,1000},{-1,1}});
        CHECK(summary.valid==2 && summary.duplicate==1 && summary.invalid==3 && summary.total_hp==130);
        CHECK((summary.ids==std::vector<int>{1,9999}));
        CHECK(summary.valid+summary.duplicate+summary.invalid==6);
        CHECK(aim::q8::summarize({}).ids.empty());
        CHECK(aim::q8::summarize({{1,5}}).total_hp==5);
        std::cout << "Boundary tests passed\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
