const testContract = require('../shared/test-contract');
const util = require('util');
const sleep = util.promisify(setTimeout);
const loggerMaker = require('../config/logger.js');
const logger = loggerMaker.getLogger('test-oracle');
const sleepInterval = 1000 * 60 * 60 * 24; //  1 day

class TESTOracle {
  constructor() {
    this.normalSleepInterval = sleepInterval;
    this.errorSleepInterval = sleepInterval;
  }

  async prepare() {
    logger.info('service started');
  }

  async iterate() {
    logger.info('iteration started');
    await testContract.reward();
    logger.info('iteration finished');
    return {nonStop: false};
  };

  async run() {
    try {
      await this.prepare();
    } catch (e) {
      logger.error(e);
      process.exit(-1);
    }

    while (true) {
      try {
        const {nonStop} = await this.iterate();
        if (!nonStop) {
          await sleep(this.normalSleepInterval);
        }
      } catch (e) {
        logger.error(e);
        await sleep(this.errorSleepInterval);
      }
    }
  }
}

const testOracle = new TESTOracle();
module.export = testOracle.run();
