#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class data
{
#define MAXN 8
private:    
    wifstream input;
    wofstream output;
    struct student
    {
        wstring name;
        int score[MAXN]; // 作业，自习，宿舍，课堂个人，课堂小组，迟到，眼保健操，卫生
    };
    vector<student> studentlist;
    int student_num;

public:
    void read(string data_dir)
    {
        input.open(data_dir, ios::in);
        if (input.is_open() == false)
        {
            throw runtime_error("File can not open!");
        }
        input >> student_num;
        for (int i = 1; i <= student_num; i++)
        {
            student temp;
            input >> temp.name;
            for (int j = 0; j < MAXN; j++)
            {
                input >> temp.score[j];
            }
            studentlist.push_back(temp);
        }
        input.close();
        return;
    }

    void homework(int id, int point)
    {
        studentlist[id].score[0] += point;
    }

    void selfstudy(int id, int point)
    {
        studentlist[id].score[1] += point;
    }

    void dormitory(int id, int point)
    {
        studentlist[id].score[2] += point;
    }

    void class_self(int id, int point)
    {
        studentlist[id].score[3] += point;
    }

    void class_group(int id, int point)
    {
        studentlist[id].score[4] += point;
    }

    void late(int id, int point)
    {
        studentlist[id].score[5] += point;
    }

    void exercises(int id, int point)
    {
        studentlist[id].score[6] += point;
    }

    void duty(int id, int point)
    {
        studentlist[id].score[7] += point;
    }

    void write(string data_dir)
    {
        output.open(data_dir, ios::out);
        if (output.is_open() == false)
        {
            throw runtime_error("File can not open!");
        }
        output << student_num;
        for (int i = 1; i <= student_num; i++)
        {
            student temp = studentlist[i];
            output << temp.name;
            for (int j = 0; j < MAXN; j++)
            {
                output << ' ' << temp.score[j];
            }
            output << endl;
        }
        output.close();
        return;
    }
#undef MAXN
};