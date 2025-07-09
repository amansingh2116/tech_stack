# IMC Prosperity

## Prosperity 1

We have very less information available online about the first Prosperity, we were just able to find algorithmic challenges.

### Round 1

#### Algorithmic Challenge

Participants have worked with two assets, namely PEARLS, whose price remains relatively constant over time at a value of 10k seashells, and BANANAS, an asset whose price is highly volatile, fluctuating frequently.

**Solution 1:**


### Round 2

#### Algorithmic Challenge

Participants have been provided with data on COCONUTS and PINA_COLADAS. Although the price of COCONUTS and PINA_COLADAS are related, as coconuts are required for the production of pina coladas, the converse is not true.

**Solution 1:**


### Round 3

#### Algorithmic Challenge

Two additional assets were introduced, BERRIES and DIVING_GEAR. The price of BERRIES is seasonal, while that of DIVING_GEAR is influenced by DOLPHIN_SIGHTINGS, another data set provided by IMC. The latter may serve as a feature for predicting the price of DIVING_GEAR.

**Solution 1:**

### Round 4

#### Algorithmic Challenge

Participants have worked with four assets, namely PICNIC_BASKET, UKULELE, DIP, and BAGUETTE. We have been informed that one PICNIC_BASKET consists of one UKULELE, two BAGUETTEs, and four DIPs. However, the price of PICNIC_BASKET is not equivalent to the sum of the prices of its individual components.

**Solution 1:**


### Round 5

#### Algorithmic Challenge

During this round, participants were granted access to IMC trader bots trading history and were given the opportunity to replicate, or take profit from the strategy of the most experienced bots.

**Solution 1:**


## Prosperity 2

### Tutorial Round

In the tutorial round there are two tradable goods: `AMETHYSTS` and `STARFRUIT`. While the value of the AMETHYSTS has been stable throughout the history of the archipelago, the value of `STARFRUIT` has been going up and down over time. All algorithms uploaded in the tutorial round will be processed and generate results instantly, so you can experiment with different programs and strategies.

Position limits for the newly introduced products:

- `AMETHYSTS`: 20
- `STARFRUIT`: 20

**Solution 1:**


### Round 1

#### Algorithmic Challenge

The first two tradable products are introduced: `STARFRUIT` and `AMETHYSTS`. While the value of the `AMETHYSTS` has been stable throughout the history of the archipelago, the value of `STARFRUIT` has been going up and down over time. Develop your initial trading strategy and write your first Python program to get off to a good start in this world of trading and market making. Even if the price of a product moves very little or in a very unpredictable way, there might still be clever ways to profit if you both buy and sell.

Position limits for the newly introduced products:

- `STARFRUIT`: 20
- `AMETHYSTS`: 20

**Solution 1:**


#### Manual Challenge

With a large school of goldfish visiting, an opportunity arises to acquire some top grade `SCUBA_GEAR`. You only have two chances to offer a good price. Each one of the goldfish will accept the lowest bid that is over their reserve price. You know there’s a constant desire for scuba gear on the archipelago. So, at the end of the round, you’ll be able to sell them for 1000 SeaShells a piece.

Whilst not every goldfish has the same reserve price, you know the distribution of their reserve prices. The reserve price will be no lower than 900 and no higher than 1000. The probability scales linearly from 0 at 900 to most likely at 1000.

You only trade with the goldfish. Bids of other participants will not affect your results.

Think hard about how you want to set your two bids in order to walk away with some serious SeaShell profit.

**Solution 1:**


### Round 2

#### Algorithmic Challenge

During this second round of the Prosperity challenge, you again get the chance to trade the same products as in round 1. In addition, a new product is introduced: `ORCHIDS`. `ORCHIDS` are very delicate and their value is dependent on all sorts of observable factors like hours of sun light, humidity, shipping costs, in- & export tariffs and suitable storage space. Can you find the right connections to optimize your program?

Position limits for the newly introduced products:

- `ORCHIDS`: 100

**Solution 1:**


#### Manual Challenge

You get the chance to do a series of trades in some foreign island currencies. The first trade is a conversion of your SeaShells into a foreign currency, the last trade is a conversion from a foreign currency into SeaShells. Everything in between is up to you. Give some thought to what series of trades you would like to do, as there might be an opportunity to walk away with more shells than you arrived with.

