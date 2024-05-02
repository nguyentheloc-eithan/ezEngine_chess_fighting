#include <iostream>
#include <string>
using namespace std;

void updateCoordinates(const std::string &s, int &x, int &y)
{
    // Find the position of the comma to separate x and y values
    size_t commaPos = s.find(',');

    // Extract substrings for x and y values
    std::string xStr = s.substr(1, commaPos - 1);
    std::string yStr = s.substr(commaPos + 1, s.size() - commaPos - 2);

    // Convert substrings to integers
    x = std::stoi(xStr);
    y = std::stoi(yStr);
}
string stre(int r, int c)
{
    string x = to_string(r);
    string y = to_string(c);
    string result = "(" + x + "," + y + ")";
    return result;
}
int main()
{
    std::string input = "(2,7)";
    int x = 0, y = 0;

    // Update coordinates
    updateCoordinates(input, x, y);

    // Print updated coordinates
    std::cout << stre(2, 3) << std::endl;

    return 0;
}
