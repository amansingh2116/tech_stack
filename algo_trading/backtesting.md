# Backtesting

## Backtesting example

```python
## Importing data

import pandas as pd
import yfinance as yf
import numpy as np
import matplotlib.pyplot as plt
from tabulate import tabulate
import warnings
warnings. simplefilter(action='ignore', category=Warning)

data = yf.download(tickers='RELIANCE.NS') # download complete historical OHLCV data of RELIANCE.NS
data = yf.download(tickers='AAPL', start='2023-01-01', end='2023-02-01') # download historical OHLCV data from of Apple from 2023-01-01 to 2023-02-01

data.to_csv('data.csv') # save data to a CSV file

equity_details = pd.read_csv('EQUITY_L.csv') # All Details for NSE stocks : Symbol is the required field, which we downloaded from nse india website
for name in equity_details.SYMBOL:
    try:
        data = yf.download(f'{name}.NS')
        data.to_csv(f'./Data/{name}.csv') # Data will be stored in data folder
    except Exception as e:
        print(f'{name} ===> {e}')


## Signal generation

data = pd.read_csv('../Data/RELIANCE.csv', parse_dates=['Date'], index_col='Date')
data[-400:].Close.plot(figsize =(15,8)) # last 400 days of RELIANCE.NS closing data

# Golden Crossover
'''
When 20 SMA crosses above 50 SMA, we get a buy signal. This is because a shorter term moving average crossing above a longer term moving average is a sign of increasing momentum and a potential trend reversal. Conversely, when 50 SMA crosses above 20 SMA, we get a sell signal. This makes sense because a longer term moving average crossing above a shorter term moving average is a sign of decreasing momentum and a potential trend reversal.
'''

data['20_SMA'] = data.Close.rolling(window=20, min_periods=1).mean() # this line of code uses the `rolling` function to calculate the 20 day moving average. The `window` parameter is set to 20, which means it will take the last 20 data points and calculate the mean of them. The `min_periods` parameter is set to 1, which means it will start calculating the mean as soon as there is one data point. The result is a new column '20_SMA' in the dataframe which contains the 20 day moving average of the closing price.
data['50_SMA'] = data.Close.rolling(window=50, min_periods=1).mean() # 50 day moving average
data['Signal'] = 0
data['Signal'] = np.where(data['20_SMA'] > data['50_SMA'], 1, 0) # if 20_SMA > 50_SMA, then Signal = 1, else Signal = 0
data['Position'] = data.Signal.diff() # if Signal changes from 0 to 1, then Position = 1, else Position = 0
data['Position']


plt.figure(figsize = (20,10))
# plot close price, short-term and long-term moving averages 
data.iloc[-300:]['Close'].plot(color = 'k', label= 'Close Price') 
data.iloc[-300:]['20_SMA'].plot(color = 'b',label = '20-day SMA') 
data.iloc[-300:]['50_SMA'].plot(color = 'g', label = '50-day SMA')
# plot ‘buy’ signals
plt.plot(data.iloc[-300:][data.iloc[-300:]['Position'] == 1].index, 
         data.iloc[-300:]['20_SMA'][data.iloc[-300:]['Position'] == 1], 
         '^', markersize = 15, color = 'g', label = 'buy')
# plot ‘sell’ signals
plt.plot(data.iloc[-300:][data.iloc[-300:]['Position'] == -1].index, 
         data.iloc[-300:]['20_SMA'][data.iloc[-300:]['Position'] == -1], 
         'v', markersize = 15, color = 'r', label = 'sell')
plt.ylabel('Price in Rupees', fontsize = 15 )
plt.xlabel('Date', fontsize = 15 )
plt.title('RELIANCE', fontsize = 20)
plt.legend()
plt.grid()
plt.show() # show the plot with buy and sell signals

# print the last 200 observations of the dataframe where there is a buy or sell signal.
# The 'Position' column is transformed to be either 'Buy' or 'Sell' instead of 1 or -1.
# The 'Close' and 'Position' columns are then selected and printed in a table format.
df_pos = data.iloc[-200:][(data.iloc[-200:]['Position'] == 1) | (data['Position'] == -1)].copy()
df_pos['Position'] = df_pos['Position'].apply(lambda x: 'Buy' if x == 1 else 'Sell')
print(tabulate(df_pos[['Close', 'Position']], headers = 'keys', tablefmt = 'psql'))

# +---------------------+---------+------------+
# | Date                |   Close | Position   |
# |---------------------+---------+------------|
# | 2022-01-18 00:00:00 | 2521.8  | Buy        |
# | 2022-02-14 00:00:00 | 2338.55 | Sell       |
# | 2022-03-28 00:00:00 | 2621.95 | Buy        |
# | 2022-05-26 00:00:00 | 2587.1  | Sell       |
# | 2022-06-10 00:00:00 | 2714.25 | Buy        |
# | 2022-06-30 00:00:00 | 2595.65 | Sell       |
# | 2022-08-17 00:00:00 | 2665.15 | Buy        |
# +---------------------+---------+------------+

def GoldenCrossverSignal(name, data_point):
    '''
    This function takes a stock name and a number of data points to plot. It will read the data from a csv file, calculate the 20 and 50 day moving averages, and create a buy/sell signal based on the golden cross indicator. The function will then plot the close price, 20 and 50 day moving averages, and indicate where the buy and sell signals are.

    Parameters
    ----------
    name : str
        The name of the stock to plot.
    data_point : int
        The number of data points to plot.

    Returns
    -------
    None
    '''
    path = f'../Data/{name}.csv'
    data = pd.read_csv(path, parse_dates=['Date'], index_col='Date')
    data['20_SMA'] = data.Close.rolling(window=20, min_periods=1).mean()
    data['50_SMA'] = data.Close.rolling(window=50, min_periods=1).mean()
    data['Signal'] = 0
    data['Signal'] = np.where(data['20_SMA'] > data['50_SMA'], 1, 0)
    data['Position'] = data.Signal.diff()
    plt.figure(figsize = (20,10))
    # plot close price, short-term and long-term moving averages 
    data.iloc[-data_point:]['Close'].plot(color = 'k', label= 'Close Price') 
    data.iloc[-data_point:]['20_SMA'].plot(color = 'b',label = '20-day SMA') 
    data.iloc[-data_point:]['50_SMA'].plot(color = 'g', label = '50-day SMA')
    # plot ‘buy’ signals
    plt.plot(data.iloc[-data_point:][data.iloc[-data_point:]['Position'] == 1].index, 
             data.iloc[-data_point:]['20_SMA'][data.iloc[-data_point:]['Position'] == 1], 
             '^', markersize = 15, color = 'g', label = 'buy')
    # plot ‘sell’ signals
    plt.plot(data.iloc[-data_point:][data.iloc[-data_point:]['Position'] == -1].index, 
             data.iloc[-data_point:]['20_SMA'][data.iloc[-data_point:]['Position'] == -1], 
             'v', markersize = 15, color = 'r', label = 'sell')
    plt.ylabel('Price in Rupees', fontsize = 15 )
    plt.xlabel('Date', fontsize = 15 )
    plt.title(name, fontsize = 20)
    plt.legend()
    plt.grid()
    plt.show()
    df_pos = data.iloc[-data_point:][(data.iloc[-data_point:]['Position'] == 1) | (data['Position'] == -1)].copy()
    df_pos['Position'] = df_pos['Position'].apply(lambda x: 'Buy' if x == 1 else 'Sell')
    print(tabulate(df_pos[['Close', 'Position']], headers = 'keys', tablefmt = 'psql'))


GoldenCrossverSignal('TATAMOTORS', 300)


## Backtesting the strategy

'''
Changed the function to use Prev_Close instead of Close to remove forward bias. 
Now, 20_SMA and 50_SMA are calculated based on the previous day's close price 
instead of the current day's close price. This is because the signal is 
generated based on the comparison of the two moving averages and should be 
based on the data available at the time of decision making, not on future data.
'''
def GoldenCrossverSignal(name):
    path = f'../Data/{name}.csv'
    data = pd.read_csv(path, parse_dates=['Date'], index_col='Date')
    data['Prev_Close'] = data.Close.shift(1)
    data['20_SMA'] = data.Prev_Close.rolling(window=20, min_periods=1).mean()
    data['50_SMA'] = data.Prev_Close.rolling(window=50, min_periods=1).mean()
    data['Signal'] = 0
    data['Signal'] = np.where(data['20_SMA'] > data['50_SMA'], 1, 0)
    data['Position'] = data.Signal.diff()
    df_pos = data[(data['Position'] == 1) | (data['Position'] == -1)].copy()
    df_pos['Position'] = df_pos['Position'].apply(lambda x: 'Buy' if x == 1 else 'Sell')
    return df_pos

data = GoldenCrossverSignal('RELIANCE')

'''
Remove unwanted signals: We want to start with a buy and end with a sell
because we know each buy will follow a sell due to how we designed our algorithm.
This is done to make sure there are no incomplete trades, i.e. a buy without
a corresponding sell or vice versa. We do this by taking the first buy signal
and the last sell signal as the start and end of our trading period, respectively.
'''
required_df = data[(data.index >= data[data['Position'] == 'Buy'].index[0]) & (data.index <= data[data['Position'] == 'Sell'].index[-1])]

# Backtesting class

class Backtest:
    """
    This class is used to backtest the strategy.
    
    Attributes:
        columns (list): list of column names for the backtesting dataframe.
        backtesting (pd.DataFrame): dataframe to store the backtesting results.
    """
    def __init__(self):
        """
        Initialize the Backtest class.
        """
        # Name, Entry TIme, Entry PRice, QTY, Exit Time, Exit Price
        self.columns = ['Equity Name', 'Trade', 'Entry Time', 'Entry Price', 'Exit Time', 'Exit Price', 'Quantity', 'Position Size', 'PNL', '% PNL']
        self.backtesting = pd.DataFrame(columns=self.columns)

    def buy(self, equity_name, entry_time, entry_price, qty):
        """
        Method to log a buy trade.
        
        Parameters:
            equity_name (str): name of the equity.
            entry_time (datetime64[ns]): entry time of the trade.
            entry_price (float): entry price of the trade.
            qty (int): quantity of the trade.
        """
        self.trade_log = dict(zip(self.columns, [None] * len(self.columns)))
        self.trade_log['Trade'] = 'Long Open'
        self.trade_log['Quantity'] = qty
        self.trade_log['Position Size'] = round(self.trade_log['Quantity'] * entry_price, 3)
        self.trade_log['Equity Name'] = equity_name
        self.trade_log['Entry Time'] = entry_time
        self.trade_log['Entry Price'] = round(entry_price, 2)

    def sell(self, exit_time, exit_price, exit_type, charge):
        """
        Method to log a sell trade.
        
        Parameters:
            exit_time (datetime64[ns]): exit time of the trade.
            exit_price (float): exit price of the trade.
            exit_type (str): type of exit (e.g. 'Exit Trigger', 'Stop Loss').
            charge (float): charge for the trade.
        """
        self.trade_log['Trade'] = 'Long Closed'
        self.trade_log['Exit Time'] = exit_time
        self.trade_log['Exit Price'] = round(exit_price, 2)
        self.trade_log['Exit Type'] = exit_type
        self.trade_log['PNL'] = round((self.trade_log['Exit Price'] - self.trade_log['Entry Price']) * self.trade_log['Quantity'] - charge, 3)
        self.trade_log['% PNL'] = round((self.trade_log['PNL'] / self.trade_log['Position Size']) * 100, 3)
        self.trade_log['Holding Period'] = exit_time - self.trade_log['Entry Time']
        self.backtesting = self.backtesting.append(self.trade_log, ignore_index=True)

    def stats(self):
        df = self.backtesting
        parameters = ['Total Trade Scripts', 'Total Trade', 'PNL',  'Winners', 'Losers', 'Win Ratio','Total Profit', 'Total Loss', 'Average Loss per Trade', 'Average Profit per Trade', 'Average PNL Per Trade', 'Risk Reward']
        total_traded_scripts = len(df['Equity Name'].unique())
        total_trade = len(df.index)
        pnl = df.PNL.sum()
        winners = len(df[df.PNL > 0])
        loosers = len(df[df.PNL <= 0])
        win_ratio = str(round((winners/total_trade) * 100, 2)) + '%'
        total_profit = round(df[df.PNL > 0].PNL.sum(), 2)
        total_loss  = round(df[df.PNL <= 0].PNL.sum(), 2)
        average_loss_per_trade = round(total_loss/loosers, 2)
        average_profit_per_trade = round(total_profit/winners, 2)
        average_pnl_per_trade = round(pnl/total_trade, 2)
        risk_reward = f'1:{-1 * round(average_profit_per_trade/average_loss_per_trade, 2)}'
        data_points = [total_traded_scripts,total_trade,pnl,winners, loosers, win_ratio, total_profit, total_loss, average_loss_per_trade, average_profit_per_trade, average_pnl_per_trade, risk_reward]
        data = list(zip(parameters,data_points ))
        print(tabulate(data, ['Parameters', 'Values'], tablefmt='psql'))
    
        # 1. Return Analysis
        initial_capital = 50000 * total_traded_scripts
        final_value = initial_capital + pnl
        total_return = (final_value - initial_capital) / initial_capital
        
        # Annualized return (CAGR)
        if not self.portfolio_dates:
            cagr = 0
        else:
            start_date = min(self.portfolio_dates)
            end_date = max(self.portfolio_dates)
            years = (end_date - start_date).days / 365.25
            cagr = (final_value / initial_capital) ** (1/years) - 1 if years > 0 else 0

        # 2. Risk Adjusted Return (Sharpe Ratio)
        returns = pd.Series(self.portfolio_values).pct_change().dropna()
        if len(returns) > 1:
            annualized_return = returns.mean() * 252
            annualized_vol = returns.std() * np.sqrt(252)
            sharpe = annualized_return / annualized_vol if annualized_vol > 0 else 0
        else:
            sharpe = 0

        # 3. Risk Analysis
        # Volatility
        volatility = returns.std() * np.sqrt(252) if len(returns) > 1 else 0
        
        # Value at Risk (95% confidence)
        var_95 = np.percentile(returns, 5) if len(returns) > 1 else 0
        
        # 4. Confidence Interval (daily returns)
        conf_interval = (returns.mean() - 1.96*returns.std(), 
                         returns.mean() + 1.96*returns.std()) if len(returns) > 1 else (0, 0)
        
        # 5. Maximum Drawdown
        portfolio_series = pd.Series(self.portfolio_values, index=self.portfolio_dates)
        rolling_max = portfolio_series.cummax()
        drawdown = (portfolio_series - rolling_max) / rolling_max
        max_drawdown = drawdown.min() if not drawdown.empty else 0
        
        # ===== RESULTS TABLE =====
        parameters = [
            'Total Trade Scripts', 'Total Trade', 'PNL', 'Winners', 'Losers', 'Win Ratio',
            'Total Profit', 'Total Loss', 'Avg Loss/Trade', 'Avg Profit/Trade', 'Avg PNL/Trade',
            'Risk Reward', 'Total Return', 'CAGR', 'Sharpe Ratio', 'Volatility (Annualized)',
            'VaR (95%)', 'Max Drawdown', 'CI Daily Return (95%)'
        ]
        
        data_points = [
            total_traded_scripts, total_trade, round(pnl, 2), winners, loosers, win_ratio,
            total_profit, total_loss, avg_loss, avg_profit, avg_pnl, risk_reward,
            f"{total_return:.2%}", f"{cagr:.2%}", f"{sharpe:.4f}", f"{volatility:.2%}",
            f"{var_95:.2%}", f"{max_drawdown:.2%}", 
            f"({conf_interval[0]:.4f}, {conf_interval[1]:.4f})"
        ]
        
        print(tabulate(zip(parameters, data_points), 
                      headers=['Parameters', 'Values'], 
                      tablefmt='psql'))


bt = Backtest()
capital = 50000
for index, data in required_df.iterrows():
    if(data.Position == 'Buy'):
        qty = capital // data.Open
        bt.buy('RELIANCE', index, data.Open, qty)
    else:
        bt.sell(index, data.Open, 'Exit Trigger', 0)

df = bt.backtesting

    #    "   Equity Name        Trade Entry Time  Entry Price  Exit Time  Exit Price  \\\n",
    #    "0     RELIANCE  Long Closed 1996-02-16        17.64 1996-04-05       16.14   \n",
    #    "1     RELIANCE  Long Closed 1996-04-24        19.12 1996-06-18       18.64   \n",
    #    "2     RELIANCE  Long Closed 1996-08-13        16.05 1996-08-16       15.98   \n",
    #    "3     RELIANCE  Long Closed 1996-08-30        16.33 1996-09-17       14.93   \n",
    #    "4     RELIANCE  Long Closed 1996-11-12        14.19 1996-11-21       14.12   \n",
    #    "..         ...          ...        ...          ...        ...         ...   \n",
    #    "81    RELIANCE  Long Closed 2021-06-03      2221.00 2021-07-23     2134.45   \n",
    #    "82    RELIANCE  Long Closed 2021-08-27      2237.00 2021-11-24     2380.00   \n",
    #    "83    RELIANCE  Long Closed 2022-01-19      2530.00 2022-02-15     2351.20   \n",
    #    "84    RELIANCE  Long Closed 2022-03-29      2638.00 2022-05-27     2593.05   \n",
    #    "85    RELIANCE  Long Closed 2022-06-13      2650.00 2022-07-01     2574.90   \n",
    #    "\n",
    #    "    Quantity  Position Size      PNL  % PNL     Exit Type Holding Period  \n",
    #    "0     2834.0      49988.304 -4251.00 -8.504  Exit Trigger        49 days  \n",
    #    "1     2615.0      49989.425 -1255.20 -2.511  Exit Trigger        55 days  \n",
    #    "2     3114.0      49988.536  -217.98 -0.436  Exit Trigger         3 days  \n",
    #    "3     3061.0      49990.246 -4285.40 -8.572  Exit Trigger        18 days  \n",
    #    "4     3523.0      49999.314  -246.61 -0.493  Exit Trigger         9 days  \n",
    #    "..       ...            ...      ...    ...           ...            ...  \n",
    #    "81      22.0      48862.000 -1904.10 -3.897  Exit Trigger        50 days  \n",
    #    "82      22.0      49214.000  3146.00  6.392  Exit Trigger        89 days  \n",
    #    "83      19.0      48070.000 -3397.20 -7.067  Exit Trigger        27 days  \n",
    #    "84      18.0      47484.000  -809.10 -1.704  Exit Trigger        59 days  \n",
    #    "85      18.0      47700.000 -1351.80 -2.834  Exit Trigger        18 days  \n",
    #    "\n",
    #    "[86 rows x 12 columns]"

bt.backtesting.to_csv('RELIANCE_TEST.csv') # Save backtesting results to a CSV file

bt.stats()

# +--------------------------+-------------+
# | Parameters               | Values      |
# |--------------------------+-------------|
# | Total Trade Scripts      | 10          |
# | Total Trade              | 668         |
# | PNL                      | 2236764.27  |
# | Winners                  | 294         |
# | Losers                   | 374         |
# | Win Ratio                | 44.01%      |
# | Total Profit             | 3728580.13  |
# | Total Loss               | -1491815.86 |
# | Average Loss per Trade   | -3988.81    |
# | Average Profit per Trade | 12682.25    |
# | Average PNL Per Trade    | 3348.45     |
# | Risk Reward              | 1:3.18      |
# +--------------------------+-------------+

bt = Backtest()
capital = 50000
current_value = capital * len(scripts)  # Starting portfolio value

for stock in scripts:
    data = GoldenCrossverSignal(stock)
    required_df = data[(data.index >= data[data['Position'] == 'Buy'].index[0]) & 
                      (data.index <= data[data['Position'] == 'Sell'].index[-1])]
    
    for index, row in required_df.iterrows():
        # Track portfolio value daily (even without trades)
        bt.track_portfolio_value(index, current_value)
        
        if row.Position == 'Buy':
            qty = capital // row.Open
            bt.buy(stock, index, row.Open, qty)
            # Deduct capital when buying
            current_value -= qty * row.Open
        else:
            bt.sell(index, row.Open, 'Exit Trigger', 0)
            # Add proceeds when selling
            current_value += bt.trade_log['Quantity'] * row.Open

# Final stats with all new metrics
bt.stats()
```

