/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MOCKCAMERAZOOMCONTROL_H
#define MOCKCAMERAZOOMCONTROL_H

#include "qcamerazoomcontrol.h"

class MockCameraZoomControl : public QCameraZoomControl
{
    Q_OBJECT
public:
    MockCameraZoomControl(QObject *parent = 0):
        QCameraZoomControl(parent),
        m_opticalZoom(1.0),
        m_digitalZoom(1.0),
        m_maxOpticalZoom(3.0),
        m_maxDigitalZoom(4.0)

    {
    }

    ~MockCameraZoomControl() {}

    qreal maximumOpticalZoom() const
    {
        return m_maxOpticalZoom;
    }

    qreal maximumDigitalZoom() const
    {
        return m_maxDigitalZoom;
    }

    qreal currentOpticalZoom() const
    {
        return m_opticalZoom;
    }

    qreal currentDigitalZoom() const
    {
        return m_digitalZoom;
    }

    qreal requestedOpticalZoom() const
    {
        return m_opticalZoom;
    }

    qreal requestedDigitalZoom() const
    {
        return m_digitalZoom;
    }

    void zoomTo(qreal optical, qreal digital)
    {
        optical = qBound<qreal>(1.0, optical, maximumOpticalZoom());
        digital = qBound<qreal>(1.0, digital, maximumDigitalZoom());

        if (!qFuzzyCompare(digital, m_digitalZoom)) {
            m_digitalZoom = digital;
            emit requestedDigitalZoomChanged(m_digitalZoom);
            emit currentDigitalZoomChanged(m_digitalZoom);
        }

        if (!qFuzzyCompare(optical, m_opticalZoom)) {
            m_opticalZoom = optical;
            emit requestedOpticalZoomChanged(m_opticalZoom);
            emit currentOpticalZoomChanged(m_opticalZoom);
        }

        maxOpticalDigitalZoomChange(4.0, 5.0);
    }

    // helper function to emit maximum Optical and Digital Zoom Changed signals
    void maxOpticalDigitalZoomChange(qreal maxOptical, qreal maxDigital)
    {
        if (maxOptical != m_maxOpticalZoom) {
            m_maxOpticalZoom = maxOptical;
            emit maximumOpticalZoomChanged(m_maxOpticalZoom);
        }

        if (maxDigital != m_maxDigitalZoom) {
            m_maxDigitalZoom = maxDigital;
            emit maximumDigitalZoomChanged(m_maxDigitalZoom);
        }
    }

private:
    qreal m_opticalZoom;
    qreal m_digitalZoom;
    qreal m_maxOpticalZoom;
    qreal m_maxDigitalZoom;
};

#endif // MOCKCAMERAZOOMCONTROL_H