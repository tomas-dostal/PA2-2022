/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz>
 * @date 15.06.2022
 */

#include <iomanip>
#include <string>
#include <ostream>
#include <utility>
#include <iostream>
#include <cmath>
#include <any>

#include "ExportBMP.h"
#include "messages.h"
#include "constants.h"
#include "Pos.h"

ExportBMP::ExportBMP(const std::string &fileName) :
        Export(fileName) {

    bmpDict = {
            {SHAPE_CIRCLE,      [this](std::map<std::string, std::string> params) {
                Pos pos = Pos(std::stoi(params[CENTER_X]), std::stoi(params[CENTER_Y]));
                Color color = Color(std::stoi(params[COLOR_R]),
                                    std::stoi(params[COLOR_G]),
                                    std::stoi(params[COLOR_B]),
                                    "colorname");
                // draw fill
                Color fill = Color(std::stoi(params[FILL_R]),
                                   std::stoi(params[FILL_G]),
                                   std::stoi(params[FILL_B]),
                                   "fill");
                DrawEllipse(pos,
                            0,
                            0,
                            color,
                            std::stoi(params[DIAMETER_X]),
                            SHAPE_NA_CIRCLE);
                // draw circle
                DrawEllipse(pos,
                            std::stoi(params[DIAMETER_X]),
                            std::stoi(params[DIAMETER_X]),
                            color,
                            std::stoi(params[THICKNESS]),
                            SHAPE_NA_CIRCLE);

            }
            },
            {SHAPE_ELLIPSE,     [this](std::map<std::string, std::string> params) {
                Pos pos = Pos(std::stoi(params[CENTER_X]), std::stoi(params[CENTER_Y]));
                Color color = Color(std::stoi(params[COLOR_R]),
                                    std::stoi(params[COLOR_G]),
                                    std::stoi(params[COLOR_B]),
                                    "colorname");
                DrawEllipse(pos,
                            std::stoi(params[DIAMETER_X]),
                            std::stoi(params[DIAMETER_Y]),
                            color,
                            std::stoi(params[THICKNESS]),
                            SHAPE_NA_ELLISPE);
            }},
            {SHAPE_RECTANGLE,   [this](std::map<std::string, std::string> params) {
                Pos start = Pos(std::stoi(params[START_X]), std::stoi(params[START_X]));
                Pos right_top = Pos(std::stoi(params[START_X]) + std::stoi(params[WIDTH]),
                                    start.y);
                Pos right_bottom = Pos(start.x + std::stoi(params[WIDTH]),
                                       start.y + std::stoi(params[HEIGHT]));
                Pos left_bottom = Pos(start.x,
                                      start.y + std::stoi(params[HEIGHT]));

                Color color = Color(std::stoi(params[COLOR_R]),
                                    std::stoi(params[COLOR_G]),
                                    std::stoi(params[COLOR_B]),
                                    "colorname");

                Color fill = Color(std::stoi(params[FILL_R]),
                                    std::stoi(params[FILL_G]),
                                    std::stoi(params[FILL_B]),
                                    "fill");
                // draw the fill
                Pos centerY_left = Pos(start.x,
                                       start.y + ceil(std::stoi(params[HEIGHT])/2));

                Pos centerY_right =  Pos(right_top.x,
                                         start.y + ceil(std::stoi(params[HEIGHT])/2));

                DrawLine(centerY_left, centerY_right, fill, std::stoi(params[HEIGHT]));

                DrawLine(start, right_top, color, std::stoi(params[THICKNESS]) * BMP_THICKNESS);
                DrawLine(right_top, right_bottom, color, std::stoi(params[THICKNESS]) * BMP_THICKNESS);
                DrawLine(right_bottom, left_bottom, color, std::stoi(params[THICKNESS]) * BMP_THICKNESS);
                DrawLine(left_bottom, start, color, std::stoi(params[THICKNESS]) * BMP_THICKNESS);
            }
            },
            {SHAPE_LINE,        [this](std::map<std::string, std::string> params) {
                Pos startPos = Pos(std::stoi(params[START_X]), std::stoi(params[START_Y]));
                Pos endPos = Pos(std::stoi(params[END_X]), std::stoi(params[END_Y]));
                Color color = Color(std::stoi(params[COLOR_R]),
                                    std::stoi(params[COLOR_G]),
                                    std::stoi(params[COLOR_B]),
                                    "colorname");
                DrawLine(startPos,
                         endPos,
                         color,
                         std::stoi(params[THICKNESS]) * BMP_THICKNESS
                );
            }
            },
            {SHAPE_GROUP_BEGIN, [](std::map<std::string, std::string> params) {

            }
            },
            {SHAPE_GROUP_END,   [](std::map<std::string, std::string> params) {

            }
            }
    };

    fileOut.open(fileName, std::ofstream::out | std::ofstream::binary);
    if (!fileOut) {
        throw std::runtime_error(ERROR_FILE_IO);
    }
}

