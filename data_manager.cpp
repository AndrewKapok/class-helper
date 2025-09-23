#include "data_manager.h"

template <int SCORE_NUMBER>
void data_manager<SCORE_NUMBER>::read(string data_dir)
{
    input.open(data_dir, ios::in);
    if (input.is_open() == false)
    {
        throw runtime_error("File can not open!");
    }
    input >> student_num;
    for (int id = 1; id <= student_num; id++)
    {
        student temp;
        for (int j = 1; j <= SCORE_NUMBER; j++)
        {
            input >> temp.score[j];
        }
        student_list[id] = temp;
    }
    input.close();
    return;
}

template <int SCORE_NUMBER>
void data_manager<SCORE_NUMBER>::add(int id, int index, int score)
{
    student_list[id].score[index] += score;
}

template <int SCORE_NUMBER>
void data_manager<SCORE_NUMBER>::write(string data_dir)
{
    output.open(data_dir, ios::out);
    if (output.is_open() == false)
    {
        throw runtime_error("File can not open!");
    }
    output << student_num;
    for (int i = 1; i <= student_num; i++)
    {
        student temp = student_list[i];
        for (int j = 1; j <= SCORE_NUMBER; j++)
        {
            output << ' ' << temp.score[j];
        }
        output << endl;
    }
    output.close();
    return;
}

template <int SCORE_NUMBER>
vector<pair<int, int>> data_manager<SCORE_NUMBER>::get_sort_list()
{
    vector<pair<int, int>> sum;
    for (int i = 0; i < student_list.size(); i++)
    {
        int s = 0;
        for (int j = 1; j <= SCORE_NUMBER; j++)
        {
            s += student_list[i].score[j]; // 获取学生分数总和
        }
        sum.push_back(make_pair(s, i));
    }
    sort(sum.begin(), sum.end()); //{分数总和，学生id}
    return sum;
}

template <int SCORE_NUMBER>
vector<int> data_manager<SCORE_NUMBER>::get_first_student(int index)
{
    vector<pair<int, int>> sum = get_sort_list();
    vector<int> ans;
    int i = 1;
    for (auto it = sum.begin(); it != sum.end() && i <= index; it++, i++)
    {
        ans.push_back(it->second);
    }
    return ans;
}

template <int SCORE_NUMBER>
vector<int> data_manager<SCORE_NUMBER>::get_last_student(int index)
{
    vector<pair<int, int>> sum = get_sort_FFFlist();
    vector<int> ans;
    int i = 1;
    for (auto it = sum.rbegin(); it != sum.rend() && i <= index; it++, i++)
    {
        ans.push_back(it->second);
    }
    return ans;
}