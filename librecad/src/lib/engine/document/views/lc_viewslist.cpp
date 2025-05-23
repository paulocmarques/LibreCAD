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

#include "lc_viewslist.h"

LC_ViewList::LC_ViewList() {
    setModified(false);
}

void LC_ViewList::clear() {
    m_namedViews.clear();
    setModified(false);
}

void LC_ViewList::add(LC_View *view) {
    if (view == nullptr) {
        return;
    }

    // check if layer already exists:
    LC_View *v = find(view->getName());
    if (v == nullptr) {
        m_namedViews.append(view);
    }
}

void LC_ViewList::addNew(LC_View *view) {
    if (view == nullptr) {
        return;
    }

    // check if layer already exists:
    LC_View *v = find(view->getName());
    if (v == nullptr) {
        m_namedViews.append(view);
        setModified(true);
    }
}

void LC_ViewList::remove(LC_View *view) {
    m_namedViews.removeOne(view);
    setModified(true);
    delete view;
}

void LC_ViewList::remove(const QString &name) {
    LC_View *v = find(name);
    if (v !=nullptr) {
        remove(v);
    }
}

void LC_ViewList::rename(LC_View *view, const QString &newName) {
    view->setName(newName);
    setModified(true);
}

void LC_ViewList::edited([[maybe_unused]]LC_View *view) {
    setModified(true);
}

LC_View *LC_ViewList::find(const QString &name) const{
    for (auto v: m_namedViews){
        if (v->getName() == name){
            return v;
        }
    }
    return nullptr;
}

int LC_ViewList::getIndex(const QString &name) const{
    int result = -1;

    for (int i = 0; i < m_namedViews.size(); i++) {
        LC_View *v = m_namedViews.at(i);
        if (v->getName() == name) {
            result = i;
            break;
        }
    }
    return result;
}

int LC_ViewList::getIndex(LC_View *view) const{
    return m_namedViews.indexOf(view);
}

void LC_ViewList::setModified(bool m) {
    m_modified = m;
    fireModified(m);
}
