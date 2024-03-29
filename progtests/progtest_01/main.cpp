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

//using namespace std;
#endif /* __PROGTEST__ */


int to_int_12(const char *string, int len) {
    int n = 0;

    for (int i = 0; i < len; i++) {
        n <<= 1;
        n |= string[i];
    }

    return n;
}


class FileManager {
public:
    bool get_bit() {
        // Loading bits should not matter to huffmann encoded strings limit
        if (this->in_file_vector.size() <= current)
            throw std::runtime_error("Out of range of the vector's in_file_vector");

        return _get_bit();
    };

    void decrement_remaining_chars_if_valid() {
        chars_till_next_chunk--;
    }


    FileManager(std::string &input, std::string &output) {

        this->is.open(input, std::ios::binary | std::ios::in);
        this->os.open(output, std::ios::binary | std::ios::out);

        if (!this->is)
            throw std::runtime_error("I/O can not open input stream");

        if (!this->os)
            throw std::runtime_error("I/O can not open output stream");

        // whatever, it should pass the memory limit anyway
        // better solution would be a custom
        std::cout << "Loading in_file_vector " << input << std::endl;
        char c;
        while (this->is.get(c)) {

            for (int i = 7; i >= 0; i--) { // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
                bool tmp = ((c >> i) & 1);
                std::cout << tmp;
                in_file_vector.push_back(tmp);
            }
            std::cout << " ";

            if (is.fail())
                throw std::runtime_error("Input error - unable to read from in_file_vector");
            if (is.eof()) {
                std::cout << std::endl << "EOF " << std::endl;
                is.close();    // left the loop and ! eof -> error reading the in_file_vector.
            }
        }
        std::cout << std::endl;
    }

    ~FileManager() {
        // need to remove rest of the stuff from the buffer
        if (this->out_buffer.size()) {
            uint8_t n = 0;
            for (int i = 0; i < 8; i++) {
                n <<= 1;
                if (this->out_buffer.size()) {
                    n |= this->out_buffer.front();
                    this->out_buffer.pop();
                } else {
                    n |= 0;
                }
            }
            this->os << n;
        }

        this->os.close();
        this->is.close();
    };


    std::vector<bool> get_bits(int how_many);

    std::vector<bool> read_utf_or_ascii_char();

    void write(bool bit) {
        // can not write bit directly, need to collect at least 1byte
        this->out_buffer.push(bit);
        write_buffer();
    };

    void write_buffer() {
        std::cout << "running write to in_file_vector, in buffer there is " << this->out_buffer.size() << " bits "
                  << std::endl;
        while (this->out_buffer.size() >= 8) {
            uint8_t n = 0;

            for (int i = 0; i < 8; i++) {
                n <<= 1;
                n |= out_buffer.front();
                out_buffer.pop();
            }
            this->os << n;
            if (this->os.bad())
                throw std::runtime_error("I/O error while writing buffer from buffer");

            std::cout << "writing to ostream '" << n << "'" << std::endl;
            std::cout << "-- in buffer there is " << this->out_buffer.size() << " bits " << std::endl;

        }
    }


    void write(const std::vector<bool> &bits) {
        // okay, I don't like it neither
        std::cout << " Writing to out_buffer: ";
        for (auto b: bits) {
            this->out_buffer.push(b);
            //std::cout << b;
        }
        //std::cout << std::endl;
        write_buffer();
    };

    bool can_continue_reading_from_buffer() const {
        return this->current < this->in_file_vector.size();
    };

    bool is_everything_processed() const {
        return (!this->full_chunk && this->chars_till_next_chunk <= 0);
    };

    void load_how_much_is_in_next_chunk() {
        if (!_get_bit()) {
            char rem[12];

            for (char &i: rem) {
                i = _get_bit();
            }
            this->chars_till_next_chunk = to_int_12(rem, 12);
            full_chunk = false;

        } else {
            full_chunk = true;
            this->chars_till_next_chunk = 4096;
        }
        std::cout << "To the next chunk chars: " << chars_till_next_chunk << "  huffmann-encoded chars are remainging"
                  << std::endl;
    }


