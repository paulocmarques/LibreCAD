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


#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include <memory>
#include <tuple>
#include <vector>

#include <QMap>
#include <QWidget>

#include "lc_cursoroverlayinfo.h"
#include "lc_rect.h"
#include "rs.h"
#include "rs_pen.h"

#define DEBUG_RENDERING_

#ifdef DEBUG_RENDERING
#include <QElapsedTimer>
#endif

class QDateTime;
class QKeyEvent;

class RS_ActionInterface;
class RS_Color;
class RS_CommandEvent;
class RS_Entity;
class RS_EntityContainer;
class RS_EventHandler;
class RS_Graphic;
class RS_Grid;
class RS_Painter;

struct RS_LineTypePattern;
struct RS_SnapMode;

/**
 * This class is a common GUI interface for the graphic viewer
 * widget which has to be implemented by real GUI classes such
 * as the Qt graphical view.
 *
 * Note that this is just an interface used as a slot to
 * communicate with the LibreCAD from a GUI level.
 */
class RS_GraphicView:public QWidget {
Q_OBJECT

public:
    RS_GraphicView(QWidget *parent = nullptr, Qt::WindowFlags f = {});
    virtual ~RS_GraphicView();
    void cleanUp();
/**
 * @return Pointer to the graphic entity if the entity container
 * connected to this view is a graphic and valid.
 * NULL otherwise.
 */
    RS_Graphic *getGraphic() const;

/**
 * \brief setDrawingMode Sets the drawing mode.
 */
    void setDrawingMode(RS2::DrawingMode m){
        drawingMode = m;
    }

/**
 * @return Current drawing mode.
 */
    RS2::DrawingMode getDrawingMode() const{
        return drawingMode;
    }

/**
 * Activates or deactivates the delete mode.
 */
    void setDeleteMode(bool m){
        deleteMode = m;
    }

/**
 * @reval true Deleting instead of drawing.
  *        false Normal drawing mode.
 */
    bool getDeleteMode() const{
        return deleteMode;
    }

    virtual void loadSettings();
/** This virtual method must be overwritten to return
  the width of the widget the graphic is shown in */
    virtual int getWidth() const = 0;
/** This virtual method must be overwritten to return
  the height of the widget the graphic is shown in */
    virtual int getHeight() const = 0;
/** This virtual method must be overwritten to redraw
  the widget. */
    virtual void redraw(RS2::RedrawMethod method = RS2::RedrawAll) = 0;
/** This virtual method must be overwritten and is then
  called whenever the view changed */
    virtual void adjustOffsetControls() = 0;
/** This virtual method must be overwritten and is then
  called whenever the view changed */
    virtual void adjustZoomControls() = 0;
/**
 * Sets the background color. Note that applying the background
 * color for the widget is up to the implementing class.
 */
    virtual void setBackground(const RS_Color &bg);
/**
  * @return Current background color.
  */
    RS_Color getBackground() const;
/**
  * @return Current foreground color.
  */
    RS_Color getForeground() const;
/**
  * Sets the grid color.
  */
    void setGridColor(const RS_Color &c);
/**
  * Sets the meta grid color.
  */
    void setMetaGridColor(const RS_Color &c);
/**
  * Sets the selection color.
  */
    void setSelectedColor(const RS_Color &c);
/**
  * Sets the highlight color.
  */
    void setHighlightedColor(const RS_Color &c);
/**
  * Sets the color for the first handle (start vertex)
  */
    void setStartHandleColor(const RS_Color &c);
/**
  * Sets the color for handles, that are neither start nor end vertices
  */
    void setHandleColor(const RS_Color &c);
/**
  * Sets the color for the last handle (end vertex)
  */
    void setEndHandleColor(const RS_Color &c);

