## Simulated Market Data Protocol (SMD)
SMD is a simplified protocol that allows trading applications to subscribe and receive market data from the simulated exchange over TCP/IP protocol. 
## Outbound Messages
Outbound messages are sent to the exchange.

#### Subscribe Market Data
The exchange allows subscribing to real-time data. To subscribe to topics, send a message with the following format:

`{"op": "subscribe", "args": [<SubscriptionTopic>]}`

where `args` is a list of comma concatenated strings. See example below.

#### Available Topics
- Level2 Order Book updates: `orderBookL2`
- Trades: `trade`

#### Example
If a client application wants to subscribe to level2 order book updates and trades for instrument `0`, she would send the following message:
 `{"op": "subscribe", "args": [orderBookL2:0, trade:0]}`


## Inbound Messages
Inbound messages are received from the exchange.

#### Add Order

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `E`            | 
|  `order_id`     | `int`        |                |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `timestamp`    | `int`        |                |

Buy or sell orders are identified by side as per below.

| Side            | Explanation  | 
| :-------------  | ----------:  | 
|  `S`            | `Sell`       |
|  `B`            | `Buy`        | 

#### Remove Order
| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `X`            |
|  `order_id`     | `int`        |                |
|  `timestamp`    | `int`        |                |

#### Modify Order
| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `M`            |
|  `order_id`     | `int`        |                |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `timestamp`    | `int`        |                |

#### Order Executed
An Order Executed message indicates that an order has been executed in part or fully. The match number is the order_id identifier for the trade.

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `E`            |
|  `order_id`     | `int`        |                |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `timestamp`    | `int`        |                |
|  `liquidity`    | `string`     | `A`  or `R`    |

Side of the order execution is based on the aggressing, i.e. the side that forced the trade to happen, order.