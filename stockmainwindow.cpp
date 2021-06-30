#include "stockmainwindow.h"
//#include "ui_stockmainwindow.h"


const int DEFAULT_STOCK_AMOUNT = 5;
const int DEFAULT_GRAPH_BUTTONS = 4;
const int DEFAULT_UPDATE_TIMER_MIN = 5;

StockMainWindow::StockMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);

    // Main layout box, splits up the graph and the summary
    QVBoxLayout* mainVLayout = new QVBoxLayout();

    mainWidget = new QWidget();
    mainWidget->setLayout(mainVLayout);
    setCentralWidget(mainWidget);

    // Horizontal layout that splits up the graph section from the stock info
    QHBoxLayout* graphAndSearchHLayout = new QHBoxLayout();
    //graphAndSearchHLayout->addStretch(0);
    //graphAndSearchHLayout->SetDefaultConstraint()


    // Vertical layout that splits up the buttons from the graph
    QVBoxLayout* buttonsAndGraphVLayout = new QVBoxLayout();


    // Horizontal layout for the buttons for the graph
    QHBoxLayout* graphButtonHLayout = new QHBoxLayout();
    m_oneMonthButton = new QPushButton("1 Month");
    m_sixMonthsButton = new QPushButton("6 Months");
    m_oneYearButton = new QPushButton("1 Year");
    m_fiveYearsButton = new QPushButton("5 Years");

    graphButtonHLayout->addWidget(m_oneMonthButton);
    graphButtonHLayout->addWidget(m_sixMonthsButton);
    graphButtonHLayout->addWidget(m_oneYearButton);
    graphButtonHLayout->addWidget(m_fiveYearsButton);


    // Graph
    m_stockPlot = new QCustomPlot(this);

    //m_stockPlot->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    Plotter = new StockPlotter(m_stockPlot);

    //m_stockPlot = new QPushButton("GRAPH");

    // Adding buttons and graph to left panel
    buttonsAndGraphVLayout->addLayout(graphButtonHLayout);
    buttonsAndGraphVLayout->addWidget(m_stockPlot);

    // Vertical layout that splits up search bar from stocks
    QVBoxLayout* searchBarAndStocksVLayout = new QVBoxLayout();

    // Horizontal Layout for search bar
    QHBoxLayout* searchBarHLayout = new QHBoxLayout();

    // m_addButton = new QPushButton("Add Stock");
    m_searchButton = new QPushButton("Go");
    m_searchBar = new QLineEdit();

    // searchBarHLayout->addWidget(m_addButton);
    searchBarHLayout->addWidget(m_searchBar);
    searchBarHLayout->addWidget(m_searchButton);

    m_watchListButton = new QPushButton("Select Watchlist Stocks");

    // Label for watchlist
    QLabel* watchlistLabel = new QLabel("Watchlist");

    // Vertical Layout for watchlist
    QVBoxLayout* watchlistVLayout = new QVBoxLayout();
    watchlistVLayout->addWidget(m_watchListButton);
    watchlistVLayout->addWidget(watchlistLabel);
    watchlistVLayout->setAlignment(watchlistLabel, Qt::AlignHCenter);

    // Vertical for all the different stocks
    m_stockButtonVector.push_back(new QPushButton("Stock 1"));
    m_stockButtonVector.push_back(new QPushButton("Stock 2"));
    m_stockButtonVector.push_back(new QPushButton("Stock 3"));
    m_stockButtonVector.push_back(new QPushButton("Stock 4"));
    m_stockButtonVector.push_back(new QPushButton("Stock 5"));

    for (unsigned int i = 0; i < DEFAULT_STOCK_AMOUNT; i++)
    {
        m_stockButtonVector.push_back(new QPushButton());
        m_stockButtonVector[i]->setVisible(false);

        m_stockPriceVector.push_back(new QLineEdit("Price = $0"));
        m_stockPriceVector[i]->setVisible(false);
        m_stockPercentageVector.push_back(new QLineEdit("Percentage = 0%"));
        m_stockPercentageVector[i]->setVisible(false);

        QVBoxLayout* stockInfoVLayout = new QVBoxLayout(); // layout for stock info
        stockInfoVLayout->setSpacing(0);

        stockInfoVLayout->addWidget(m_stockPriceVector[i]);		// adding widgets to stock info
        stockInfoVLayout->addWidget(m_stockPercentageVector[i]);

        QHBoxLayout* stockNameHBox = new QHBoxLayout();			// layout for button and stock info

        stockNameHBox->addWidget(m_stockButtonVector[i]);		// adding widget and layout to stock name
        stockNameHBox->addLayout(stockInfoVLayout);

        watchlistVLayout->addLayout(stockNameHBox);				// adding stock to watchlist layout
    }

    // Adding search bar and watchlist to layout
    searchBarAndStocksVLayout->addLayout(searchBarHLayout);
    searchBarAndStocksVLayout->addLayout(watchlistVLayout);

    // adding graph and watchlist to layout
    graphAndSearchHLayout->addLayout(buttonsAndGraphVLayout);
    graphAndSearchHLayout->addLayout(searchBarAndStocksVLayout);

    // Summary
    QVBoxLayout* stockSummaryVLayout = new QVBoxLayout();

    QLabel* stockSummary = new QLabel("Stock Summary");

    // First Line
    QHBoxLayout* summaryLineOneHLayout = new QHBoxLayout();
    QLabel* companyName = new QLabel("Company Name:");
    m_companyNameLabel = new QLabel("Company Name Here");
    QLabel* ticker = new QLabel("Ticker:");
    m_tickerLabel = new QLabel("Ticker Here");

    summaryLineOneHLayout->addWidget(companyName);
    summaryLineOneHLayout->addWidget(m_companyNameLabel);
    summaryLineOneHLayout->addWidget(ticker);
    summaryLineOneHLayout->addWidget(m_tickerLabel);


    // Second Line
    QHBoxLayout* summaryLineTwoHLayout = new QHBoxLayout();
    QLabel* price = new QLabel("Price:");
    m_priceLabel = new QLabel("Price Here");
    QLabel* volume = new QLabel("Volume:");
    m_volumeLabel = new QLabel("Volume Here");

    summaryLineTwoHLayout->addWidget(price);
    summaryLineTwoHLayout->addWidget(m_priceLabel);
    summaryLineTwoHLayout->addWidget(volume);
    summaryLineTwoHLayout->addWidget(m_volumeLabel);


    // Third Line
    QHBoxLayout* summaryLineThreeHLayout = new QHBoxLayout();
    QLabel* currentChange = new QLabel("Current Change:");
    m_currentChangeLabel = new QLabel("Current Change Here");
    QLabel* currentPercentage = new QLabel("Current Percentage:");
    m_currentPercentageLabel = new QLabel("Current Percentage Here");

    summaryLineThreeHLayout->addWidget(currentChange);
    summaryLineThreeHLayout->addWidget(m_currentChangeLabel);
    summaryLineThreeHLayout->addWidget(currentPercentage);
    summaryLineThreeHLayout->addWidget(m_currentPercentageLabel);


    // Fourth Line
    QHBoxLayout* summaryLineFourHLayout = new QHBoxLayout();
    QLabel* weekHigh = new QLabel("S2 Week High:");
    m_weekHightLabel = new QLabel("S2 High Here");
    QLabel* weekLow = new QLabel("S2 Week Low:");
    m_weekLowLabel = new QLabel("S2 Low Here");

    summaryLineFourHLayout->addWidget(weekHigh);
    summaryLineFourHLayout->addWidget(m_weekHightLabel);
    summaryLineFourHLayout->addWidget(weekLow);
    summaryLineFourHLayout->addWidget(m_weekLowLabel);

    // Fifth Line
    QHBoxLayout* summaryLineFiveHLayout = new QHBoxLayout();
    QLabel* vwap = new QLabel("VWAP:");
    m_vwap = new QLabel("VWAP Here");
    QLabel* rsi = new QLabel("RSI:");
    m_rsi = new QLabel("RSI Here");

    summaryLineFiveHLayout->addWidget(vwap);
    summaryLineFiveHLayout->addWidget(m_vwap);
    summaryLineFiveHLayout->addWidget(rsi);
    summaryLineFiveHLayout->addWidget(m_rsi);

    // Sixth Line
    QHBoxLayout* summaryLineSixHLayout = new QHBoxLayout();
    QLabel* volatility = new QLabel("VWAP:");
    m_volatility = new QLabel("VWAP Here");
    QLabel* empty = new QLabel("");
    m_newsButton = new QPushButton("Stock News");

    summaryLineSixHLayout->addWidget(volatility);
    summaryLineSixHLayout->addWidget(m_volatility);
    summaryLineSixHLayout->addWidget(empty);
    summaryLineSixHLayout->addWidget(m_newsButton);

    // Adding lines to layout
    stockSummaryVLayout->addWidget(stockSummary);
    stockSummaryVLayout->setAlignment(stockSummary, Qt::AlignHCenter);
    stockSummaryVLayout->addLayout(summaryLineOneHLayout);
    stockSummaryVLayout->addLayout(summaryLineTwoHLayout);
    stockSummaryVLayout->addLayout(summaryLineThreeHLayout);
    stockSummaryVLayout->addLayout(summaryLineFourHLayout);
    stockSummaryVLayout->addLayout(summaryLineFiveHLayout);
    stockSummaryVLayout->addLayout(summaryLineSixHLayout);


    // Adding both big layouts to main layout
    mainVLayout->addLayout(graphAndSearchHLayout);
    mainVLayout->addLayout(stockSummaryVLayout);

    /*for (int i = 0; i<DEFAULT_STOCK_AMOUNT; i++){

       m_watchList.push_back(Stock());
    }*/

    // Setting up Signals
    QObject::connect(m_oneMonthButton, SIGNAL(clicked()), this, SLOT(onOneMonthClicked()));
    QObject::connect(m_sixMonthsButton, SIGNAL(clicked()), this, SLOT(onSixMonthsClicked()));
    QObject::connect(m_oneYearButton, SIGNAL(clicked()), this, SLOT(onOneYearClicked()));
    QObject::connect(m_fiveYearsButton, SIGNAL(clicked()), this, SLOT(onFiveYearsClicked()));

    QObject::connect(m_watchListButton, SIGNAL(clicked()), this, SLOT(onWatchListClicked()));
    QObject::connect(m_searchButton, SIGNAL(clicked()), this, SLOT(onSearchClicked()));
    QObject::connect(m_newsButton, SIGNAL(clicked()), this, SLOT(onNewsClicked()));

    QSignalMapper* signalMapper = new QSignalMapper(this);
    for(unsigned int i = 0; i < DEFAULT_STOCK_AMOUNT; i++)
    {
        QObject::connect(m_stockButtonVector[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(m_stockButtonVector[i],i);
    }
    QObject::connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(onStockClicked(int)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateStocks()));
    timer->start(std::chrono::minutes(DEFAULT_UPDATE_TIMER_MIN));

    m_listWidget = new QListWidget();

    init();

}


