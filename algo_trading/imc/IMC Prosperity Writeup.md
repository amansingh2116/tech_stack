# IMC Prosperity

> The explanation below assumes familiarity with the basics of Object-Oriented Programming in Python. To refresh this knowledge you can have a look at the source provided on the [Programming resources](https://www.notion.so/Programming-resources-17be8453a0938135a7c5ef6acedb0ab5?pvs=21).

This is a competition where you create a program (called an algorithm) using Python. Your program acts like a trader that buys and sells things on a virtual market called the "island exchange." It will compete against other computer programs (bots), and your goal is to make as much virtual money—called SeaShells—as you can.

- You write a Python program (algorithm) to trade.
- It runs on a virtual market (island exchange).
- You compete with bots to earn SeaShells (money).

The challenge happens over multiple stages, called rounds, on different days. Each round introduces new items (products) you can trade, like coconuts or pineapples. You’ll get sample data—past prices of these items—so you can study how their prices change and make your trading program smarter.

- The challenge has rounds on different days.
- New products are added each round.
- Sample data helps you understand price changes.

Even when new products are added, you can still trade the products from earlier rounds. If your program didn’t do well with an old product (like coconuts) in round 1, you can tweak it in round 2 based on what happened before.

- Old products don’t go away; you can keep trading them.
- You can improve your strategy for old products based on past rounds.

The format for the trading algorithm will be a predefined `Trader` class, which has a single method called `run` which contains all the trading logic coded up by the trader.

After you submit your program, it runs in a virtual world (simulation). This world moves forward in steps called iterations—like turns in a game. Each turn, your run method gets a `TradingState`, which is like a report telling your program what’s happening in the market.

- Your algorithm is a `Trader` class.
- The run method holds all your trading decisions.
- Your program runs in a simulation with many iterations (steps).
- Each iteration, run gets a `TradingState` with market info.

The `TradingState` tells you two things:

1. What trades just happened—like what your program bought or what others sold.
2. What the bots are currently offering—like "Bot A will sell coconuts for 50 SeaShells" or "Bot B will buy for 45 SeaShells." These offers are called quotes.

Your `run` method looks at the bots’ quotes and decides whether to buy or sell. To trade:

- To buy, offer the bot’s sell price or higher (e.g., 50 or more if they ask 50).
- To sell, offer the bot’s buy price or lower (e.g., 45 or less if they offer 45).
If your offer matches, a trade happens.

If the algorithm sends a buy (sell) order with an associated quantity that is larger than the bot sell (buy) quote that it is matched to, the remaining quantity will be left as an outstanding buy (sell) quote with which the trading bots will then potentially trade. When the next iteration begins, the `TradingState` will then reveal whether any of the bots decided to ‘trade on’ the player’s outstanding quote. If none of the bots trade on an outstanding player quote, the quote is automatically cancelled at the end of the iteration.  Example: Bot sells 4 coconuts at 50. You order 10 at 50. You buy 4, and your order for 6 more waits. Next turn, if a bot sells you 6 at 50, you get them. If not, your order for 6 is cancelled.

- Extra order amounts become your own quotes.
- Bots might trade with them next iteration.
- If no trade happens, your quote cancels.

Every trade done by the algorithm in a certain product changes the ‘position’ of the algorithm in that product. E.g. if the initial position in product X was 2 and the algorithm buys an additional quantity of 3, the position in product X is then 5. If the algorithm then subsequently sells a quantity of 7, the position in product X will be -2, called ‘short 2’.

- Position tracks what you own.
- Buying adds, selling subtracts.
- Negative position means you owe (short).

Like in the real world, the algorithms are restricted by per product position limits, which define the absolute position (long or short) that the algorithm is not allowed to exceed. If the aggregated quantity of all the buy (sell) orders an algorithm sends during a certain iteration would, if all fully matched, result in the algorithm obtaining a long (short) position exceeding the position limit, all the orders are cancelled by the exchange.

**Summary:**

This challenge is about writing a Python program to trade virtual products on a market, competing with bots to earn SeaShells. It runs in rounds with new and old products, using a Trader class and run method. The simulation gives you market updates (TradingState) each step, and you make trades based on bots’ offers. Your position changes with each trade, but you must stay within limits, or your orders are cancelled.

## Overview of the `Trader` class

The `Trader` class is a Python class you’ll create. It’s like a blueprint for a trading robot. This class needs one key function called `run`. The simulation calls `run` every time there’s new market data, which comes in the form of a `TradingState`. Inside `run`, you write the rules—like “*buy if the price is low*”—that control what your trader does. When `run` finishes, it returns a dictionary called `result`, which lists all the buy or sell orders your trader wants to place.

### Key Idea

- **Class Name**: `Trader`
- **Main Method**: `run`
- **Input**: A `TradingState` object (a snapshot of the market)
- **Output**: A dictionary (`result`) with your trading orders

Imagine you’re at a market stall. Every few minutes, someone hands you a report (`TradingState`) about what’s for sale and at what price. Your run method looks at this report and decides, “I’ll buy 5 apples at $1 each,” then hands that decision back in the result dictionary.

```python
from datamodel import OrderDepth, UserId, TradingState, Order
'''
**OrderDepth**: Shows buy and sell offers in the market.
**TradingState**: The market snapshot you get each time run is called.
**Order**: A way to create buy/sell instructions.
'''
from typing import List # Helps specify that some variables will be lists

class Trader: # Defines Trader with a run method that takes state (a TradingState object) as input.
    
    def run(self, state: TradingState # type hint denoting a TradingState object):
    # Your trading logic goes here
        print("traderData: " + state.traderData) # Access previous state
        print("Observations: " + str(state.observations)) # Read market observations

    # Orders to be placed on exchange matching engine
        result = {} # Initialize order container
        # Process each product
        for product in state.order_depths:
            order_depth: OrderDepth = state.order_depths[product]
            orders: List[Order] = []
            # Trading strategy (simplified)
            acceptable_price = 10  # Participant should calculate this value
            print("Acceptable price : " + str(acceptable_price))
            print("Buy Order depth : " + str(len(order_depth.buy_orders)) + ", Sell order depth : " + str(len(order_depth.sell_orders)))
        
        # Check buy opportunities (sell orders)
            if len(order_depth.sell_orders) != 0:
                best_ask, best_ask_amount = list(order_depth.sell_orders.items())[0]
                if int(best_ask) < acceptable_price:
                    print("BUY", str(-best_ask_amount) + "x", best_ask)
                    # Create BUY order (negative amount becomes positive)
                    orders.append(Order(product, best_ask, -best_ask_amount))
    
        # Check sell opportunities (buy orders)
            if len(order_depth.buy_orders) != 0:
                best_bid, best_bid_amount = list(order_depth.buy_orders.items())[0]
                if int(best_bid) > acceptable_price:
                    print("SELL", str(best_bid_amount) + "x", best_bid)
                    # Create SELL order (negative amount)
                    orders.append(Order(product, best_bid, -best_bid_amount))
            # Store product's orders
            result[product] = orders
    
      # String value holding Trader state data required. 
    # It will be delivered as TradingState.traderData on next execution.
        traderData = "SAMPLE" 
        
    # Sample conversion request. Check more details below. 
        conversions = 1
        return result, conversions, traderData
```

When you submit your `Trader` code, you get a unique ID, like a ticket number (e.g., “59f81e67-f6c6-4254-b61e-39661eac6141”). If something goes wrong—like your robot loses money—and you need help, you share this ID on Discord so they can find your exact submission.

AWS Lambda functions (which run your trading algorithm) **do not remember anything** between executions.

- Every time your `Trader` class runs, it starts fresh.
- Any variables, data, or calculations from the previous run are **lost** unless you explicitly save them.
- **Why is this a problem for trading?**

    Trading strategies often need to remember past data, such as:

  - Previous prices (for moving averages, trends)
  - Your current position (how many shares you own)
  - Historical trades (to avoid repeating mistakes)
    If Lambda forgets everything, your strategy can’t make smart decisions.

Since Lambda doesn’t store data, the system provides a way for **you** to save and load data manually.

This is done using `traderData`, a **string** that you control.

1. **At the end of each run**, you can return a string (`traderData`) containing any data you want to remember.
    - Example: `traderData = "last_price=100;position=5"`
    - The system saves this string for you.
2. **On the next run**, the system gives you back your saved string inside `TradingState.traderData`.
    - Example:

        ```python
        def run(self, state: TradingState):
            print(state.traderData)  # "last_price=100;position=5"
        
        ```

3. **You must manually decode and use this data** to continue where you left off.

---

### **How to Store and Retrieve Data (Using `jsonpickle`)**

Since `traderData` must be a string, you need a way to **convert Python objects (like dictionaries, lists) into a string** and back.

This is called **serialization** (saving) and **deserialization** (loading).

### **Example: Storing a Dictionary**

```python
import jsonpickle  # A library for converting objects to strings

def run(self, state: TradingState):
    # === LOAD PREVIOUS STATE (if it exists) ===
    if state.traderData:  # Check if there's saved data
        saved_data = jsonpickle.decode(state.traderData)  # Convert string back to Python object
    else:
        saved_data = {"last_prices": [], "position": 0}  # Default if first run

    # === UPDATE STATE WITH NEW DATA ===
    current_price = 105  # Example: Get from market
    saved_data["last_prices"].append(current_price)
    saved_data["position"] += 1  # Example: Update position

    # === SAVE FOR NEXT RUN ===
    traderData = jsonpickle.encode(saved_data)  # Convert to string

    return orders, conversions, traderData

```

---

### **4. Why Can’t You Just Use Normal Variables?**

- **Class variables (`self.x`) and global variables are reset** every time Lambda runs.

    Example (❌ **WRONG** approach):

    ```python
    class Trader:
        def __init__(self):
            self.last_price = None  # Will be forgotten on next run!
    
        def run(self, state):
            if self.last_price:  # Always None because Lambda resets
                print(f"Last price was {self.last_price}")
            self.last_price = current_price  # Useless, won’t persist
    
    ```

  - **This doesn’t work** because AWS Lambda destroys the `Trader` instance after each run.
- **✅ Correct way:** Always use `traderData` to save and load data.

---

### **5. Common Use Cases for `traderData`**

1. **Tracking Your Position**
    - Store how many shares you own so you don’t accidentally over-trade.

    ```python
    saved_data = {"position": 0}
    if new_order:
        saved_data["position"] += order_amount
    
    ```

2. **Storing Price History**
    - Calculate moving averages, detect trends.

    ```python
    saved_data = {"prices": []}
    saved_data["prices"].append(current_price)
    if len(saved_data["prices"]) > 20:
        moving_avg = sum(saved_data["prices"][-20:]) / 20
    
    ```

3. **Avoiding Duplicate Trades**
    - Remember past trades to prevent repeating the same action.

    ```python
    saved_data = {"last_trades": {}}
    if trade_id not in saved_data["last_trades"]:
        place_order()
        saved_data["last_trades"][trade_id] = True
    
    ```

---

### **Final Example (Complete Workflow)**

```python
import jsonpickle

class Trader:
    def run(self, state: TradingState):
        # 1. Load previous state (or initialize if first run)
        if state.traderData:
            saved_data = jsonpickle.decode(state.traderData)
        else:
            saved_data = {"positions": {}, "price_history": {}}

        # 2. Update state with new market data
        current_price = get_current_price(state)
        saved_data["price_history"][state.timestamp] = current_price

        # 3. Make trading decisions
        orders = generate_orders(saved_data, state)

        # 4. Update position tracking
        saved_data["positions"]["PEARLS"] = compute_new_position(orders)

        # 5. Save for next run
        traderData = jsonpickle.encode(saved_data)

        return orders, conversions, traderData
```

## Overview of the `TradingState` class

The `TradingState` class is essentially a snapshot of the market at a given moment in a trading simulation. It provides your trading algorithm with all the critical information needed to make decisions, such as your trades, other traders’ activities, your current holdings, the available buy and sell orders, whether to buy or sell a product. Think of it as a real-time report that updates each time the simulation progresses, giving you the latest market details. Below the definition is provided for the `TradingState` class:

```python
Time = int
Symbol = str
Product = str
Position = int

class TradingState(object):
   def __init__(self,
                 traderData: str, # A string where you can store custom information to carry over between simulation steps. Example: "last_price=50"
                 timestamp: Time, # An integer representing the current time in the simulation. If timestamp = 100, it’s the 100th step of the simulation.
                 listings: Dict[Symbol, Listing], # A dictionary of available products and their details (e.g., product name, symbol).
                 order_depths: Dict[Symbol, OrderDepth], # A dictionary showing buy and sell orders for each product from other traders.
                 own_trades: Dict[Symbol, List[Trade]], # A dictionary of your algorithm’s recent trades, keyed by product.
                 market_trades: Dict[Symbol, List[Trade]], # A dictionary of trades other market participants made recently.
                 position: Dict[Product, Position], # A dictionary tracking how much of each product you own (positive) or owe
                 observations: Observation): # Extra data that might help your decisions, like weather or news (details depend on the simulation).
        self.traderData = traderData
        self.timestamp = timestamp
        self.listings = listings
        self.order_depths = order_depths
        self.own_trades = own_trades
        self.market_trades = market_trades
        self.position = position
        self.observations = observations
        
    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True)
```

When the simulation updates, it creates a new `TradingState` object with the latest values for these properties. Your algorithm (`run` method in `Trader` Class) uses this object to analyze the market and act.

The most important properties

- `own_trades` (`Dict[Symbol, List[Trade]]`): the trades the algorithm itself has done since the last `TradingState` came in. This property is a dictionary of `Trade` objects with key being a product name. The definition of the `Trade` class is provided in the subsections below. It shows your recent activity, helping you track your strategy’s performance.
- `market_trades` (`Dict[Symbol, List[Trade]]`): the trades that other market participants have done since the last `TradingState` came in. This property is also a dictionary of `Trade` objects with key being a product name. It gives insight into market trends and other traders’ behaviors.
- `position` (`Dict[Product, Position]`): the long or short position that the player holds in every tradable product. This property is a dictionary with the product as the key for which the value is a signed integer denoting the position. It tells you your inventory, which affects what you can buy or sell next.
- `order_depths` (`Dict[Symbol, OrderDepth]`): all the buy and sell orders per product that other market participants have sent and that the algorithm is able to trade with. This property is a dict where the keys are the products and the corresponding values are instances of the `OrderDepth` class. This `OrderDepth` class then contains all the buy and sell orders. An overview of the `OrderDepth` class is also provided in the subsections below. It’s your view of the market’s supply and demand, guiding your buy/sell decisions.

Your trading algorithm receives a `TradingState` object at each simulation step. Here’s how you can use it:

1. **Analyze Your Position (`position`):**
Check what you own or owe to avoid overbuying or overselling. *Example:* If position["COCONUTS"] = 5, you might sell some if prices rise.
2. **Review Your Trades (`own_trades`):**
See what you’ve done recently to adjust your strategy. *Example:* If you just bought 3 coconuts, maybe wait before buying more.
3. **Monitor the Market (`market_trades`):**
Spot trends, like if others are buying coconuts heavily, suggesting a price increase. *Example:* If market_trades shows lots of coconut sales, prices might drop soon.
4. **Evaluate Opportunities (`order_depths`):**
Look at buy and sell orders to find profitable trades. *Example:* If bots buy at 45 and sell at 50, you could buy low and sell high.
5. **Track Time (`timestamp`):**
Use the simulation’s progress to time your moves. *Example:* Near the end (timestamp high), you might close positions.
6. **Store Data (`traderData`):**
Save notes between steps, like past prices, to inform future decisions. *Example:* Store "avg_price=48" to compare with current offers.

## `Trade` class

In a trading simulation, the `Trade` class is a fundamental building block that represents a single transaction where a product is exchanged between a buyer and a seller. Both the `own_trades` and `market_trades` properties in the `TradingState` provide traders with lists of trades organized by product, and each trade in these lists is an instance of the `Trade` class.

```python
Symbol = str
UserId = str

class Trade:
    def __init__(self, symbol: Symbol, price: int, quantity: int, buyer: UserId = None, seller: UserId = None, timestamp: int = 0) -> None:
        self.symbol = symbol
        self.price: int = price
        self.quantity: int = quantity
        self.buyer = buyer
        self.seller = seller
        self.timestamp = timestamp

    def __str__(self) -> str:
        return "(" + self.symbol + ", " + self.buyer + " << " + self.seller + ", " + str(self.price) + ", " + str(self.quantity) + ", " + str(self.timestamp) + ")"

    def __repr__(self) -> str:
        return "(" + self.symbol + ", " + self.buyer + " << " + self.seller + ", " + str(self.price) + ", " + str(self.quantity) + ", " + str(self.timestamp) + ")" + self.symbol + ", " + self.buyer + " << " + self.seller + ", " + str(self.price) + ", " + str(self.quantity) + ")"
```

This code defines a `Trade` object with several attributes initialized when a trade is created. The **`__str__`** and **`__repr__`** methods provide a formatted string representation of the trade, making it easy to read or debug.

Each instance of the `Trade` class captures five essential pieces of information about a transaction (plus an additional timestamp property):

1. **Symbol/Product**
    - **Description:** The identifier of the product being traded, such as "COCONUTS" or "PEARLS."
    - **Example:** "COCONUTS" indicates the trade involves coconuts.
    - **Purpose:** Specifies *what* is being exchanged, allowing your algorithm to differentiate between products.
2. **Price**
    - **Description:** The price per unit at which the product was traded, represented as an integer (e.g., in SeaShells).
    - **Example:** 50 means the product was traded at 50 SeaShells per unit.
    - **Purpose:** Indicates the cost or value of the transaction, critical for understanding market pricing.
3. **Quantity**
    - **Description:** The number of units of the product exchanged, also an integer.
    - **Example:** 3 means 3 units (e.g., 3 coconuts) were traded.
    - **Purpose:** Shows the scale of the trade, which can reflect demand or supply strength.
4. **Buyer**
    - **Description:** The identifier of the buyer, a string representing the user ID.
    - **Example:** "SUBMISSION" if your algorithm bought the product, otherwise an empty string ("").
    - **Purpose:** Identifies who purchased the product, but only reveals your algorithm’s involvement.
5. **Seller**
    - **Description:** The identifier of the seller, also a string representing the user ID.
    - **Example:** "SUBMISSION" if your algorithm sold the product, otherwise an empty string ("").
    - **Purpose:** Identifies who sold the product, again only highlighting your algorithm’s role.
6. **Additional Property: Timestamp**
    - **Description:** An integer representing the time the trade occurred in the simulation (defaults to 0 if not specified).
    - **Example:** 100 means the trade happened at the 100th step.
    - **Purpose:** Provides a chronological context, though it’s supplementary to the five core properties.

### Anonymity in Trades

On the island exchange, similar to many real-world trading platforms, the identities of counterparties (other traders) are not disclosed. This means:

- **If your algorithm is involved:**
  - If it buys, buyer will be "SUBMISSION" and seller will be an empty string ("").
  - If it sells, seller will be "SUBMISSION" and buyer will be an empty string ("").
- **If your algorithm is not involved:**
  - Both buyer and seller will be empty strings (""), keeping other traders anonymous.

### Examples of Trades

- **Your algorithm buys:** Trade("COCONUTS", 50, 3, buyer="SUBMISSION", seller="", timestamp=100)
  - Translation: Your algorithm bought 3 coconuts at 50 each at time 100; the seller’s identity is hidden.
- **Your algorithm sells:** Trade("PEARLS", 100, 2, buyer="", seller="SUBMISSION", timestamp=200)
  - Translation: Your algorithm sold 2 pearls at 100 each at time 200; the buyer’s identity is hidden.
- **Other traders:** Trade("COCONUTS", 52, 5, buyer="", seller="", timestamp=300)
  - Translation: Someone traded 5 coconuts at 52 each at time 300; both buyer and seller are anonymous.

### How Trades Appear in `TradingState`

The `TradingState` provides two key properties that use the `Trade` class:

- **`own_trades`**
  - A dictionary mapping products to the lists of your algorithm’s recent trades.
  - **Example:** `own_trades["COCONUTS"] = [Trade("COCONUTS", 50, 3, buyer="SUBMISSION", seller="")]`
  - **Use:** Helps you track and confirm your own buying and selling activity.
- **`market_trades`**
  - A dictionary mapping products to lists of trades by all market participants (including yours).
  - **Example:** `market_trades["PEARLS"] = [Trade("PEARLS", 102, 4, buyer="", seller="")]`
  - **Use:** Offers a window into overall market activity, revealing price and volume trends.

## `OrderDepth` class

The `OrderDepth` class, provided within the `TradingState` class, represents a snapshot of all outstanding buy and sell orders (quotes) for a specific product or symbol, as submitted by trading bots. It allows your algorithm to assess the current market supply and demand.

```python
class OrderDepth:
    def __init__(self):
        self.buy_orders: Dict[int, int] = {}
        self.sell_orders: Dict[int, int] = {}
```

- **`buy_orders`**: A dictionary where:
  - **Keys**: Prices (integers) at which buy orders are placed.
  - **Values**: Total quantity of buy orders at that price (positive integers).
  - **Example**: {9: 5, 10: 4} indicates 5 units to buy at 9 SeaShells and 4 units at 10 SeaShells.
- **`sell_orders`**: A dictionary where:
  - **Keys**: Prices (integers) at which sell orders are placed.
  - **Values**: Total quantity of sell orders at that price (negative integers).
  - **Example**: {12: -3, 11: -2} indicates 3 units to sell at 12 SeaShells and 2 units at 11 SeaShells.

### Key Characteristics

1. **Aggregation**: Orders on each side (buy or sell) are aggregated by price level, showing the total volume available.
2. **Price Separation**: Every price level at which there are buy orders should always be strictly lower than all the levels at which there are sell orders. If not, then there is a potential match between buy and sell orders, and a trade between the bots should have happened.
3. **Usage**: Use this data to:
    - Identify the best bid (highest buy price) and best ask (lowest sell price).
    - Spot trading opportunities like market-making or arbitrage.

### Example

For a product "PEARLS":

- `buy_orders = {45: 10, 46: 5}`: Bots want to buy 10 units at 45 and 5 units at 46.
- `sell_orders = {50: -8, 51: -3}`: Bots want to sell 8 units at 50 and 3 units at 51.
- **Action**: Your algorithm might buy at 46 if you expect prices to rise or sell at 50 if you think it’s a good deal.

## Observation Classes

Observation details help to decide on eventual orders or conversion requests. There are two items delivered inside the TradingState instance:

1. Simple product to value dictionary inside `plainValueObservations`
2. Dictionary of complex **`ConversionObservation`** values for respective products. Used to place conversion requests from Trader class. Structure visible below.

## `Observation` class

The `Observation` class provides additional data within the `TradingState` instance to help your trading algorithm decide on orders or conversion requests. It contains two main components:

- **`plainValueObservations`**:
  - A dictionary mapping products (or external factors) to simple values.
  - Example: `{"WEATHER": "SUNNY"}` might indicate good weather affecting prices.
- **`conversionObservations`**:
  - A dictionary mapping products to `ConversionObservation` objects, which provide detailed data for conversion decisions.

```python
class Observation:
    def __init__(self, plainValueObservations: Dict[Product, ObservationValue], conversionObservations: Dict[Product, ConversionObservation]) -> None:
        self.plainValueObservations = plainValueObservations
        self.conversionObservations = conversionObservations
        
    def __str__(self) -> str:
        return "(plainValueObservations: " + jsonpickle.encode(self.plainValueObservations) + ", conversionObservations: " + jsonpickle.encode(self.conversionObservations) + ")"
```

## `ConversionObservation` Class

The `ConversionObservation` class supplies specific data points for deciding whether to convert one product into another (e.g., coconuts to coconut water).

```python
class ConversionObservation:

    def __init__(self, bidPrice: float, askPrice: float, transportFees: float, exportTariff: float, importTariff: float, sugarPrice: float, sunlightIndex: float):
        self.bidPrice = bidPrice # Price at which you can sell the converted product.
        self.askPrice = askPrice # Price at which you can buy the converted product.
        self.transportFees = transportFees # Cost to move the product.
        self.exportTariff = exportTariff # Fee for exporting the product.
        self.importTariff = importTariff # Fee for importing the product.
        self.sugarPrice = sugarPrice # Price of a related commodity (e.g., sugar) that might affect conversion.
        self.sunlightIndex = sunlightIndex # An environmental factor (e.g., sunlight level) influencing conversion efficiency or quality.
```

**Example:**

For converting "COCONUTS" to coconut water:

- `bidPrice = 10.5`, `askPrice = 11.0`, `transportFees = 0.5`, `exportTariff = 0.2`, `importTariff = 0.3`, `sugarPrice = 2.0`, `sunlightIndex = 80`.
- Interpretation: You can sell coconut water for 10.5 SeaShells, but conversion costs include 0.5 (transport) + 0.2 (export) + 0.3 (import) = 1.0 SeaShells per unit, plus any sugar-related costs.

## Placing Conversion Requests

To convert a product, your trading algorithm must return an integer as the "`conversions`" value from the `run()` method. This integer specifies how many units to convert. Based on logic defined inside Prosperity container it will convert positions acquired by submitted code. There is a number of conditions for conversion to happen:

### Conditions

1. **Position Requirement**:
    - You must already hold a position in the product (long or short).
    - Long: Owning units (positive position).
    - Short: Owing units (negative position).
2. **Quantity Limits**:
    - The request cannot exceed the smaller of:
        - Your position size (absolute value for short positions).
        - The conversion limit set by the system.
3. **Short Position Example**:
    - If you’re short 10 units (-10) and the limit is 5, you can request 1 to 5 units. A request for 6 or above is fully ignored.
4. **Costs**:
    - You must cover `transportFees`, `exportTariff`, and `importTariff` from `ConversionObservation`.
5. **Optional**:
    - Conversion request is not mandatory. You can send 0 or None as value.

## How to send orders using the `Order` class

After analyzing the incoming `TradingState` in your trading algorithm, the `run` method must produce a dictionary of orders to be executed. This dictionary specifies the products you want to trade and the details of each order, utilizing the `Order` class. Let’s dive deeper into how this works, including practical examples and considerations.

### `Order` Class

The `Order` class is the building block for submitting trades. Each order you create defines three critical properties:

1. **Symbol**: A string representing the product you’re trading (e.g., "COCONUTS" or "PINA_COLADAS").
2. **Price**: An integer indicating:
    - For a **buy order**, the maximum price you’re willing to pay.
    - For a **sell order**, the minimum price you’re willing to accept.
3. **Quantity**: An integer specifying how much you want to trade:
    - **Positive** quantity (e.g., 5) indicates a buy order.
    - **Negative** quantity (e.g., -5) indicates a sell order.

Example: **Sell Order**: `Order("COCONUTS", 55, -2)`. This means you want to sell up to 2 units of coconuts at a price of 55 or higher.

These orders are collected into lists and organized by product in the output dictionary of the `run` method.

```python
Symbol = str

class Order:
    def __init__(self, symbol: Symbol, price: int, quantity: int) -> None:
        self.symbol = symbol
        self.price = price
        self.quantity = quantity

    def __str__(self) -> str:
        return "(" + self.symbol + ", " + str(self.price) + ", " + str(self.quantity) + ")"

    def __repr__(self) -> str:
        return "(" + self.symbol + ", " + str(self.price) + ", " + str(self.quantity) + ")"
```

The `run` method is where your trading logic comes to life. It takes a TradingState object as input (containing market data and your current positions) and returns a dictionary where:

- **Keys** are product symbols (e.g., "COCONUTS").
- **Values** are lists of Order objects for that product.

### Example Implementation

```python
# If market conditions allow, the buy order executes at 50 or less, and the sell order at 55 or more.
# You can add orders for other products (e.g., "PINA_COLADAS") to the same dictionary.
def run(self, state: TradingState):
    orders = {}
    
    # Trading logic: Buy 3 coconuts at 50 or less, sell 2 at 55 or more
    coconut_orders = []
    coconut_orders.append(Order("COCONUTS", 50, 3))   # Buy order
    coconut_orders.append(Order("COCONUTS", 55, -2))  # Sell order
    
    orders["COCONUTS"] = coconut_orders
    
    return orders
```

## How Orders Are Executed

Once submitted, your orders interact with the market as follows:

1. **Immediate Execution**:
If there are existing bot orders that match your price and quantity (e.g., a bot selling at 50 when you buy at 50), your order executes fully or partially right away.
2. **Remaining Quantity**:
If only part of your order is filled (e.g., you want 5 units but only 2 are available), the remaining quantity (3 units) becomes a visible order in the market. Bots can then choose to trade against it in the next iteration.
3. **Cancellation**:
If no bot trades with the remaining quantity by the end of the iteration, it’s cancelled automatically.

Note that after cancellation of the algorithm’s orders but before the next `Tradingstate` comes in, bots might also trade with each other.

### Speed Advantage

On the Prosperity Island exchange, your orders are processed **infinitely fast**. This means they’re matched with existing bot orders before any new bot orders are considered in the same iteration, giving you a first-mover advantage.  In other words, none of the bots can send an order that is faster than the player’s order and get the opportunity instead.

## Position Limits: Staying Within Bounds

Position limits cap how much of a product you can hold, ensuring risk management. These limits are:

- **Per-product**: Each product has its own limit.
- **Absolute**: The limit applies to both long (positive) and short (negative) positions.

For example, with a position limit of 10:

- Your position can’t exceed +10 (long) or drop below -10 (short).

### Enforcement by the Exchange

The exchange checks your orders against position limits **before execution**:

- **Buy Orders**: If the total quantity (aggregated) of your buy orders would push your position above the positive limit, **all buy orders** for that product are rejected.
- **Sell Orders**: If the total quantity (aggregated) of your sell orders would push your position below the negative limit, **all sell orders** for that product are rejected.

### Example Scenario

- **Product**: "`COCONUTS`"
- **Position Limit**: 30
- **Current Position**: -5 (you owe 5 units)
- **Max Buy Quantity**:
To avoid exceeding +30:
Max position = 30, Current position = -5
Max buy = 30 - (-5) = 35 units
Sending an aggregated buy order for more than 35 units (e.g., `Order("COCONUTS", 50, 40))` rejects all buy orders.
- **Max Sell Quantity**:
To avoid dropping below -30:
Max short position = -30, Current position = -5
Max sell = -30 - (-5) = -25 units
Sending a sell order for more than 25 units (e.g., `Order("COCONUTS", 45, -30))` rejects all sell orders.

For an overview of the per-product position limit players are referred to the ‘Rounds’ section on [Prosperity 3 Wiki](https://www.notion.so/19ee8453a09380529731c4e6fb697ea4?pvs=21).

### Practical code to respect limits

```python
current_position = state.position.get("COCONUTS", 0)  # Default to 0 if no position
position_limit = 30  # Example limit

max_buy = position_limit - current_position
max_sell = -position_limit - current_position  # Negative for sell

# Example: Only send buy order if within limit
if max_buy >= 3:
    orders["COCONUTS"] = [Order("COCONUTS", 50, 3)]
```

## Example of Trading

Let’s dive into the trading example provided and explore how the simulation behaves over the two iterations for `PRODUCT1` and `PRODUCT2`. The goal is to understand how the algorithm’s decisions, based on its price convictions, interact with the market and update the `TradingState`. We’ll walk through the initial state, the algorithm’s actions, the resulting trades, and the updated state, making observations along the way.

---

### Initial `TradingState` (Timestamp 1000)

```python
from datamodel import Listing, OrderDepth, Trade, TradingState

timestamp = 1000

listings = {
 "PRODUCT1": Listing(
  symbol="PRODUCT1", 
  product="PRODUCT1", 
  denomination= "SEASHELLS"
 ),
 "PRODUCT2": Listing(
  symbol="PRODUCT2", 
  product="PRODUCT2", 
  denomination= "SEASHELLS"
 ),
}

order_depths = {
 "PRODUCT1": OrderDepth(
  buy_orders={10: 7, 9: 5},
  sell_orders={11: -4, 12: -8}
 ),
 "PRODUCT2": OrderDepth(
  buy_orders={142: 3, 141: 5},
  sell_orders={144: -5, 145: -8}
 ), 
}

own_trades = {
 "PRODUCT1": [],
 "PRODUCT2": []
}

market_trades = {
 "PRODUCT1": [
  Trade(
   symbol="PRODUCT1",
   price=11,
   quantity=4,
   buyer="",
   seller="",
   timestamp=900
  )
 ],
 "PRODUCT2": []
}

position = {
 "PRODUCT1": 3,
 "PRODUCT2": -5
}

observations = {}
traderData = ""

state = TradingState(
 traderData,
 timestamp,
  listings,
 order_depths,
 own_trades,
 market_trades,
 position,
 observations
)
```

At the start of the first iteration, the `TradingState` is initialized as follows:

- **Products and Position Limits**:
  - `PRODUCT1`: Position limit of 10.
  - `PRODUCT2`: Position limit of 20.
- **Order Depths** (buy and sell orders in the market):
  - `PRODUCT1`:
    - **Buy Orders**: 10 (7 units), 9 (5 units) — these are bids to buy.
    - **Sell Orders**: 11 (-4 units), 12 (-8 units) — these are offers to sell, with negative quantities indicating sell side.
  - `PRODUCT2`:
    - **Buy Orders**: 142 (3 units), 141 (5 units).
    - **Sell Orders**: 144 (-5 units), 145 (-8 units).
- **Own Trades**: Empty for both `PRODUCT1` and `PRODUCT2` — no trades by the algorithm yet.
- **Market Trades** (trades by others):
  - `PRODUCT1`: One trade at price 11 for 4 units (timestamp 900).
  - `PRODUCT2`: No trades.
- **Position**:
  - `PRODUCT1`: 3 (long, meaning the algorithm owns 3 units).
  - `PRODUCT2`: -5 (short, meaning the algorithm has sold 5 units it doesn’t own).
- **Other Fields**: `observations` and `traderData` are empty, and the timestamp is 1000.

This state represents the market conditions and the algorithm’s current holdings before it makes any decisions.

---

### Algorithm’s Convictions and Decision-Making

The algorithm has specific beliefs about the fair value of each product:

- `PRODUCT1` is worth 13.
- `PRODUCT2` is worth 142.

Based on these convictions, it evaluates the market and decides on trades:

### For `PRODUCT1`

- **Market Prices vs. Fair Value**:
  - Sell orders exist at 11 (4 units) and 12 (8 units), both below the fair value of 13.
  - This suggests `PRODUCT1` is undervalued in the sell orders, making it attractive to buy.
- **Position Check**:
  - Current position: 3 long.
  - Position limit: 10.
  - Maximum additional units it can buy: 10 - 3 = 7 units.
- **Action**:
  - The algorithm sends a buy order for 7 units at price 12.
  - By bidding 12, it aims to match with the sell orders at 11 and 12 (since buy orders match with the best available sell prices first).

### For `PRODUCT2`

- **Market Prices vs. Fair Value**:
  - Buy orders at 142 (3 units) and 141 (5 units) — at or below fair value, not profitable to sell into.
  - Sell orders at 144 (-5 units) and 145 (-8 units) — above fair value, not attractive to buy from.
  - No current orders are immediately profitable relative to 142.
- **Action**:
  - The algorithm tests the market by sending a sell order for 5 units at 143.
  - This price is between the buy orders (142) and sell orders (144), probing if bots will buy at 143.
- **Position Check**:
  - Current position: -5 (short).
  - Short position limit: -20 (since the limit is 20 in either direction).
  - Selling 5 more units would move the position to -10, still within limits.

The algorithm’s output is:

```python
result["PRODUCT1"] = [Order("PRODUCT1", 12, 7)]
result["PRODUCT2"] = [Order("PRODUCT2", 143, -5)]

```

---

### How the Orders Are Executed

The simulation processes these orders, matching them with the market and bot reactions:

### `PRODUCT1`

- **Order**: Buy 7 units at 12.
- **Matching Process**:
  - Buy orders match with the best (lowest) sell prices first.
  - Sell order at 11 (-4 units): Fully matched, buying 4 units at 11.
  - Sell order at 12 (-8 units): Matches the remaining 3 units at 12 (reducing the sell order to -5 units).
- **Trades Executed**:
  - Buy 4 units at 11.
  - Buy 3 units at 12.
- **Position Update**:
  - Starting position: 3.
  - After buying 7 units: 3 + 7 = 10 (hits the position limit).

### `PRODUCT2`

- **Order**: Sell 5 units at 143.
- **Matching Process**:
  - No existing buy orders at 143 (highest is 142).
  - Bots in the simulation react: One bot places a buy order for 2 units at 143.
  - Trade occurs for 2 units; the remaining 3 units of the sell order are unmatched.
- **Trades Executed**:
  - Sell 2 units at 143 (partial execution).
  - Remaining 3 units are cancelled (no further bot interest).
- **Position Update**:
  - Starting position: -5.
  - After selling 2 units: -5 - 2 = -7 (short position increases).

---

### Next `TradingState` (Timestamp 1100)

After the trades, the `TradingState` updates to reflect the new market conditions. An example of what the next `TradingState` will look like is generated by the code below:

```python
from datamodel import Listing, OrderDepth, Trade, TradingState

timestamp = 1100

listings = {
 "PRODUCT1": Listing(
  symbol="PRODUCT1", 
  product="PRODUCT1", 
  denomination: "SEASHELLS"
 ),
 "PRODUCT2": Listing(
  symbol="PRODUCT2", 
  product="PRODUCT2", 
  denomination: "SEASHELLS"
 ),
}

order_depths = {
 "PRODUCT1": OrderDepth(
  buy_orders={10: 7, 9: 5},
  sell_orders={12: -5, 13: -3}
 ),
 "PRODUCT2": OrderDepth(
  buy_orders={142: 3, 141: 5},
  sell_orders={144: -5, 145: -8}
 ), 
}

own_trades = {
 "PRODUCT1": [
  Trade(
   symbol="PRODUCT1",
   price=11,
   quantity=4,
   buyer="SUBMISSION",
   seller="",
   timestamp=1000
  ),
  Trade(
   symbol="PRODUCT1",
   price=12,
   quantity=3,
   buyer="SUBMISSION",
   seller="",
   timestamp=1000
  )
 ],
 "PRODUCT2": [
  Trade(
   symbol="PRODUCT2",
   price=143,
   quantity=2,
   buyer="",
   seller="SUBMISSION",
   timestamp=1000
  ),
 ]
}

market_trades = {
 "PRODUCT1": [],
 "PRODUCT2": []
}

position = {
 "PRODUCT1": 10,
 "PRODUCT2": -7
}

observations = {}
traderData = ""

state = TradingState(
 traderData,
 timestamp,
  listings,
 order_depths,
 own_trades,
 market_trades,
 position,
 observations
)
```

- **Order Depths**:
  - `PRODUCT1`:
    - **Buy Orders**: 10 (7), 9 (5) — unchanged, as no sell orders matched these.
    - **Sell Orders**: 12 (-5), 13 (-3) — sell order at 11 is gone (fully matched), 12 reduced from -8 to -5 (3 units traded), and 13 (-3) is new or existing.
  - `PRODUCT2`:
    - **Buy Orders**: 142 (3), 141 (5) — unchanged.
    - **Sell Orders**: 144 (-5), 145 (-8) — unchanged, as the sell order at 143 was a new offer, partially filled, then cancelled.
- **Own Trades** (the algorithm’s executed trades):
  - `PRODUCT1`:
    - Trade: Buy 4 at 11 (buyer: "SUBMISSION", timestamp 1000).
    - Trade: Buy 3 at 12 (buyer: "SUBMISSION", timestamp 1000).
  - `PRODUCT2`:
    - Trade: Sell 2 at 143 (seller: "SUBMISSION", timestamp 1000).
- **Market Trades**: Empty for both products — no new trades by others.
- **Position**:
  - `PRODUCT1`: 10 (long).
  - `PRODUCT2`: -7 (short).
- **Other Fields**: `traderData` and `observations` remain empty, timestamp advances to 1100.

---

### Key Observations

1. **Order Matching Priority**:
    - For `PRODUCT1`, the buy order at 12 matched first with the sell order at 11 (4 units), then with 12 (3 units). This shows the simulation prioritizes the best available price for the buyer (lowest sell price).
2. **Partial Execution**:
    - For `PRODUCT2`, the sell order of 5 units at 143 only filled 2 units. Bots selectively traded, and the remaining 3 units were cancelled, indicating not all orders fully execute.
3. **Position Limits**:
    - The algorithm respected limits: `PRODUCT1` reached 10 (max long), and `PRODUCT2` moved to -7 (within the -20 short limit).
4. **Market Dynamics**:
    - Bot reactions (e.g., buying 2 units at 143 for `PRODUCT2` as a reaction to the player’s sell order at that price level) show the simulation includes responsive agents, but their actions are limited and unpredictable. For the player’s initial order this means that a quantity of 3 of the 5 total remains unexecuted. None of the bots decides to trade against this order, and the full order quantity is automatically cancelled.

## Technical Notes

When writing your trading algorithm, there are some important technical details to consider. These rules ensure your algorithm works smoothly within the competition’s system and follows its guidelines. Let’s break them down:

### 1. **Supported Libraries**

- **What It Means**: Your algorithm can only use specific Python libraries that are officially allowed by the competition. The following libraries are supported in the simulation. Importing other external libraries is not supported.
  - [pandas](https://pandas.pydata.org/)
  - [NumPy](https://numpy.org/)
  - [statistics](https://docs.python.org/3.9/library/statistics.html)
  - [math](https://docs.python.org/3.9/library/math.html)
  - [typing](https://docs.python.org/3.9/library/typing.html)
  - [jsonpickle](https://pypi.org/project/jsonpickle/)
- **Why It’s Important**: This keeps the competition fair by ensuring everyone uses the same tools and prevents anyone from gaining an edge with unapproved software. Before coding, review the supported libraries and stick to what’s allowed to avoid submission errors.

### 2. **Response Time Limit**

- **What It Means**: Every time your algorithm’s run method is called, it must finish and return a response in less than 900 milliseconds (0.9 seconds). If it takes longer, the system will stop it, and your algorithm might miss trades or fail entirely.
- **Why It’s Important**: The competition simulates real-time trading, so your algorithm needs to be fast to keep up with market changes.
- **Key Tips**:
  - Keep your code simple and avoid heavy calculations or big loops.
  - Test how long your run method takes on your computer before submitting.
  - Optimize your algorithm to be as fast as possible.

## Available Resources to Help Build the Algorithm

The IMC Prosperity Challenge provides useful resources to help you design, test, and improve your trading algorithm. These tools give you insight into how the market works and let you see how your algorithm performs. Here’s what’s available:

### 1. **Sample Data for New Products**

- **What It Is**: For every new product (like a stock or item you can trade), you get several days of sample data in two CSV files:
  - **Trades CSV**: This lists every trade that happened on a given day. It includes details like the price, quantity, and time of each trade.
  - **Market Orders CSV**: This shows the order book (all buy and sell orders) at every time step, so you can see how the market looked throughout the day.
- **Why It’s Useful**: These files let you study past market behavior, spot trends, and test your algorithm’s strategy on real data before the competition starts.
- **Key Tips**:
  - Look for patterns in the data, like price changes or trading volume spikes.
  - Use this data to “backtest” your algorithm—run it on past days to see what it would have done.

### 2. **Log Files for Debugging**

- **What It Is**: After you upload your algorithm to the Prosperity platform, it’s tested over 1000 iterations using data from a sample day (not the real competition day). Once the test is done, you get a log file that shows:
  - How your algorithm performed (like trades it made or profits earned).
  - Any output from `print` statements you added to your `run` method.
- **Why It’s Useful**: The log file helps you figure out what’s going wrong if your algorithm doesn’t work as expected. It’s like a window into your code’s decisions during the test.
- **Practical Example**: Let’s say your algorithm buys 100 units of `PRODUCT2` when you didn’t expect it to. The log might show the price was $5 and your code thought it was a good deal. You could then check your logic and fix it.
- **Key Tips**:
  - Add print statements in your run method to track important decisions (e.g., `print("Buying at price:", price)`).
  - Study the log file after each test to spot mistakes or improve your strategy.

---

## `Trader` Class Example

Below an example of an implementation of the `Trader` class is provided. While very simple and likely not profitable, this example algorithm does include all the necessary logic to send orders for the first day’s “PEARLS” product (see the page that describes the first round).

```python
from datamodel import OrderDepth, UserId, TradingState, Order
from typing import List
import string

class Trader:
    
    def run(self, state: TradingState):
        # Only method required. It takes all buy and sell orders for all symbols as an input, and outputs a list of orders to be sent
        print("traderData: " + state.traderData)
        print("Observations: " + str(state.observations))
        result = {}
        for product in state.order_depths:
            order_depth: OrderDepth = state.order_depths[product]
            orders: List[Order] = []
            acceptable_price = 10;  # Participant should calculate this value
            print("Acceptable price : " + str(acceptable_price))
            print("Buy Order depth : " + str(len(order_depth.buy_orders)) + ", Sell order depth : " + str(len(order_depth.sell_orders)))
    
            if len(order_depth.sell_orders) != 0:
                best_ask, best_ask_amount = list(order_depth.sell_orders.items())[0]
                if int(best_ask) < acceptable_price:
                    print("BUY", str(-best_ask_amount) + "x", best_ask)
                    orders.append(Order(product, best_ask, -best_ask_amount))
    
            if len(order_depth.buy_orders) != 0:
                best_bid, best_bid_amount = list(order_depth.buy_orders.items())[0]
                if int(best_bid) > acceptable_price:
                    print("SELL", str(best_bid_amount) + "x", best_bid)
                    orders.append(Order(product, best_bid, -best_bid_amount))
            
            result[product] = orders
    
    
        traderData = "SAMPLE" # String value holding Trader state data required. It will be delivered as TradingState.traderData on next execution.
        
        conversions = 1
        return result, conversions, traderData

```

---

## Complete `datamodel.py`

```python
import json
from typing import Dict, List
from json import JSONEncoder
import jsonpickle

Time = int
Symbol = str
Product = str
Position = int
UserId = str
ObservationValue = int

class Listing:

    def __init__(self, symbol: Symbol, product: Product, denomination: Product):
        self.symbol = symbol
        self.product = product
        self.denomination = denomination
        
                 
class ConversionObservation:

    def __init__(self, bidPrice: float, askPrice: float, transportFees: float, exportTariff: float, importTariff: float, sugarPrice: float, sunlightIndex: float):
        self.bidPrice = bidPrice
        self.askPrice = askPrice
        self.transportFees = transportFees
        self.exportTariff = exportTariff
        self.importTariff = importTariff
        self.sugarPrice = sugarPrice
        self.sunlightIndex = sunlightIndex
        

class Observation:

    def __init__(self, plainValueObservations: Dict[Product, ObservationValue], conversionObservations: Dict[Product, ConversionObservation]) -> None:
        self.plainValueObservations = plainValueObservations
        self.conversionObservations = conversionObservations
        
    def __str__(self) -> str:
        return "(plainValueObservations: " + jsonpickle.encode(self.plainValueObservations) + ", conversionObservations: " + jsonpickle.encode(self.conversionObservations) + ")"
     

class Order:

    def __init__(self, symbol: Symbol, price: int, quantity: int) -> None:
        self.symbol = symbol
        self.price = price
        self.quantity = quantity

    def __str__(self) -> str:
        return "(" + self.symbol + ", " + str(self.price) + ", " + str(self.quantity) + ")"

    def __repr__(self) -> str:
        return "(" + self.symbol + ", " + str(self.price) + ", " + str(self.quantity) + ")"
    

class OrderDepth:

    def __init__(self):
        self.buy_orders: Dict[int, int] = {}
        self.sell_orders: Dict[int, int] = {}

class Trade:

    def __init__(self, symbol: Symbol, price: int, quantity: int, buyer: UserId=None, seller: UserId=None, timestamp: int=0) -> None:
        self.symbol = symbol
        self.price: int = price
        self.quantity: int = quantity
        self.buyer = buyer
        self.seller = seller
        self.timestamp = timestamp

    def __str__(self) -> str:
        return "(" + self.symbol + ", " + self.buyer + " << " + self.seller + ", " + str(self.price) + ", " + str(self.quantity) + ", " + str(self.timestamp) + ")"

    def __repr__(self) -> str:
        return "(" + self.symbol + ", " + self.buyer + " << " + self.seller + ", " + str(self.price) + ", " + str(self.quantity) + ", " + str(self.timestamp) + ")"

class TradingState(object):

    def __init__(self,
                 traderData: str,
                 timestamp: Time,
                 listings: Dict[Symbol, Listing],
                 order_depths: Dict[Symbol, OrderDepth],
                 own_trades: Dict[Symbol, List[Trade]],
                 market_trades: Dict[Symbol, List[Trade]],
                 position: Dict[Product, Position],
                 observations: Observation):
        self.traderData = traderData
        self.timestamp = timestamp
        self.listings = listings
        self.order_depths = order_depths
        self.own_trades = own_trades
        self.market_trades = market_trades
        self.position = position
        self.observations = observations
        
    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True)

    
class ProsperityEncoder(JSONEncoder):

        def default(self, o):
            return o.__dict__
```
