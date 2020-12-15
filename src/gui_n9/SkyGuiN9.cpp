/*
 * Stellarium
 * Copyright (C) 2008 Fabien Chereau
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

#include "SkyGuiN9.hpp"
#include "StelObjectMgr.hpp"
#include "StelGuiItems.hpp"
#include "StelApp.hpp"
#include "StelGuiN9.hpp"
#include "StelCore.hpp"
#include <QGraphicsView>
#include <QDebug>
#include <QTimeLine>
#include <QGraphicsSceneMouseEvent>
#include <QSettings>
#include <QTextDocument>

#include "StelMainGraphicsView.hpp"
#include "StelQmlGui.hpp"
#include "StelUtils.hpp"

InfoPanelN9::InfoPanelN9(QGraphicsItem* parent) : QGraphicsTextItem("", parent)
{
    QSettings* conf = StelApp::getInstance().getSettings();
    Q_ASSERT(conf);
    QString objectInfo = conf->value("gui/selected_object_info", "all").toString();
    if (objectInfo == "all")
    {
        infoTextFilters = StelObject::InfoStringGroup(StelObject::AllInfo);
    }
    else if (objectInfo == "short")
    {
        infoTextFilters = StelObject::InfoStringGroup(StelObject::ShortInfo);
    }
    else if (objectInfo == "none")
    {
        infoTextFilters = StelObject::InfoStringGroup(0);
    }
    else if (objectInfo == "custom")
    {
        infoTextFilters = StelObject::InfoStringGroup(0);

        conf->beginGroup("custom_selected_info");
        if (conf->value("flag_show_name", false).toBool())
            infoTextFilters |= StelObject::Name;
        if (conf->value("flag_show_catalognumber", false).toBool())
            infoTextFilters |= StelObject::CatalogNumber;
        if (conf->value("flag_show_magnitude", false).toBool())
            infoTextFilters |= StelObject::Magnitude;
        if (conf->value("flag_show_absolutemagnitude", false).toBool())
            infoTextFilters |= StelObject::AbsoluteMagnitude;
        if (conf->value("flag_show_radecj2000", false).toBool())
            infoTextFilters |= StelObject::RaDecJ2000;
        if (conf->value("flag_show_radecofdate", false).toBool())
            infoTextFilters |= StelObject::RaDecOfDate;
        if (conf->value("flag_show_hourangle", false).toBool())
            infoTextFilters |= StelObject::HourAngle;
        if (conf->value("flag_show_altaz", false).toBool())
            infoTextFilters |= StelObject::AltAzi;
        if (conf->value("flag_show_distance", false).toBool())
            infoTextFilters |= StelObject::Distance;
        if (conf->value("flag_show_size", false).toBool())
            infoTextFilters |= StelObject::Size;
        if (conf->value("flag_show_extra1", false).toBool())
            infoTextFilters |= StelObject::Extra1;
        if (conf->value("flag_show_extra2", false).toBool())
            infoTextFilters |= StelObject::Extra2;
        if (conf->value("flag_show_extra3", false).toBool())
            infoTextFilters |= StelObject::Extra3;

        conf->endGroup();
    }
    else
    {
        qWarning() << "config.ini option gui/selected_object_info is invalid, using \"all\"";
        infoTextFilters = StelObject::InfoStringGroup(StelObject::AllInfo);
    }
}

void InfoPanelN9::setQmlLabelFromObjects(const QList<StelObjectP>& selected)
{
    QObject* infoTextLabel = StelMainGraphicsView::getInstance().getQmlGui()->getInfoTextLabel();
    QObject* nameLabel = StelMainGraphicsView::getInstance().getQmlGui()->getNameLabel();

    if (selected.isEmpty())
    {
        nameLabel->setProperty("text", "");
        infoTextLabel->setProperty("text", "");
    }
    else
    {
        StelCore* core = StelApp::getInstance().getCore();

        QString s = selected[0]->getInfoString(core, infoTextFilters | StelObject::StyledText);

        QString name, infoText;
        int h0 = s.indexOf("<h2>");
        int h1 = s.indexOf("</h2>");
        if (h0 >= 0 && h1 > 0)
        {
            name = s.mid(h0+4, h1-h0-4);
            infoText = s.mid(h1+5);
        }
        else
        {
            infoText = s;
        }

        infoTextLabel->setProperty("text", infoText);
        infoTextLabel->setProperty("color", StelUtils::vec3fToHtmlColor(selected[0]->getInfoColor()));

        nameLabel->setProperty("text", name);
        nameLabel->setProperty("color", StelUtils::vec3fToHtmlColor(selected[0]->getInfoColor()));

    }



}

void InfoPanelN9::setTextFromObjects(const QList<StelObjectP>& selected)
{
    if (selected.isEmpty())
    {
        if (!document()->isEmpty())
            document()->clear();
    }
    else
    {
        // just print details of the first item for now
        QString s = selected[0]->getInfoString(StelApp::getInstance().getCore(), infoTextFilters);
        setHtml(s);
    }
}

const QString InfoPanelN9::getSelectedText(void)
{
    return toPlainText();
}

SkyGuiN9::SkyGuiN9(QGraphicsItem * parent): QGraphicsWidget(parent), stelGui(NULL)
{

    setObjectName("StelSkyGui");

    // Construct the Windows buttons bar
    //winBar = new LeftStelBar(this);
    // Construct the bottom buttons bar
//    buttonBar = new BottomStelBar(this, QPixmap(":/graphicGui/btbg-left.png"), QPixmap(":/graphicGui/btbg-right.png"),
//                                  QPixmap(":/graphicGui/btbg-middle.png"), QPixmap(":/graphicGui/btbg-single.png"));
    infoPanel = new InfoPanelN9(this);

    // Used to display some progress bar in the lower right corner, e.g. when loading a file
    progressBarMgr = new StelProgressBarMgr(this);

//    // The path drawn around the button bars
//    buttonBarPath = new StelBarsPath(this);


//    lastButtonbarWidth = 0;
//    autoHidebts = NULL;

//    autoHideHorizontalButtonBar = true;
//    autoHideVerticalButtonBar = true;

//    animLeftBarTimeLine = new QTimeLine(200, this);
//    animLeftBarTimeLine->setCurveShape(QTimeLine::EaseInOutCurve);
//    connect(animLeftBarTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateBarsPos()));

//    animBottomBarTimeLine = new QTimeLine(200, this);
//    animBottomBarTimeLine->setCurveShape(QTimeLine::EaseInOutCurve);
//    connect(animBottomBarTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateBarsPos()));

//    setAcceptHoverEvents(true);
}

void SkyGuiN9::init(StelGuiN9* astelGui)
{
    stelGui = astelGui;

    //winBar->setParentItem(this);
//    buttonBar->setParentItem(this);
//    buttonBarPath->setParentItem(this);
    infoPanel->setParentItem(this);
    progressBarMgr->setParentItem(this);

    //winBar->setVisible(false);
//    buttonBar->setVisible(false);
//    buttonBarPath->setVisible(false);


    // Create the 2 auto hide buttons in the bottom left corner
//    autoHidebts = new CornerButtons();
//    QPixmap pxmapOn = QPixmap(":/graphicGui/HorizontalAutoHideOn.png");
//    QPixmap pxmapOff = QPixmap(":/graphicGui/HorizontalAutoHideOff.png");
//    btHorizAutoHide = new StelButton(autoHidebts, pxmapOn, pxmapOff, QPixmap(), stelGui->getGuiActions("actionAutoHideHorizontalButtonBar"), true);
//    btHorizAutoHide->setChecked(autoHideHorizontalButtonBar);
//    pxmapOn = QPixmap(":/graphicGui/VerticalAutoHideOn.png");
//    pxmapOff = QPixmap(":/graphicGui/VerticalAutoHideOff.png");
//    btVertAutoHide = new StelButton(autoHidebts, pxmapOn, pxmapOff, QPixmap(), stelGui->getGuiActions("actionAutoHideVerticalButtonBar"), true);
//    btVertAutoHide->setChecked(autoHideVerticalButtonBar);

//    btHorizAutoHide->setPos(1,btVertAutoHide->pixmap().height()-btHorizAutoHide->pixmap().height()+1);
//    btVertAutoHide->setPos(0,0);
//    btVertAutoHide->setZValue(1000);
//    autoHidebts->setParentItem(this);

//    // If auto hide is off, show the relevant toolbars
//    if (!autoHideHorizontalButtonBar)
//    {
//        animBottomBarTimeLine->setDirection(QTimeLine::Forward);
//        animBottomBarTimeLine->start();
//    }

//    if (!autoHideVerticalButtonBar)
//    {
//        animLeftBarTimeLine->setDirection(QTimeLine::Forward);
//        animLeftBarTimeLine->start();
//    }

//    buttonBarPath->setZValue(-0.1);
    updateBarsPos();
    //connect(&StelApp::getInstance(), SIGNAL(colorSchemeChanged(const QString&)), this, SLOT(setStelStyle(const QString&)));
}

void SkyGuiN9::resizeEvent(QGraphicsSceneResizeEvent* event)
{
    QGraphicsWidget::resizeEvent(event);
        updateBarsPos();
}



//! Update the position of the button bars in the main window
void SkyGuiN9::updateBarsPos()
{
    const int ww = geometry().width();
    const int hh = geometry().height();
//    bool updatePath = false;

//    // Use a position cache to avoid useless redraw triggered by the position set if the bars don't move
//    double rangeX = winBar->boundingRectNoHelpLabel().width()+2.*buttonBarPath->getRoundSize()+1.;
//    const qreal newWinBarX = buttonBarPath->getRoundSize()-(1.-animLeftBarTimeLine->currentValue())*rangeX-0.5;
//    const qreal newWinBarY = hh-winBar->boundingRectNoHelpLabel().height()-buttonBar->boundingRectNoHelpLabel().height()-20;
//    if (winBar->pos().x()!=newWinBarX || winBar->pos().y()!=newWinBarY)
//    {
//        winBar->setPos(round(newWinBarX), round(newWinBarY));
//        updatePath = true;
//    }

//    double rangeY = buttonBar->boundingRectNoHelpLabel().height()+0.5-7.-buttonBarPath->getRoundSize();
//    const qreal newButtonBarX = winBar->boundingRectNoHelpLabel().right()+buttonBarPath->getRoundSize();
//    const qreal newButtonBarY = hh-buttonBar->boundingRectNoHelpLabel().height()-buttonBarPath->getRoundSize()+0.5+(1.-animBottomBarTimeLine->currentValue())*rangeY;
//    if (buttonBar->pos().x()!=newButtonBarX || buttonBar->pos().y()!=newButtonBarY)
//    {
//        buttonBar->setPos(round(newButtonBarX), round(newButtonBarY));
//                updatePath = true;
//    }

//    if (lastButtonbarWidth != buttonBar->boundingRectNoHelpLabel().width())
//    {
//                updatePath = true;
//                lastButtonbarWidth = (int)(buttonBar->boundingRectNoHelpLabel().width());
//    }

//    if (updatePath)
//        buttonBarPath->updatePath(buttonBar, winBar);

    const qreal newProgressBarX = ww-progressBarMgr->boundingRect().width()-20;
    const qreal newProgressBarY = hh-progressBarMgr->boundingRect().height()+7;
    progressBarMgr->setPos(newProgressBarX, newProgressBarY);
    progressBarMgr->setZValue(400);

    // Update position of the auto-hide buttons
//    autoHidebts->setPos(0, hh-autoHidebts->childrenBoundingRect().height()+1);
//    double opacity = qMax(animLeftBarTimeLine->currentValue(), animBottomBarTimeLine->currentValue());
//    autoHidebts->setOpacity(opacity < 0.01 ? 0.01 : opacity);	// Work around a qt bug
}


// Add a new progress bar in the lower right corner of the screen.
QProgressBar* SkyGuiN9::addProgressBar()
{
    return progressBarMgr->addProgressBar();
}

void SkyGuiN9::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
    stelGui->update();
}

