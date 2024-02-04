#include <iostream>
#include <vector>
#include <sstream>

struct ModifiedTrieNode {
    ModifiedTrieNode* children[26];
    bool isEnd;

    ModifiedTrieNode() {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
        isEnd = false;
    }
};

class ModifiedTrie {
public:
    ModifiedTrie() {
        root = new ModifiedTrieNode();
    }

    void insertWord(const std::string& word) {
        ModifiedTrieNode* node = root;
        for (char character : word) {
            int index = character - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new ModifiedTrieNode();
            }
            node = node->children[index];
        }
        node->isEnd = true;
    }

    bool hasPrefix(const std::string& word) {
        ModifiedTrieNode* node = root;
        for (char character : word) {
            int index = character - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
            if (node->isEnd) {
                return true;
            }
        }
        return false;
    }

private:
    ModifiedTrieNode* root;
};

bool checkPasswordValidity(const std::vector<std::string>& passwordList) {
    ModifiedTrie modifiedTrie;
    for (const std::string& pass : passwordList) {
        if (modifiedTrie.hasPrefix(pass)) {
            std::cout << "INVALID PASSWORD" << std::endl;
            return false;
        }
        modifiedTrie.insertWord(pass);
    }
    std::cout << "VALID PASSWORD" << std::endl;
    return true;
}

int main() {
    std::string userInput;
    std::getline(std::cin, userInput);
    std::stringstream inputParser(userInput);
    std::vector<std::string> passwordList;
    std::string currentPassword;
    while (inputParser >> currentPassword) {
        passwordList.push_back(currentPassword);
    }

    checkPasswordValidity(passwordList);

    return 0;
}
