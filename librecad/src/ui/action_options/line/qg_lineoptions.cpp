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
#include "qg_lineoptions.h"
#include "rs_actiondrawline.h"
#include "ui_qg_lineoptions.h"

/*
 *  Constructs a QG_LineOptions as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_LineOptions::QG_LineOptions()
    : LC_ActionOptionsWidgetBase(RS2::ActionDrawLine, "","")
	, ui(new Ui::Ui_LineOptions{})
{
	ui->setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_LineOptions::~QG_LineOptions() = default;

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_LineOptions::languageChange(){
	ui->retranslateUi(this);
}

void QG_LineOptions::doSaveSettings(){
}

void QG_LineOptions::doSetAction(RS_ActionInterface *a, [[maybe_unused]]bool update){
		m_action = dynamic_cast<RS_ActionDrawLine*>(a);
}

void QG_LineOptions::close() {
    if (m_action) {
        m_action->close();
    }
}

void QG_LineOptions::undo() {
    if (m_action) {
        m_action->undo();
    }
}


void QG_LineOptions::redo() {
    if (m_action) {
        m_action->redo();
    }
}