The analysis focuses on stocks that have continuously performed well over 20 years, rather than just current Nifty 50 stocks. Some stocks might have been in the Nifty 50 previously but are no longer, and those could be significant losers. Therefore, the currently selected stocks are considered "winner" stocks.

A point to consider is that a real-world scenario might not allow for signals to be generated for all 50 trades, as capital needs to be divided. A suggestion is to generate signals first and then apply filters to select a limited number of stocks. For example, if 50 signals are generated, one could set a limit and prioritize based on PNL or specific filters. This would allow for a more focused approach, potentially identifying patterns in the top 10 stocks or those that have experienced significant profit. Backtesting is valuable for this kind of analysis.

## Backtesting Analysis: Comprehensive Metrics

These metrics provide foundational insights into the basic performance characteristics of a trading strategy.

### **a. Total Trade Scripts**

* **What it measures:** The count of **unique equities or stocks** that the strategy has traded within the backtesting period.
* **Calculation:** Achieved by getting the `length` of the set of `unique_equity_names` encountered during the trades.
* **Interpretation:** This metric quantifies the **diversification** of the strategy. A **higher number indicates broader market exposure**, suggesting the strategy isn't overly concentrated in a few assets. Conversely, a low number might mean the strategy is highly specialized or less diversified.

### **b. Total Trades**

