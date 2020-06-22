

# Create token in production

* Activate the production account in official wallet PlasmaPay on the dashboard: https://app.plasmapay.com/dashboard and decrypt your private keys (key icon on the wallet). Attention: you can create only one account in PlasmaPay and the account's name will be your contract name.
* Choice producer from the network from http://plasmadlt.com/monitor
* Setup dApp https://app.plasmapay.com/dashboard and get Auoth for front-end


## Import wallet  

```
sol --url  --wallet-url   wallet import --private-key 5JF********************************
```
* unlock wallet

```
sol --url  wallet unlock --password 5JF********************************
```

## Buckle you token with ion contracts
```
sol  --url  --wallet-url  set contract accountname  Users/contracts/ion.token -p accountname@active
```

## Deploy contract in production
```
sol --url  --wallet-url  set contract accountname /Users/contracts/ion.token -p accountname@active
Reading WASM from Users/plasma//build/contracts/ion.token/ion.token.wasm...
Publishing contract...
executed transaction: Wcsc********************************  10048 bytes  4014 us
#           ion <= ion::setcode                 {"account":"accountname","vmtype":0,"vmversion":0,"code":"00sd********************************...
#           ion <= ion::setabi                  {"account":"accountname","abi":"0c696********************************...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
## Create Supply  

```
sol --url  --wallet-url push action accountname create '{"issuer": "accountname", "maximum_supply": "1000000.000000 TEST"}' -p accountname@active


executed transaction: eef5b********************************  120 bytes  729 us
#  accountname <= accountname::create         {"issuer":"accountname","maximum_supply":"1000000.000000 PBV"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Check supply

```
 sol --url  --wallet-url  get currency stats accountname TEST


{
  "TEST": {
    "supply": "0.000000 TEST",
    "max_supply": "1000000.000000 TEST",
    "issuer": "accountname"
  }
```

## Allow the system wrap contract - call the actions of our token (BUY/SELL) with inter rate token contract
```
sol set account permission accountname active '{"keys": [{"key": "PLASMA5j18E7JMG4y5nbqyKfqYy6bpwfKnY4hQqFpvRSBTiKuUGd9KJG", "weight": 1}], "threshold": 1, "accounts": [
{"permission": {"actor": "simple.token", "permission": "ion.code"}, "weight": 1}
], "waits": []}' -p accountname@active
```
# Set the token rate against PLASMA
* token  TEST = 2 / (10 ^ 4),  1 TEST = 0,0002 PLASMA
```
sol push action simple.token updaterate '["accountname", "TEST", "PLASMA", "2", "4"]' -p accountname@active
```

# TEST

* Create new account for test users account in official wallet PlasmaPay on the dashboard: https://app.plasmapay.com/dashboard and decrypt your private keys (key icon on the wallet).

## Issue tokens to the recipient's account
```
sol push action accountname1 issue '{"to":"accountname2", "quantity":"100.000000000000000000 TEST", "memo": "test"}' -p accountname@active
```

## Check the balance - is everything ok
```
sol get table accountname1 accountname2 accounts
```

## Buy new  tokens
```
sol push action accountname1 buytokens '["accountname2", "accountname1", "10000.000000  TEST"]' -p accountname2@active
```

## Check balance
```
sol get table accountname1 accountname2 accounts
```