    bool full_chunk = true;
    int chars_till_next_chunk = 0;
    std::vector<bool> in_file_vector;

protected:

    bool eof() {
        return is.eof();
    };

    bool _get_bit() {
        // this one does skip the chunks stuff
        //if(current >= (in_file_vector.size()-1))
        //    cout << "asdf " << std::endl;
        return this->in_file_vector.at(current++);
    };


    std::ifstream is;
    std::ofstream os;
    std::queue<bool> out_buffer;

    unsigned long current = 0;
};


std::vector<bool> FileManager::read_utf_or_ascii_char() {
    // If an UCS fits 7 bits, its coded as 0xxxxxxx. This makes ASCII character represented by themselves
    //If an UCS fits 11 bits, it is coded as 110xxxxx 10xxxxxx
    //If an UCS fits 16 bits, it is coded as 1110xxxx 10xxxxxx 10xxxxxx
    //If an UCS fits 21 bits, it is coded as 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    //If an UCS fits 26 bits, it is coded as 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    //If an UCS fits 31 bits, it is coded as 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx



    std::vector<bool> tmp_0 = get_bits(8);
    // ASCII
    if (!tmp_0[0]) {
        return tmp_0;
    }
        // UTF 11 bits, it is coded as 110xxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && !tmp_0[2]) {
        std::vector<bool> tmp_1 = get_bits(8);
        if (tmp_1[0] && !tmp_1[1]) {
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
            return tmp_0;
        }
    }
        // UTF 16 bits, it is coded as 1110xxxx 10xxxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && !tmp_0[3]) {
        std::vector<bool> tmp_1 = get_bits(8);
        std::vector<bool> tmp_2 = get_bits(8);
        if (tmp_1[0] && !tmp_1[1] && tmp_2[0] && !tmp_2[1]) {
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_1), std::end(tmp_1));
            tmp_0.insert(std::end(tmp_0), std::begin(tmp_2), std::end(tmp_2));

            return tmp_0;
        }
    }
        // UTF 21 bits, it is coded as 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && tmp_0[3] && !tmp_0[4]) {
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
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && tmp_0[3] && tmp_0[4] && !tmp_0[5]) {
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
    else if (tmp_0[0] && tmp_0[1] && tmp_0[2] && tmp_0[3] && tmp_0[4] && tmp_0[5] && !tmp_0[6]) {
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

std::vector<bool> FileManager::get_bits(int how_many) {

    if (this->in_file_vector.size() < current + how_many)
        throw std::runtime_error("Out of range of the vector's in_file_vector");

    std::vector<bool> result = {this->in_file_vector.begin() + current,
                                this->in_file_vector.begin() + current + how_many};
    current += how_many;
    return result;
}

struct node {
    std::vector<bool> data;
    node *left{};
    node *right{};
    std::string prefix;
};


class HuffmannEncodingManager {
public:
    explicit HuffmannEncodingManager(FileManager &fm) : fm(fm) {};

    bool decompress();

    bool compress();

    std::vector<bool> read_key_and_get_value();

    void load_tree();

private:
    void new_node(node **currentNode);

    bool _load_subtree(node *n, std::string str_prefix);

    node *root = nullptr;
    int tree_empty = 0;
    FileManager &fm;
};

bool HuffmannEncodingManager::decompress() {
    // load whole tree to the memory (map: key:value)
    // decode key by key and write to the output in_file_vector

    load_tree();

    fm.load_how_much_is_in_next_chunk();

    // after loading, there is some chunks in_file_vector section
    // there is bit 1 if there are 4096 bits in the huffmann code
    // if there is bit 0, following 12 bits are number of letters to be decoded, e.g. 110110111000
    while (this->fm.can_continue_reading_from_buffer() && !fm.is_everything_processed()) {
        if (fm.chars_till_next_chunk == 0) {
            fm.load_how_much_is_in_next_chunk();
            if (fm.chars_till_next_chunk == 0)
                return true;
        }

        std::vector<bool> my_char = read_key_and_get_value();
        fm.decrement_remaining_chars_if_valid();
        this->fm.write(my_char);
    }
    if (!this->fm.can_continue_reading_from_buffer() && fm.chars_till_next_chunk > 0)
        throw std::runtime_error("File stream ended, but there are " + std::to_string(fm.chars_till_next_chunk) +
                                 " remaining chars to be loaded");

    return true;
}

std::vector<bool> HuffmannEncodingManager::read_key_and_get_value() {
    node *current_node = this->root;
    //std::cout << "read_key_and_get_value: ";
    while (current_node->right != nullptr && current_node->left != nullptr) { // need to find the leaf
        if (this->fm.get_bit())
            current_node = current_node->right;
        else
            current_node = current_node->left;
    }
    //std::cout << " prefix: " << current_node->prefix << std::endl;
    if (current_node->data.empty())
        throw std::runtime_error(
                "read_key_and_get_value: Current node (prefix=" + current_node->prefix + " has empty data");

    return current_node->data;
}

void HuffmannEncodingManager::load_tree() {

    new_node(&this->root);
    tree_empty = 1;

    while (_load_subtree(this->root, ""));
}

bool HuffmannEncodingManager::compress() {
    // load all chars to memory
    // sort by most often


// create a binary tree (map) and write it to the in_file_vector
// read the in_file_vector again and encode it

// load to the tree

while (this->fm.

can_continue_reading_from_buffer()

) {
std::vector<bool> my_char = this->fm.read_utf_or_ascii_char();
// whatever, it won't be a good compression, but we can try to
// just read letter by letter
}
return false;
}

bool HuffmannEncodingManager::_load_subtree(node *n, std::string str_prefix) {
    std::cout << "_load_subtree prefix: " << str_prefix << std::endl;
    if (tree_empty == 0 && n == root) {
        if (this->fm.get_bit()) {
            if (fm.can_continue_reading_from_buffer()) {
                if (!fm.is_everything_processed())
                    this->root->data = read_key_and_get_value();
                else
                    return false;
            } else {
                throw std::runtime_error("HuffmannEncodingManager can't read while load_tree");
            }
            return false;
        }
    }
    if (tree_empty == 0 && n != root)
        throw std::runtime_error("There is no space for other letters.");
    // return false;

    if (!fm.can_continue_reading_from_buffer())
        throw std::runtime_error("_load_subtree: can not read from buffer");

    n->prefix = str_prefix;
    if (!this->fm.get_bit()) {
        std::cout << "creating new nodes" << std::endl;
        new_node(&n);
        new_node(&n);
        tree_empty++;

        _load_subtree(n->left, n->prefix + "0");
        _load_subtree(n->right, n->prefix + "1");
    } else {
        // load char
        std::cout << "Loading char" << std::endl;
        std::vector<bool> _char = this->fm.read_utf_or_ascii_char();
        for (bool byte: _char)
            std::cout << byte;

        std::cout << std::endl;

        n->data = std::vector<bool>(_char);
        tree_empty--;

    }

    std::cout << "Currently " << tree_empty << " empty nodes" << std::endl;
    if (n != root) {
        if (tree_empty == 0)
            return false;
        else
            return true;
    }
    return false; // this should not happen
}

void HuffmannEncodingManager::new_node(node **currentNode) {
    if (*currentNode == nullptr) {
        *currentNode = new node;
        (*currentNode)->data = std::vector<bool>();
        (*currentNode)->left = nullptr;
        (*currentNode)->right = nullptr;
    } else if ((*currentNode)->left == nullptr) { // pokud je vlevo nullptr, pak tam muzu vytvorit novy node
        (*currentNode)->left = new node;
        (*currentNode)->left->data = std::vector<bool>();
        (*currentNode)->left->left = nullptr;
        (*currentNode)->left->right = nullptr;
    } else if ((*currentNode)->right == nullptr) {
        (*currentNode)->right = new node;
        (*currentNode)->right->data = std::vector<bool>();
        (*currentNode)->right->left = nullptr;
        (*currentNode)->right->right = nullptr;
    } else {
        //std::cout << "Can not create new node - right and left leaf already filled." << std::endl;
        throw std::runtime_error("Tree is already filled");
    }
}


// Při dekompresi je potřeba nejprve načíst serializovaný kódovací strom. Načítání je rekurzivní.
// Rekurzivní funkce čte jeden bit ze souboru. Pokud načte bit 0, vytvoří vnitřní uzel a 2x se rekurzivně zavolá pro levý a pravý podstrom.
// Pokud načte bit 1, načte ještě následující ASCII/UTF-8 znak a vytvoří pro něj odpovídající listový uzel.


bool decompressFile(const char *inFileName, const char *outFileName) {
    std::string infile = inFileName;
    std::string outfile = outFileName;
    std::cout << "***************** Decomress " << infile << " ********************" << std::endl;

    try {
        FileManager fm(infile, outfile);
        HuffmannEncodingManager hm(fm);
        hm.decompress();
    }
    catch (std::runtime_error &exception) {
        std::cout << exception.what() << std::endl;
        return false;
    }
    return true;
}

bool compressFile(const char *inFileName, const char *outFileName) {
    std::string infile = inFileName;
    std::string outfile = outFileName;
    std::cout << "***************** Compress " << infile << " ********************" << std::endl;

    return false;
    /*
     * Maybe in another life when I'll be reborn as a briliant C++ engineer.
     * But.. I would get it to the vector, then make an occurrence map, according to the occurrence
     * I'd create the tree representation (that would be the tricky one) and.. from that point it's easy.
    try {
        FileManager fm(infile, outfile);
        HuffmannEncodingManager hm(fm);
        hm.compress();
    }
    catch (std::runtime_error &exception) {
        std::cout << exception.what() << std::endl;
        return false;
    }
    return true;
     */
}

#ifndef __PROGTEST__

bool identicalFiles(const char *fileName1, const char *fileName2) {

/*
    std::ifstream file1(fileName1, ios::in);
    std::ifstream file2(fileName2, ios::in);


    std::cout << "File1" << std::endl;

    char c;
    while (file1.get(c)) {
        std::cout << c;
    }
    cout << std::endl;
    cout << std::endl;
    cout << std::endl;

    std::cout << "File2" << std::endl;

    while (file2.get(c)) {
        std::cout << c;
    }


    cout << std::endl;
    cout << std::endl;
    cout << std::endl;
*/

    try {
        std::ifstream myfile1(fileName1, std::ifstream::ate | std::ifstream::binary);
        std::ifstream myfile2(fileName2, std::ifstream::ate | std::ifstream::binary);

        // something went wrong with filestreams
        if (!myfile1.good() || !myfile2.good())
            return false;

        const std::ifstream::pos_type fsize = myfile1.tellg();

        // in_file_vector size unequal
        if (fsize != myfile2.tellg())
            return false;

        myfile1.seekg(0);
        myfile2.seekg(0);
        std::istreambuf_iterator<char> begin1(myfile1);
        std::istreambuf_iterator<char> begin2(myfile2);

        return std::equal(begin1, std::istreambuf_iterator<char>(), begin2);
    }
    catch (...) {
        return false;
    }

}

int main() {

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

    // extra tests
    assert(decompressFile("tests/progtest_01.huf", "tempfile"));
    assert(!decompressFile("tests/progtest_02.huf", "tempfile"));

    assert(!decompressFile("tests/in_4585071.huf", "tempfile"));
    assert(decompressFile("tests/in_4585946.huf", "tempfile"));
    assert(!decompressFile("tests/in_4586298.huf", "tempfile")); // this one is failing

    return 0;
}

#endif /* __PROGTEST__ */
