#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
#include "CustomPlotZoom.h"
#define LOG_FILE "./1.txt"

namespace Ui {
class MainWindow;
//class CustomPlotZoom;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void setupStatistic(QCustomPlot *customPlot);

private slots:
  void UpdateSlot();
  void screenShot();

  void mousePressEvent(QMouseEvent * event) override;

  void horzScrollBarChanged(int value);
  void horzSliderChanged(int value);

protected:
  Ui::MainWindow *ui;
  QTimer dataTimer;
  CustomPlotZoom *zoom;
  SelectEl *click;

  QFile *File;
  QTextStream *filein;
  qptrdiff lastpos;

  QVector<QMap<QString,QVariant> > BigTable;
  QVector<double> ticks;
  QVector<QString> labels;
  QVector<double> columnData;
  QCPBars *column;

  int maxHeightFromInterval;

  char StartInitTable();
  void FillGrid();
  void FillBars(int i);
};


#endif // MAINWINDOW_H