StockMainWindow::~StockMainWindow()
{
    watchlist TickerList;
    TickerList.writeOutWatchlist(m_watchList);
}


// SLOTS


void StockMainWindow::init()
{
    watchlist TickerList;
    std::vector<std::string> tickers = TickerList.GetTickers();

    for (unsigned int i = 0; i < tickers.size(); i++){
        m_watchList.push_back(AdvancedStock(tickers[i]));
        AdvancedStock newStock(tickers[i]);
        QListWidgetItem* widgetItem = new QListWidgetItem(QString::fromStdString(newStock.getName()), m_listWidget);
        widgetItem->setFlags(widgetItem->flags() | Qt::ItemIsUserCheckable);
        widgetItem->setCheckState(Qt::Unchecked);
    }


}

void StockMainWindow::onOneMonthClicked()
{
    // enabling and disabling buttons, need to change to function
    changeEnabledGraphButtons({0,1,1,1});
    std::string TimePeriod = "1m";
    showData(TimePeriod);
}

void StockMainWindow::onSixMonthsClicked()
{
    changeEnabledGraphButtons({1,0,1,1});
    std::string TimePeriod = "6m";
    showData(TimePeriod);
}

void StockMainWindow::onOneYearClicked()
{
    changeEnabledGraphButtons({1,1,0,1});
    std::string TimePeriod = "1y";
    showData(TimePeriod);
}

