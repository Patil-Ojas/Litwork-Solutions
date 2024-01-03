#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

class MyQueue {
public:
    stack<int> inputStack;
    stack<int> outputStack;

    void enqueue(int x) {
        while (!inputStack.empty()) {
            outputStack.push(inputStack.top());
            inputStack.pop();
        }
        inputStack.push(x);
        while (!outputStack.empty()) {
            inputStack.push(outputStack.top());
            outputStack.pop();
        }
    }

    void dequeue() {
        if (!inputStack.empty()) {
            int frontElement = inputStack.top();
            inputStack.pop();
            // Note: You might want to use frontElement in some way or print it.
        }
    }

    int peek() {
        return inputStack.top();
    }

    bool isEmpty() {
        return inputStack.empty();
    }
};

int main() {
    MyQueue* myQueue = new MyQueue();

    string input;
    cout << "Enter commands and numbers separated by commas. Enter 'q' to stop:\n";
    getline(cin, input);

    istringstream iss(input);
    vector<string> tokens;
    string token;
    while (getline(iss, token, ',')) {
        tokens.push_back(token);
    }

    for (const string& t : tokens) {
        if (t == "q") {
            break;
        }

        char command;
        int num;
        istringstream ss(t);
        ss >> command >> num;

        if (command == '1') {
            myQueue->enqueue(num);
        } else if (command == '2') {
            myQueue->dequeue();
        } else if (command == '3') {
            cout << "Peeked element: " << myQueue->peek() << endl;
        }
    }

    // Free the allocated memory
    delete myQueue;

    return 0;
}
