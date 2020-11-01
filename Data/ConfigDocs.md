# Config Documentation

This is the documentation for Atomic's config
***
# Authentication

`ROBLOSECURITY [characters]`

ROBLOSECURITY is roblox's authentication token, Atomic needs your roblosecurity cookie in order to log into your account and begin trading  
To get your Roblosecurity cookie open [roblox.com](https://roblox.com) and on the top left of your browser you should see the lock icon, click that -> Cookies -> roblox.com -> ROBLOSECURITY double click on the content then copy.


# System

`operating_system [characters]`

What operating system you're using, Atomic only has support for windows & linux, if you're hosting Atomic on a virtual private server then make sure to change this to linux.  

# General

`update_values [number]`

How long to wait before updating item values, in minutes.

`not_to_trade [list]`

Have an item that you do not want the bot to trade? Add it here, separate items with a comma.

`trade_by [characters]`

If you want to trade by rap then set it to `rap`, otherwise leave it at `value`

`trade_projected_at_value [true/false]`

If you're being offered a projected item or you're offering one, setting this to true will trade it at its actual value, if you have trade_by set to `rap`, then it'll still trade by value.

`max_item_value [number]`

Atomic will not be trading any items that exceed this value, set it to an obnoxiously large value if you want it to trade items of any value.

`minimum_profit [number]`

The minimum amount of profit Atomic should try to aim for

`maximum_item_to_trade [characters]`

The maximum amount of items that Atomic will be able to offer/request, you can change this if you wish to upgrade/downgrade  
For example, if set to 4/1, it'll be able to offer up to 4 items and can only request 1, if set to 3/3 it'll only be able to offer up to 3 items and request 3 items.

# Inbound

`evaluate_inbound_trades [true/false]`

If set to true, Atomic will accept/decline inbound trades, set this to false if you don't want Atomic to touch your inbound trades

`check_inbound_trades [true/false]`

I know this is named almost exactly like evaluate_inbound_trades, but this is a timer of how long to wait before checking your inbound trades, if evaluate_inbound_trades is false this does nothing

`ignore_trades_above [number]`

Ignores any inbound trades with a sum value higher than this

`counter_bad_trades [true/false]`

If set to true, Atomic will start countering bad trades with a trade it thinks is better.

