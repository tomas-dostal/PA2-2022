/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#pragma once


class Polyline: Shape {
public:
    Polyline() = delete;
    Polyline(std::vector<shared_ptr<Line>> lines): lines(lines);

private:
    std::vector<shared_ptr<Line>> lines;
};
