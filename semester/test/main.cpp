/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <iterator>

#include "../src/Application.h"

bool StringContains(std::string text, std::string word){
   return (text.find(word) != std::string::npos);
}

int CopmareString(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1)
    {
        while (isspace(*p1)) p1++;
        if (!*p1) break;

        while (isspace(*p2)) p2++;

        if (!*p2) return  1;
        if (*p2 > *p1) return -1;
        if (*p1 > *p2) return  1;

        p1++;
        p2++;
    }

    if (*p2) return -1;

    return 0;
}

void TestAddCircle(){

    std::stringstream ssIn;
    ssIn << "draw circle 1 2 3";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1): circle (2)") == 0) ;
}


void TestAddRectangle(){

    std::stringstream ssIn;
    ssIn << "draw rectangle 1 1 100 200";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1): rectangle (2)") == 0) ;
}
void TestAddLine(){

    std::stringstream ssIn;
    ssIn << "draw line 1 1 100 100";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1): line (2)") == 0) ;
}
void TestAddPolyLine(){

    std::stringstream ssIn;
    ssIn << "draw polyline 5 1 1 2 2 3 3 4 4 5 5";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1): polyline (2)") == 0) ;
}
void TestAddEllipse(){

    std::stringstream ssIn;
    ssIn << "draw ellipse 5 6 100 200";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1): ellipse (2)") == 0) ;
    assert(tspaint->root->List()[0]);
}

void TestGroupObjects(){

    std::stringstream ssIn;
    ssIn << "draw ellipse 5 6 100 200";
    ssIn << "draw circle 10 6 100";
    ssIn << "group objects 2 2 3";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1): Group (4) : ellipse (2) circle (3)") == 0) ;
}


void TestGroupClone(){

    std::stringstream ssIn;
    ssIn << "draw ellipse 5 6 100 200";
    ssIn << "draw circle 10 6 100";
    ssIn << "group clone 1";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1):  ellipse (2) circle (3) Group (6) : ellipse (4) circle (5)") == 0) ;
}
void TestGroupCloneDouble(){

    std::stringstream ssIn;
    ssIn << "draw ellipse 5 6 100 200";
    ssIn << "draw circle 10 6 100";
    ssIn << "group clone 1";
    ssIn << "group clone 6";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1):  ellipse (2) circle (3) Group (6) : ellipse (4) circle (5) Group (9) : ellipse (7) circle (8)") == 0) ;
}
void TestLoadFromFile(){

    std::stringstream ssIn;
    ssIn << "load ../examples/house.tspaint y";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1):  rectangle (2) line (3)  line (4) line (8) Group (9): polyline (5) line (6) line (7)") == 0) ;
}

void TestSaveSvg(){

    std::stringstream ssIn;
    ssIn << "load ../examples/house.tspaint y ";
    ssIn << "save test_svg.svg";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    std::ifstream testFile;
    testFile.open ("test_svg.svg");
    std::ostringstream sout;
    copy(std::istreambuf_iterator<char>(testFile),
         std::istreambuf_iterator<char>(),
         std::ostreambuf_iterator<char>(sout));
    testFile.close();
    std::string output = sout.str();
    assert(StringContains(output, "<svg") == true) ;
    assert(StringContains(output, "<line") == true) ;
    assert(StringContains(output, "<rect") == true) ;
    assert(StringContains(output, "<g") == true) ;
    assert(StringContains(output, "</svg>") == true) ;
    std::remove("test_svg.svg");
}

void TestSaveBmp(){

    std::stringstream ssIn;
    ssIn << "load ../examples/house.tspaint y ";
    ssIn << "save test_bmp.bmp";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    );

    std::ifstream testFile;
    testFile.open ("test_bmp.bmp", std::ios::binary );
    testFile.seekg(0, std::ios::end);
    if(testFile.tellg() == 0){
        assert("bmp file is empty");
    }
    testFile.close();
    std::remove("test_bmp.bmp");
}




void TestCommandEOF(){

    std::stringstream ssIn;
    ssIn << "draw ellipse 5 6 100 200";
    ssIn << "draw ";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    assert(!app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    ));

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1):  ellipse (2)") == 0) ;
}

void TestDrawInvalidInput(){

    std::stringstream ssIn;
    ssIn << "draw Let me pass PA2 pretty please <3";

    std::stringstream ssOut;
    std::shared_ptr<Interface> interface = std::make_shared<Interface>(Interface(ssIn, ssOut));
    auto app = Application();
    std::shared_ptr<Tspaint> tspaint = std::make_shared<Tspaint>(Tspaint());

    assert(!app.Run(interface,
            tspaint,
            [&app]() { return app.IsRunning(); },
            [](Command *) { return true; }
    ));

    assert(CopmareString(tspaint->root->Print(0).c_str(),  "Group (1):") == 0) ;
}

/**
 * Unit tests covering basic functionality
 * @return
 */
int main(void) {

    TestAddCircle();
    TestAddRectangle();
    TestAddLine();
    TestAddPolyLine();
    TestAddEllipse();
    TestAddCircle();
    TestGroupObjects();
    TestGroupClone();
    TestGroupCloneDouble();

    TestLoadFromFile();
    TestSaveSvg();
    TestSaveBmp();

    TestCommandEOF();
    TestDrawInvalidInput();
}



