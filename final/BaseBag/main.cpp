/*
 * Hướng dẫn chạy testcase
 * Chạy 2 lệnh sau trong terminal
 *
 * Lệnh 1:
 * g++ -o main main.cpp basebag.cpp
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

#include "basebag.h"
using namespace std;
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
        cout << "link check comparefile: https://www.diffchecker.com/text-compare/" << endl;
    }
}
void testAll(string inputFile)
{
    // SAMPLE INPUT
    Position position;
    Map *map = new Map(1, 1, 0, nullptr, 0, nullptr);
    // TEST INPUT
    ifstream fileInput(inputFile);
    string line = "";
    getline(fileInput, line);
    stringstream ssHp(line);
    int sherHp = 0, sherExp = 0, watHp = 0, watExp = 0;
    ssHp >> line >> sherHp >> watHp;
    getline(fileInput, line);
    stringstream ssExp(line);
    ssExp >> line >> sherExp >> watExp;
    Sherlock *sherlock = new Sherlock(
        0,
        "U",
        position,
        map,
        sherHp,
        sherExp);
    Watson *watson = new Watson(
        0,
        "U",
        position,
        map,
        watHp,
        watExp);
    SherlockBag *sherlockBag = new SherlockBag(sherlock);
    WatsonBag *watsonBag = new WatsonBag(watson);
    // SAMPLE INPUT
    Criminal *criminal = new Criminal(0, position, map, sherlock, watson);
    Robot *robotC = new RobotC(0, position, map, C, criminal);
    Robot *robotS = new RobotS(0, position, map, S, criminal, sherlock);
    Robot *robotW = new RobotW(0, position, map, W, criminal, watson);
    Robot *robotSW = new RobotSW(0, position, map, SW, criminal, sherlock, watson);
    Robot *robotList[5] = {robotC, robotS, robotW, robotSW, nullptr};
    // TEST OUTPUT
    OUTPUT << "Sherlock stats : HP = "
           << sherlock->getHP() << " ; EXP = "
           << sherlock->getEXP() << endl;
    OUTPUT << "Watson stats : HP = "
           << watson->getHP() << " ; EXP = "
           << watson->getEXP() << endl;
    int lineNumber = 2;
    while (getline(fileInput, line))
    {
        lineNumber++;
        OUTPUT << "___(" << lineNumber << ")___" << line << endl;
        stringstream ss(line);
        string command = "";
        ss >> command;
        if (command == "INSERT")
        {
            BaseItem *item1 = nullptr, *item2 = nullptr;
            // !if else testcase
            string itemName = "";
            ss >> itemName;
            if (itemName == "MagicBook")
            {
                item1 = new MagicBook();
                item2 = new MagicBook();
            }
            else if (itemName == "EnergyDrink")
            {
                item1 = new EnergyDrink();
                item2 = new EnergyDrink();
            }
            else if (itemName == "FirstAid")
            {
                item1 = new FirstAid();
                item2 = new FirstAid();
            }
            else if (itemName == "ExcemptionCard")
            {
                item1 = new ExcemptionCard();
                item2 = new ExcemptionCard();
            }
            else if (itemName == "PassingCard")
            {
                int x = 0, y = 0;
                ss >> x >> y;
                item1 = new PassingCard(x, y);
                item2 = new PassingCard(x, y);
            }

            if (!(sherlockBag->insert(item1)))
            {
                delete item1;
                item1 = nullptr;
            }
            OUTPUT << sherlockBag->str() << endl;
            // if else testcase
            if (!(watsonBag->insert(item2)))
            {
                delete item2;
                item2 = nullptr;
            }
            OUTPUT << watsonBag->str() << endl;
        }
        else if (command == "USE")
        {
            BaseItem *item = nullptr;
            // !if else testcase
            string itemName = "";
            ss >> itemName;
            if (itemName == "MagicBook")
                item = new MagicBook();
            else if (itemName == "EnergyDrink")
                item = new EnergyDrink();
            else if (itemName == "FirstAid")
                item = new FirstAid();
            else if (itemName == "ExcemptionCard")
                item = new ExcemptionCard();
            else if (itemName == "PassingCard")
            {
                int x = 0, y = 0;
                ss >> x >> y;
                item = new PassingCard(x, y);
            }
            string robotString[5] = {"RobotC : ",
                                     "RobotS : ",
                                     "RobotW : ",
                                     "RobotSW : ",
                                     "No Robot : "};
            // Sherlock
            for (int i = 0; i < 5; i++)
            {
                if (item->canUse(sherlock, robotList[i]))
                {
                    string robotName = robotString[i];
                    OUTPUT << robotName;
                    OUTPUT << "Sherlock used " << item->str() << endl;
                    item->use(sherlock, robotList[i]);
                    OUTPUT << "Sherlock stats : HP = "
                           << sherlock->getHP() << " ; EXP = "
                           << sherlock->getEXP() << endl;
                }
            }
            // Watson
            for (int i = 0; i < 5; i++)
            {
                if (item->canUse(watson, robotList[i]))
                {
                    string
                        robotName =
                            i == 0   ? "RobotC : "
                            : i == 1 ? "RobotS : "
                            : i == 2 ? "RobotW : "
                            : i == 3 ? "RobotSW : "
                                     : "No robot : ";
                    OUTPUT << robotName;
                    OUTPUT << "Watson used " << item->str() << endl;
                    item->use(watson, robotList[i]);
                    OUTPUT << "Watson stats : HP = "
                           << watson->getHP() << " ; EXP = "
                           << watson->getEXP() << endl;
                }
            }
            delete item;
        }
        else if (command == "GET")
        {
            BaseItem *item = nullptr;
            // Sherlock
            item = sherlockBag->get();
            OUTPUT << sherlockBag->str() << endl;
            if (item != nullptr)
            {
                OUTPUT << "Item sherlock can use is : " << item->str() << endl;

                OUTPUT << "Sherlock stats : HP = "
                       << sherlock->getHP() << " ; EXP = "
                       << sherlock->getEXP() << endl;
                delete item;
                item = nullptr;
            }
            else
            {
                OUTPUT << "Sherlock can not use any items" << endl;
            }
            // Watson
            item = watsonBag->get();
            OUTPUT << watsonBag->str() << endl;
            if (item != nullptr)
            {
                OUTPUT << "Item watson can use is : " << item->str() << endl;

                OUTPUT << "Watson stats : HP = "
                       << watson->getHP() << " ; EXP = "
                       << watson->getEXP() << endl;
                if (item != nullptr)
                    delete item;
                item = nullptr;
            }
            else
            {
                OUTPUT << "Watson can not use any items" << endl;
            }
        }
        else if (command == "GETITEM")
        {
            BaseItem *item = nullptr;
            ItemType itemType = MAGIC_BOOK;
            // !if else testcase
            string itemName = "";
            ss >> itemName;
            if (itemName == "MagicBook")
                itemType = MAGIC_BOOK;
            else if (itemName == "EnergyDrink")
                itemType = ENERGY_DRINK;
            else if (itemName == "FirstAid")
                itemType = FIRST_AID;
            else if (itemName == "ExcemptionCard")
                itemType = EXCEMPTION_CARD;
            else if (itemName == "PassingCard")
                itemType = PASSING_CARD;
            item = dynamic_cast<BaseBag *>(sherlockBag)->get(itemType);
            // Sherlock
            OUTPUT << sherlockBag->str() << endl;
            if (item != nullptr)
            {

                OUTPUT << "Sherlock can use : " << item->str() << endl;

                delete item;
                item = nullptr;
            }
            else
            {
                OUTPUT << "Sherlock's bag doesn't have " << itemName << endl;
            }
            item = dynamic_cast<BaseBag *>(watsonBag)->get(itemType);
            // Watson
            OUTPUT << watsonBag->str() << endl;
            if (item != nullptr)
            {

                OUTPUT << "Watson can use : " << item->str() << endl;

                delete item;
                item = nullptr;
            }
            else
            {
                OUTPUT << "Watson's bag doesn't have " << itemName << endl;
            }
        }
    }

    // ! Delete có thể các bạn chưa thực hiện, có thể comment lại khi chưa được test
    delete sherlock;
    delete watson;
    delete map;
    delete criminal;
    delete robotC;
    delete robotS;
    delete robotW;
    delete robotSW;
    delete sherlockBag;
    delete watsonBag;
}

int main(int argc, char *argv[])
{
    cout << "Start program assignments 2 KTLT" << endl;
    cout << "Running test : ";
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
        cout << i << " ";
        string folderr = "testcase/output/output";
        // string folderr = "testcase/expect/expect";
        string inputFile = "testcase/input/input" + to_string(i) + ".txt";
        string outputFile = folderr + to_string(i) + ".txt";
        OUTPUT.open(outputFile);
        testAll(inputFile);
        OUTPUT.close();
    }
    cout << endl;
    comparefile(start, end);
}
