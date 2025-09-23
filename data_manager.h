#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
template <int SCORE_NUMBER>
class data_manager
{
private:
    ifstream input;
    ofstream output;
    struct student
    {
        int score[SCORE_NUMBER + 1]; // 作业，自习，宿舍，课堂个人，课堂小组，迟到，眼保健操，卫生
    };
    map<int, student> student_list;
    int student_num;

public:
    extern void read(string data_dir);

    extern void add(int id, int index, int score);

    extern void write(string data_dir);

    extern vector<pair<int, int>> get_sort_list();

    extern vector<int> get_first_student(int index);

    extern vector<int> get_last_student(int index);
};