bool ExportBMP::Process(std::string SuperShapeName, std::map<std::string, std::string> dict) {
    auto svgShape = bmpDict.find(SuperShapeName);
    if (svgShape == bmpDict.end())
        throw std::runtime_error("ExportBMP:: No such a shape");

    std::invoke(svgShape->second, dict);

    return true;
}

/**
 * @basedon https://rosettacode.org/wiki/Superellipse#C
 * https://en.wikipedia.org/wiki/Superellipse
 * @param center
 * @param diameter_x
 * @param diameter_y
 * @param color
 */
void ExportBMP::DrawEllipse(Pos &center, size_t diameter_x, size_t diameter_y, Color &color, size_t thickness,
                            float shapeNa) {
    double majorAxis = diameter_x;
    double minorAxes = diameter_y;
    // na == 0 -> rectangle
    // na == 1 -> circle
    // na == 2 -> ellipse
    size_t steps = 10000;


    for (size_t round = 0; round <= floor(thickness); round++) {
        double piece = (M_PI * 2) / steps;
        double t = 0;

        for (size_t i = 0; i <= steps; i++) {
            int x = center.x +
                    pow(abs(cos(t)), shapeNa) * (majorAxis + round) * ((cos(t) > 0) ? 1 : ((cos(t) < 0) ? -1 : 0));
            int y = center.y +
                    pow(abs(sin(t)), shapeNa) * (minorAxes + round) * ((sin(t) > 0) ? 1 : ((sin(t) < 0) ? -1 : 0));


//            int x = thickness + (int) (center.x + (majorAxis + round) * pow(fabs(cos(i)), na) * (M_PI / 2 < i && i < 3 * M_PI / 2 ? -1 : 1));
//            int y = thickness + (int) (center.y + (minorAxes + round) * pow(fabs(sin(i)), na) * (M_PI < i && i < 2 * M_PI ? -1 : 1));
            if (x < image.size() && x >= 0 && y < image[0].size() && y >= 0)
                image[x][y] = *(color.GetPixel());
            t += piece;
        }
    }
}

/**
 * @baseon http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
 * @param start
 * @param end
 * @param c
 */
void ExportBMP::DrawLine(Pos &start, Pos &end, Color &color, size_t thickness) {

    auto isHorizontalLine = [&start, &end](){
        return start.y == end.y && !( start.x == end.x);

    };

    auto isVerticalLine = [&start, &end](){
        return start.x == end.x && !(start.y == end.y);
    };

    auto elseLine = [&start, &end](){
        return !(start.y == end.y) && !( start.x == end.x);
    };

    if(elseLine())
        thickness *= 2;
    // Bresenham's line algorithm
    for (int thick = (int) (-1 * floor(thickness / 2)); thick <= ((int) ceil(thickness / 2)); thick++) {
        int startX = start.x
                + (isVerticalLine() ? thick : 0)
                + (isHorizontalLine() ? 0 : 0)
                + (elseLine() ? (int) (-1 * floor((thickness)) / 2): 0);
        int startY = start.y
                + (isVerticalLine() ?  0: 0)
                + (isHorizontalLine() ? thick : 0)
                + (elseLine() ? (int) floor((thick) / 2): 0);
        int endX = end.x
                +  (isVerticalLine() ? thick : 0)
                + (isHorizontalLine() ? 0 : 0)
                + (elseLine() ? (int) floor((thickness) / 2): 0);
        int endY =  end.y
                + (isVerticalLine() ? 0 : 0)
                + (isHorizontalLine() ? thick : 0)
                + (elseLine() ? (int) floor((thick) / 2): 0);

        //        int startX = start.x + (isStraihtLine() ? (int) floor((thick + 1) / 2): (int) floor((thick + 1) / 2));
        //        int startY = start.y + (isStraihtLine() ? (int) floor(thick / 2): 0);
        //        int endX = end.x + (isStraihtLine()? (int) floor((thick + 1) / 2);
        //        int endY = end.y + (int) floor(thick / 2);
        const bool steep = (fabs(endY - startY) > fabs(endX - startX));
        if (steep) {
            std::swap(startX, startY);
            std::swap(endX, endY);
        }

        if (startX > endX) {
            std::swap(startX, endX);
            std::swap(startY, endY);
        }

        const float dx = endX - startX;
        const float dy = fabs(endY - startY);

        float error = dx / 2.0f;
        const int yStep = (startY < endY) ? 1 : -1;
        int y = (int) startY;

        for (int x = startX; x <= endX; x++) {
            if (steep) {
                if (x < image.size() && y < image[0].size())
                    image[x][y] = *color.GetPixel();
            }
            else {
                if (x < image[0].size() && y < image.size())
                    image[y][x] = *color.GetPixel();
            }

            error -= dy;
            if (error < 0) {
                y += yStep;
                error += dx;
            }
        }
    }
}


