# Qt-StockAdviser

This app allows one to:
* get price change graph and most useful fundamental ratios on a chosen stock
* get correlation graph between two chosen securities

## Tech performance
My main focus was not on functionality, but on making the app multithreaded and optimized.
Each client request is readed in a seperate thread, each request is processed in a seperate thread.

How everything works:
1) Server gets the request and opens one of .py scripts
2) .py scipt finds needed data via yFinance API and builds graph with matplotlib
3) .py creates .png and .txt files with a specific cryptographic hash
4) server sends files to the client and then deletes them from the program folder

## Starting the app
Choose one of two options

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/b718c0f2-0be7-4280-904c-12f3ce6bdaa8)

If "Get stock data" button is pressed you will see the following 

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/47f25d99-b9d1-461f-8abe-6953cc5aa66b)

Enter the ticker you are interested in and get some useful data

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/6053a446-326d-47fc-b80c-58619fc53104)

Or if "Measure correlations is pressed"

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/585a1221-b952-4920-9aa4-1c45c1f029c7)

Enter two tickers and get some info

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/eb147c87-d62f-42ed-afaa-3543d9523873)


## How to install my app
1) Make sure you have Qt Creator and Git CMD installed
2) Create a "git" folder on your Dekstop

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/87a3f3a7-1cfc-4928-8dee-1938dad171d9)

3) Open Git CMD and type "git clone https://github.com/KozlovVP/Qt-StockAdviser.git"

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/5779ae5e-09a5-4528-a563-d57f0055265b)

4) Copy PATH to the "git" folder on your Dekstop and type "cd <PATH>"

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/a755c90b-c6a3-4f1a-bbfe-a447d1aa7696)

5) Type "git clone https://github.com/KozlovVP/Qt-StockAdviser.git" one more time

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/fc6700a4-0597-4dc5-b1fd-b7b8409c1289)

6) Congrats! Now you have all src files in your "git" folder
7) Open Qt Creator and press "Open project"->C:\Users\..\Desktop\git\Qt-StockAdviser\Server\Server.pro You will see server's src code

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/1c06e383-0ee3-4094-8e61-67f8f526e1c5)

8) Open Qt Creator and press "Open project"->C:\Users..\Desktop\git\Qt-StockAdviser\Client\Client.pro You will see client's src code

![image](https://github.com/KozlovVP/Qt-StockAdviser/assets/114473389/794364a2-1a19-4a4f-9cf1-b892253f9b7f)

Thanks for installation!
