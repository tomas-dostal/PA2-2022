/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */


#include <ostream>
#include <utility>
#include <iostream>

#include "ExportSVG.h"
#include "messages.h"
#include "Formatter.h"

ExportSVG::ExportSVG(const std::string &fileName):
        Export(fileName) {
    std::map<std::string, std::string> svgDict {
            {SHAPE_CIRCLE,    SVG_CIRCLE },
            {SHAPE_ELLIPSE,   SVG_ELLIPSE },
            {SHAPE_RECTANGLE, SVG_RECTANGLE },
            {SHAPE_LINE,      SVG_LINE }
    };
}

bool ExportSVG::Process(std::string SuperShapeName, std::map<std::string, std::string> dict){
    auto svgShape = svgDict.find(SuperShapeName);
    if(svgShape == svgDict.end())
        throw std::runtime_error("ExportSVG:: No such a shape");
    if(dict.find(FILL_R) != dict.end() && dict.find(FILL_G) != dict.end() && dict.find(FILL_B) != dict.end())
        dict.insert({SVG_FILL_RGBA, Formatter().FillNamedPlaceholders(svgShape->second, dict)});
    if(dict.find(COLOR_R) != dict.end() && dict.find(COLOR_G) != dict.end() && dict.find(COLOR_B) != dict.end())
        dict.insert({SVG_COLOR_RGBA, Formatter().FillNamedPlaceholders(svgShape->second, dict)});
    std::cout << Formatter().FillNamedPlaceholders(svgShape->second, dict);
}

bool ExportSVG::Start() {
    std::cout << Formatter().FillNamedPlaceholders(SVG_INIT, {
            //{MAX_WIDTH,  std::to_string(root->Height())},
            //{MAX_HEIGHT, std::to_string(root->Height())}

    }) << std::endl;

    //root->Draw(*this);

    std::cout << Formatter().FillNamedPlaceholders(SVG_END, {}) << std::endl;
}