void StockMainWindow::onFiveYearsClicked()
{
    changeEnabledGraphButtons({1,1,1,0});
    std::string TimePeriod = "5y";
    showData(TimePeriod);
}

void StockMainWindow::onAddClicked()
{
    // add stock to list
    std::string tickerSymbol = "";

    for (int i = 0; i < m_searchListWidget->count(); i++)
    {
        Qt::CheckState state = m_searchListWidget->item(i)->checkState();
        if (state == Qt::Checked)
        {
            tickerSymbol = m_searchListWidget->item(i)->text().toStdString();
            m_searchDialog->accept();
            break;
        }
    }


    try
    {
        AdvancedStock newStock(tickerSymbol);

        m_watchList.push_back(newStock);

        QListWidgetItem* widgetItem = new QListWidgetItem(QString::fromStdString(newStock.getName()), m_listWidget);
        widgetItem->setFlags(widgetItem->flags() | Qt::ItemIsUserCheckable);
        widgetItem->setCheckState(Qt::Unchecked);
        
    }
    catch(string e) 
    {
        //const char * c = e.c_str();
        QMessageBox msgWarning;
            msgWarning.setText("WARNING!\nTicker Symbol not found. Try again");
            msgWarning.setIcon(QMessageBox::Warning);
            msgWarning.setWindowTitle("Caution");
            msgWarning.exec();
    }

}