    const RS_Color &getOverlayBoxLineColor() const;
    void setOverlayBoxLineColor(const RS_Color &overlayBoxLine);
    const RS_Color &getOverlayBoxLineInvertedColor() const;
    void setOverlayBoxLineInvertedColor(const RS_Color &overlayBoxLineInverted);
    const RS_Color &getOverlayBoxFillInvertedColor() const;
    const RS_Color &getOverlayBoxFillColor() const;
    void setOverlayBoxFillColor(const RS_Color &overlayBoxFill);
    void setOverlayBoxFillInvertedColor(const RS_Color &overlayBoxFillInverted);

/* Sets the color for the relative-zero marker. */
    void setRelativeZeroColor(const RS_Color &c);
    void setPreviewReferenceEntitiesColor(const RS_Color& c);
    void setPreviewReferenceHighlightedEntitiesColor(const RS_Color& c);
    void setXAxisExtensionColor(const RS_Color& c);
    void setYAxisExtensionColor(const RS_Color& c);

/* Sets the hidden state for the relative-zero marker. */
    void setRelativeZeroHiddenState(bool isHidden);
    bool isRelativeZeroHidden();
/**
 * This virtual method can be overwritten to set the mouse
 * cursor to the given type.
 */
    virtual void setMouseCursor(RS2::CursorType /*c*/) = 0;
    void setContainer(RS_EntityContainer *container);
    RS_EntityContainer *getContainer() const;
    void setFactor(double f);
    void setFactorX(double f);
    void setFactorY(double f);
    RS_Vector getFactor() const;
/**
 * @brief setOffset
 * @param ox, offset X
 * @param oy, offset Y
 */
    virtual void setOffset(int ox, int oy);
    void setOffsetX(int ox);
    void setOffsetY(int oy);
    int getOffsetX() const;
    int getOffsetY() const;
    void centerOffsetX();
    void centerOffsetY();
    void centerX(double x);
    void centerY(double y);
/**
 * Sets a fixed border in pixel around the graphic. This border
 * specifies how far the user can scroll outside the graphic
 * area.
 */
    void setBorders(int left, int top, int right, int bottom);
    int getBorderLeft() const;
    int getBorderTop() const;
    int getBorderRight() const;
    int getBorderBottom() const;
    void freezeZoom(bool freeze);
    bool isZoomFrozen() const;
    void setDefaultAction(RS_ActionInterface *action);
    RS_ActionInterface *getDefaultAction();
    void setCurrentAction(RS_ActionInterface *action);
    RS_ActionInterface *getCurrentAction();
    QString getCurrentActionName();
    QIcon getCurrentActionIcon();
    void killSelectActions();
    void killAllActions();
    void back();
    void enter();
    void commandEvent(RS_CommandEvent *e);
    void keyPressEvent(QKeyEvent *event) override;
    void enableCoordinateInput();
    void disableCoordinateInput();
    virtual void zoomIn(double f = 1.5, const RS_Vector &center = RS_Vector(false));
    virtual void zoomInX(double f = 1.5);
    virtual void zoomInY(double f = 1.5);
    virtual void zoomOut(double f = 1.5, const RS_Vector &center = RS_Vector(false));
    virtual void zoomOutX(double f = 1.5);
    virtual void zoomOutY(double f = 1.5);
    virtual void zoomAuto(bool axis = true, bool keepAspectRatio = true);
    virtual void zoomAutoY(bool axis = true);
    virtual void zoomPrevious();
    virtual void saveView();
    virtual void restoreView();
    virtual void zoomWindow(
        RS_Vector v1, RS_Vector v2,
        bool keepAspectRatio = true);

