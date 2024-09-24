/*Sept/23/2024

#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <map>

bool isPangram(const std::string& str) {
    std::unordered_set<char> letters;
    //std::map<char,bool> letters;
    // Iterate through each character in the string
    for (char ch : str) {
        // Convert to lowercase and check if it's a letter
        if (std::isalpha(ch)) {
            letters.insert(std::tolower(ch));
            //letters.insert({std::tolower(ch),true});
        }
    }

    // Check if we have all 26 letters of the alphabet
    return letters.size() == 26;
}

int main() {
    std::string input;

    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    if (isPangram(input)) {
        std::cout << "The string is a pangram." << std::endl;
    } else {
        std::cout << "The string is not a pangram." << std::endl;
    }

    return 0;
}


/* My Code in Ford Coding Interview:

#include <iostream>
#include <vector>
#include <string>

string isPangram(vector<std::string> pangram){
    std::string op ="";
    int flag =0;
    int track =0;
    for (int i=0; i<pangram.size();i++){
        for (char c:pangram[i]){
            for(char _c='a'; c<='z';c++){
                if(c==' ')
                  flag=1;
                if(c == _c)
                  flag=1;
            }
            if(flag == 1)
              track =1;
            else
              track =0;
        }

        if(track == 1)
          op +="1";
        else
          op +="0";
    }
}

int main()
{
    vector<std::string> p1;
    p1 = "qwertyuiopasdfghjklzxcvbnm mnbv";
    std::string result = isPangram(p1);
    std::cout<<"Hello World";

    return 0;
} */