* **What it measures:** The **absolute number of completed trade cycles**, where each cycle consists of both a buy and a corresponding sell action for a given asset.
* **Calculation:** A simple `count of all trade entries` (or exits, as they should be paired).
* **Interpretation:** A higher value signifies a more **active trading strategy**, which could lead to more opportunities but also potentially higher **transaction costs** (commissions, slippage) due to increased trading frequency.

### **c. PNL (Profit and Loss)**

* **What it measures:** The **net financial gain or loss** generated from all executed trades after accounting for all relevant costs.
* **Calculation:** The sum of `(Exit Price - Entry Price) × Quantity - Fees` for every trade. This aggregates the profit or loss from each individual trade.
* **Interpretation:** This is a **core profitability metric**. A **positive PNL indicates a profitable strategy**, while a **negative PNL signifies an overall loss**. It gives a direct monetary value of the strategy's success.

### **d. Winners & Losers**

* **What it measures:** A categorized count of individual trades based on their profitability. **Winners** are trades that generated a profit, and **Losers** are trades that resulted in a loss or broke even.
* **Calculation:**
  * **Winners:** `Count(PNL > 0)` for individual trades.
  * **Losers:** `Count(PNL ≤ 0)` for individual trades.
* **Interpretation:** These counts are essential for understanding the **consistency** of the strategy and forming the basis for the win/loss ratio. They show how frequently the strategy is successful versus unsuccessful on a per-trade basis.

