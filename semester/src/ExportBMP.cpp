/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz>
 * @date 15.06.2022
 */

#include <string>
#include <ostream>
#include <utility>
#include <cmath>
#include <any>

#include "ExportBMP.h"
#include "messages.h"
#include "constants.h"
#include "Pos.h"
#include "Helper.h"


ExportBMP::ExportBMP(const std::function<std::shared_ptr<std::fstream>(std::ios_base::openmode)>& openFile) :
        Export(openFile, OPEN_FILE_WRITE_BINARY) {

    bmpDict = {
            {SHAPE_ELLIPSE,     [this](std::map<std::string, std::string> params) {
                Color color = Color(std::stoi(params[COLOR_R]),
                                    std::stoi(params[COLOR_G]),
                                    std::stoi(params[COLOR_B]),
                                    "colorname");
                Pos pos = Pos(std::stoi(params[CENTER_X]), std::stoi(params[CENTER_Y]));
                DrawEllipse(pos,
                            std::stoi(params[DIAMETER_X]),
                            std::stoi(params[DIAMETER_Y]),
                            color,
                            std::stoi(params[THICKNESS]),
                            SHAPE_NA_ELLISPE);
            }},
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
}

bool ExportBMP::Process(std::string SuperShapeName, std::map<std::string, std::string> dict) {
    auto svgShape = bmpDict.find(SuperShapeName);
    if (svgShape == bmpDict.end())
        throw std::runtime_error("ExportBMP:: No such a shape '" + SuperShapeName + "' in dictionary");

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
 * @param start point for the line
 * @param end point for the line
 * @param color
 * @param thickness
 */
void ExportBMP::DrawLine(Pos &start, Pos &end, Color &color, size_t thickness) {
    // Calculate the differences between start and end points
    int dx = static_cast<int>(end.x) - static_cast<int>(start.x);
    int dy = static_cast<int>(end.y) - static_cast<int>(start.y);

    // Determine the direction of the line
    int xStep = (dx >= 0) ? 1 : -1;
    int yStep = (dy >= 0) ? 1 : -1;

    // Calculate absolute values of dx and dy
    dx = abs(dx);
    dy = abs(dy);

    // Calculate the longest and shortest dimensions
    int longestDim = (dx > dy) ? dx : dy;
    int shortestDim = (dx > dy) ? dy : dx;

    // Calculate the error adjustment factors
    int errorFactor = 2 * shortestDim;
    int errorThreshold = shortestDim;

    // Calculate the initial error
    int error = errorFactor - longestDim;

    // Calculate the starting coordinates
    int x = static_cast<int>(start.x);
    int y = static_cast<int>(start.y);

    // Calculate the thickness offset
    int thicknessOffset = (thickness - 1) / 2;

    // Iterate over the longest dimension
    for (int i = 0; i <= longestDim; i++) {
        // Draw a line of pixels for the given thickness
        for (int t = -thicknessOffset; t <= thicknessOffset; t++) {
            int px = x;
            int py = y;

            // Adjust the coordinates based on the direction and thickness
            if (dx >= dy) {
                px += t;
            } else {
                py += t;
            }

            // Check if the coordinates are within the image bounds
            if (px >= 0 && px < image[0].size() && py >= 0 && py < image.size()) {
                image[py][px] = *color.GetPixel();
            }
        }

        // Update the error and coordinates
        if (error >= 0) {
            if (dx >= dy) {
                y += yStep;
            } else {
                x += xStep;
            }
            error -= errorFactor;
        }

        if (dx >= dy) {
            x += xStep;
        } else {
            y += yStep;
        }
        error += errorThreshold;
    }
}

void ExportBMP::Blur(int radius) {
    auto blurredImage = std::vector<std::vector<Pixel>>(image);
    auto height = image.size();
    auto width = image[0].size();

    for (int x = 0; x < height; x++) {
        image[x] = std::vector<Pixel>(width);
        for (int y = 0; y < width; y++) {
            image[x][y] = Pixel(background->R(), background->G(), background->B());
        }
    }

    blurredImage = std::vector<std::vector<Pixel>>(height);


    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int pixelCount = 0;

            for (int offsetX = -radius; offsetX <= radius; offsetX++) {
                for (int offsetY = -radius; offsetY <= radius; offsetY++) {
                    int neighborX = x + offsetX;
                    int neighborY = y + offsetY;

                    if (neighborX >= 0 && neighborX < width && neighborY >= 0 && neighborY < height) {
                        redSum += image[neighborX][neighborY].red;
                        greenSum += image[neighborX][neighborY].green;
                        blueSum += image[neighborX][neighborY].blue;
                        pixelCount++;
                    }
                }
            }

            int blurredRed = redSum / pixelCount;
            int blurredGreen = greenSum / pixelCount;
            int blurredBlue = blueSum / pixelCount;

            blurredImage[x][y].red = blurredRed;
            blurredImage[x][y].green = blurredGreen;
            blurredImage[x][y].blue = blurredBlue;
        }
    }

    // Update the original image with the blurred image
    image = blurredImage;
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
    // Blur(2);
    SaveToFile();
    // todo
    return file->good();
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

struct bmpFileHeader {
    uint32_t fileSize;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmpOffset;
};

struct bmpFileDibInfo {
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
 * attempt to save the file.
 *
 **/
void ExportBMP::SaveToFile() {
    // Write all the header information that the BMP file format requires.
    bmpfileMagic magic;
    magic.magic[0] = 'B';
    magic.magic[1] = 'M';
    file->write((char *) (&magic), sizeof(magic));
    bmpFileHeader header = {0, 0, 0, 0};
    header.bmpOffset = sizeof(bmpfileMagic)
                       + sizeof(bmpFileHeader) + sizeof(bmpFileDibInfo);
    header.fileSize = header.bmpOffset
                      + (image.size() * 3 + image[0].size() % 4) * image.size();
    file->write((char *) (&header), sizeof(header));
    bmpFileDibInfo dibInfo{};
    dibInfo.headerSize = sizeof(bmpFileDibInfo);
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
    file->write((char *) (&dibInfo), sizeof(dibInfo));

    // Write each row and column of Pixels into the image file -- we write
    // the rows upside-down to satisfy the easiest BMP format.
    for (int row = image.size() - 1; row >= 0; row--) {
        const std::vector<Pixel> &rowData = image[row];

        for (unsigned long col = 0; col < rowData.size(); col++) {
            const Pixel &pix = rowData[col];
            file->put((uchar_t) (pix.blue));
            file->put((uchar_t) (pix.green));
            file->put((uchar_t) (pix.red));
        }

        // Rows are padded so that they're always a multiple of 4
        // bytes. This line skips the padding at the end of each row.
        for (unsigned long i = 0; i < rowData.size() % 4; i++) {
            file->put(0);
        }
    }
}