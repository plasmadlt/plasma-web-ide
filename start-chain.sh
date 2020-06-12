#!/bin/bash

plk --verbose-http-errors --http-validate-host=0 --wallet-dir /root/ion-wallet &
sol wallet unlock --password < /root/wallet-password
ionode --config ~/config.ini --genesis-json ~/genesis.json --data-dir ~/data
