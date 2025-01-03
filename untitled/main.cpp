#include <iostream>
using namespace std;


//1. Write a C++ Program to Check Whether a Number is a Positive or Negative Number.
/*
int main() {

    int number;
    cout << "Type a number you want to check " << "\n";
    cin >> number;

    if(number < 0){
        cout << number << " is negative";
    }
    else if (number == 0){
        cout << number << " is not positive nor negative";
    }
    else cout << number << " is positive";
    return 0;
}
*/


//2. Write a Program to Find the Greatest of the Three Numbers.
/*
int main(){
    int array[] = {900, 7, 9, 1, 3, 77, 1, 9, 0, 104};
    int size = sizeof(array)/sizeof(array[0]);
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if(max < array[i]){
            max = array[i];
        }
    }
    cout << "The greatest number is " << max;
    return 0;
}
*/


//3. C++ Program To Check Whether Number is Even Or Odd
/*
int main() {
    int numbers[] = {1,2,3,4,4,6,7,79,12,1, 0};
    int size = sizeof(numbers)/sizeof(numbers[0]);

    for (int i = 0; i < size; i++) {

        if(numbers[i] % 2 == 0) {
            cout << numbers[i] << " is even" << '\n';
        }
        else { cout << numbers[i] << " is odd" << '\n' ;
        }
    }
    return 0;
}
*/

//4. Write a Program to Find the ASCII Value of a Character
/*
int main() {
    cout << "Write a letter" << "\n";
    char letter;
    cin >> letter;
    cout << "the ASCII Value of " << letter << " is " << int(letter);
    return 0;
}
*/

//5. Write a Program to Check Whether a Character is a Vowel or Consonant
/*
int main() {
    cout << "Type a character ";
    char ch;
    cin >> ch;
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o'
        || ch == 'u' || ch == 'A' || ch == 'E'
        || ch == 'I' || ch == 'O' || ch == 'U'){
        cout << "It is a vowel";
    }
   else cout << "It is a consonant";
   return 0;
}
 */

//



