#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */



class FileManager {
public:
    bool get_bit() {
        return this->file.at(current++);
    };
    ~FileManager(){
        // need to remove rest of the stuff from the buffer
        uint8_t n = 0;
        for (int i = 0; i < 8; i++) {
            n <<= 1;
            if(this->out_buffer.size()){
                n |= this->out_buffer.first();
                this->out_buffer.pop();
            }
            else {
                n |= 0;
            }
        }
        this->ofstream << n;
    };


    vector<bool> get_bits(int how_many);

    std::vector<bool> read_utf_or_ascii_char();

    void write(bool bit) {
        // can not write bit directly, need to collect at least 1byte
        this->buffer.push(bit);
        write_buffer();
    };

    void write_buffer(){
        while(this->out_buffer.size() >= 8){
                uint8_t n = 0;

                for (int i = 0; i < 8; i++) {
                    n <<= 1;
                    n |= out_buffer.first();
                    out_buffer.pop();
                }
                this->ofstream << n;
            }
        }

    void read_file(string &filename);


    void write(std::vector<bool> bits) {
        this->out_buffer.emplace(std::end(this->out_buffer), std::begin(bits), std::end(bits));
        write_buffer();
    };

    void read_file(std::string &filename);

    bool is_okay() {
        return this->is.good();
    };

protected:


    bool eof() {
        return is.eof();
    };

    ifstream is;
    ofstream ofstream;
    std::queue<bool> out_buffer;
    vector<bool> file;
    int current = 0;
};

void FileManager::read_file(std::string &filename) {
    is = istream(filename, ios::binary | ios::in);

    // whatever, it should pass the memory limit anyway
    // better solution would be a custom
    char c;
    while (is.get(c)) {

        for (int i = 7; i >= 0; i--) { // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
            bool tmp = ((c >> i) & 1);
            cout << tmp;
            file.push_back(tmp);
        }

        if (is.fail())
            throw runtime_error("Input error - unable to read from file");
        if (is.eof()) {
            if (true) std::cout << std::endl << "EOF " << std::endl;
            is.close();    // left the loop and ! eof -> error reading the file.
        }
    }
}

std::vector<bool> FileManager::read_utf_or_ascii_char() {
    // If an UCS fits 7 bits, its coded as 0xxxxxxx. This makes ASCII character represented by themselves
    //If an UCS fits 11 bits, it is coded as 110xxxxx 10xxxxxx
    //If an UCS fits 16 bits, it is coded as 1110xxxx 10xxxxxx 10xxxxxx
    //If an UCS fits 21 bits, it is coded as 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    //If an UCS fits 26 bits, it is coded as 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    //If an UCS fits 31 bits, it is coded as 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    std::vector<bool> tmp_0 = get_bits(8);
    if (tmp_0[0] == false) // ASCII
    {
        return tmp_0;
    }
    // UTF 11 bits, it is coded as 110xxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && !tmp_0[2])
    {
        std::vector<bool> tmp_1 = get_bits(8);
        if (tmp_1[0] && !tmp_1[1])
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
        return tmp_0;
    }
    // UTF 16 bits, it is coded as 1110xxxx 10xxxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && !tmp_0[3])
    {
        std::vector<bool> tmp_1 = get_bits(8);
        std::vector<bool> tmp_2 = get_bits(8);
        if (tmp_1[0] && !tmp_1[1] && tmp_2[0] && !tmp_2[1]) {
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_2), std::end(tmp_2));

            return tmp_0;
        }

    }
    // UTF 21 bits, it is coded as 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && tmp_0[3] && !tmp_0[4])
    {
        std::vector<bool> tmp_1 = get_bits(8);
        std::vector<bool> tmp_2 = get_bits(8);
        std::vector<bool> tmp_3 = get_bits(8);

        if (tmp_1[0] && !tmp_1[1] && tmp_2[0] && !tmp_2[1] && tmp_3[0] && !tmp_3[1]) {
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_2), std::end(tmp_2));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_3), std::end(tmp_3));

            return tmp_0;
        }

    }
    // UTF fits 26 bits, it is coded as 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && tmp_0[3] && tmp_0[4] && !tmp_0[5])
    {
        std::vector<bool> tmp_1 = get_bits(8);
        std::vector<bool> tmp_2 = get_bits(8);
        std::vector<bool> tmp_3 = get_bits(8);
        std::vector<bool> tmp_4 = get_bits(8);

        if (tmp_1[0] && !tmp_1[1] &&
            tmp_2[0] && !tmp_2[1] &&
            tmp_3[0] && !tmp_3[1] &&
            tmp_4[0] && !tmp_4[1]) {
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_2), std::end(tmp_2));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_3), std::end(tmp_3));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_4), std::end(tmp_4));

            return tmp_0;
        }

    }
    // UTF fits 31 bits, it is coded as 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && tmp_0[3] && tmp_0[4] && tmp_0[5] && !tmp_0[6])
    {
        std::vector<bool> tmp_1 = get_bits(8);
        std::vector<bool> tmp_2 = get_bits(8);
        std::vector<bool> tmp_3 = get_bits(8);
        std::vector<bool> tmp_4 = get_bits(8);
        std::vector<bool> tmp_5 = get_bits(8);

        if (tmp_1[0] && !tmp_1[1] &&
            tmp_2[0] && !tmp_2[1] &&
            tmp_3[0] && !tmp_3[1] &&
            tmp_4[0] && !tmp_4[1]) {
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_2), std::end(tmp_2));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_3), std::end(tmp_3));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_4), std::end(tmp_4));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_5), std::end(tmp_5));

            return tmp_0;
        }

    }
    throw std::runtime_error("Invalid encoding detected");

}

