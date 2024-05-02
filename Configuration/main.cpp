/*
 * Hướng dẫn chạy testcase
 * Chạy 2 lệnh sau trong terminal
 *
 * Lệnh 1:
 * g++ -o main main.cpp
 *
 * Lệnh 2:
 * Chạy full 200 test
 * ./main
 *
 * Chạy test chỉ định
 * ./main <test>
 * VD: ./main 111
 *
 * Chạy cụm test
 * ./main <from> <to>
 * VD: ./main 1 10
 */

#include "config.cpp"
using namespace std;

void resetValues()
{
    // Đặt lại các giá trị về mặc định
    map_num_rows = -1;
    map_num_cols = -1;
    max_num_moving_objects = -1;
    num_walls = -1;

    // Giải phóng bộ nhớ của mảng 2 chiều arr_walls nếu đã được cấp phát
    if (arr_walls != nullptr)
    {
        for (int i = -1; i < num_walls; i++)
        {
            delete[] arr_walls[i];
        }
        delete[] arr_walls;
    }

    num_fake_walls = -1;

    // Giải phóng bộ nhớ của mảng 2 chiều arr_fake_walls nếu đã được cấp phát
    if (arr_fake_walls != nullptr)
    {
        for (int i = -1; i < num_fake_walls; i++)
        {
            delete[] arr_fake_walls[i];
        }
        delete[] arr_fake_walls;
    }

    sherlock_moving_rule = "";
    sherlock_init_pos[0] = -1;
    sherlock_init_pos[1] = -1;
    sherlock_init_hp = -1;
    sherlock_init_exp = -1;

    watson_moving_rule = "";
    watson_init_pos[0] = -1;
    watson_init_pos[1] = -1;
    watson_init_hp = -1;
    watson_init_exp = -1;

    criminal_init_pos[0] = -1;
    criminal_init_pos[1] = -1;
    num_steps = -1;
}
void Output(const string &fileName, int i)
{
    ofstream outputFile(fileName);

    if (!outputFile.is_open())
    {
        cout << "Không thể mở tệp đầu ra!" << endl;
        return;
    }
    outputFile << "test case " << i << endl;
    // Ghi các giá trị đáp án vào tệp tin
    outputFile << "map_num_rows : " << map_num_rows << endl;
    outputFile << "map_num_cols : " << map_num_cols << endl;
    outputFile << "max_num_moving_objects : " << max_num_moving_objects << endl;
    outputFile << "num_walls : " << num_walls << endl;
    for (int i = 0; i < num_walls; i++)
    {
        outputFile << "( " << arr_walls[i][0] << "," << arr_walls[i][1] << ")"
                   << " ";
    }
    outputFile << "\nnum_fake_walls : " << num_fake_walls << endl;
    for (int i = 0; i < num_fake_walls; i++)
    {
        outputFile << "( " << arr_fake_walls[i][0] << "," << arr_fake_walls[i][1] << ")"
                   << " ";
    }
    outputFile << "\nsherlock_moving_rule : " << sherlock_moving_rule << endl;
    outputFile << "sherlock_init_pos : "
               << "( " << sherlock_init_pos[0] << "," << sherlock_init_pos[1] << ")" << endl;
    outputFile << "sherlock_init_hp : " << sherlock_init_hp << endl;
    outputFile << "sherlock_init_exp : " << sherlock_init_exp << endl;
    outputFile << "watson_moving_rule : " << watson_moving_rule << endl;
    outputFile << "watson_init_pos : "
               << "( " << watson_init_pos[0] << "," << watson_init_pos[1] << ")" << endl;
    outputFile << "watson_init_hp : " << watson_init_hp << endl;
    outputFile << "watson_init_exp : " << watson_init_exp << endl;
    outputFile << "criminal_init_pos : "
               << "( " << criminal_init_pos[0] << "," << criminal_init_pos[1] << ")" << endl;
    outputFile << "num_steps : " << num_steps << endl;
    outputFile << "----------------------------------------------------" << endl;
    outputFile.close();
}

void comparefile(int start, int end)
{
    vector<int> result;
    for (int i = start; i <= end; i++)
    {
        string outputFile = "testcase/output/output" + to_string(i) + ".txt";
        string expectFile = "testcase/expect/expect" + to_string(i) + ".txt";
        ifstream read_output(outputFile);
        ifstream read_expect(expectFile);
        if (read_expect.fail())
        {
            cout << "Error reading file - " << i << endl;
            return;
        }
        string s1, s2;
        while (read_output >> s1 && read_expect >> s2)
        {
            if (s1 != s2)
            {
                result.push_back(i);
                break;
            }
        }
        if (read_output >> s1 || read_expect >> s2)
        {
            if (result.size() == 0 || result.size() > 0 && result[result.size() - 1] != i)
                result.push_back(i);
        }
    }

    if (result.size() == 0)
    {
        cout << "Success: test " << start << " to " << end << endl;
    }
    else
    {
        cout << "percent success : " << (1 - result.size() * 1.0 / (end - start + 1)) * 100 << "%" << endl;
        cout << "Fail : test [";
        for (int i = 0; i < result.size() - 1; i++)
        {
            cout << result[i] << ", ";
        }
        cout << result[result.size() - 1] << "]\n";
        cout << "link check comparefile: https://www.diffchecker.com/text-compare\\" << endl;
    }
}
int main(int argc, char *argv[])
{

    cout << "Start program assignments 1 DSA" << endl;
    int start = 0, end = 0;
    if (argc == 1)
    {
        start = 1;
        end = 200;
    }
    else if (argc == 2)
    {
        start = stoi(argv[1]);
        end = stoi(argv[1]);
    }
    else if (argc == 3)
    {
        start = stoi(argv[1]);
        end = stoi(argv[2]);
    }
    for (int i = start; i <= end; i++)
    {
        string folderr = "testcase/output/output";
        // string folderr = "testcase/expect/expect";
        string inputFile = "testcase/input/input" + to_string(i) + ".txt";
        string outputFile = folderr + to_string(i) + ".txt";
        configuration(inputFile);
        Output(outputFile, i);
    }
    comparefile(start, end);
}