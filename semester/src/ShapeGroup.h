/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 09.06.2022
 */

#pragma once

#include "vector"
#include "Shape.h"

template <class T>
class ShapeGroup {

    /**
     * ShapeGroup solves the feature of groups in
     * @param id shapeGroup unique identifier
     * @param children - vector of Shapes and/or ShapeGroups
     */
    ShapeGroup(unsigned int id, std::vector<T> children);

    /**
     * Add Shape or Group into group.
     * @param shapeOrGroup
     */
    void Add(std::shared_ptr<T> shapeOrGroup);

    /**
     * Clone
     * @param newId Id from GroupID manager, it should be unique (nice to have)
     * @return Clone of current ShapeGroup with all subgroups
     */
    std::shared_ptr<ShapeGroup> Clone(unsigned int newId) const;

    /**
     * List all groups/subgroups
     * @return vector of groups/subgroups which are children to *this
     */
    std::vector<T> List() const;

    /**
     * Print basic info about shape/group
     * @return string
     */
    std::string Print() const;

    /**
     * Overloaded print operator
     * @param os output stream
     * @param shapeGroup group to be printer
     * @return output stream
     */
    friend std::ostream & operator << (std::ostream & os, const ShapeGroup & shapeGroup);

private:
    std::vector<T> children;
    std::shared_ptr<ShapeGroup> parent;

    unsigned int id;

};

