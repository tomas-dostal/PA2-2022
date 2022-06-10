/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 11.06.2022
 */

#pragma once

#include "string"
#include "Pos.h"
#include "Interface.h"

class SuperShape {
public:
    /**
     * SuperShape - Top class covering generic shapes and groups like circle, line etc.
     * @param id
     * @param name
     * @param center
     * @param width
     * @param height
     */

    SuperShape( unsigned int id,
               std::string name,
                std::shared_ptr<Pos> center,
                size_t width,
                size_t height
           );

    ~SuperShape() noexcept = default; // choose destructors to match class to be sure all the memory is freed

    /**
     * Draw shape into the interface
     * @param interface
     */
    virtual void Draw(std::shared_ptr<Interface> interface, std::string format) = 0; // layers are solved by order of drawings, from rear (first drawn) to front (last drawn)

    virtual bool operator==(const SuperShape &s) = 0;

    virtual unsigned int Id();

    virtual std::string Name();

    virtual size_t Width();

    virtual size_t Height();

    //virtual std::vector<std::pair<std::string, std::any>> ShapeNamedCoords();

    virtual std::string Print() const = 0;

protected:
    std::string name;

    std::shared_ptr<Pos> center;

    size_t width;
    size_t height;
    unsigned int id;
};
