#ifndef STOCKMAINWINDOW_H
#define STOCKMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "qcustomplot.h"
#include "Stock.h"
#include "stockplotter.h"
#include "Search.h"
#include "watchlist.h"
#include "advancedstock.h"


class StockMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    StockMainWindow(QWidget *parent = nullptr);
    ~StockMainWindow();


    void showData(std::string TimePeriod);

    int getIndexOfAvailableStockSpot();
    void getStockSummary();
    void changeEnabledGraphButtons(std::vector<int> enabledVector);
    void changeEnabledStockButtons(int index);
    void init();

public slots:
    void onOneMonthClicked();
    void onSixMonthsClicked();
    void onOneYearClicked();
    void onFiveYearsClicked();
    void onAddClicked();
    void onSearchClicked();
    void onStockClicked(int index);
    void UpdateStocks();
    void onWatchListClicked();
    void onSaveListClicked();
    void onNewsClicked();

signals:
    void dosomething(int val);


private:

    QWidget* mainWidget;

    QPushButton* m_oneMonthButton;
    QPushButton* m_sixMonthsButton;
    QPushButton* m_oneYearButton;
    QPushButton* m_fiveYearsButton;

    QPushButton* m_addButton;
    QPushButton* m_searchButton;
    QPushButton* m_watchListButton;
    QPushButton* m_saveList;
    QPushButton* m_close;
    QPushButton* m_newsButton;

    QLineEdit* m_searchBar;

    QCustomPlot* m_stockPlot;
    //QPushButton* m_stockPlot;
    QListWidget* m_listWidget;
    QListWidget* m_searchListWidget;
    QDialog* m_searchDialog;

    QLabel* m_companyNameLabel;
    QLabel* m_tickerLabel;
    QLabel* m_priceLabel;
    QLabel* m_volumeLabel;
    QLabel* m_currentChangeLabel;
    QLabel* m_currentPercentageLabel;
    QLabel* m_weekHightLabel;
    QLabel* m_weekLowLabel;
    QLabel* m_vwap;
    QLabel* m_rsi;
    QLabel* m_volatility;

    std::vector<QPushButton*> m_stockButtonVector;
    std::vector<QLineEdit*> m_stockPriceVector;
    std::vector<QLineEdit*> m_stockPercentageVector;

    std::vector<AdvancedStock> m_watchList;
    std::vector<int> m_viewWatchList;
    int displayedIndex;
    StockPlotter* Plotter;
    QTimer *timer;
};
#endif // STOCKLMAINWINDOW_H