### **e. Win Ratio**

* **What it measures:** The **percentage of trades that were profitable** out of the total number of trades executed.
* **Calculation:** `(Number of Winners / Total Trades) × 100%`.
* **Interpretation:** A **higher ratio (typically >50%) suggests a more consistent strategy** in terms of generating profitable trades. However, it's important to note that a high win ratio doesn't necessarily guarantee overall profitability if the losing trades are significantly larger in magnitude than the winning ones. It doesn't reflect the size of the profits or losses.

### **f. Total Profit & Total Loss**

* **What it measures:** The **aggregate sum of all gains from winning trades** and the **aggregate sum of all losses from losing trades**, respectively.
* **Calculation:**
  * **Total Profit:** `∑(PNL where PNL > 0)` for all individual trades.
  * **Total Loss:** `∑(PNL where PNL ≤ 0)` for all individual trades.
* **Interpretation:** These metrics provide insight into the **distribution of profitability**. They help determine if the overall PNL is driven by a few large winning trades or many small gains, and similarly, if losses are concentrated in a few large losing trades or spread across many small ones.

### **g. Average Loss/Profit per Trade**

* **What it measures:** The **mean financial gain from a winning trade** and the **mean financial loss from a losing trade**.
* **Calculation:**
  * **Average Profit per Winner:** `Total Profit / Number of Winners`.
  * **Average Loss per Loser:** `Total Loss / Number of Losers`.
