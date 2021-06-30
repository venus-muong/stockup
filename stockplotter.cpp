#include "stockplotter.h"

StockPlotter::StockPlotter(QCustomPlot* m_stockPlot){
    //Sets up an initially empty plot
    //MUST TAKE IN POINTER TO THE QCustomPlot object
    stockPlot = m_stockPlot;
    stockPlot->addGraph();
    stockPlot->xAxis->setLabel("Date");
    stockPlot->yAxis->setLabel("Price");
    stockPlot->yAxis2->setLabel("Volume");
    m_stockPlot->replot();
}
StockPlotter::~StockPlotter(){

}
void StockPlotter::PlotPriceDate(AdvancedStock GraphingStock,std::string TimePeriod){
    //Uses the GraphingStock to plot the date against the price
    //replots using the same pointer to QCustomPlot Widget
    std::vector<double> volume = GraphingStock.getHistVolume(TimePeriod);
    std::vector<double> price = GraphingStock.getHistPrice(TimePeriod);
    std::vector<std::string> dates = GraphingStock.getDates(TimePeriod);

    std::vector<std::string>::iterator it;
    QVector<double> Time;
    QDateTime DatePoint;
    for (it= dates.begin(); it != dates.end(); ++it){
        int Year, Month, Day;
        std::sscanf((*it).c_str(), "%d-%d-%d", &Year, &Month, &Day);
        DatePoint = QDateTime(QDate(Year, Month, Day));
        Time.push_back(DatePoint.toTime_t());
    }
    QVector<double> QVolume = QVector<double>::fromStdVector(volume);
    QVector<double> QPrice = QVector<double>::fromStdVector(price);

    stockPlot ->addGraph();
    stockPlot -> graph(0)->setData(Time,QPrice);

    stockPlot->xAxis->setLabel("Date");
    stockPlot->yAxis->setLabel("Price");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    stockPlot->xAxis->setTicker(dateTicker);
    //stockPlot ->addGraph();
    //stockPlot ->graph(1)->setData(Time,QVolume);

    // set a more compact font size for bottom and left axis tick labels:
    stockPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    stockPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    //stockPlot->xAxis->setRange(-1,1);
    //stockPlot->yAxis->setRange(0,1);
    stockPlot->graph(0)->rescaleAxes();
    stockPlot->replot();
}
