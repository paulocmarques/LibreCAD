/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/

#include <QPolygon>
#include "rs.h"
#include "rs_infoarea.h"

/**
 * Constructor.
 */
RS_InfoArea::RS_InfoArea():
    calculationNeeded(true){
}

/**
 * Adds a point to the internal list
 *
 * @param p coordinate of the point
 */
void RS_InfoArea::push_back(const RS_Vector &p){
    if (m_points.empty()){
        baseY = p.y;
    }

    m_points.push_back(p);
    calculationNeeded = true;
}

//remove the last point
void RS_InfoArea::pop_back(){
    m_points.pop_back();
    calculationNeeded = true;
}

/**
 * Resets the points.
 */
void RS_InfoArea::reset(){
    m_points.clear();
    area = 0.0;
    circumference = 0.0;
}

/**
  * whether a point is already in contour
  *@return true if the point is a duplicate
  *@return false if the point is not in contour
  **/
bool RS_InfoArea::duplicated(const RS_Vector &p){
    if (m_points.size() < 1) return false;
    for (const RS_Vector &v: m_points) {
        if ((v - p).squared() < RS_TOLERANCE2) return true;
    }

    return false;
}

/**
 * Calculates the area and the circumference of the area.
 */
void RS_InfoArea::calculate(){
    area = 0.0;
    circumference = 0.0;
    if (m_points.size() < 3) return;

    RS_Vector p1 = m_points.front();
    for (size_t i = 0; i < m_points.size(); ++i) {
//        std::cout<<"RS_InfoArea::calculate(): "<<i<<" , "<<p1<<std::endl;
        RS_Vector p2 = m_points.at((i + 1) % m_points.size());
        area += calcSubArea(p1, p2);
        circumference += p1.distanceTo(p2);
        p1 = p2;
    }

    area = 0.5 * std::abs(area);
    calculationNeeded = false;
}

double RS_InfoArea::getArea(const QPolygon &polygon){
    double ret = 0.0;
    if (polygon.size() < 3) return ret;

    for (int i = 0; i < polygon.size(); ++i) {
        const QPoint &p0 = polygon.at(i);
        const QPoint &p1 = polygon.at((i + 1) % polygon.size());
        ret += p0.x() * p1.y() - p0.y() * p1.x();
    }
    return 0.5 * std::abs(ret);
}

/**
 * Calculates a sub area.
 *
 * @param p1 first point
 * @param p2 second point
 */
double RS_InfoArea::calcSubArea(const RS_Vector &p1, const RS_Vector &p2){
    double width = p2.x - p1.x;
    double height = (p1.y - baseY) + (p2.y - baseY);

    return width * height; //moved a factor of 0.5 to calculate()
}

// ---------------------------------//
double RS_InfoArea::getArea() const{
    return area;
}

// ---------------------------------//
double RS_InfoArea::getCircumference(){
    if (calculationNeeded)
        calculate();
    return circumference;
}

// ---------------------------------//
int RS_InfoArea::size(){
    if (calculationNeeded)
        calculate();
    return m_points.size();
}

// ---------------------------------//
const RS_Vector &RS_InfoArea::at(int i) const{
    return m_points.at(i);
}

// ---------------------------------//
RS_Vector &RS_InfoArea::at(int i) {
    return m_points.at(i);
}

// ---------------------------------//
const RS_Vector &RS_InfoArea::back() const{
    return m_points.back();
}

// ---------------------------------//
RS_Vector &RS_InfoArea::back() {
    return m_points.back();
}