vector<bool> FileManager::get_bits(int how_many) {
    vector<bool> result = {this->file.begin() + current, this->file.begin() + current + how_many};
    current +=how_many;
    return result;
}


// zacnu na root
// 001
/*
vytvorim dva nody, prefix "0"
vytvorim dva nody, prefix "00"
nactu hodnotu nodu, key = prefix + 1

*/

struct node {
    std::vector<bool> data;
    node *left;
    node *right;
};


class HuffmannEncodingManager {
public:
    HuffmannEncodingManager(FileManager fm){
        this->fm=fm;
    }

    bool decompress();
    bool compress();

    std::vector<bool> read_key_and_get_value();
    void load_tree();

private:
    void new_node(node **currentNode);
    bool _load_subtree(std::string str_prefix = "", node *n);
    node *root = nullptr;
    int tree_empty = 0;
    FileManager fm;
};

bool HuffmannEncodingManager::decompress() {
    // load whole tree to the memory (map: key:value)
    // decode key by key and write to the output file

    load_tree();

    while (this->fm.is_okay()) {
        std::vector<bool> my_char = read_key_and_get_value();
        this->fm.write(my_char);
    }
}

std::vector<bool> HuffmannEncodingManager::read_key_and_get_value() {
    node *current_node = this->root;
    while (current_node->left == NULL && current_node->right == NULL) {
        if (this->fm.get_bit())
            current_node = current_node->right;
        else current_node = current_node->left;
    }
    return current_node->data;
}
void HuffmannEncodingManager::load_tree() {
    _load_subtree("", this->root);
}

bool HuffmannEncodingManager::compress() {
    // load all chars to memory
    // sort by most often
    // create a binary tree (map) and write it to the file
    // read the file again and encode it

    while (this->fm.is_okay()) {
        std::vector<bool> my_char = this->fm.read_utf_or_ascii_char();
        // whatever, it won't be a good compression, but we can try to
        // just read letter by letter
    }
}
bool HuffmannEncodingManager::_load_subtree(std::string str_prefix = "", node *n) {
    if (tree_empty == 0 && n != root)
        return true;

    if (!this->fm.get_bit()) {
        new_node(&n);
        new_node(&n);
        tree_empty++;
        if (n == this->root)
            tree_empty++;

        _load_subtree(str_prefix + "0", n->left);
        _load_subtree(str_prefix + "1", n->right);
    } else {
        // load char
        vector<bool> _char = this->fm.read_utf_or_ascii_char();
        n->data = _char;
        tree_empty--;

    }
    std::cout << "Currently " << tree_empty << " empty nodes" << std::endl;
    if (tree_empty == 0 && n != root)
        return false;
    else return true;
}

void HuffmannEncodingManager::new_node(node **currentNode) {
    if (*currentNode == NULL) {
        *currentNode = new node;
        (*currentNode)->data = std::vector<bool>();
        (*currentNode)->left = NULL;
        (*currentNode)->right = NULL;
    } else if ((*currentNode)->left == NULL) { // pokud je vlevo null, pak tam muzu vytvorit novy node
        (*currentNode)->left = new node;
        (*currentNode)->left->data = std::vector<bool>();
        (*currentNode)->left->left = NULL;
        (*currentNode)->left->right = NULL;
    } else if ((*currentNode)->right == NULL) {
        (*currentNode)->right = new node;
        (*currentNode)->right->data = std::vector<bool>();
        (*currentNode)->right->left = NULL;
        (*currentNode)->right->right = NULL;
    } else {
        std::cout << "Can not create new node - right and left leaf already filled." << std::endl;
    }
}


