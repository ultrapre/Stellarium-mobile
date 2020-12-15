/*
 * StellariumN9 QML Gui
 * Copyright (C) 2012 Marko Srebre
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


import QtQuick 1.1
import com.nokia.meego 1.1
import com.nokia.extras 1.1



Page {
    tools: commonTools

    id: dateTimePage
    objectName: "DateTimePage"

    property double yeard

    property alias year: dateDialog.year
    property alias month: dateDialog.month
    property alias day: dateDialog.day

    property alias hour: timeDialog.hour
    property alias minute: timeDialog.minute
    property alias second: timeDialog.second

    signal dateChanged(int y, int m, int d)
    signal timeChanged(int h, int m, int s)


    function formatDate() {
        var d = new Date
        d.setFullYear(year)
        d.setMonth(month)
        d.setDate(day)
        //return year + "-" + month + "-" + day
        return Qt.formatDate(d)

    }

    function formatTime() {
        var t = new Date
        t.setHours(hour)
        t.setMinutes(minute)
        t.setSeconds(second)

        //return hour + ":" + minute + ":" + second
        return Qt.formatTime(t, "hh:mm:ss")
    }

    ListView {

        id: view
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        clip: true
        model: itemModel


    }

    property bool updateMinMaxYears: true

    onYearChanged: {
        yearSlider.value = year
        updateMinMaxYears = (year < dateDialog.minimumYear + 5 || year > dateDialog.maximumYear - 5)
    }



    VisualItemModel {
        id: itemModel

        HeaderRow {
            title: "Date and time"
        }

        SeparatorRow {}


        PageRow {
            title: "Date"
            subtitle: formatDate()
            mouseArea.onClicked: {
                if (updateMinMaxYears)
                {
                    var newMin = year - 30
                    var newMax = year + 30
                    if (newMin < dateDialog.minimumYear)
                    {
                        dateDialog.maximumYear = newMax
                        dateDialog.minimumYear = newMin
                    }
                    else
                    {
                        dateDialog.minimumYear = newMin
                        dateDialog.maximumYear = newMax
                    }

                    updateMinMaxYears = false
                }
                dateDialog.open()
            }
        }

        PageRow {
            title: "Time"
            subtitle: formatTime()
            mouseArea.onClicked: timeDialog.open()
        }

        SeparatorRow {}

        SliderRow {
            id: yearSlider
            title: "Year " + year
            label.font: UiConstants.TitleFont
            minimumValue: -10000
            maximumValue:   10000
            stepSize: 50
            onValueChanged: {
                year = Math.floor(value)
                dateTimePage.dateChanged(year, month, day)
            }
        }



    }

    DatePickerDialog {
        id: dateDialog
        onAccepted: { dateTimePage.dateChanged(year, month, day) }
    }

    TimePickerDialog {
        id: timeDialog
        onAccepted: { dateTimePage.timeChanged(hour, minute, second) }
    }



}

