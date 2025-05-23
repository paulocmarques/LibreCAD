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
#ifndef QG_DLGATTRIBUTES_H
#define QG_DLGATTRIBUTES_H

#include "ui_qg_dlgattributes.h"
#include "lc_dialog.h"

struct RS_AttributesData;
class RS_LayerList;

class QG_DlgAttributes : public LC_Dialog, public Ui::QG_DlgAttributes{
    Q_OBJECT
public:
    QG_DlgAttributes(QWidget* parent = nullptr);
    ~QG_DlgAttributes() override;
public slots:
    void setData( RS_AttributesData * data, RS_LayerList & layerList );
    void updateData();
protected slots:
    void languageChange();
private:
    RS_Pen m_pen;
    RS_AttributesData* m_attributesData = nullptr;
};

#endif // QG_DLGATTRIBUTES_H
