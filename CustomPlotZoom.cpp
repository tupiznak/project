#include <QRubberBand>
#include "CustomPlotZoom.h"

CustomPlotZoom::CustomPlotZoom(QCustomPlot * parent)
    : mZoomMode(false)
{
    qP = parent;
    mRubberBand = new QRubberBand(QRubberBand::Rectangle, qP);
}

CustomPlotZoom::~CustomPlotZoom()
{
   delete mRubberBand;
}

void CustomPlotZoom::setZoomMode(bool mode)
{
    mZoomMode = mode;
}

void CustomPlotZoom::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::RightButton)
    {
        mOrigin = event->pos();
        mRubberBand->setGeometry(QRect(mOrigin, QSize()));
        mRubberBand->show();
    }
    QCustomPlot::mousePressEvent(event);
}

void CustomPlotZoom::mouseMoveEvent(QMouseEvent * event)
{
    if (mRubberBand->isVisible())
    {
        mRubberBand->setGeometry(QRect(mOrigin, event->pos()).normalized());
    }
    QCustomPlot::mouseMoveEvent(event);
}

void CustomPlotZoom::mouseReleaseEvent(QMouseEvent * event)
{
    if (mRubberBand->isVisible())
    {
        const QRect & zoomRect = mRubberBand->geometry();
        int xp1, yp1, xp2, yp2;
        zoomRect.getCoords(&xp1, &yp1, &xp2, &yp2);
        auto x1 = qP->xAxis->pixelToCoord(xp1);
        auto x2 = qP->xAxis->pixelToCoord(xp2);
        auto y1 = qP->yAxis->pixelToCoord(yp1);
        auto y2 = qP->yAxis->pixelToCoord(yp2);

        qP->xAxis->setRange(x1, x2);
        qP->yAxis->setRange(y1, y2);

        mRubberBand->hide();
        qP->replot();
    }
    QCustomPlot::mouseReleaseEvent(event);
}

SelectEl::SelectEl(QCustomPlot * parent, QVector<double> &d)
    :data(d),
      Selected(-1)
{
    qP = parent;
    mRubberBand = new QRubberBand(QRubberBand::Rectangle, qP);
}

void SelectEl::setSelect(int el)
{
    Selected=el;
}

void SelectEl::mousePressEvent(QMouseEvent * event)
{
//    qWarning()<<event->pos().x()<<event->pos().y()<<
//                qP->xAxis->coordToPixel(qP->xAxis->range().size())<<
//                qP->yAxis->coordToPixel(data[(int)qP->xAxis->pixelToCoord(event->pos().x())]);
    if (event->button() == Qt::LeftButton&&
            event->pos().x()>qP->xAxis->coordToPixel(0)&&
            event->pos().x()<qP->xAxis->coordToPixel(qP->xAxis->range().size())&&
            event->pos().y()<qP->yAxis->coordToPixel(0)&&
            event->pos().y()>qP->yAxis->coordToPixel(data[(int)qP->xAxis->pixelToCoord(event->pos().x())])
            )
    {
        if(Selected==(int)qP->xAxis->pixelToCoord(event->pos().x())){
            mRubberBand->hide();
            Selected=-1;
        }
        else{
            QPoint mOrigin1 = QPoint(qP->xAxis->coordToPixel((int)qP->xAxis->pixelToCoord(event->pos().x())),
                                    qP->yAxis->coordToPixel(data[(int)qP->xAxis->pixelToCoord(event->pos().x())]));
            QPoint mOrigin2 = QPoint(qP->xAxis->coordToPixel(1+(int)qP->xAxis->pixelToCoord(event->pos().x())),
                                    qP->yAxis->coordToPixel(0));
            mRubberBand->setGeometry(QRect(mOrigin1, mOrigin2));
            mRubberBand->show();

            Selected = (int)qP->xAxis->pixelToCoord(event->pos().x());
        }

       // QCPBarData a=tmp->data()->value(0.5);
    }
    QCustomPlot::mousePressEvent(event);
}