bool ExportBMP::Start(int width, int height) {
    image = std::vector<std::vector<Pixel>>(height);
    for (int x = 0; x < height; x++) {
        image[x] = std::vector<Pixel>(width);
        for (int y = 0; y < width; y++) {
            image[x][y] = Pixel(background->R(), background->G(), background->B());
        }
    }

    return true;
}

bool ExportBMP::End() {
    SaveToFile();
    // todo
    return fileOut.good();
}

void ExportBMP::SetBackground(std::shared_ptr<Color> c) {
    background = c;
}


typedef unsigned char uchar_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
const int BMP_MAGIC_ID = 2;

// --------------------------------------------------------------
// Windows BMP-specific format data
struct bmpfileMagic {
    uchar_t magic[BMP_MAGIC_ID];
};

struct bmpfile_header {
    uint32_t fileSize;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmpOffset;
};

struct bmpfile_dib_info {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t numPlanes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t bmpByteSize;
    int32_t hres;
    int32_t vres;
    uint32_t numColors;
    uint32_t numImportantColors;
};


/**
 * @author Kevin Buffardi <kbuffardi@csuchico.edu>
 * @modified_by Tomas Dostal <dostato6@fit.cvut.cz>
 * @besedon https://github.com/kbuffardi/Bitmap
 * @date 15.06.2022
 *
 * Saves the current image, represented by the matrix of pixels, as a
 * Windows BMP file. File extension is not forced but should be .bmp.
 * Any errors will print to cerr and will NOT
 * attempt to save the fileOut.
 *
 **/
void ExportBMP::SaveToFile() {
    // Write all the header information that the BMP file format requires.
    bmpfileMagic magic;
    magic.magic[0] = 'B';
    magic.magic[1] = 'M';
    fileOut.write((char *) (&magic), sizeof(magic));
    bmpfile_header header = {0};
    header.bmpOffset = sizeof(bmpfileMagic)
                       + sizeof(bmpfile_header) + sizeof(bmpfile_dib_info);
    header.fileSize = header.bmpOffset
                      + (image[0].size() * 3 + image.size() % 4) * image[0].size();
    fileOut.write((char *) (&header), sizeof(header));
    bmpfile_dib_info dibInfo = {0};
    dibInfo.headerSize = sizeof(bmpfile_dib_info);
    dibInfo.width = image[0].size();
    dibInfo.height = image.size();
    dibInfo.numPlanes = 1;
    dibInfo.bitsPerPixel = 24;
    dibInfo.compression = 0;
    dibInfo.bmpByteSize = 0;
    dibInfo.hres = 2835;
    dibInfo.vres = 2835;
    dibInfo.numColors = 0;
    dibInfo.numImportantColors = 0;
    fileOut.write((char *) (&dibInfo), sizeof(dibInfo));

    // Write each row and column of Pixels into the image file -- we write
    // the rows upside-down to satisfy the easiest BMP format.
    for (int row = image.size() - 1; row >= 0; row--) {
        const std::vector<Pixel> &rowData = image[row];

        for (int col = 0; col < rowData.size(); col++) {
            const Pixel &pix = rowData[col];
            fileOut.put((uchar_t) (pix.blue));
            fileOut.put((uchar_t) (pix.green));
            fileOut.put((uchar_t) (pix.red));
        }

        // Rows are padded so that they're always a multiple of 4
        // bytes. This line skips the padding at the end of each row.
        for (int i = 0; i < rowData.size() % 4; i++) {
            fileOut.put(0);
        }
    }

    fileOut.close();
}