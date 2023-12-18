/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>


// A function to test the output of the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n);

/***************************
 * Main function           *
 **************************/

int main() {  
    std::cout << "Text file: ";
	std::string file_name;
	std::cin >> file_name;

	std::ifstream in_File{"../code/" + file_name};  // modify path, if needed

	if (!in_File) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

    std::map<std::string, int> table;
    int counter{0};  // to count total number of words read from the input file

    std::string ignore = ".,!?:\"();"; 
    std::string word;

    while (in_File >> word) { // läser filen så l'nge det finns ord

        // remove 
        word.erase(
            std::remove_if(word.begin(), word.end(), [ignore](auto c) { // går igenom varje bokstav i word, om "bokstaven" c finns i ignore
                return ignore.contains(c); // tar bort om det innhåller tecken från ignore
                }
            ),
            word.end()
        );

        // transform to lowercase
        std::transform(word.begin(), word.end(), word.begin(), [](auto c) {
            return std::tolower(c);
            });

        counter++;
        table[word]++;
    }

    std::vector<std::pair<std::string, int>> freq;

    std::transform(table.begin(), table.end(), std::back_inserter(freq), [](const auto& pair) { // lägg in från table i freq för att enklare kunna sortera
        return pair;
        });
    
    std::sort(freq.begin(), freq.end(), [](const auto& a, const auto& b) { // sortera vektor
        // har dom samma frequence? om ja, ordna i alfabetisk ordning. om nej sortera efter antal frequences
        return a.second == b.second ? a.first < b.first : a.second > b.second;
        });

    /* ************** Testing **************** */

    test(table, freq, file_name, counter);
}


/*******************************
 * Test implementation         *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n) {

    std::ifstream file{"../code/out_" + file_name}; //modify path, if needed

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{0};
    int total{0};

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }

    /*
     * uppgift1_kort: 69 words
     * uppgift1.txt: 1063 words
     */

    assert(total == n);    // test if total number of words is correct
    assert(t == result1);  // test if map/table contents are correct

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{word, counter});
    }
    assert(v == result2);  // test if vector contents are correct

    std::cout << "\nPassed all tests successfully!!\n";
}