**Solution 1:**


### Round 3

#### Algorithmic Challenge

Cupid has landed in our archipelago and infected almost every inhabitant. Next to the products from the previous two rounds, the `GIFT_BASKET` is now available as a tradable good. This lovely basket contains three things:

1. Four `CHOCOLATE` bars
2. Six `STRAWBERRIES`
3. A single `ROSES`

All four of the above products can now also be traded on the island exchange. Are the gift baskets a bit expensive for your taste? Then perhaps see if you can get the contents directly.

Position limits for the newly introduced products:

- `CHOCOLATE`: 250
- `STRAWBERRIES`: 350
- `ROSES`: 60
- `GIFT_BASKET`: 60

**Solution 1:**


#### Manual Challenge

A mysterious treasure map and accompanying note has everyone acting like heroic adventurers. You get to go on a maximum of three expeditions to search for treasure. Your first expedition is free, but the second and third one will come at a cost. Keep in mind that you are not the only one searching and you’ll have to split the spoils with all the others that search in the same spot. Plan your expeditions carefully and you might return with the biggest loot of all.

Here's a breakdown of how your profit from an expedition will be computed:
Every spot has its **treasure multiplier** (up to 100) and the number of **hunters** (up to 8). The spot's total treasure is the product of the **base treasure** (7500, same for all spots) and the spot's specific treasure multiplier. However, the resulting amount is then divided by the sum of the hunters and the percentage of all the expeditions (from other players) that took place there. For example, if a field has 5 hunters, and 10% of all the expeditions (from all the other players) are also going there, the prize you get from that field will be divided by 15. After the division, **expedition costs** apply (if there are any), and profit is what remains.

Second and third expeditions are optional: you are not required to do all 3. Fee for embarking upon a second expedition is 25 000, and for third it's 75 000. Order of submitted expeditions does not matter for grading.

**Solution 1:**


### Round 4

Our inhabitants are crazy about coconuts. So crazy even, that they invented a new tradable good, `COCONUT_COUPON`. The coupons will give you the right to buy `COCONUT` at a certain price by the end of the round and can be traded as a separate good. Of course you will have to pay a premium for these coupons, but if you play your coconuts right, SeaShells spoils will be waiting for you on the horizon.

Coconut Coupons give the right to buy Coconut at a certain price at some time in future. Certain price = 10000 and some time in future = 250 trading days, each round is 1 trading day.

Position limits for the newly introduced products:

- `COCONUT`: 300
- `COCONUT_COUPON`: 600

**Solution 1:**


#### Algorithmic Challenge

#### Manual Challenge

The goldfish are back with more `SCUBA_GEAR`. Each of the goldfish will have new reserve prices, but they still follow the same distribution as in Round 1.

Your trade options are similar to before. You’ll have two chances to offer a good price. Each one of the goldfish will accept the lowest bid that is over their reserve price. But this time, for your second bid, they also take into account the average of the second bids by other traders in the archipelago. They’ll trade with you when your offer is above the average of all second bids. But if you end up under the average, the probability of a deal decreases rapidly.

To simulate this probability, the PNL obtained from trading with a fish for which your second bid is under the average of all second bids will be scaled by a factor *p*:

$$
p = (1000 – \text{average bid}) / (1000 – \text{your bid})
$$

What can you learn from the available data and how will you anticipate on this new dynamic? Place your feet firmly in the sand and brace yourself, because this could get messy.

**Solution 1:**


### Round 5

#### Algorithmic Challenge

The final round of the challenge is already here! And surprise, no new products are introduced for a change. Dull? Probably not, as you do get another treat. The island exchange now discloses to you who the counterparty is you have traded against. This means that the `counter_party` property of the `OwnTrade` object is now populated. Perhaps interesting to see if you can leverage this information to make your algorithm even more profitable?

```python
class OwnTrade:
    def __init__(self, symbol: Symbol, price: int, quantity: int, counter_party: UserId = None) -> None:
        self.symbol = symbol
        self.price: int = price
        self.quantity: int = quantity
        self.counter_party = counter_party
```

**Solution 1:**


#### Manual Challenge

