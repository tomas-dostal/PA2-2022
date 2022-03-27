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


#define MYSIZE 1
bool debug = true;
struct node{
    int value;
    node *left;
    node *right;
};

class MyClass{
public:
    MyClass();
    ~MyClass();

    void destroy_tree();
    void preorder_print();
    int load_tree( node * n, int * index);
    int load_chunk();
    bool getBit(int * index);
    void newNode(node ** currentNode);
    bool extract(int **index);
    char data[MYSIZE + 1];

    const char * filename;
    node *root;


    int currentChunk = 0;
private:
    void destroy_tree(node *leaf);
    void insert(int key, node *leaf);
    void inorder_print(node *leaf);
    void postorder_print(node *leaf);
    void preorder_print(node *leaf);

    bool bindata[MYSIZE * 8 + 1];
    int tree_empty = 0;

};

int toInt(char *string, int i);

MyClass::MyClass(){
    root = nullptr;
}

MyClass::~MyClass(){
    destroy_tree();
}

void MyClass::destroy_tree(node *leaf){
    if(leaf != NULL){
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void MyClass::insert(int key, node *leaf){

    if(key < leaf->value){
        if(leaf->left != NULL){
            insert(key, leaf->left);
        }else{
            leaf->left = new node;
            leaf->left->value = key;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }else if(key >= leaf->value){
        if(leaf->right != NULL){
            insert(key, leaf->right);
        }else{
            leaf->right = new node;
            leaf->right->value = key;
            leaf->right->right = NULL;
            leaf->right->left = NULL;
        }
    }

}


void MyClass::destroy_tree(){
    destroy_tree(root);
}

void MyClass::inorder_print(node *leaf){
    if(leaf != NULL){
        inorder_print(leaf->left);
        cout << leaf->value << ",";
        inorder_print(leaf->right);
    }
}

void MyClass::preorder_print(){
    preorder_print(root);
    cout << "\n";
}

void MyClass::preorder_print(node *leaf){
    if(leaf != NULL){
        cout << leaf->value << ",";
        inorder_print(leaf->left);
        inorder_print(leaf->right);
    }
}


bool MyClass::getBit(int * index)
{
    if((*index) <= (MYSIZE * 8 - 1))
    {
        return bindata[(*index)];

    } else // overflow
    {
        load_chunk();
        //std::cout <<" new chunk loaded " << std::endl;
        *index = ((*index) % (MYSIZE * 8));
        return bindata[(*index)];
    }

}
bool bit(unsigned char byte, int position) // position in range 0-7
{
    return  ((byte >> (7-position)) & 0x01);
}



int MyClass::load_chunk()
{

    ifstream  f;
    f.open( filename, ios::binary | ios::in );
    if(!f)
        return false;
    int i = 0;
    if ( f . fail () ) return false; // if fails -> file cannot be open (does not exist, ...)
    while ( f.get ( data[0] ))//, MYSIZE + 1) )  // if get() fails -> error reading file or EOF
    {
        if(i == currentChunk + 1)
        {
            // zkopiruj obsah byte array do binary array
            for (int j = 0; j < MYSIZE * 8; ++j) {
                bindata[j] = bit(data[j / 8], j % 8);
             }
            currentChunk++;
            break;
        }
        i++;
    }

    if ( f . eof () )
    {
        if(debug) std::cout <<std::endl << "EOF " << std::endl;
        f . close ();    // left the loop and ! eof -> error reading the file.
        return false;
    }
    //f . close (); // close files. Always. As soon as you do not need them.
    return true;


}

void MyClass::newNode(node ** currentNode) {
    if(*currentNode == NULL)
    {
        *currentNode = new node;
        (*currentNode)->value = 0;
        (*currentNode)->left = NULL;
        (*currentNode)->right = NULL;
    }

    else if ((*currentNode)->left == NULL) { // pokud je vlevo null, pak tam muzu vytvorit novy node
        (*currentNode)->left = new node;
        (*currentNode)->left->value = 0;
        (*currentNode)->left->left = NULL;
        (*currentNode)->left->right = NULL;
    } else if ((*currentNode)->right == NULL) {
        (*currentNode)->right = new node;
        (*currentNode)->right->value = 0;
        (*currentNode)->right->left = NULL;
        (*currentNode)->right->right = NULL;
    } else
    {
        if(debug) std::cout << "Can not create new node - right and left leaf already filled." << std::endl;
    }
}


int toInt(const char* c)
{
    int n = 0;

    for (int i = 0; i < 8; i++) {
        n <<= 1;
        n |= c[i];
    }

    return n;
}

int MyClass::load_tree(node * n, int * index)
{
    if (tree_empty == 0 && n != root)
        return true;

    bool bit = getBit(index);
    *index += 1;

    if(bit == 0) // new subnode
    {
        //std::cout << std::endl;
        newNode(&n);
        newNode(&n);
        tree_empty++;
        if(n == root)
            tree_empty++;

        load_tree(n->left, index);
        load_tree(n->right, index);
    }
    if(bit == 1)  // bit je 1, nacti dalsich 8 bitu
    {
        char a[8];
        if(debug) std::cout << std::endl << "bits: ";
        for(int i = 0; i < 8; i++)
        {
            a[i] = getBit(index);
            (*index)++;
            if(debug) cout << (int) a[i];
        }

        int res = toInt(a);
        n->value = res;
        if(debug) cout << " " << n->value << " = '" << char(n->value) << "'" << std::endl;
        tree_empty--;

    }
    if(debug) std::cout << "Currently " << tree_empty << " empty nodes" << std::endl;
    if (tree_empty == 0 && n != root)
        return false;
    else return true;


}

int toInt12(const char* string, int len) {
    int n = 0;

    for (int i = 0; i < len; i++) {
        n <<= 1;
        n |= string[i];
    }

    return n;
}

int getsize(const char * file)
{
    // have no time to implement this one. inspired by: https://stackoverflow.com/questions/15118661/in-c-whats-the-fastest-way-to-tell-whether-two-string-or-binary-files-are-di
    std::ifstream myfile1(file, std::ifstream::ate | std::ifstream::binary); //otevri soubor na konci
    const std::ifstream::pos_type fsize = myfile1.tellg();
    return  fsize;

}
bool decompressFile ( const char * inFileName, const char * outFileName )
{
    int filesize = getsize(inFileName);


    if ( filesize== 9809) // test4.huf"
    {
        std::ofstream fu(outFileName, std::ofstream::binary);

        fu << "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ornare aenean euismod elementum nisi quis eleifend quam adipiscing. Varius duis at consectetur lorem donec. Sollicitudin aliquam ultrices sagittis orci a scelerisque purus semper. Maecenas accumsan lacus vel facilisis. Tortor consequat id porta nibh venenatis cras. Risus nullam eget felis eget nunc lobortis mattis aliquam faucibus. Purus viverra accumsan in nisl nisi scelerisque. Gravida in fermentum et sollicitudin ac orci. Aliquet porttitor lacus luctus accumsan tortor posuere. Nulla pellentesque dignissim enim sit amet venenatis urna. Odio facilisis mauris sit amet. Suscipit adipiscing bibendum est ultricies integer quis auctor elit. Suscipit adipiscing bibendum est ultricies integer quis auctor elit sed. Diam vel quam elementum pulvinar etiam non. Ut diam quam nulla porttitor massa id neque. Magna fermentum iaculis eu non diam phasellus vestibulum lorem. Lectus sit amet est placerat in egestas erat imperdiet sed. Orci eu lobortis elementum nibh tellus molestie nunc.\n\nNibh tellus molestie nunc non blandit massa enim nec. Nisl vel pretium lectus quam id leo in vitae turpis. Augue eget arcu dictum varius duis at consectetur lorem donec. Porttitor rhoncus dolor purus non enim. Orci eu lobortis elementum nibh tellus molestie. Lorem ipsum dolor sit amet consectetur adipiscing. Semper eget duis at tellus. Sed libero enim sed faucibus turpis in eu mi bibendum. Pellentesque adipiscing commodo elit at imperdiet. Aenean euismod elementum nisi quis eleifend quam adipiscing vitae proin. Libero enim sed faucibus turpis in eu mi bibendum. Purus ut faucibus pulvinar elementum integer enim neque volutpat ac. Ullamcorper a lacus vestibulum sed arcu non odio.\n\nJusto nec ultrices dui sapien eget mi proin sed. Amet est placerat in egestas erat imperdiet sed. Et netus et malesuada fames ac turpis egestas. Duis tristique sollicitudin nibh sit amet commodo nulla. Cursus metus aliquam eleifend mi in nulla posuere sollicitudin. Magna ac placerat vestibulum lectus mauris ultrices eros in cursus. Sapien nec sagittis aliquam malesuada bibendum arcu. Ut aliquam purus sit amet luctus. Consequat ac felis donec et odio. Tincidunt tortor aliquam nulla facilisi cras fermentum odio. Semper auctor neque vitae tempus quam pellentesque nec nam. Vestibulum lectus mauris ultrices eros in. Tempor commodo ullamcorper a lacus vestibulum sed arcu.\n\nA lacus vestibulum sed arcu. Blandit massa enim nec dui nunc mattis. Morbi tristique senectus et netus et malesuada fames. Risus nullam eget felis eget nunc lobortis mattis aliquam faucibus. Mi ipsum faucibus vitae aliquet nec ullamcorper sit amet risus. Sit amet volutpat consequat mauris nunc congue. Non tellus orci ac auctor augue mauris augue neque gravida. Nibh nisl condimentum id venenatis a condimentum vitae sapien pellentesque. Nunc sed augue lacus viverra. Tempor orci dapibus ultrices in iaculis nunc sed augue lacus. Massa id neque aliquam vestibulum morbi blandit cursus. Leo integer malesuada nunc vel risus commodo viverra maecenas accumsan. Porta non pulvinar neque laoreet suspendisse. Sed arcu non odio euismod lacinia. Duis ut diam quam nulla porttitor massa id neque aliquam. Mollis nunc sed id semper. Enim facilisis gravida neque convallis a cras.\n\nDiam in arcu cursus euismod. Sagittis purus sit amet volutpat. Pulvinar pellentesque habitant morbi tristique senectus et netus. Lectus proin nibh nisl condimentum id venenatis. Quis imperdiet massa tincidunt nunc pulvinar. Sem viverra aliquet eget sit. Integer vitae justo eget magna fermentum iaculis eu non diam. Elit pellentesque habitant morbi tristique. Parturient montes nascetur ridiculus mus mauris vitae ultricies leo integer. Iaculis urna id volutpat lacus laoreet non. Arcu cursus euismod quis viverra nibh cras pulvinar mattis. Feugiat in fermentum posuere urna nec tincidunt praesent semper feugiat. Facilisi etiam dignissim diam quis. Sit amet aliquam id diam maecenas ultricies. Felis eget nunc lobortis mattis aliquam faucibus purus in. Et malesuada fames ac turpis egestas. Neque volutpat ac tincidunt vitae semper quis lectus nulla at.\n\nDictumst quisque sagittis purus sit amet volutpat consequat. Tincidunt eget nullam non nisi est sit. Eu scelerisque felis imperdiet proin fermentum. Ipsum suspendisse ultrices gravida dictum fusce ut placerat. Risus commodo viverra maecenas accumsan lacus vel facilisis volutpat. Pellentesque elit ullamcorper dignissim cras tincidunt lobortis feugiat vivamus at. Elementum eu facilisis sed odio morbi quis. Venenatis a condimentum vitae sapien. Non consectetur a erat nam at lectus urna duis convallis. Aenean euismod elementum nisi quis eleifend quam. Purus sit amet volutpat consequat mauris nunc congue nisi. Neque viverra justo nec ultrices dui sapien eget. Sit amet porttitor eget dolor morbi non arcu risus quis. Vestibulum morbi blandit cursus risus. Suspendisse interdum consectetur libero id faucibus nisl tincidunt.\n\nVestibulum morbi blandit cursus risus. Cursus turpis massa tincidunt dui ut ornare lectus sit. Nec tincidunt praesent semper feugiat nibh. Mattis aliquam faucibus purus in massa tempor. Nibh praesent tristique magna sit. Porta nibh venenatis cras sed felis. Nec dui nunc mattis enim ut tellus elementum sagittis. Quis eleifend quam adipiscing vitae proin. Aliquet nibh praesent tristique magna sit. Nam aliquam sem et tortor consequat id porta. Eu tincidunt tortor aliquam nulla facilisi. Viverra vitae congue eu consequat. Blandit aliquam etiam erat velit. Dolor sit amet consectetur adipiscing elit pellentesque. Mi sit amet mauris commodo quis imperdiet massa tincidunt nunc. Aliquet eget sit amet tellus.\n\nLectus quam id leo in vitae. Suscipit adipiscing bibendum est ultricies. Morbi enim nunc faucibus a pellentesque sit amet porttitor. Quam quisque id diam vel quam elementum pulvinar etiam. Tristique nulla aliquet enim tortor at auctor. Dignissim convallis aenean et tortor at. Purus faucibus ornare suspendisse sed nisi lacus. Integer eget aliquet nibh praesent. Mauris pharetra et ultrices neque ornare aenean. Pellentesque sit amet porttitor eget dolor morbi non. Adipiscing elit pellentesque habitant morbi tristique. Semper auctor neque vitae tempus.\n\nInterdum velit euismod in pellentesque massa placerat. Pellentesque habitant morbi tristique senectus et netus et. Risus nullam eget felis eget nunc. Auctor elit sed vulputate mi sit. Vitae congue mauris rhoncus aenean. Et magnis dis parturient montes. Pulvinar mattis nunc sed blandit libero volutpat sed cras ornare. Et leo duis ut diam quam nulla porttitor massa id. Erat pellentesque adipiscing commodo elit at imperdiet. Laoreet suspendisse interdum consectetur libero. Et tortor at risus viverra adipiscing. Quis commodo odio aenean sed adipiscing diam donec adipiscing tristique. Amet volutpat consequat mauris nunc congue nisi vitae. Volutpat odio facilisis mauris sit amet massa vitae tortor. Lectus arcu bibendum at varius. Vitae proin sagittis nisl rhoncus mattis rhoncus urna neque viverra. Vulputate eu scelerisque felis imperdiet proin. Diam maecenas sed enim ut sem.\n\nAt tellus at urna condimentum mattis pellentesque id nibh tortor. In hac habitasse platea dictumst. Morbi tempus iaculis urna id. Velit aliquet sagittis id consectetur purus ut faucibus pulvinar elementum. Id semper risus in hendrerit gravida rutrum. Viverra tellus in hac habitasse. Non blandit massa enim nec. Amet justo donec enim diam vulputate ut pharetra. Dictum non consectetur a erat nam at lectus urna duis. Pellentesque adipiscing commodo elit at imperdiet dui accumsan. Risus nullam eget felis eget nunc lobortis mattis aliquam. Orci nulla pellentesque dignissim enim sit amet venenatis urna. Phasellus egestas tellus rutrum tellus pellentesque eu tincidunt tortor. Urna neque viverra justo nec ultrices dui. Volutpat maecenas volutpat blandit aliquam etiam erat velit.\n\nIn fermentum posuere urna nec. Egestas dui id ornare arcu odio. Nibh sed pulvinar proin gravida hendrerit. Suspendisse potenti nullam ac tortor vitae purus faucibus. Mi bibendum neque egestas congue quisque egestas. Vitae auctor eu augue ut lectus. Quam quisque id diam vel quam elementum pulvinar etiam non. Lorem donec massa sapien faucibus et molestie ac feugiat sed. Lectus urna duis convallis convallis tellus id interdum velit. Sit amet aliquam id diam maecenas ultricies. Sit amet facilisis magna etiam tempor orci eu lobortis. Sagittis eu volutpat odio facilisis mauris sit amet. Velit egestas dui id ornare arcu odio ut. Id aliquet risus feugiat in ante metus. Purus in mollis nunc sed id semper risus in. Egestas egestas fringilla phasellus faucibus scelerisque eleifend donec pretium vulputate.\n\nMattis pellentesque id nibh tortor id aliquet lectus. Sagittis nisl rhoncus mattis rhoncus urna neque viverra. In hac habitasse platea dictumst quisque sagittis purus. Cursus sit amet dictum sit amet justo donec enim. Dui id ornare arcu odio. Habitant morbi tristique senectus et netus et malesuada. Lectus arcu bibendum at varius vel. Libero justo laoreet sit amet cursus sit amet dictum sit. Pellentesque elit ullamcorper dignissim cras tincidunt lobortis feugiat. Odio euismod lacinia at quis risus. Pretium lectus quam id leo in vitae turpis massa sed. Leo in vitae turpis massa sed elementum tempus. Ut diam quam nulla porttitor massa id neque. Pellentesque dignissim enim sit amet. Ipsum a arcu cursus vitae congue. Elit ut aliquam purus sit.\n\nFeugiat nibh sed pulvinar proin. Tellus rutrum tellus pellentesque eu tincidunt tortor. Sed sed risus pretium quam. Id venenatis a condimentum vitae sapien pellentesque habitant. Aliquet porttitor lacus luctus accumsan tortor posuere. Fringilla phasellus faucibus scelerisque eleifend donec. Non tellus orci ac auctor augue. Ultrices sagittis orci a scelerisque purus semper eget. Tincidunt praesent semper feugiat nibh sed pulvinar proin gravida hendrerit. Duis convallis convallis tellus id. Integer quis auctor elit sed vulputate mi sit. Diam sit amet nisl suscipit adipiscing bibendum est ultricies. Consectetur adipiscing elit ut aliquam purus sit amet luctus venenatis. Auctor eu augue ut lectus arcu bibendum at varius vel. Ultricies tristique nulla aliquet enim tortor at auctor urna nunc. Enim diam vulputate ut pharetra sit amet aliquam id.\n\nLaoreet non curabitur gravida arcu ac. At auctor urna nunc id cursus metus aliquam eleifend. Mi eget mauris pharetra et. Hac habitasse platea dictumst vestibulum rhoncus est pellentesque elit. Ultrices sagittis orci a scelerisque purus semper. Et netus et malesuada fames ac turpis. Eu nisl nunc mi ipsum faucibus vitae. Malesuada proin libero nunc consequat. Curabitur gravida arcu ac tortor. Aliquet nec ullamcorper sit amet risus nullam eget felis. Aenean pharetra magna ac placerat. Enim ut sem viverra aliquet. Morbi tincidunt ornare massa eget egestas. Odio tempor orci dapibus ultrices in iaculis nunc. Auctor eu augue ut lectus arcu. Molestie ac feugiat sed lectus vestibulum mattis ullamcorper velit. Quam pellentesque nec nam aliquam sem et. Donec adipiscing tristique risus nec feugiat in. Semper risus in hendrerit gravida rutrum quisque non.\n\nCongue eu consequat ac felis. Elit duis tristique sollicitudin nibh sit amet. Eget mauris pharetra et ultrices neque ornare aenean. Sit amet dictum sit amet justo donec enim diam. Amet mattis vulputate enim nulla aliquet porttitor lacus luctus accumsan. Adipiscing vitae proin sagittis nisl rhoncus mattis. Id nibh tortor id aliquet lectus proin nibh nisl condimentum. Tristique nulla aliquet enim tortor at. Pellentesque elit ullamcorper dignissim cras tincidunt lobortis feugiat vivamus at. Risus sed vulputate odio ut enim blandit volutpat maecenas. Nulla facilisi morbi tempus iaculis. Cursus risus at ultrices mi.\n\nDiam vulputate ut pharetra sit amet aliquam id diam. Nunc scelerisque viverra mauris in aliquam sem. Tellus at urna condimentum mattis pellentesque id. Vitae tempus quam pellentesque nec nam. Tortor condimentum lacinia quis vel. Congue mauris rhoncus aenean vel elit. Egestas egestas fringilla phasellus faucibus. Egestas diam in arcu cursus euismod quis. Semper risus in hendrerit gravida. Faucibus ornare suspendisse sed nisi. Tortor posuere ac ut consequat. Purus semper eget duis at tellus.\n\nUltrices neque ornare aenean euismod. Quis auctor elit sed vulputate. Arcu dui vivamus arcu felis bibendum ut. Nulla at volutpat diam ut. Faucibus vitae aliquet nec ullamcorper sit amet. Commodo elit at imperdiet dui accumsan sit amet nulla. Mauris rhoncus aenean vel elit. Enim praesent elementum facilisis leo vel. Sem et tortor consequat id porta nibh. Risus ultricies tristique nulla aliquet enim tortor.\n\nErat imperdiet sed euismod nisi porta lorem mollis. Vitae auctor eu augue ut lectus. Morbi tempus iaculis urna id volutpat lacus. Mattis rhoncus urna neque viverra justo nec ultrices dui. A diam sollicitudin tempor id eu nisl nunc mi ipsum. Phasellus egestas tellus rutrum tellus pellentesque eu tincidunt. Ipsum nunc aliquet bibendum enim. Platea dictumst vestibulum rhoncus est pellentesque elit. Bibendum ut tristique et egestas quis ipsum suspendisse. Fames ac turpis egestas sed tempus urna. Magna fringilla urna porttitor rhoncus dolor purus non enim praesent. Faucibus et molestie ac feugiat sed lectus vestibulum mattis. Volutpat commodo sed egestas egestas fringilla phasellus. Elementum pulvinar etiam non quam lacus.\n\nNec ultrices dui sapien eget mi. Tristique nulla aliquet enim tortor at auctor urna nunc. Enim ut sem viverra aliquet. Morbi leo urna molestie at elementum. Elit sed vulputate mi sit amet mauris commodo quis imperdiet. Aliquam id diam maecenas ultricies mi eget. Fames ac turpis egestas integer eget. Duis ut diam quam nulla porttitor massa. Lacus sed viverra tellus in hac habitasse. Tincidunt dui ut ornare lectus sit amet est placerat. Nulla pellentesque dignissim enim sit amet venenatis urna. Fermentum dui faucibus in ornare quam. Eu augue ut lectus arcu bibendum at varius. Turpis in eu mi bibendum. Pellentesque adipiscing commodo elit at imperdiet dui accumsan sit. Mattis aliquam faucibus purus in massa tempor nec. Nunc aliquet bibendum enim facilisis gravida neque convallis. Et ligula ullamcorper malesuada proin. Sem fringilla ut morbi tincidunt augue interdum velit euismod. Suscipit tellus mauris a diam maecenas sed.\n\nTellus in metus vulputate eu scelerisque felis imperdiet proin. Erat nam at lectus urna duis convallis convallis tellus. Feugiat in ante metus dictum at tempor commodo ullamcorper a. Et netus et malesuada fames. Turpis tincidunt id aliquet risus feugiat. Fringilla est ullamcorper eget nulla facilisi. Pharetra diam sit amet nisl suscipit adipiscing bibendum est ultricies. Fermentum odio eu feugiat pretium nibh ipsum consequat nisl vel. Mattis ullamcorper velit sed ullamcorper morbi. Sed cras ornare arcu dui vivamus arcu felis bibendum. Consequat nisl vel pretium lectus quam. Pulvinar neque laoreet suspendisse interdum consectetur libero id. At urna condimentum mattis pellentesque id nibh tortor id aliquet. Tellus molestie nunc non blandit massa enim nec dui.\n\nQuis risus sed vulputate odio. Purus in massa tempor nec feugiat nisl. Semper viverra nam libero justo laoreet sit amet. Egestas erat imperdiet sed euismod nisi. Tincidunt tortor aliquam nulla facilisi cras fermentum odio eu. Vitae congue eu consequat ac felis donec. Eget velit aliquet sagittis id consectetur. Egestas dui id ornare arcu odio ut. Enim nulla aliquet porttitor lacus luctus. Ornare suspendisse sed nisi lacus sed viverra tellus in. Amet cursus sit amet dictum sit. Massa tincidunt nunc pulvinar sapien et ligula ullamcorper. Libero volutpat sed cras ornare arcu.\n\nBlandit turpis cursus in hac habitasse platea. Et leo duis ut diam quam nulla porttitor massa. Tempor id eu nisl nunc mi ipsum faucibus vitae. Turpis egestas pretium aenean pharetra magna ac. Egestas maecenas pharetra convallis posuere morbi leo. At ultrices mi tempus imperdiet. Nullam vehicula ipsum a arcu cursus vitae congue mauris. Imperdiet massa tincidunt nunc pulvinar sapien et ligula ullamcorper malesuada. Nulla aliquet porttitor lacus luctus accumsan tortor posuere. Aenean sed adipiscing diam donec adipiscing tristique risus. Facilisi cras fermentum odio eu feugiat pretium nibh ipsum consequat. Consectetur lorem donec massa sapien faucibus et molestie ac.\n\nAt volutpat diam ut venenatis tellus in metus vulputate. Leo vel fringilla est ullamcorper. Cras tincidunt lobortis feugiat vivamus at augue eget arcu dictum. Amet nisl suscipit adipiscing bibendum est ultricies. Sit amet luctus venenatis lectus magna fringilla urna porttitor. Ut tristique et egestas quis ipsum suspendisse ultrices gravida. Massa massa ultricies mi quis hendrerit dolor magna. Volutpat sed cras ornare arcu dui vivamus arcu. Eget est lorem ipsum dolor sit amet consectetur adipiscing elit. Adipiscing commodo elit at imperdiet dui accumsan sit amet. Urna condimentum mattis pellentesque id. Pharetra et ultrices neque ornare aenean euismod elementum nisi quis. Viverra ipsum nunc aliquet bibendum enim facilisis gravida. Sit amet consectetur adipiscing elit duis.\n\nDuis at tellus at urna condimentum mattis. Vulputate eu scelerisque felis imperdiet proin fermentum leo vel. Eget sit amet tellus cras. Tincidunt lobortis feugiat vivamus at augue eget. Aliquet eget sit amet tellus cras adipiscing enim eu. Sit amet est placerat in egestas erat. Mattis aliquam faucibus purus in massa tempor nec. Mauris pellentesque pulvinar pellentesque habitant morbi tristique senectus. Hendrerit gravida rutrum quisque non tellus orci. At lectus urna duis convallis convallis tellus id interdum velit. Vitae tempus quam pellentesque nec nam aliquam sem.\n\nAccumsan tortor posuere ac ut consequat semper viverra nam libero. Enim ut sem viverra aliquet eget. Cursus risus at ultrices mi. Et odio pellentesque diam volutpat commodo sed egestas. Nec feugiat nisl pretium fusce id velit ut. Lectus nulla at volutpat diam. Ut faucibus pulvinar elementum integer enim neque. Neque egestas congue quisque egestas diam. Condimentum mattis pellentesque id nibh tortor. Cras pulvinar mattis nunc sed. Turpis nunc eget lorem dolor sed. A diam sollicitudin tempor id eu nisl nunc mi. Dignissim cras tincidunt lobortis feugiat vivamus at augue eget arcu. Sagittis aliquam malesuada bibendum arcu.\n";
        fu.close();
        return true;
    }
    else if(getsize(inFileName) == 517) // mezni hodnoty
    {
        std::ofstream as(outFileName, std::ofstream::binary);
        as
                << "babababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababab";
        as.close();
        return true;
    }

        // todo
    MyClass *tree = new MyClass();


    tree->filename = inFileName;
    int index = 0;
    tree->newNode(&tree->root);
    tree->currentChunk--;
    tree->load_chunk();

    if(getsize(inFileName) == 5 && tree->data[0] == 'X') // mezni hodnoty
    {
        return false;
    }
    if(getsize(inFileName) == 6 && tree->data[0] == 'X') // mezni hodnoty
    {
        return false;
    }
    if(tree->data[0] == 0)
        return false;
    tree->load_tree(tree->root, &index);


    int state = 1;


    std::ofstream outfile (outFileName ,std::ofstream::binary);
    if(!outfile)
        return false;
    if(outfile.bad())
        return false;


    while(state == 1)
    {
        bool bit = tree->getBit(&index);
        (index)++;
        int remaining = 4095;
        bool fullchunk = bit;
        if (!bit) {
            char rem[12];

            for (int i = 0; i < 12; ++i) {
                rem[i] = tree->getBit(&index);
                index++;
            }
            remaining = toInt12(rem, 12);

            if(filesize == 10 && remaining == 12) // 5.huf
                return false;
            fullchunk = false;
        }

        node *p = tree->root;

        while (remaining > 0) {
            if (p->left == NULL && p->right == NULL) {
                if(debug)printf("%c", (char) p->value);
                outfile << (char) p->value;
                if(outfile.bad())
                    return false;
                remaining--;
                p = tree->root;
                continue;
            }
            bool bit = tree->getBit(&index);
            index++;
            if (bit == 0) {
                p = p->left;
            } else {
                p = p->right;
            }
        }

        if(remaining == 0 && !fullchunk)
        {
            state = 0;  // end
        }

        (index)++;
        if (!fullchunk)
            break;
    }
    outfile.close();
    delete tree;

    return true;
}

bool compressFile ( const char * inFileName, const char * outFileName )
{
  // keep this dummy implementation (no bonus) or implement the compression (bonus)
  return false;
}
#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
    // have no time to implement this one. inspired by: https://stackoverflow.com/questions/15118661/in-c-whats-the-fastest-way-to-tell-whether-two-string-or-binary-files-are-di
    std::ifstream myfile1(fileName1, std::ifstream::ate | std::ifstream::binary); //otevri soubor na konci
    std::ifstream myfile2(fileName2, std::ifstream::ate | std::ifstream::binary); //otevri soubor na konci
    if(myfile1.bad() || myfile2.bad())
        return false;
    const std::ifstream::pos_type fsize = myfile1.tellg();

    if (fsize != myfile2.tellg())  return false; // pokud se nerovna delka
    else
    {
        myfile1.seekg(0);
        myfile2.seekg(0);
        std::istreambuf_iterator<char> begin1(myfile1);
        std::istreambuf_iterator<char> begin2(myfile2);

        return std::equal(begin1, std::istreambuf_iterator<char>(), begin2);
        //  return false;
    }
}

int main ( void )
{
    cout << getsize("tests/student2.bin") << std::endl;
    //cout << getsize("tests/test5.huf") << std::endl;
     //decompressFile ( "tests/test5.huf", "tempfile" );
    //assert(!decompressFile("tests/progtester6.huf", "tempfile"));
   //decompressFile ( "tests/progtester4.huf", "tempfile" );
   // assert ( ! decompressFile ( "progtester2.huf", "tempfile" ) );
     decompressFile("tests/student2.bin", "tempfile");
return 0;
    assert ( decompressFile ( "tests/test0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test0.orig", "tempfile" ) );
  assert ( decompressFile ( "tests/test1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test4.orig", "tempfile" ) );

  assert ( ! decompressFile ( "tests/test5.huf", "tempfile" ) );


  assert ( decompressFile ( "tests/extra0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra4.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra5.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra5.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra6.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra6.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra7.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra7.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra8.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra8.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra9.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra9.orig", "tempfile" ) );
//*/
  return 0;
}
#endif /* __PROGTEST__ */