* **Interpretation:** These averages are crucial for evaluating the **risk-reward profile per individual trade**. They help determine if the average winning trade is large enough to offset the average losing trade.

### **h. Average PNL Per Trade**

* **What it measures:** The **expected monetary value (gain or loss) per trade** on average.
* **Calculation:** `Total PNL / Total Trades`.
* **Interpretation:** A **positive average PNL per trade indicates that, on average, each trade contributes positively to the strategy's profitability**. It's a quick way to gauge the overall effectiveness of the trading logic.

### **i. Risk-Reward Ratio**

* **What it measures:** The **potential profit for every unit of risk** taken. It compares the average profit from winning trades to the average loss from losing trades.
* **Calculation:** `Average Profit per Winner / |Average Loss per Loser|` (absolute value of average loss).
* **Interpretation:**
  * A **ratio > 1 suggests that the average gains from winning trades exceed the average losses from losing trades**, which is generally desirable. For example, a 1:3 ratio means the strategy aims to gain ₹3 for every ₹1 risked.
  * A **ratio < 1 indicates that losses tend to be larger than gains**, requiring a very high win rate to be profitable.

These advanced metrics provide a more holistic and sophisticated evaluation of a strategy, focusing on risk-adjusted returns and portfolio stability.

### **a. Total Return**