You’ve been invited to trade on the exchange of the north archipelago for one day only. An exclusive event and perfect opportunity to make some big final profits before the champion is crowned. The penguins have granted you access to their trusted news source: Iceberg. You’ll find all the information you need right there. Be aware that trading these foreign goods comes at a price. The more you trade in one good, the more expensive it will get. This is the final stretch. Make it count!

**Solution 1:**


## Prosperity 3

### Tutorial Round

In the tutorial round there are two tradable goods: `Rainforest Resin` and `Kelp`. While the value of the `Rainforest Resin` has been stable throughout the history of the archipelago, the value of `Kelp` has been going up and down over time.

Position limits for the newly introduced products:

- `RAINFOREST_RESIN`: 50
- `KELP`: 50

⚠️ All algorithms uploaded in the tutorial round will be processed and generate results instantly, so you can experiment with different programs and strategies.

**Solution 1:**


### Round 1

#### Algorithmic Challenge

The first three tradable products are introduced: : `Rainforest Resin` , `Kelp`, and `Squid Ink`. The value of the `Rainforest Resin` has been stable throughout the history of the archipelago, the value of `Kelp` has been going up and down over time, and the value of `Squid Ink` can also swing a bit, but some say there is a pattern to be discovered in its prize progression. All algorithms uploaded in the tutorial round will be processed and generate results instantly, so you can experiment with different programs and strategies.

Position limits for the newly introduced products:

- `RAINFOREST_RESIN`: 50
- `KELP`: 50
- `SQUID_INK`: 50

**Hint:**

Squid Ink can be a very volatile product with price having large swings. Making a two-sided market or carrying position can be risky for such an instrument. However, with large swings comes large reversion. Squid Ink prices show more tendency to revert short term swings in price.

A metric to keep track of the size of deviation/swing from recent average could help in trading profitable positions.

**Solution 1:**


#### Manual Challenge

You get the chance to do a series of trades in some foreign island currencies. The first trade is a conversion of your SeaShells into a foreign currency, the last trade is a conversion from a foreign currency into SeaShells. Everything in between is up to you. Give some thought to what series of trades you would like to do, as there might be an opportunity to walk away with more shells than you arrived with.

**Solution 1:**


### Round 2

#### Algorithmic Challenge

In this second round, you’ll find that everybody on the archipelago loves to picnic. Therefore, in addition to the products from round one, two Picnic Baskets are now available as a tradable good.

`PICNIC_BASKET1` contains three products:

1. Six (6) `CROISSANTS`
2. Three (3) `JAMS`
3. One (1) `DJEMBES`

`PICNIC_BASKET2` contains just two products:

1. Four (4) `CROISSANTS`
2. Two (2) `JAMS`

Aside from the Picnic Baskets, you can now also trade the three products individually on the island exchange.

Position limits for the newly introduced products:

- `CROISSANTS`: 250
- `JAMS`: 350
- `DJEMBES`: 60
- `PICNIC_BASKET1`: 60
- `PICNIC_BASKET2`: 100

**Solution 1:**


#### Manual Challenge

Some shipping containers with valuables inside washed ashore. You get to choose a maximum of two containers to open and receive the valuable contents from. The first container you open is free of charge, but for the second one you will have to pay some SeaShells. Keep in mind that you are not the only one choosing containers and making a claim on its contents. You will have to split the spoils with all others that choose the same container. So, choose carefully.

Here's a breakdown of how your profit from a container will be computed:
Every container has its **treasure multiplier** (up to 90) and number of **inhabitants** (up to 10) that will be choosing that particular container. The container’s total treasure is the product of the **base treasure** (10 000, same for all containers) and the container’s specific treasure multiplier. However, the resulting amount is then divided by the sum of the inhabitants that choose the same container and the percentage of opening this specific container of the total number of times a container has been opened (by all players).

For example, if **5 inhabitants** choose a container, and **this container was chosen** **10% of the total number of times a container has been opened** (by all players), the prize you get from that container will be divided by 15. After the division, **costs for opening a container** apply (if there are any), and profit is what remains.

**Solution 1:**


### Round 3

#### Algorithmic Challenge

