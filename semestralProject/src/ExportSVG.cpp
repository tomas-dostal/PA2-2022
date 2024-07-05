/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */


#include <ostream>
#include <utility>
#include <iostream>
#include <stdexcept>

#include "ExportSVG.h"
#include "messages.h"
#include "Formatter.h"
#include "Helper.h"

ExportSVG::ExportSVG(const std::function<std::shared_ptr<std::fstream>(std::ios_base::openmode)>& openFile):
        Export(openFile, OPEN_FILE_WRITE_STR) {
    svgDict = {
//            {SHAPE_CIRCLE,    SVG_CIRCLE },
//            {SHAPE_ELLIPSE,   SVG_ELLIPSE },
//            {SHAPE_RECTANGLE, SVG_RECTANGLE },
            {SHAPE_LINE,      SVG_LINE },
            {SHAPE_GROUP_BEGIN,  SVG_GROUP_BEGIN },
            {SHAPE_GROUP_END,    SVG_GROUP_END }
    };
}

bool ExportSVG::Process(std::string SuperShapeName, std::map<std::string, std::string> dict){
    auto svgShape = svgDict.find(SuperShapeName);
    if(svgShape == svgDict.end())
        throw std::runtime_error("ExportSVG:: No such a shape");
    if(dict.find(FILL_R) != dict.end() && dict.find(FILL_G) != dict.end() && dict.find(FILL_B) != dict.end()) {
        dict.insert({FILL_RGBA, Formatter().FillNamedPlaceholders(SVG_FILL_RGB, dict)});
        dict.erase(dict.find(FILL_R)); 
        dict.erase(dict.find(FILL_G)); 
        dict.erase(dict.find(FILL_B));
    }
    if(dict.find(COLOR_R) != dict.end() && dict.find(COLOR_G) != dict.end() && dict.find(COLOR_B) != dict.end()) {
        dict.insert({COLOR_RGB, Formatter().FillNamedPlaceholders(SVG_COLOR_RGB, dict)});
        dict.erase(dict.find(COLOR_R));
        dict.erase(dict.find(COLOR_G));
        dict.erase(dict.find(COLOR_B));
    }
    
    *file << Formatter().FillNamedPlaceholders(svgShape->second, dict) << std::endl;
    return file->good();
}

bool ExportSVG::Start(int width, int height) {
    *file << Formatter().FillNamedPlaceholders(SVG_INIT,
                                                   {
                                                    {MAX_WIDTH,  std::to_string(width)},
                                                    {MAX_HEIGHT, std::to_string(height)}
                                                   }
        ) << std::endl;

    return file->good();
}

bool ExportSVG::End() {
    *file << Formatter().FillNamedPlaceholders(SVG_END, {}) << std::endl;
    // File is closed in the descructor
    return file->good();
}