* **What it measures:** The **overall percentage increase or decrease in the initial investment capital** over the entire backtesting period.
* **Calculation:**
    $$\frac{(\text{Final Portfolio Value} - \text{Initial Capital})}{\text{Initial Capital}}$$
* **Interpretation:** This is a straightforward measure of the **absolute performance**. For instance, a 20% total return means that for every ₹100 invested initially, the strategy generated a ₹20 profit. It gives a clear picture of the strategy's capital appreciation.

### **b. CAGR (Compound Annual Growth Rate)**

* **What it measures:** The **smooth, annualized rate at which an investment has grown over a specified period**, assuming profits are reinvested. It provides a more accurate representation of long-term growth than simple average returns.
* **Formula:**
    $$\text{CAGR} = \left( \frac{\text{Final Value}}{\text{Initial Value}} \right)^{\frac{1}{\text{Number of Years}}} - 1$$
* **Interpretation:** CAGR allows for **direct comparison of different strategies over different timeframes**. A 10% CAGR, for example, implies that the investment doubled in approximately 7.2 years (using the Rule of 72). It normalizes returns to an annual basis, making it easier to understand the true growth trajectory.

### **c. Sharpe Ratio**

* **What it measures:** A **Nobel Prize-winning metric that assesses the risk-adjusted return of an investment**. It quantifies how much return an investor receives for the volatility (risk) undertaken.
* **Formula:**
    $$\text{Sharpe Ratio} = \frac{( \text{Annualized Portfolio Return} - \text{Risk-Free Rate} )}{\text{Annualized Portfolio Volatility}}$$
  * Where:
    * $R_p$ = Portfolio return
    * $R_f$ = Risk-free rate (e.g., return on a government bond, often assumed to be 0 for simplicity in backtesting unless specified).
    * $\sigma_p$ = Portfolio volatility (standard deviation of returns).