Our inhabitants really like volcanic rock. So much even, that they invented a new tradable good, `VOLCANIC ROCK VOUCHERS`. The vouchers will give you the right but not obligation to buy `VOLCANIC ROCK` at a certain price (strike price) at voucher expiry timestamp. These vouchers can be traded as a separate item on the island’s exchange. Of course you will have to pay a premium for these vouchers, but if your strategy is solid as a rock, SeaShells spoils will be waiting for you on the horizon.

There are five Volcanic Rock Vouchers, each with their own **strike price** and **premium.**

**At beginning of Round 1, all the Vouchers have 7 trading days to expire. By end of Round 5, vouchers will have 2 trading days left to expire.**

Position limits for the newly introduced products:

- `VOLCANIC_ROCK`: 400

`VOLCANIC_ROCK_VOUCHER_9500` :

- Position Limit: 200
- Strike Price: 9,500 SeaShells
- Expiration deadline: 7 days (1 round = 1 day) starting from round 1

`VOLCANIC_ROCK_VOUCHER_9750` :

- Position Limit: 200
- Strike Price: 9,750 SeaShells
- Expiration deadline: 7 days (1 round = 1 day) starting from round 1

`VOLCANIC_ROCK_VOUCHER_10000` :

- Position Limit: 200
- Strike Price: 10,000 SeaShells
- Expiration deadline: 7 days (1 round = 1 day) starting from round 1

`VOLCANIC_ROCK_VOUCHER_10250` :

- Position Limit: 200
- Strike Price: 10,250 SeaShells
- Expiration deadline: 7 days (1 round = 1 day) starting from round 1

`VOLCANIC_ROCK_VOUCHER_10500` :

- Position Limit: 200
- Strike Price: 10,500 SeaShells
- Expiration deadline: 7 days (1 round = 1 day) starting from round 1

**Hint for Algorithmic Challenge:**

Hello everyone, hope you're enjoying the VOLCANIC_ROCK vouchers and a variety of trading strategies these new products introduce. While digging for the rock, Archipelago residents found some ancient mathematics sharing insights into VOLCANIC_ROCK voucher trading. Here's what the message with obscure and advanced mathematics read,

Message begins,

I have discovered a strategy which will make ArchiCapital the biggest trading company ever. Here's how my thesis goes,

t: Timestamp
St: Voucher Underlying Price at t
K: Strike
TTE: Remaining Time till expiry at t
Vt: Voucher price of strike K at t

Compute,

m_t = log(K/St)/ sqrt(TTE)
v_t = BlackScholes ImpliedVol(St, Vt, K, TTE)

for each t, plot v_t vs m_t and fit a parabolic curve to filter random noise.

This fitted v_t(m_t) allows me to evaluate opportunities between different strikes. I also call fitted v_t(m_t=0) the base IV and I have identified interesting patterns in timeseries of base IV.

Message ends.

**Solution 1:**


#### Manual Challenge

A big group of Sea Turtles is visiting our shores, bringing with them an opportunity to acquire some top grade `FLIPPERS`. You only have two chances to offer a good price. Each one of the Sea Turtles will accept the lowest bid that is over their reserve price.

The distribution of reserve prices is uniform between 160–200 and 250–320, but none of the Sea Turtles will trade between 200 and 250 due to some ancient superstition.

For your second bid, they also take into account the average of the second bids by other traders in the archipelago. They’ll trade with you when your offer is above the average of all second bids. But if you end up under the average, the probability of a deal decreases rapidly.

To simulate this probability, the PNL obtained from trading with a fish for which your second bid is under the average of all second bids will be scaled by a factor *p*:

$$
p = (\frac{320 – \text{average bid}}{320 – \text{your bid}})^3
$$

You know there’s a constant desire for Flippers on the archipelago. So, at the end of the round, you’ll be able to sell them for 320 SeaShells ****a piece.

Think hard about how you want to set your two bids, place your feet firmly in the sand and brace yourself, because this could get messy.

**Solution 1:**


### Round 4

#### Algorithmic Challenge

In this fourth round of Prosperity a new luxury product is introduced: `MAGNIFICENT MACARONS`. `MAGNIFICENT MACARONS` are a delicacy and their value is dependent on all sorts of observable factors like hours of sun light, sugar prices, shipping costs, in- & export tariffs and suitable storage space. Can you find the right connections to optimize your program?