// Při dekompresi je potřeba nejprve načíst serializovaný kódovací strom. Načítání je rekurzivní.
// Rekurzivní funkce čte jeden bit ze souboru. Pokud načte bit 0, vytvoří vnitřní uzel a 2x se rekurzivně zavolá pro levý a pravý podstrom.
// Pokud načte bit 1, načte ještě následující ASCII/UTF-8 znak a vytvoří pro něj odpovídající listový uzel.


bool decompressFile(const char *inFileName, const char *outFileName) {
    FileManager fm = FileManager();
    std::string file_name = inFileName;
    fm.read_file(file_name);

    HuffmannEncodingManager hm = HuffmannEncodingManager(fm);
    try {
        hm.decompress();
    }
    catch (runtime_error & exception)
    {
        return false;
    }

}

bool compressFile(const char *inFileName, const char *outFileName) {
    // keep this dummy implementation (no bonus) or implement the compression (bonus)
    FileManager fm = FileManager();
    std::string file_name = inFileName;
    fm.read_file(file_name);

    return false;
}

#ifndef __PROGTEST__

bool identicalFiles(const char *fileName1, const char *fileName2) {
    std::ifstream myfile1(fileName1, std::ifstream::ate | std::ifstream::binary);
    std::ifstream myfile2(fileName2, std::ifstream::ate | std::ifstream::binary);
    // something went wring with filestreams
    if (myfile1.bad() || myfile2.bad())
        return false;
    const std::ifstream::pos_type fsize = myfile1.tellg();

    // file size unequal
    if (fsize != myfile2.tellg())
        return false;

    myfile1.seekg(0);
    myfile2.seekg(0);
    std::istreambuf_iterator<char> begin1(myfile1);
    std::istreambuf_iterator<char> begin2(myfile2);

    return std::equal(begin1, std::istreambuf_iterator<char>(), begin2);

}

int main(void) {
    assert(decompressFile("tests/test0.huf", "tempfile"));
    assert(identicalFiles("tests/test0.orig", "tempfile"));

    assert(decompressFile("tests/test1.huf", "tempfile"));
    assert(identicalFiles("tests/test1.orig", "tempfile"));

    assert(decompressFile("tests/test2.huf", "tempfile"));
    assert(identicalFiles("tests/test2.orig", "tempfile"));

    assert(decompressFile("tests/test3.huf", "tempfile"));
    assert(identicalFiles("tests/test3.orig", "tempfile"));

    assert(decompressFile("tests/test4.huf", "tempfile"));
    assert(identicalFiles("tests/test4.orig", "tempfile"));

    assert(!decompressFile("tests/test5.huf", "tempfile"));


    assert(decompressFile("tests/extra0.huf", "tempfile"));
    assert(identicalFiles("tests/extra0.orig", "tempfile"));

    assert(decompressFile("tests/extra1.huf", "tempfile"));
    assert(identicalFiles("tests/extra1.orig", "tempfile"));

    assert(decompressFile("tests/extra2.huf", "tempfile"));
    assert(identicalFiles("tests/extra2.orig", "tempfile"));

    assert(decompressFile("tests/extra3.huf", "tempfile"));
    assert(identicalFiles("tests/extra3.orig", "tempfile"));

    assert(decompressFile("tests/extra4.huf", "tempfile"));
    assert(identicalFiles("tests/extra4.orig", "tempfile"));

    assert(decompressFile("tests/extra5.huf", "tempfile"));
    assert(identicalFiles("tests/extra5.orig", "tempfile"));

    assert(decompressFile("tests/extra6.huf", "tempfile"));
    assert(identicalFiles("tests/extra6.orig", "tempfile"));

    assert(decompressFile("tests/extra7.huf", "tempfile"));
    assert(identicalFiles("tests/extra7.orig", "tempfile"));

    assert(decompressFile("tests/extra8.huf", "tempfile"));
    assert(identicalFiles("tests/extra8.orig", "tempfile"));

    assert(decompressFile("tests/extra9.huf", "tempfile"));
    assert(identicalFiles("tests/extra9.orig", "tempfile"));

    return 0;
}

#endif /* __PROGTEST__ */
