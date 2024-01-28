import yfinance as yf
import sys
import warnings
import matplotlib.pyplot as plt
warnings.simplefilter(action='ignore', category=FutureWarning)


def calculate_correlation():
    ticker1 = sys.argv[1]
    ticker2 = sys.argv[2]

    data = yf.download([ticker1, ticker2], period="1y")["Close"]
    correlation = data[ticker1].corr(data[ticker2])

    print(correlation)

    plt.figure(figsize=(8, 6))
    plt.plot(data.index, data[ticker1], label=ticker1)
    plt.plot(data.index, data[ticker2], label=ticker2)
    plt.title("Stock price")
    plt.xlabel("Date")
    plt.ylabel("Price")
    plt.grid(True)
    plt.legend()

    path = sys.argv[0].replace("\\", "/")
    index = path.rfind("/")
    new_path = path[:index] + "/" + sys.argv[3] + ".png"
    plt.savefig(new_path, dpi=300, bbox_inches="tight")

    new_path_txt = path[:index] + "/" + sys.argv[3] + ".txt"
    with open(new_path_txt, "w") as txt_file:
        txt_file.write(str(round(correlation, 3)))

calculate_correlation()