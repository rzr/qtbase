/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPOLYGON_H
#define QPOLYGON_H

#include <QtCore/qvector.h>
#include <QtCore/qpoint.h>
#include <QtCore/qrect.h>

QT_BEGIN_NAMESPACE


class QMatrix;
class QTransform;
class QRect;
class QVariant;

class Q_GUI_EXPORT QPolygon : public QVector<QPoint>
{
public:
    inline QPolygon() {}
    inline ~QPolygon() {}
    inline explicit QPolygon(int size);
    inline QPolygon(const QPolygon &a) : QVector<QPoint>(a) {}
    inline /*implicit*/ QPolygon(const QVector<QPoint> &v) : QVector<QPoint>(v) {}
    QPolygon(const QRect &r, bool closed=false);
    QPolygon(int nPoints, const int *points);
#ifdef Q_COMPILER_RVALUE_REFS
    QPolygon &operator=(QPolygon &&other) Q_DECL_NOTHROW { swap(other); return *this; }
#endif
    QPolygon &operator=(const QPolygon &other) { QVector<QPoint>::operator=(other); return *this; }
    void swap(QPolygon &other) Q_DECL_NOTHROW { QVector<QPoint>::swap(other); } // prevent QVector<QPoint><->QPolygon swaps

    operator QVariant() const;

    void translate(int dx, int dy);
    void translate(const QPoint &offset);

    QPolygon translated(int dx, int dy) const Q_REQUIRED_RESULT;
    inline QPolygon translated(const QPoint &offset) const Q_REQUIRED_RESULT;

    QRect boundingRect() const;

    void point(int i, int *x, int *y) const;
    QPoint point(int i) const;
    void setPoint(int index, int x, int y);
    void setPoint(int index, const QPoint &p);
    void setPoints(int nPoints, const int *points);
    void setPoints(int nPoints, int firstx, int firsty, ...);
    void putPoints(int index, int nPoints, const int *points);
    void putPoints(int index, int nPoints, int firstx, int firsty, ...);
    void putPoints(int index, int nPoints, const QPolygon & from, int fromIndex=0);

    bool containsPoint(const QPoint &pt, Qt::FillRule fillRule) const;

    QPolygon united(const QPolygon &r) const Q_REQUIRED_RESULT;
    QPolygon intersected(const QPolygon &r) const Q_REQUIRED_RESULT;
    QPolygon subtracted(const QPolygon &r) const Q_REQUIRED_RESULT;
};

inline QPolygon::QPolygon(int asize) : QVector<QPoint>(asize) {}

#ifndef QT_NO_DEBUG_STREAM
Q_GUI_EXPORT QDebug operator<<(QDebug, const QPolygon &);
#endif

/*****************************************************************************
  QPolygon stream functions
 *****************************************************************************/
#ifndef QT_NO_DATASTREAM
Q_GUI_EXPORT QDataStream &operator<<(QDataStream &stream, const QPolygon &polygon);
Q_GUI_EXPORT QDataStream &operator>>(QDataStream &stream, QPolygon &polygon);
#endif

/*****************************************************************************
  Misc. QPolygon functions
 *****************************************************************************/

inline void QPolygon::setPoint(int index, const QPoint &pt)
{ (*this)[index] = pt; }

inline void QPolygon::setPoint(int index, int x, int y)
{ (*this)[index] = QPoint(x, y); }

inline QPoint QPolygon::point(int index) const
{ return at(index); }

inline void QPolygon::translate(const QPoint &offset)
{ translate(offset.x(), offset.y()); }

inline QPolygon QPolygon::translated(const QPoint &offset) const
{ return translated(offset.x(), offset.y()); }

class QRectF;

class Q_GUI_EXPORT QPolygonF : public QVector<QPointF>
{
public:
    inline QPolygonF() {}
    inline ~QPolygonF() {}
    inline explicit QPolygonF(int size);
    inline QPolygonF(const QPolygonF &a) : QVector<QPointF>(a) {}
    inline /*implicit*/ QPolygonF(const QVector<QPointF> &v) : QVector<QPointF>(v) {}
    QPolygonF(const QRectF &r);
    /*implicit*/ QPolygonF(const QPolygon &a);
#ifdef Q_COMPILER_RVALUE_REFS
    QPolygonF &operator=(QPolygonF &&other) Q_DECL_NOTHROW { swap(other); return *this; }
#endif
    QPolygonF &operator=(const QPolygonF &other) { QVector<QPointF>::operator=(other); return *this; }
    inline void swap(QPolygonF &other) { QVector<QPointF>::swap(other); } // prevent QVector<QPointF><->QPolygonF swaps

    operator QVariant() const;

    inline void translate(qreal dx, qreal dy);
    void translate(const QPointF &offset);

    inline QPolygonF translated(qreal dx, qreal dy) const;
    QPolygonF translated(const QPointF &offset) const Q_REQUIRED_RESULT;

    QPolygon toPolygon() const;

    bool isClosed() const { return !isEmpty() && first() == last(); }

    QRectF boundingRect() const;

    bool containsPoint(const QPointF &pt, Qt::FillRule fillRule) const;

    QPolygonF united(const QPolygonF &r) const Q_REQUIRED_RESULT;
    QPolygonF intersected(const QPolygonF &r) const Q_REQUIRED_RESULT;
    QPolygonF subtracted(const QPolygonF &r) const Q_REQUIRED_RESULT;
};

inline QPolygonF::QPolygonF(int asize) : QVector<QPointF>(asize) {}

#ifndef QT_NO_DEBUG_STREAM
Q_GUI_EXPORT QDebug operator<<(QDebug, const QPolygonF &);
#endif

/*****************************************************************************
  QPolygonF stream functions
 *****************************************************************************/
#ifndef QT_NO_DATASTREAM
Q_GUI_EXPORT QDataStream &operator<<(QDataStream &stream, const QPolygonF &array);
Q_GUI_EXPORT QDataStream &operator>>(QDataStream &stream, QPolygonF &array);
#endif

inline void QPolygonF::translate(qreal dx, qreal dy)
{ translate(QPointF(dx, dy)); }

inline QPolygonF QPolygonF::translated(qreal dx, qreal dy) const
{ return translated(QPointF(dx, dy)); }

QT_END_NAMESPACE

#endif // QPOLYGON_H
