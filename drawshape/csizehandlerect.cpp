#include "csizehandlerect.h"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <qdebug.h>


CSizeHandleRect::CSizeHandleRect(QGraphicsItem *parent, EDirection d, QGraphicsItem *resizable)
    : QGraphicsRectItem(0, 0, SELECTION_HANDLE_SIZE, SELECTION_HANDLE_SIZE, parent)
    , m_dir(d)
    , m_resizable(resizable)
    , m_state(SelectionHandleOff)
{
    setParentItem(parent);
    hide();
}

CSizeHandleRect::CSizeHandleRect(QGraphicsItem *parent, CSizeHandleRect::EDirection d, QGraphicsItem *resizable, const QPixmap &pixMap)
    : QGraphicsRectItem(0, 0, pixMap.width(), pixMap.height(), parent)
    , m_dir(d)
    , m_resizable(resizable)
    , m_state(SelectionHandleOff)
{
    m_rotaImage = pixMap;
    setParentItem(parent);
    hide();
}

void CSizeHandleRect::updateCursor()
{
    switch (m_dir) {
    case Right:
        setCursor(Qt::SizeHorCursor);
        return;
    case RightTop:
        setCursor(Qt::SizeBDiagCursor);
        return;
    case RightBottom:
        setCursor(Qt::SizeFDiagCursor);
        return;
    case LeftBottom:
        setCursor(Qt::SizeBDiagCursor);
        return;
    case Bottom:
        setCursor(Qt::SizeVerCursor);
        return;
    case LeftTop:
        setCursor(Qt::SizeFDiagCursor);
        return;
    case Left:
        setCursor(Qt::SizeHorCursor);
        return;
    case Top:
        setCursor(Qt::SizeVerCursor);
        return;
    default:
        break;
    }
    setCursor(Qt::ArrowCursor);
}


void CSizeHandleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_dir == Rotation) {
        painter->drawPixmap(QPointF(rect().x(), rect().y()), m_rotaImage);
    } else {
        QColor c = QColor("limegreen");
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(c));
        painter->drawRect(rect());
    }
}


void CSizeHandleRect::setState(ESelectionHandleState st)
{
    if (st != m_state) {
        switch (st) {
        case SelectionHandleOff:
            hide();
            break;
        case SelectionHandleInactive:
        case SelectionHandleActive:
            show();
            break;
        }
        m_state = st;
    }
}

bool CSizeHandleRect::hitTest(const QPointF &point)
{
    QPointF pt = mapFromScene(point);
    return rect().contains(pt);
}

void CSizeHandleRect::move(qreal x, qreal y)
{
    setPos(x, y);
}