Position limits for the newly introduced products:

- `MAGNIFICENT_MACARONS`: 75
- Conversion Limit for `MAGNIFICENT_MACARONS` = 10

**Hint - Algo**

It was well understood lore in Archipelago that low sunlight index can impact sugar and MACARON production negatively causing prices to rise due to panic among residents. However, ArchiResearchers have identified existence of a CriticalSunlightIndex (CSI).

If sunlightIndex goes below this CSI with an anticipation to remain under this critical level for a long period of time, sugar and MACARON prices can increase by substantial amount with a strong correlation.

When sunlightIndex is above this CSI, Sugar and MACARON prices tend to trade around their respective fair values and demonstrates market supply-demand dynamics.

Can you find this CSI and use it to trade better than ever and make your island prosper? All the best!

**Solution 1:**


#### Manual Challenge

You’re participating in a brand new game show and have the opportunity to open up a maximum of three suitcases with great prizes in them. The whole archipelago is participating, so you’ll have to share the spoils with everyone choosing the same suitcase. Opening one suitcase is free, but for the second and third one you’ll need to pay to get inside.

Here's a breakdown of how your profit from a suitcase will be computed:
Every suitcase has its **prize multiplier** (up to 100) and number of **inhabitants** (up to 15) that will be choosing that particular suitcase. The suitcase’s total treasure is the product of the **base treasure** (10 000, same for all suitcases) and the suitcase’s specific treasure multiplier. However, the resulting amount is then divided by the sum of the inhabitants that choose the same suitcase and the percentage of opening this specific suitcase of the total number of times a suitcase has been opened (by all players).

For example, if **5 inhabitants** choose a suitcase, and **this suitcase was chosen** **10% of the total number of times a suitcase has been opened** (by all players), the prize you get from that suitcase will be divided by 15. After the division, **costs for opening a suitcase** apply (if there are any), and profit is what remains.

To help you with your decision making, here's the distribution of player's choices from **Round 2** Manual:

![Round_4_Manual_Wiki](image-5.png)

**Additional trading microstructure information:**

1. ConversionObservation (detailed in “[Writing an Algorithm in Python](https://www.notion.so/Writing-an-Algorithm-in-Python-17be8453a09381988c6ed45b1b597049?pvs=21)” under E-learning center) shows quotes of `MAGNIFICENT_MACARONS` offered by the chefs from Pristine Cuisine
2. To purchase 1 unit of `MAGNIFICENT_MACARONS` from Pristine Cuisine, you will purchase at askPrice, pay `TRANSPORT_FEES` and `IMPORT_TARIFF`
3. To sell 1 unit of `MAGNIFICENT_MACARONS` to Pristine Cuisine, you will sell at bidPrice, pay `TRANSPORT_FEES` and `EXPORT_TARIFF`
4. You can ONLY trade with Pristine Cuisine via the conversion request with applicable conditions as mentioned in the wiki
5. For every 1 unit of `MAGNIFICENT_MACARONS` net long position, storage cost of 0.1 Seashells per timestamp will be applied for the duration that position is held. No storage cost applicable to net short position

**Solution 1:**


### Round 5

#### Algorithmic Challenge

The final round of the challenge is already here! And surprise, no new products are introduced for a change. Dull? Probably not, as you do get another treat. The island exchange now discloses to you who the counterparty is you have traded against. This means that the counter_party property of the OwnTrade object is now populated. Perhaps interesting to see if you can leverage this information to make your algorithm even more profitable?

```python
class OwnTrade:
    def __init__(self, symbol: Symbol, price: int, quantity: int, counter_party: UserId = None) -> None:
        self.symbol = symbol
        self.price: int = price
        self.quantity: int = quantity
        self.counter_party = counter_party
```

**Solution 1:**


#### Manual Challenge

You’ve been invited to trade on the exchange of the West Archipelago for one day only. An exclusive event and perfect opportunity to make some big final profits before the champion is crowned. Benny the Bull has granted you access to his most trusted news source: Goldberg. You’ll find all the information you need right there. Be aware that trading these foreign goods comes at a price. The more you trade in one good, the more expensive it will get. This is the final stretch. Make it count!

**Solution 1:**