void StockMainWindow::onSearchClicked()
{
    m_searchDialog = new QDialog(this);

    QVBoxLayout* verticalLayout = new QVBoxLayout();

    m_searchListWidget = new QListWidget;

    verticalLayout->addWidget(m_searchListWidget);

    QHBoxLayout* horizontalLayout = new QHBoxLayout();

    m_addButton = new QPushButton("Add Stock");
    // m_close = new QPushButton("Close");

    horizontalLayout->addWidget(m_addButton);
    // horizontalLayout->addWidget(m_close);

    verticalLayout->addLayout(horizontalLayout);

    m_searchDialog->setLayout(verticalLayout);

    QObject::connect(m_addButton, SIGNAL(clicked()), this, SLOT(onAddClicked()));
    // QObject::connect(m_close, SIGNAL(clicked()), dialog, SLOT(accept()));


    Search searchVar;
    std::vector<SearchResult> results = searchVar.search(m_searchBar->text().toStdString());

    for (unsigned int i = 0; i < results.size(); i++)
    {
        QListWidgetItem* widgetItem = new QListWidgetItem(QString::fromStdString(results[i].ticker), m_searchListWidget);
        widgetItem->setFlags(widgetItem->flags() | Qt::ItemIsUserCheckable);
        widgetItem->setCheckState(Qt::Unchecked);
    }

    m_searchDialog->exec();
}

void StockMainWindow::onStockClicked(int index)
{
    // Change displayed stock

    // Disable / Enable stocks
    changeEnabledStockButtons(index);

    // Graph function needed here
    try {
        displayedIndex = index;
        onFiveYearsClicked();

    // update summary

        m_companyNameLabel->setText(QString::fromStdString(m_watchList[index].getName()));
        m_priceLabel->setText(QString("$ " + QString::number(m_watchList[index].getCurrPrice())));
        m_currentChangeLabel->setText(QString::number(m_watchList[index].getCurrChange()));
        m_weekHightLabel->setText(QString::number(m_watchList[index].getHigh52()));
        m_tickerLabel->setText(QString::fromStdString(m_watchList[index].getTicker()));
        m_volumeLabel->setText(QString::number(m_watchList[index].getCurrVolume()));
        m_currentPercentageLabel->setText(QString(QString::number(m_watchList[index].getCurrPercentChange()) + " %"));
        m_weekLowLabel->setText(QString::number(m_watchList[index].getLow52()));
        // UNCOMMENT FOLLOWING LINES WHEN ADVANCED STOCK IS ADDED
        m_vwap->setText(QString::number(m_watchList[index].getVWAP()));
        m_rsi->setText(QString::number(m_watchList[index].getRSI()));
        m_volatility->setText(QString::number(m_watchList[index].getVolatility()));
    } catch (std::string e) {
        const char * c = e.c_str();
        QMessageBox msgWarning;
        msgWarning.setText(c);
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    }

}

void StockMainWindow::UpdateStocks(){
    for (unsigned int i =0; i<DEFAULT_STOCK_AMOUNT; i++){
        std::string tickerSym = m_watchList[i].getTicker();
        if(!tickerSym.empty()){
            m_watchList[i].updateHistory();
            bool QuoteUpdateCheck = m_watchList[i].getQuote();
            if ( QuoteUpdateCheck){
                m_stockPriceVector[i]->setText(QString("$ " + QString::number(m_watchList[i].getCurrPrice())));
                m_stockPercentageVector[i]->setText(QString(QString::number(m_watchList[i].getCurrPercentChange()) + " %"));
                if(m_stockButtonVector[i]->isEnabled()){
                    onStockClicked(i);
                }
                 //update the stock data
            }
        }
    }
    timer->start(std::chrono::minutes(DEFAULT_UPDATE_TIMER_MIN));
}


void StockMainWindow::onWatchListClicked()
{
    QDialog* dialog = new QDialog(this);

    QVBoxLayout* verticalLayout = new QVBoxLayout();

    verticalLayout->addWidget(m_listWidget);

    QHBoxLayout* horizontalLayout = new QHBoxLayout();

    m_saveList = new QPushButton("Save Selection");
    m_close = new QPushButton("Close");

    horizontalLayout->addWidget(m_saveList);
    horizontalLayout->addWidget(m_close);

    verticalLayout->addLayout(horizontalLayout);

    dialog->setLayout(verticalLayout);

    QObject::connect(m_saveList, SIGNAL(clicked()), this, SLOT(onSaveListClicked()));
    QObject::connect(m_close, SIGNAL(clicked()), dialog, SLOT(accept()));

    dialog->exec();

}

