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

#include "rs_actionblocksattributes.h"

#include "qc_applicationwindow.h"
#include "qc_mdiwindow.h"
#include "rs_block.h"
#include "rs_debug.h"
#include "rs_dialogfactory.h"
#include "rs_dialogfactoryinterface.h"
#include "rs_graphic.h"

class RS_BlockList;
class RS_Block;

RS_ActionBlocksAttributes::RS_ActionBlocksAttributes(LC_ActionContext *actionContext)
        :RS_ActionInterface("Edit Block Attributes",actionContext, RS2::ActionBlocksAttributes) {}

void RS_ActionBlocksAttributes::trigger() {
    RS_DEBUG->print("editing block attributes");

	if (m_graphic != nullptr) {
        RS_Block* block = m_graphic->getActiveBlock();
        RS_BlockList* blockList = m_graphic->getBlockList();
        if (blockList != nullptr && block != nullptr) {
            QString oldName = block->getName();

            RS_BlockData d = RS_DIALOGFACTORY->requestBlockAttributesDialog(blockList);

            if (d.isValid()) {
                QString newName = d.name;
                // update window title of opened block
                auto& appWindow = QC_ApplicationWindow::getAppWindow();
                if (QC_MDIWindow* blockWindow = appWindow->getWindowWithDoc(block)) {
                    QString title = blockWindow->windowTitle();
                    title = title.replace(
                            "'" + oldName + "'",
                            "'" + newName + "'");
                    blockWindow->setWindowTitle(title);
                }
                blockList->rename(block, newName);
                // update the name of all inserts:
                m_graphic->renameInserts(oldName, newName);
                m_graphic->addBlockNotification();
            }
        }
    }
    finish(false);
}

void RS_ActionBlocksAttributes::init(int status) {
    RS_ActionInterface::init(status);
    trigger();
}
