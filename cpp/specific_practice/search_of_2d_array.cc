#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        vector<int>& rFinal = array[array.size() - 1];
        int max = rFinal[rFinal.size() - 1];
        int min = array[0][0];
        return (target >= min && target <= max);
    }
};

int main()
{
	vector<vector<int> >  array(2, vector<int>(4));
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			array[i][j] = i + j + 1;
		}
	}

	Solution s;
	std::cout << s.Find(1, array) << std::endl;
	return 0;
}