    virtual void zoomPan(int dx, int dy);
    virtual void zoomScroll(RS2::Direction direction);
    virtual void zoomPage();
    void zoomPageEx();
    virtual void drawWindow_DEPRECATED(RS_Vector v1, RS_Vector v2);
    void drawLayer1(RS_Painter *painter);
    void drawLayer2(RS_Painter *painter);
    void drawLayer3(RS_Painter *painter);
    void deleteEntity(RS_Entity *e);
    void drawEntity(RS_Painter *painter, RS_Entity *e, double &patternOffset);
    void drawAsChild(RS_Painter *painter, RS_Entity *e, double &patternOffset);
    void drawEntity(RS_Painter *painter, RS_Entity *e);
    void drawEntity(RS_Entity *e, double &patternOffset);
    void drawEntity(RS_Entity *e);
    void drawEntityPlain(RS_Painter *painter, RS_Entity *e);
    void drawEntityPlain(RS_Painter *painter, RS_Entity *e, double &patternOffset);
    void setPenForEntity(RS_Painter *painter, RS_Entity *e, double &patternOffset, bool inOverlay);
    void setPenForPrintingEntity(RS_Painter *painter, RS_Entity *e, double &patternOffset);
    void setPenForDraftEntity(RS_Painter *painter, RS_Entity *e, double &patternOffset, bool inOverlay);
    void setPenForOverlayEntity(RS_Painter *painter, RS_Entity *e, double &patternOffset);
    void drawEntityHighlighted(RS_Entity *e, bool highlighted = true);
    virtual RS_Vector getMousePosition() const = 0;
    virtual const RS_LineTypePattern *getPattern(RS2::LineType t);
    void drawAbsoluteZero(RS_Painter *painter);
    void drawRelativeZero(RS_Painter *painter);
    void drawPaper(RS_Painter *painter);
    void drawOverlay(RS_Painter *painter);
    /**
     * @brief drawDraftSign     Display "Draft" at corners if the draft mode is turned on
     * @param painter           Painter assumed to be non-nullptr
     */
    void drawDraftSign(RS_Painter *painter);
    RS_Grid *getGrid() const;
    virtual void updateGridStatusWidget(QString) = 0;
    void setDefaultSnapMode(RS_SnapMode sm);
    RS_SnapMode getDefaultSnapMode() const;
    void setSnapRestriction(RS2::SnapRestriction sr);
    RS2::SnapRestriction getSnapRestriction() const;
    bool isGridOn() const;
    bool isGridIsometric() const;
    void setIsoViewType(RS2::IsoGridViewType chType);
    RS2::IsoGridViewType getIsoViewType() const;
    RS_Vector toGui(RS_Vector v) const;
    RS_Vector toGui(double x, double y) const;
    RS_Vector toGuiD(RS_Vector v) const;
    double toGuiX(double x) const;
    double toGuiY(double y) const;
    double toGuiDX(double d) const;
    double toGuiDY(double d) const;
    RS_Vector toGraph(const RS_Vector &v) const;
    RS_Vector toGraph(const QPointF &v) const;
    RS_Vector toGraph(int x, int y) const;
    double toGraphX(int x) const;
    double toGraphY(int y) const;
    double toGraphDX(int d) const;
    double toGraphDY(int d) const;
    RS_Vector toGraphD(int d, int y) const;
    /**
  * (Un-)Locks the position of the relative zero.
  *
  * @param lock true: lock, false: unlock
  */
    void lockRelativeZero(bool lock);
    /**
  * @return true if the position of the relative zero point is
  * locked.
  */
    bool isRelativeZeroLocked() const;
    /**
  * @return Relative zero coordinate.
  */
    RS_Vector const &getRelativeZero() const;
    void setRelativeZero(const RS_Vector &pos);
    void moveRelativeZero(const RS_Vector &pos);
    RS_EventHandler *getEventHandler() const;
    /**
  * Enables or disables print preview.
  */
    void setPrintPreview(bool pv);
    /**
  * @retval true This is a print preview graphic view.
  * @retval false Otherwise.
  */
    bool isPrintPreview() const;
    /**
  * Enables or disables printing.
  */
    void setPrinting(bool p);
/**
  * @retval true This is a graphic view for printing.
  * @retval false setSnapOtherwise.
  */
    bool isPrinting() const;
/**
  * @retval true Draft mode is on for this view (all lines with 1 pixel / no style scaling).
  * @retval false Otherwise.
  */
    bool isDraftMode() const;
    void setDraftMode(bool dm);
    bool isCleanUp(void) const;
    virtual RS_EntityContainer *getOverlayContainer(RS2::OverlayGraphics position);

    const LC_Rect &getViewRect() const{
        return view_rect;
    }

    bool isPanning() const;
    void setPanning(bool state);

    void setLineWidthScaling(bool state){
        scaleLineWidth = state;
    }

    bool getLineWidthScaling() const{
        return scaleLineWidth;
    }

    RS2::EntityType getTypeToSelect() const;
    void setTypeToSelect(RS2::EntityType mType);

    void loadGridSettings();
    double getDefaultWidthFactor() const {return defaultWidthFactor;};

    int getPointMode() const;
    int getPointSize() const;
    double getMinCircleDrawingRadius() const;
    double getMinArcDrawingRadius() const;
    double getMinEllipseMajorRadius() const;
    double getMinEllipseMinorRadius() const;
    double getMinLineDrawingLen() const;
    int getMinRenderableTextHeightInPx() const;
    void setHasNoGrid(bool hasNoGrid);
    bool isDraftLinesMode() const;
    void setDraftLinesMode(bool draftLinesMode);
    void setForcedActionKillAllowed(bool forcedActionKillAllowed);
    virtual QString obtainEntityDescription(RS_Entity *entity, RS2::EntityDescriptionLevel shortDescription);

    LC_InfoCursorOverlayPrefs*getInfoCursorOverlayPreferences(){
        return &infoCursorOverlayPreferences;
    }

    bool getPanOnZoom() const;
    bool getSkipFirstZoom() const;


    void setShowEntityDescriptionOnHover(bool show);
    bool isShowEntityDescriptionOnHover(){
        return showEntityDescriptionOnHover;
    }

    bool isDrawTextsAsDraftForPreview() const;

    void markRelativeZero(){
        markedRelativeZero = relativeZero;
    }

    RS_Vector getMarkedRelativeZero(){return markedRelativeZero;}

    RS_Undoable* getRelativeZeroUndoable();
protected:

    RS_EntityContainer *container = nullptr; // Holds a pointer to all the enties
    RS_EventHandler *eventHandler = nullptr;
    /** colors for different usages*/
    struct ColorData;
    std::unique_ptr<ColorData> m_colorData;
/** Grid */
    std::unique_ptr<RS_Grid> grid;
/**
  * Current default snap mode for this graphic view. Used for new
  * actions.
  */
    std::unique_ptr<RS_SnapMode> defaultSnapMode;
/**
  * Current default snap restriction for this graphic view. Used for new
  * actions.
  */
    RS2::SnapRestriction defaultSnapRes{};
    RS2::DrawingMode drawingMode{};

