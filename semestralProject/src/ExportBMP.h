/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 31.05.2022
 */

#pragma once


#include "Export.h"
#include "Pixel.h"
#include "Color.h"


class ExportBMP : public Export {
public:

    ExportBMP(const std::function<std::shared_ptr<std::fstream>(std::ios_base::openmode)>& openFile);

    bool Start(int width, int height) override;

    bool End() override;

    bool Process(std::string SuperShapeName, std::map<std::string, std::string> dict) override;

    void SetBackground(std::shared_ptr<Color> c);

private:
    void DrawLine(Pos & start, Pos & end, Color & c, size_t thickness);

    void DrawEllipse(Pos &center, size_t diameter_x, size_t diameter_y, Color &color, size_t thickness, float shapeNa);

    void SaveToFile();

    std::map<std::string, std::function<void(std::map<std::string, std::string> params)>> bmpDict;

    std::vector<std::vector<Pixel>> image;

    std::shared_ptr<Color> background;

    void Blur(int radius);
};