void StockMainWindow::onSaveListClicked()
{
    int count = 0;
    m_viewWatchList.clear();

    for (int i = 0; i < m_listWidget->count(); i++)
    {
        Qt::CheckState state = m_listWidget->item(i)->checkState();
        if (state == Qt::Checked && count < 6)
        {
            count++;
            m_viewWatchList.push_back(i);
        }
    }

    for (int i = 0; i < DEFAULT_STOCK_AMOUNT; i++)
    {
        m_stockButtonVector[i]->setVisible(false);
        m_stockPriceVector[i]->setVisible(false);
        m_stockPercentageVector[i]->setVisible(false);
    }

    for (unsigned int i = 0; i < m_viewWatchList.size(); i++)
    {
        m_stockButtonVector[i]->setText(QString::fromStdString(m_watchList[m_viewWatchList[i]].getName()));
        m_stockButtonVector[i]->setChecked(false);
        m_stockPriceVector[i]->setText(QString::number(m_watchList[m_viewWatchList[i]].getCurrPrice()));
        m_stockPercentageVector[i]->setText(QString::number(m_watchList[m_viewWatchList[i]].getCurrPercentChange()));

        m_stockButtonVector[i]->setVisible(true);
        m_stockPriceVector[i]->setVisible(true);
        m_stockPercentageVector[i]->setVisible(true);
    }

}

// UNCOMMENT ONCE STOCK NEWS HAS BEEN ADDED
void StockMainWindow::onNewsClicked()
{
    /*
    for(int i = 0; i < DEFAULT_STOCK_AMOUNT; i++)
    {
        if(m_stockButtonVector[i]->isChecked())
        {
            StockNews stockNews(m_watchList[m_viewWatchList[i]].getTicker());
            if(stockNews.getNews())
            {
                std::string headline = stockNews.getHeadline();
                std::string summary = stockNews.getSummary();
                std::string source = stockNews.getSource();

                QDialog* dialog = new QDialog(this);

                QVBoxLayout* verticalLayout = new QVBoxLayout();

                QLabel* headlineLabel = new QLabel(QString::fromStdString(headline));
                QLabel* summaryLabel = new QLabel(QString("Summary: " + QString::fromStdString(summary)));
                QLabel* sourceLabel = new QLabel(QString("Source: " + QString::fromStdString(source)));
                QPushButton* closeButton = new QPushButton("Close");

                verticalLayout->addWidget(headlineLabel);
                verticalLayout->addWidget(headlineLabel);
                verticalLayout->addWidget(headlineLabel);
                verticalLayout->addWidget(closeButton);

                dialog->setLayout(verticalLayout);

                QObject::connect(closeButton, SIGNAL(clicked()), dialog, SLOT(accept()));

                dialog->exec();




            }
        }
    }
    */
}

// ////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS

void StockMainWindow::changeEnabledGraphButtons(std::vector<int> enabledVector)
{
    m_oneMonthButton->setEnabled(enabledVector[0]);
    m_sixMonthsButton->setEnabled(enabledVector[1]);
    m_oneYearButton->setEnabled(enabledVector[2]);
    m_fiveYearsButton->setEnabled(enabledVector[3]);
}

void StockMainWindow::changeEnabledStockButtons(int index)
{
    for(unsigned int i = 0; i < DEFAULT_STOCK_AMOUNT; i++)
    {
        if(i == index)
        {
            m_stockButtonVector[i]->setEnabled(false);
        }
        else
        {
            m_stockButtonVector[i]->setEnabled(true);
        }
    }
}

void StockMainWindow::getStockSummary()
{
    // Sets all summary info
}

int StockMainWindow::getIndexOfAvailableStockSpot()
{
    for(unsigned int i = 0; i < DEFAULT_STOCK_AMOUNT; i++)
    {
        if(!m_stockButtonVector[i]->isVisible())
        {
            m_stockButtonVector[i]->setVisible(true);
            m_stockPriceVector[i]->setVisible(true);
            m_stockPercentageVector[i]->setVisible(true);
            return i;
        }
    }
    return -1;
}


void StockMainWindow::showData(std::string TimePeriod)
{
    try {
        AdvancedStock GraphingStock(m_watchList[displayedIndex].getTicker());
        Plotter->PlotPriceDate(GraphingStock,TimePeriod);
    } catch (std::string e) {
        const char * c = e.c_str();
        QMessageBox msgWarning;
        msgWarning.setText(c);
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    }

}

