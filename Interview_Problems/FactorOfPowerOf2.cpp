/*Sept/23/2024

#include <iostream>
#include <vector>

using namespace std;

//std::vector<int>
void powerOfTwo(vector<int>& p){
    for(int i =0; i<p.size(); i++){
        if (p[i]==1){
                p[i]=1;
        }
        else{
            while(p[i]%2 == 0){
                p[i]/=2;
            }
            if(p[i]==1){
                p[i]=1;
            }
            else
                p[i]=0;
        }
    }
    //return p;
}

int main()
{
    std::vector<int> a={1,2,3,4,5,12,34,32,64,137}; // {1,1,0,1,0,0,0,1,1,0}
    cout << "program to check array value divisibal by 2^n or not: " << endl;
    powerOfTwo(a);
    for( auto x : a)
      cout << x <<" ";
    return 0;
}



/* ChatGpt Ans

#include <iostream>
#include <vector>

bool isDivisibleByPowerOf2(int number) {
    // Check if number is zero
    if (number == 0) return false;

    // Keep dividing by 2 while it's even
    while (number % 2 == 0) {
        number /= 2;
    }

    // If the result is 1, it was a power of 2
    return number == 1;
}

int main() {
    // Example array
    std::vector<int> arr = {4, 8, 15, 16, 23, 42, 32};

    for (int num : arr) {
        if (isDivisibleByPowerOf2(num)) {
            std::cout << num << " is divisible by a power of 2." << std::endl;
        } else {
            std::cout << num << " is not divisible by a power of 2." << std::endl;
        }
    }

    return 0;
}
*/
