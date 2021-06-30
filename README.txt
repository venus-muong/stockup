This release of StockUp is the first version for the project.
It covers issues (SU-001 Data Retrieval, SU-002 Simple Display,
SU-003 Basic Analytics and SU-004 Simple User Interface). 

Dependencies for this program include jsoncpp and curl as well as
QT core. We also use a third party library for plotting in QT called
QCustomPlot. Use of this library is covered under the GPL. Its Source
code is included with our files. 

IMPORTANT NOTE: This application accesses the IEX (Investors Exchange)
cloud end point. Wecurrently are using the IEX cloud sandbox for
development to avoid going over message limits. This means the 
results shown on this version may not be accurate to real current
data or estimates but proves that accesses the endpoint.   

To download dependencies on linux (debian) use the following commands:

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libjsoncpp-dev libcurl4-gnutls-dev
sudo apt-get install qt5-default

To run the program, in the folder use:
 
make
./StockUp

IMPORTANT NOTE: The current search function MUST BE AN EXACT TICKER
SYMBOL as we have not yet developed the search functionality (this
is part of SU-006 Advanced UI).ALSO, the maximum number of stocks
in the watch list is 5 at the moment. The capacity and ability to
remove will be added in the final version.  

Example stock ticker symbols: AC, XOM, MSFT, APPL, GD, GE, BRK.A

How application can be tested for acceptance in current state:
- Enter a ticker symbol (maybe use one from provided list). 
- click add stock
- click the button with company name that appears in watch list
- click the 1m,6m, 1y and 5y buttons to cycle through graphs
- add up to 5 stocks and cycle through them using the buttons. 

How it covers accpetance tests:
 
SU-001: Data retrieval
- The data is retrieved when a stock is added to the watchlist. 
- The summary of stock data is shown proving it pulls info from IEX. 

SU-002: 
- The data is displaying using QT as shown with the the layout of
the stock summary. 
- We are able to display 1 month, 6month, 1 year and 5 year plots
of price against date

SU-003:
- The displays show multiple stocks of data
- summary table shows the summary of current stock analytics and data

SU-004: 
- The search bar and buttons are proof of interface
- error will be thrown if incorrect ticker symbol provided