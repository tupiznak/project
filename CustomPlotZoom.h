#pragma once

#include <QPoint>
#include "qcustomplot.h"

class QRubberBand;
class QMouseEvent;
class QWidget;

class CustomPlotZoom : public QCustomPlot
{
    Q_OBJECT
 
public:
    CustomPlotZoom(QCustomPlot * parent = 0);
    virtual ~CustomPlotZoom();

    void setZoomMode(bool mode);
 
public slots:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
 
private:
    bool mZoomMode;
    QRubberBand * mRubberBand;
    QPoint mOrigin;
    QCustomPlot *qP;
};

class SelectEl:public QCustomPlot
{
    Q_OBJECT

public:
    SelectEl(QCustomPlot * parent, QVector<double> &d);
    virtual ~SelectEl(){delete mRubberBand;};

    int Selected;

    void setSelect(int el);

public slots:
    void mousePressEvent(QMouseEvent * event) override;

private:
    QRubberBand * mRubberBand;
    QCustomPlot *qP;
    QVector<double> &data;
};
