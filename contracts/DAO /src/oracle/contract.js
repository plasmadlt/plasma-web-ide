const {Api, JsonRpc} = require('@plasma/plasmajs');
const networkConfig = require('../config/plasma.network.config');
const testConfig = require('../config/plasma.test.config');
const JsSignatureProvider = require('@plasma/plasmajs/dist/plasmajs-jssig').default;
const fetch = require('node-fetch');
const {TextEncoder, TextDecoder} = require('util');
const loggerMaker = require('../config/logger.js');
const logger = loggerMaker.getLogger('plasma-oracles');

const rpc = new JsonRpc(networkConfig.httpEndpoint, {fetch});
const signatureProvider = new JsSignatureProvider([testConfig.testKey]);
const api = new Api({rpc, signatureProvider, textDecoder: new TextDecoder(), textEncoder: new TextEncoder()});

const BigNumber = require('bignumber.js');
const Formatter = require('plasmajs/lib/format');

const reward = async () => {
    var next_user = new BigNumber(0);
    while(true) {

        const res = await rpc.get_table_rows( {
            json : true,
            code : testConfig.testAccount,
            scope : testConfig.testAccount,
            table : 'test.owner',
            limit: 1,
            reverse : false,
            lower_bound : next_user.toString(),
        });

        if(typeof(res.rows[0]) == 'undefined') {
            break;
        }

        const test_owner = res.rows[0].owner;
        console.log("test payout -> ", test_owner);

        try {
            await api.transact({
                actions: [{
                    account: testConfig.testContract,
                    name: 'reward',
                    authorization: [{ actor: testConfig.testAccount, permission: 'active' }],
                    data: { user: test_owner } ,
                }]
            },
            {
                blocksBehind: 3,
                expireSeconds: 30,
            });
        }
        catch (e) {
            console.error(e);
            continue;
        }

        next_user = new BigNumber(Formatter.encodeName(res.rows[0].owner, false));
        next_user = next_user.plus(1);
    }
};

module.exports = {
    reward
};