* **Interpretation:**
  * A **Sharpe Ratio > 1.0 is generally considered good**, indicating that the returns are sufficiently compensating for the risk taken.
  * A **ratio > 2.0 is excellent**, suggesting very strong risk-adjusted returns.
  * A **ratio < 0 implies that the risk-free rate is outperforming the portfolio**, or the portfolio has negative returns, making it undesirable. A higher Sharpe ratio is always better.

### **d. Volatility (Annualized)**

* **What it measures:** The **degree of variation in the strategy's returns**, typically expressed as the annualized standard deviation of daily returns. It serves as a quantitative measure of risk.
* **Formula:**
    $$\text{Annualized Volatility} = \text{Standard Deviation}(\text{Daily Returns}) \times \sqrt{252}$$
    (Assuming 252 trading days in a year).
* **Interpretation:** **Higher volatility indicates greater price fluctuations and thus higher risk**. A strategy with low volatility suggests more stable and predictable returns. It helps in understanding the "bumpiness" of the equity curve.

### **e. VaR (Value at Risk) 95%**

* **What it measures:** The **maximum expected loss over a specific time horizon (e.g., daily) at a given confidence level (e.g., 95%)**. It provides a probabilistic estimate of potential downside risk.
* **Calculation:**
  * **Historical VaR:** Calculated as the `5th Percentile of Daily Returns` observed during the backtesting period.
  * **Parametric VaR (for normally distributed returns):** $-1.65 \times \sigma$ (for a 95% confidence interval, where $\sigma$ is the standard deviation of returns).
* **Interpretation:** A **-2% VaR at 95% confidence** means that, on any given day, there is only a 5% chance that the strategy's loss will exceed 2%. It provides a specific number that defines the worst expected loss under normal market conditions, crucial for setting risk limits.

### **f. Maximum Drawdown**

* **What it measures:** The **largest peak-to-trough decline in the strategy's portfolio value** during the backtesting period, expressed as a percentage. It represents the worst-case capital loss an investor would have endured if they had bought at the peak and sold at the subsequent trough.
* **Calculation:**
    $$\text{Max Drawdown} = \text{Max}\left(1 - \frac{\text{Current Value}}{\text{Historical Peak}}\right)$$
    $$\text{Drawdown}_t = \text{Max}(0, \text{Peak}_t - \text{Current}_t)$$
    $$\text{Maximum Drawdown} = \text{Max}(\text{Drawdown}_t) \text{ for all } t$$
* **Interpretation:** This is a **critical risk management metric**. A smaller maximum drawdown is highly desirable, as it indicates greater capital preservation during adverse market conditions. It highlights the psychological impact and recovery period an investor might face.

### **g. Confidence Interval (95%) for Daily Returns**

* **What it measures:** A **range around the mean daily return within which the true average daily return is expected to fall 95% of the time**. It provides an estimate of the precision of the calculated mean return.
* **Formula:**
    $$\text{Mean} \pm 1.96 \times \frac{\text{Standard Deviation}}{\sqrt{\text{Number of Daily Returns}}}$$
* **Interpretation:** If the confidence interval for daily returns is, for example, (-0.1%, 0.3%), it suggests that the strategy's average daily return is likely to be very small, potentially hovering around breakeven, with 95% certainty. It helps in understanding the reliability of the estimated average return.

### **h. Holding Period**

* **What it measures:** The **average duration that assets are held** within a trade cycle (from entry to exit).
* **Calculation:** `Mean(Exit Time - Entry Time)` for all trades.
* **Interpretation:** This metric differentiates between **high-frequency trading strategies (short holding periods)** and **longer-term investment strategies (extended holding periods)**. It provides insight into the style and liquidity requirements of the strategy.

