
#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class TextEditor {
stack<char> left;
stack<char> right;
public:
    TextEditor() {
        
    }
    
    void addText(string text) {
        for(auto &c : text){
            left.push(c);
        }
    }
    
    int deleteText(int k) {
        int cnt=0;
        while(!left.empty() and k>0){
            left.pop();
            cnt++;
            k--;
        }
        return cnt;
    }
    
    string cursorLeft(int k) {
        while(!left.empty() and k>0){
            char c = left.top();left.pop();
            right.push(c);
            k--;
        }
		// returning the last min(10, len) characters to the left of the cursor
        return cursorShiftString();
    }
    
    string cursorRight(int k) {
        while(!right.empty() and k>0){
            char c = right.top();right.pop();
            left.push(c);
            k--;
        }
		// returning the last min(10, len) characters to the left of the cursor
        return cursorShiftString();
    }
    
	// function to return the last min(10, len) characters to the left of the cursor
    string cursorShiftString(){
        string rtn = "";
        int cnt=10;
        while(!left.empty() and cnt>0){
            char c = left.top();left.pop();
            rtn += c;
            cnt--;
        }
        reverse(rtn.begin(),rtn.end());
        for(int i=0;i<rtn.size();i++){
            left.push(rtn[i]);
        }
        return rtn;
    }
};



int main() {
    TextEditor textEditor;

    textEditor.addText("Hello, World!");

    std::cout << "Initial Text: " << textEditor.cursorShiftString() << std::endl;

    int deletedChars = textEditor.deleteText(5);
    std::cout << "Deleted " << deletedChars << " characters. Text now: " << textEditor.cursorShiftString() << std::endl;

    textEditor.addText(" OpenAI");
    std::cout << "Added text. Text now: " << textEditor.cursorShiftString() << std::endl;

    std::string movedLeft = textEditor.cursorLeft(3);
    std::cout << "Moved cursor left. Text now: " << movedLeft << std::endl;

    std::string movedRight = textEditor.cursorRight(2);
    std::cout << "Moved cursor right. Text now: " << movedRight << std::endl;

    return 0;
}
