import yfinance as yf
import sys
import warnings
import matplotlib.pyplot as plt
warnings.simplefilter(action='ignore', category=FutureWarning)

def save_txt(tick, txt_n):
    ans = ""
    msft = yf.Ticker(tick)
    try:
        working_capital_ratio = msft.balance_sheet.loc['Current Assets'][0] / \
                                msft.balance_sheet.loc['Current Liabilities'][0]
    except:
        ...
    else:
        working_capital_ratio = round(working_capital_ratio, 2)
        ans += "wcr:" + str(working_capital_ratio) + " "

    try:
        debt_ratio = msft.balance_sheet.loc['Total Debt'][0] / msft.balance_sheet.loc['Total Assets'][0]
    except:
        ...
    else:
        debt_ratio = round(debt_ratio, 2)
        ans += "dr:" + str(debt_ratio) + " "

    try:
        quick_ratio = (msft.balance_sheet.loc['Cash And Cash Equivalents'][0] +
                       msft.balance_sheet.loc['Accounts Receivable'][0]) / \
                      msft.balance_sheet.loc['Current Liabilities'][0]
    except:
        ...
    else:
        quick_ratio = round(quick_ratio, 2)
        ans += "qr:" + str(quick_ratio) + " "

    try:
        acid_test = (msft.balance_sheet.loc['Current Assets'][0] - msft.balance_sheet.loc['Inventory'][0]) / \
                    msft.balance_sheet.loc['Current Liabilities'][0]
    except:
        ...
    else:
        acid_test = round(acid_test, 2)
        ans += "at:" + str(debt_ratio)

    path = sys.argv[0].replace("\\", "/")
    index = path.rfind("/")
    new_path = path[:index] + "/" + txt_n + ".txt"

    with open(new_path, "w") as txt_file:
        txt_file.write(ans)


def save_png(tick, png_n):
    stock_data = yf.download(tick, period="1y")
    stock_prices = stock_data["Close"]
    plt.plot(stock_prices)
    plt.title("Сhange in {} stock price over the year".format(ticker))
    plt.xlabel("Date")
    plt.ylabel("Price in $USD")

    path = sys.argv[0].replace("\\", "/")
    index = path.rfind("/")
    new_path = path[:index] + "/" + png_n + ".png"

    plt.savefig(new_path, dpi=300, bbox_inches="tight")


ticker = sys.argv[1]
file_name = sys.argv[2]

save_txt(ticker, file_name)
save_png(ticker, file_name)