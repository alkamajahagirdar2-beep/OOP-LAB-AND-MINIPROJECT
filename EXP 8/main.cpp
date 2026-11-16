#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    vector<int> marks = {70, 85, 60, 90, 75};

    sort(marks.begin(), marks.end());

    cout << "Sorted Marks: ";

    for (int x : marks)
        cout << x << " ";

    cout << endl;

    auto it = find(marks.begin(), marks.end(), 85);

    if (it != marks.end())
        cout << "85 Found" << endl;

    auto result = find_if(marks.begin(), marks.end(),
                          [](int x) { return x > 80; });

    if (result != marks.end())
        cout << "First mark above 80: " << *result << endl;

    transform(marks.begin(), marks.end(),
              marks.begin(), [](int x) { return x + 5; });

    cout << "Updated Marks: ";

    for (int x : marks)
        cout << x << " ";

    cout << endl;

    map<int, string> students;
    students[1] = "Rahul";
    students[2] = "Aman";

    cout << "Student: " << students[1] << endl;

    unordered_map<int, int> data;
    data[1] = 100;

    cout << "Unordered Map: " << data[1] << endl;

    return 0;
}