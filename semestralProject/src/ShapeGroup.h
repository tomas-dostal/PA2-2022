/**
 * @author Tomas Dostal <dostato6@fit.cvut.cz> 
 * @date 09.06.2022
 */

#pragma once

#include <vector>

#include "SuperShape.h"
#include "Export.h"

class ShapeGroup : public SuperShape{
public:
    /**
     * ShapeGroup solves the feature of groups in
     * @param id shapeGroup unique identifier
     * @param name Name
     * @param children - vector of Shapes and/or ShapeGroups
     */
    ShapeGroup(int id, std::string name, std::vector<std::shared_ptr<SuperShape>>);

    void Add(std::shared_ptr<SuperShape> ss);

    void RemoveIfExists(int id);

    ~ShapeGroup() noexcept = default;

    void MoveRelative(int, int) override;

    std::shared_ptr<SuperShape> Clone( const std::function<int(void)>& IdGenerator) override;

    std::pair<size_t, size_t> CalcMaxDimensions() override;
    /**
     * Add Shape or Group into group.
     * @param shapeOrGroup
     */
    /**
     * Clone
     * @param newId Id from GroupID manager, it should be unique (nice to have)
     * @return Clone of current ShapeGroup with all subgroups
     */
    //std::shared_ptr<ShapeGroup> Clone(int newId) const;

    /**
     * List all groups/subgroups
     * @return vector of groups/subgroups which are children to *this
     */
    [[nodiscard]] std::vector<std::shared_ptr<SuperShape>> List() const;

    /**
     * Print basic info about shape/group
     * @return string
     */
    [[nodiscard]] std::string Print(int indent) const override;

    /**
     * Method Draw is used for export in specified format
     * @param interface
     * @param format
     */
     void Draw(Export & exporter) override;

    /**
     * Overloaded print operator
     * @param os output stream
     * @param shapeGroup group to be printer
     * @return output stream
     */
    friend std::ostream & operator << (std::ostream & os, const ShapeGroup & shapeGroup);

    bool operator==(const SuperShape &s) override;

    void NewId( const std::function<int(void)> IdGenerator) override;

protected:
    std::map<int, std::shared_ptr<SuperShape>> children;

};

