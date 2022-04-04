#include <vector>
#include <stdint.h>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n)
    {
        Hash(SinglePass(cells));
        cells[0] = 0;
        cells[7] = 0;

        uint8_t repeated_state = 0;

        int i = 1;
        for (; i < n; ++i) {
            uint8_t state = SinglePass(cells);
            if (Hash(state)) {
                repeated_state = state;
                break; //we got old pattern;
            }
        }
        if(i == n) //we reached end
            return cells;

        int iterations = 1; //let's collect pattern
        for (; SinglePass(cells) != repeated_state; ++iterations) {

        }

        if (iterations == 0)
            return cells; //state is frozen, we done
        int steps_left = n - (i + 1);

        steps_left %= iterations; //real steps left

        for (i = 0; i < steps_left; ++i)
            SinglePass(cells); //let's make that steps

        return cells;
    }

private:
    bool states_hash[256] {0};

    bool Hash(uint8_t value)
    {
        if ((states_hash[value]) == 0) {
            states_hash[value] = 1;
            return false;
        } else {
            return true;
        }
    }

    uint8_t SinglePass(vector<int>& cells)
    {
        uint8_t ret = 0;
        int last_state = cells[0];
        for (int i = 1; i <= 6; ++i) { //last and first will be 0 anyway due to rules
            int new_state = !(last_state ^ cells[i + 1]);
            last_state = cells[i];
            cells[i] = new_state;
            ret += new_state << i;
        }
        return ret;
    }
};

int main()
{
    Solution sol;

/*    {
        vector<int> cells {0,1,0,1,1,0,0,1};
        vector<int> res = sol.prisonAfterNDays(cells, 7);
    } */
    vector<int> cells {1,0,0,1,0,0,1,0};
    vector<int> res = sol.prisonAfterNDays(cells, 1000000000);
    for (auto const &x : res)
        cout << x << ", ";
    return 0;
}
