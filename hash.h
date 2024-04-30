#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long int w[5] = {0};
        int wCount = 0;
        bool leadingZero = true;
        std::string newString = addZeroes(k);

        for(int i = 0; i < newString.length(); i++) {
            if(newString[i] != '0') {
                leadingZero = false;
            }
            if(i < 4) {
                if(!leadingZero) {
                    HASH_INDEX_T num = letterDigitToNumber(newString[i]);
                    w[wCount] += num;
                    if(i != 3) {
                        w[wCount] *= 36;
                    }
                    if(i == 3) {
                        wCount++;
                    }
                }
                else if(i == 3 && leadingZero) {
                    wCount++;
                }
            } 
            else if(i >= 4 && i <= 9) {
                if(!leadingZero) {
                    HASH_INDEX_T num = letterDigitToNumber(newString[i]);
                    w[wCount] += num;
                    if(i != 9) {
                        w[wCount] *= 36;
                    }
                    if(i == 9) {
                        wCount++;
                    }
                }
                else if(i == 9 && leadingZero){
                    wCount++;
                }
            }
            else if(i >= 10 && i <= 15) {
                if(!leadingZero) {
                    HASH_INDEX_T num = letterDigitToNumber(newString[i]);
                    w[wCount] += num;
                    if(i != 15) {
                        w[wCount] *= 36;
                    }
                    if(i == 15) {
                        wCount++;
                    }
                }
                else if(i == 15 && leadingZero){
                    wCount++;
                }
            }
            else if(i >= 16 && i <= 21) {
                if(!leadingZero) {
                    HASH_INDEX_T num = letterDigitToNumber(newString[i]);
                    w[wCount] += num;
                    if(i != 21) {
                        w[wCount] *= 36;
                    }
                    if(i == 21) {
                        wCount++;
                    }
                }
                else if(i == 21 && leadingZero){
                    wCount++;
                }

            }
            else if(i >= 22 && i <= 27) {
                if(!leadingZero) {
                    HASH_INDEX_T num = letterDigitToNumber(newString[i]);
                    w[wCount] += num;
                    if(i != 27) {
                        w[wCount] *= 36;
                    }
                    if(i == 27) {
                        wCount++;
                    }
                }
                else if(i == 27 && leadingZero){
                    wCount++;
                }
            }
        }

        HASH_INDEX_T finalSum = 0;
        for(int i = 0; i < 5; i++) {
            finalSum += (rValues[i]*w[i]);
        }
        return finalSum;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T output;       
        if(letter >= 65 && letter <= 90) {      // letter is uppercase
            letter += 32;       // turning letter to lowercase
        }
        if(letter >= 97 && letter <= 122) {     // letter is lowercase
            if(letter >= 97 && letter <=106) {      // letters a-j
                letter -= 49;
                std::string s(1, letter);
                std::stringstream ss(s);
                ss >> output;
                return output;
            }
            else if(letter >= 107 && letter <= 116){ //letters k-s
                letter -= 59;
                std::string s(1, letter);
                std::stringstream ss{s};
                ss >> output;
                output += 10;
                return output;
            }
            else {      // letters u-z
                letter -= 69;
                std::string s(1, letter);
                std::stringstream ss{s};
                ss >> output;
                output += 20;
                return output;
            }
        }
        std::string s(1, letter);     // letter is a number
        std::stringstream ss(s);
        ss >> output;
        return output+26;

    }

    std::string addZeroes(const std::string& k) const {
        std::string s(28, '-');
        int pos = 0; int kpos = 0;
        for(int i = 27; i >= 0; i--) {       // putting leading 0's
            if(i >= k.length()) {
                s[pos] = '0';
                pos++;
            }
            else {
                s[pos] = k[kpos];
                pos++; kpos++;
            }
        }
        return s;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
