# Qt-StockAdviser

This app allows one to:
* get price change graph and most useful fundamental ratios
* get correlation graph between two securities

## Tech performance
My main focus was not on functionality, but on making the app multithreaded and optimized.
Each client request is readed in a seperate thread, each request is processed in a different thread.

How everything works:
1) Server gets the request and opens one of .py scripts
2) .py scipt finds needed data via yFinance API and builds graph with matplotlib
3) .py creates .png and .txt files with a specific cryptographic hash
4) server sends files to the client and then deletes them from the hard drive
