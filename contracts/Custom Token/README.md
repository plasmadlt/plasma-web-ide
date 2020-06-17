

# Create token in production

* Activate the production account in official wallet PlasmaPay on the dashboard: https://app.plasmapay.com/dashboard and decrypt your private keys (key icon on the wallet). Attention: you can create only one account in PlasmaPay and the account's name will be your contract name.
* Choice producer from the network from http://plasmadlt.com/monitor
* Setup dApp https://app.plasmapay.com/dashboard and get Auoth for front-end


## Import wallet  

```
sol --url http://comeric.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999  wallet import --private-key 5JF********************************
```
* unlock wallet

```
sol wallet unlock --password 5JF********************************
```

## Buckle you token with ion contracts
```
sol set contract vlad.issuer  Users/contracts/ion.token -p accountname@active
```

## Deploy contract in production
```
sol --url http://nothtrust.liberty.plasmadlt.com set contract accountname /Users/contracts/ion.token -p accountname@active
Reading WASM from Users/plasma//build/contracts/ion.token/ion.token.wasm...
Publishing contract...
executed transaction: Wcsc********************************  10048 bytes  4014 us
#           ion <= ion::setcode                 {"account":"accountname","vmtype":0,"vmversion":0,"code":"00sd********************************...
#           ion <= ion::setabi                  {"account":"accountname","abi":"0c696********************************...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
## Create Supply  

```
sol --url http://nothtrust.liberty.plasmadlt.com push action accountname create '{"issuer": "accountname", "maximum_supply": "1000000.000000 PBV"}' -p accountname@active


executed transaction: eef5b********************************  120 bytes  729 us
#  accountname <= accountname::create         {"issuer":"accountname","maximum_supply":"1000000.000000 PBV"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Check supply

```
 sol --url http://nothtrust.liberty.plasmadlt.com get currency stats accountname PBV


{
  "PBV": {
    "supply": "0.000000 PBV",
    "max_supply": "1000000.000000 PBV",
    "issuer": "accountname"
  }
```

## Allow the system wrap contract - call the actions of our token (BUY/SELL) with inter rate token contract
```
sol set account permission accountname active '{"keys": [{"key": "PLASMA5j18E7JMG4y5nbqyKfqYy6bpwfKnY4hQqFpvRSBTiKuUGd9KJG", "weight": 1}], "threshold": 1, "accounts": [
{"permission": {"actor": "simple.token", "permission": "ion.code"}, "weight": 1}
], "waits": []}' -p accountname@active
```
## Set the token rate against PLASMA
* token  PBV = 2 / (10 ^ 4),  1 PBV = 0,0002 PLASMA
```
sol push action simple.token updaterate '["accountname", "PBV", "PLASMA", "2", "4"]' -p accountname@active
```

# TEST

* Create new account for test users account in official wallet PlasmaPay on the dashboard: https://app.plasmapay.com/dashboard and decrypt your private keys (key icon on the wallet).

## Issue tokens to the recipient's account
```
sol push action accountname1 issue '{"to":"accountname2", "quantity":"100.000000000000000000 PBV", "memo": "test"}' -p accountname@active
```

## Check the balance - is everything ok
```
sol get table accountname1 accountname2 accounts
```

## Buy new  tokens
```
sol push action accountname1 buytokens '["accountname2", "accountname1", "10000.000000  PBV"]' -p accountname2@active
```

## Check balance
```
sol get table accountname1 accountname2 accounts
```
