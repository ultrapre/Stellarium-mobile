/*
 * Stellarium
 * Copyright (C) 2009 Fabien Chereau
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef _SKYGUIN9_HPP_
#define _SKYGUIN9_HPP_

#include "StelStyle.hpp"
#include "StelObject.hpp"

#include <QDebug>
#include <QGraphicsWidget>



class QGraphicsSceneMouseEvent;
class QAction;
class QGraphicsTextItem;
class QTimeLine;
class StelButton;
class BottomStelBar;



//! The informations about the currently selected object
class InfoPanelN9 : public QGraphicsTextItem
{
    public:
        //! Reads "gui/selected_object_info", etc from the configuration file.
        //! @todo Bad idea to read from the configuration file in a constructor? --BM
        InfoPanelN9(QGraphicsItem* parent);
        void setInfoTextFilters(const StelObject::InfoStringGroup& aflags) {infoTextFilters=aflags;}
        const StelObject::InfoStringGroup& getInfoTextFilters(void) const {return infoTextFilters;}
        void setTextFromObjects(const QList<StelObjectP>&);
        const QString getSelectedText(void);

        void setQmlLabelFromObjects(const QList<StelObjectP>&);

    private:
        StelObject::InfoStringGroup infoTextFilters;

};
/*
*/

//! The class managing the layout for button bars, selected object info and loading bars.
class SkyGuiN9: public QGraphicsWidget
{
    Q_OBJECT

public:
    friend class StelGuiN9;


    SkyGuiN9(QGraphicsItem * parent=NULL);
    //! Add a new progress bar in the lower right corner of the screen.
    //! When the progress bar is deleted with removeProgressBar() the layout is automatically rearranged.
    //! @return a pointer to the progress bar
    class QProgressBar* addProgressBar();

    void init(class StelGuiN9* stelGui);

    virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = 0);

protected:
    virtual void resizeEvent(QGraphicsSceneResizeEvent* event);


private slots:

    //! Update the position of the button bars in the main window
    void updateBarsPos();

private:
    //class StelBarsPath* buttonBarPath;
    //QTimeLine* animLeftBarTimeLine;
    //QTimeLine* animBottomBarTimeLine;
    //int lastButtonbarWidth;
    //class LeftStelBar* winBar;
    //BottomStelBar* buttonBar;
    class InfoPanelN9* infoPanel;
    class StelProgressBarMgr* progressBarMgr;

    // The 2 auto hide buttons in the lower left corner
    //StelButton* btHorizAutoHide;
    //StelButton* btVertAutoHide;

    //class CornerButtons* autoHidebts;

    //bool autoHideHorizontalButtonBar;
    //bool autoHideVerticalButtonBar;

    StelGuiN9* stelGui;

};

#endif // _SKYGUIN9_HPP_
