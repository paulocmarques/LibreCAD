/*******************************************************************************
 *
 This file is part of the LibreCAD project, a 2D CAD program

 Copyright (C) 2024 LibreCAD.org
 Copyright (C) 2024 sand1024

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 ******************************************************************************/

#ifndef LC_ACTIONPOLYLINEARCSTOLINES_H
#define LC_ACTIONPOLYLINEARCSTOLINES_H

#include "rs_previewactioninterface.h"

class RS_Polyline;

class LC_ActionPolylineArcsToLines:public RS_PreviewActionInterface {
    Q_OBJECT
public:
    explicit LC_ActionPolylineArcsToLines(LC_ActionContext *actionContext);
    ~LC_ActionPolylineArcsToLines() override;
    void init(int status) override;
protected:
    enum Status{
        SetEntity
    };
    RS_Polyline* m_polyline;
    RS2::CursorType doGetMouseCursor(int status) override;
    void updateMouseButtonHints() override;
    void onMouseLeftButtonRelease(int status, LC_MouseEvent *e) override;
    void onMouseRightButtonRelease(int status, LC_MouseEvent *e) override;
    void onMouseMoveEvent(int status, LC_MouseEvent *event) override;
    RS_Polyline *createPolyline(RS_Polyline *pPolyline);
    bool hasArcsSegments(RS_Polyline *p);
    void doTrigger() override;
};
#endif // LC_ACTIONPOLYLINEARCSTOLINES_H