---

### Key Relationships & Interpretation Guide

Understanding the interplay between these metrics is crucial for a holistic evaluation of any trading strategy.

| Metric Pair                 | Relationship Insight                                                                                                    |
| :-------------------------- | :---------------------------------------------------------------------------------------------------------------------- |
| **CAGR vs. Max Drawdown** | **Ideal strategies exhibit a high CAGR alongside a low Maximum Drawdown**. This signifies strong returns with manageable risk and capital preservation during downturns. |
| **Sharpe Ratio vs. Volatility** | For a given level of return, a **higher Sharpe Ratio is achieved with lower Volatility**. It highlights efficient risk-taking, where returns are generated without excessive swings. |
| **Win Rate vs. Risk-Reward** | A strategy can be profitable even with a relatively **low Win Rate (e.g., 40%) if its Risk-Reward Ratio is sufficiently high (e.g., >1.5:1)**, meaning winning trades are significantly larger than losing ones. This demonstrates that not every trade needs to be a winner for overall success. |
| **VaR vs. Actual Losses** | **Consistent breaches of the VaR estimate (actual losses exceeding the VaR)** indicate a potentially **flawed or underestimated risk model**, suggesting that the strategy is riskier than initially perceived. |

---

### Practical Interpretation Example

Let's consider a hypothetical trading strategy with the following backtesting results:

* **CAGR**: 15%
* **Max Drawdown**: -12%
* **Sharpe Ratio**: 1.8
* **Win Rate**: 55%
* **Risk-Reward**: 1:2.5

**Interpretation**:

"This strategy demonstrates **strong annualized returns of 15% (CAGR)**, indicating robust growth over the backtesting period. It exhibits **moderate risk, with a maximum drawdown of only 12%**, suggesting good capital preservation even during adverse market conditions. The **excellent Sharpe Ratio of 1.8** signifies that the strategy is generating superior risk-adjusted returns, effectively rewarding the risk taken. This favorable performance is achieved through a strategically sound approach, where the **average winning trade is 2.5 times larger than the average losing trade (Risk-Reward 1:2.5)**. This allows the strategy to remain profitable despite a modest **Win Rate of 55%**, as the gains from winners significantly outweigh the losses from losers."

## How to backtest properly

1. **Identify Your Trading Time Frame:** A common mistake is backtesting every single trade indication regardless of the time of day. Different trading sessions (London, New York, Asian) have different market behaviors, with Asian sessions often showing consolidation. It is crucial to only backtest your strategy during the specific hours you intend to trade. For example, if you trade the London session from 7 AM to 12 PM, only analyze that period.
2. **Set Up Visual Brackets for Trading Windows:** Use vertical lines on your chart to mark the start and end of your daily trading window. This should be done for 100 trading days to create a substantial data pool for analysis, which helps determine an accurate win/loss rate for your strategy.
3. **Utilize the Replay Option on TradingView:** The replay feature allows you to simulate real-time trading by hiding future candles from a chosen point forward. This prevents bias, as you won't know how the price will move, forcing you to make decisions as if in a live trading scenario. TradingView offers a premium package with the replay option, often with a free trial and discounts. Adjust the replay speed to a comfortable pace that allows for decision-making.
4. **Conduct Pre-Market Analysis:** Before your trading window opens, analyze the market structure and identify potential trends or reversals. For example, if the market has been in an uptrend but starts breaking market structure and trading below moving averages, one should look for short positions.
5. **Be Patient and Avoid Traps:** Do not trade immediately at market open due to high fluctuations. Be wary of "traps," which are big spikes in one direction followed by an engulfing opposite candle. These often indicate a reversal. It's important to wait for confirmation of your strategy's conditions before entering a trade.
6. **Manage Your Trades and Take Profits:** Adjust your stop loss as the trade moves in your favor, potentially moving it to a break-even or slightly profitable level to eliminate risk. Close trades when market structure breaks or when consolidation begins, even if you haven't hit your full profit target. Take your profits at the end of your defined trading window.
7. **Adhere to a Rules-Based Strategy:** Only enter trades that meet all your predefined rules. Do not force trades, especially during consolidation, as this often leads to losses. It's important to understand that not every day will present a trading opportunity.
8. **Forward Test on Demo Account:** After backtesting 100 times and establishing a win/loss ratio, forward test your strategy on a demo account for a week or two. If you are consistently profitable on demo, then consider trading with real money.