    RS_Pen lastPaintEntityPen = {};
    bool lastPaintedHighlighted = false;
    bool lastPaintedSelected = false;
    bool lastPaintOverlay = false;

    LC_InfoCursorOverlayPrefs infoCursorOverlayPreferences = LC_InfoCursorOverlayPrefs();

    enum ExtendAxisArea{
        Both,
        Positive,
        Negative,
        None
    };

    bool extendAxisLines = false;
    int extendAxisModeX = 0;
    int extendAxisModeY = 0;
    int entityHandleHalfSize = 2;
    int relativeZeroRadius = 5;
    int zeroShortAxisMarkSize = 20;
    int minRenderableTextHeightInPx = 4;
    bool ignoreDraftForHighlight = false;
/**
  * Delete mode. If true, all drawing actions will delete in background color
  * instead.
  */
    bool deleteMode = false;
    LC_Rect view_rect;
    void drawEntityReferencePoints(RS_Painter *painter, const RS_Entity *e) const;
    void invalidate();

    // painting cached values

    double unitFactor = 1.0;
    double unitFactor100 = 0.01;
    double defaultWidthFactor = 1.0;
    double paperScale = 1.0;
    // points rendering settings
    int pdmode = 1;
    double pdsize = 1;
    int screenPDSize = 1;
#ifdef DEBUG_RENDERING
    QElapsedTimer drawTimer;
    QElapsedTimer isVisibleTimer;
    QElapsedTimer setPenTimer;
    QElapsedTimer painterSetPenTimer;
    QElapsedTimer getPenTimer;
    QElapsedTimer isConstructionTimer;
    QElapsedTimer drawLayer1Timer;
    QElapsedTimer drawLayer2Timer;
    QElapsedTimer drawLayer3Timer;
    // painting debug
    int drawEntityCount = 1;
    long long entityDrawTime = 0;
    long long isVisibleTime = 0;
    long long isConstructionTime = 0;
    long long setPenTime = 0;
    long long painterSetPenTime = 0;
    long long getPenTime = 0;
    long layer1Time = 0;
    long layer2Time = 0;
    long layer3Time = 0;
#endif

    int determinePointScreenSize(RS_Painter *painter, double pdsize) const;

    double minCircleDrawingRadius = 2.0;
    double minArcDrawingRadius = 0.5;
    double minEllipseMajorRadius = 2.;
    double minEllipseMinorRadius = 1.;
    double minLineDrawingLen = 2;
    bool drawTextsAsDraftForPanning = true;
    bool drawTextsAsDraftForPreview = true;
    Qt::PenJoinStyle penJoinStyle = Qt::RoundJoin;
    Qt::PenCapStyle penCapStyle = Qt::RoundCap;

    void updateEndCapsStyle(const RS_Graphic *graphic);
    void updateJoinStyle(const RS_Graphic *graphic);
    void updatePointsStyle(RS_Graphic *graphic);
    void updateUnitAndDefaultWidthFactors(const RS_Graphic *graphic);
    void updateGraphicRelatedSettings(RS_Graphic *graphic);
private:
    bool zoomFrozen = false;
    bool draftMode = false;
    bool draftLinesMode = false;
    RS_Vector factor{1., 1.};
    int offsetX = 0;
    int offsetY = 0;
//circular buffer for saved views
    std::vector<std::tuple<int, int, RS_Vector> > savedViews;
    unsigned short savedViewIndex = 0;
    unsigned short savedViewCount = 0;
    std::unique_ptr<QDateTime> previousViewTime;
    int borderLeft = 0;
    int borderTop = 0;
    int borderRight = 0;
    int borderBottom = 0;
    RS_Vector relativeZero = RS_Vector(0, 0, 0);
    RS_Vector markedRelativeZero = RS_Vector(0,0,0);
    bool relativeZeroLocked = false;
    //! Print preview flag
    bool printPreview = false;
    //! Active when printing only:
    bool printing = false;
    // Map that will be used for overlaying additional items on top of the main CAD drawing
    QMap<int, RS_EntityContainer *> overlayEntities;
    /** if true, graphicView is under cleanup */
    bool m_bIsCleanUp = false;
    bool panning = false;
    // this flag is applicable for print-preview mode
    bool scaleLineWidth = false;
    bool inOverlayDrawing = false;
    RS2::EntityType typeToSelect = RS2::EntityType::EntityUnknown;
    bool hasNoGrid = false;
    bool forcedActionKillAllowed = true;
    bool showEntityDescriptionOnHover = false;
    bool m_panOnZoom = false;
    bool m_skipFirstZoom = false;
signals:
    void relative_zero_changed(const RS_Vector &);
    void previous_zoom_state(bool);
};

#endif
