/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 09.06.2022
 */

#pragma once

#include "vector"
#include "Shape.h"
#include "SuperShape.h"

class ShapeGroup : public SuperShape{
public:
    /**
     * ShapeGroup solves the feature of groups in
     * @param id shapeGroup unique identifier
     * @param name Name
     * @param children - vector of Shapes and/or ShapeGroups
     */
    ShapeGroup(unsigned int id, std::string name, std::vector<std::shared_ptr<SuperShape>>);

    ShapeGroup(const ShapeGroup &shapeGroup);

    ~ShapeGroup() noexcept = default;

    /**
     * Add Shape or Group into group.
     * @param shapeOrGroup
     */
    void Add(std::shared_ptr<SuperShape> && superShape);

    /**
     * Clone
     * @param newId Id from GroupID manager, it should be unique (nice to have)
     * @return Clone of current ShapeGroup with all subgroups
     */
    //std::shared_ptr<ShapeGroup> Clone(unsigned int newId) const;

    /**
     * List all groups/subgroups
     * @return vector of groups/subgroups which are children to *this
     */
    std::vector<std::shared_ptr<SuperShape>> List() const;

    /**
     * Print basic info about shape/group
     * @return string
     */
    std::string Print() const override;

    /**
     * Method Draw is used for export in specified format
     * @param interface
     * @param format
     */
    void Draw(std::shared_ptr<Interface> interface, std::string format) override;

    /**
     * Overloaded print operator
     * @param os output stream
     * @param shapeGroup group to be printer
     * @return output stream
     */
    friend std::ostream & operator << (std::ostream & os, const ShapeGroup & shapeGroup);

    bool operator==(const SuperShape &s) override;

protected:

    std::vector<std::shared_ptr<SuperShape>> children;

    unsigned int id;

};

