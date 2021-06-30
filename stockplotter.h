#ifndef STOCKPLOTTER_H
#define STOCKPLOTTER_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "qcustomplot.h"
#include "Stock.h"
#include "advancedstock.h"

class StockPlotter
{
    //Class is inteded to be used with QCustomPlot
    //QcustomPlot pointer needs to be passed in
    //Each StockPlotter requires a QcustomPlot pointer assigned to a widget in QT
public:
    StockPlotter(QCustomPlot* m_stockPlot);
    ~StockPlotter();
    void PlotPriceDate(AdvancedStock GraphingStock,std::string TimePeriod);
private:
    QCustomPlot* stockPlot;
};

#endif // STOCKPLOTTER_H
