#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <vector>
// #include <map>

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

void s_panGram(std::vector<std::string> pan){
    std::string op;
    for(int i=0; i<pan.size(); i++){
        if(isPangram(pan[i]))
            op+="1";
        else
            op+="0";
    }
    std::cout<<op<<std::endl;
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
    s_panGram({"qwertyuiopasdfghjklzxcvbnm", "ouysadvhasvdjasdj", "hdvsdhkKJDkhjdsguiDGidguID", "mnbvcxzasdfghjklpoiuytrewq"});

    return 0;
}
