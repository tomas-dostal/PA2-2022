/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 11.06.2022
 */

#pragma once

#include <string>
#include <functional>

#include "Pos.h"
#include "Interface.h"
#include "Export.h"

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

    SuperShape( int id,
               std::string name,
                std::shared_ptr<Pos> center,
                size_t width,
                size_t height
           );

    ~SuperShape() noexcept = default; // choose destructors to match class to be sure all the memory is freed

    /**
     * Draw shape into the exporter. Standardised dictionary is created for each object.
     * This method is used for exporting to svg, tspaint, bmp.
     * @param exporter
     */
    virtual void Draw(Export & exporter) = 0;

    virtual bool operator==(const SuperShape &s) = 0;

    /**
     * Id()
     * @return supershape's id
     */
    virtual int Id();

    /**
     * Name()
     * @return std::string Name
     */
    virtual std::string Name();

    virtual size_t Width();

    virtual size_t Height();

    /**
     * Moves SuperShape relatively by (x, y).
     * Changes are applied fo all children (if any)
     */
    virtual void MoveRelative(int, int) = 0;

    /**
     * Clone SuperShape
     * @param IdGenerator Tspaint's unique ID generator function pointer
     * @return std::shared_ptr<SuperShape>: clone
     */
    virtual std::shared_ptr<SuperShape> Clone( const std::function<int(void)>& IdGenerator) = 0;

    /**
     * Used for print simple summary about the objects with respect to hierarchy (@param indent)
     * @param indent int: indent for current SuperShape, used when printing groups. Default = 0;
     * @return std::string: summery for this object and all it's children (if any)
     */
    virtual std::string Print(int indent) const = 0;

    virtual void NewId( const std::function<int(void)> IdGenerator);

    /**
     * Max(width), Max(height) for this object and all it's children (if any)
     * @return std::pair<size_t, size_t>: <width, height>
     */
    virtual std::pair<size_t, size_t> CalcMaxDimensions();

protected:
    std::string name;

    std::shared_ptr<Pos> center;

    size_t width;
    size_t height;

    int id;
};
