# PlasmaDLT quickstart Web IDE for decentralized applications ![PlasmaDLT Latest](https://img.shields.io/badge/PLasmaDLT-latest-blue.svg)

[![Software License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](./LICENSE)

PlasmaDLT Quickstart Web IDE lets developers start building full-stack PlasmaDLT applications in a matter of minutes. 

Powered by Gitpod.io and Docker, it provides developers with a personal single-node PlasmaDLT blockchain for development and testing purposes without a need of going through advanced local environment setup. It also includes an example application with a smart contract and web frontend, connected to the blockchain. Developers can also use PlasmaDLT tools like sol and  ion.cdt straight out of the box. This project requires zero installation on the user's machine. All code is stored and managed on the developer's personal GitHub account, with the changes saved automatically.

We built this project with ease of use and simplicity in mind. It can be used by new developers trying out or learning PlasmaDLT, as well as advanced developers and teams. It is especially useful in the environments where users don't have full control over the systems they work on (universities, banks, government organizations, etc.) or when they have lower-than-required computer specs to run PlasmaDLT locally.

We hope you will find this project useful and welcome feedback on future improvements.

# Setup

1. Fork this repo to your personal GitHub account so that you can save your work into your personal Github account.

2. Point your browser to the following URL https://gitpod.io/#https://github.com/your-github-account/plasma-web-ide to start the IDE. You will be automatically prompted to create a Gitpod account (all types of Gitpod accounts (including free) will work). You can also choose to provide multiple developers push access to your personal github fork of this repo to collaborate with them (one developer working on the smart contract (C++) while the other working on the front-end decentralized application (PlasmaJS), etc.). Each such developer sharing access to the forked repo will get their own copy of the PlasmaDLT blockchain components to enable independent development.

You can test drive the system by accessing the IDE at https://gitpod.io/#https://github.com/plasmadlt/plasma-web-ide (however you will not be able to save your work into the plasmadlt/plasma-web-ide Github repository)

# Instructions

The following instructions assume that the Web IDE was started successfully (see [Setup](#setup)).

## Opening a terminal

To open a terminal, use the Terminal drop-down menu in the IDE user interface.

## Building sample contract

The source code for the sample smartcontract is at `contracts/talk/talk.cpp` within the IDE. To compile the contract, run this in a terminal:

```
cd contracts/talk/
ion-cpp talk.cpp

```

This will produce `talk.abi` and `talk.wasm`.

## Installing the contract

Run this in a terminal:

Generate contract's account on behalf of ion account (ion's account key is already in the wallet). 

```
sol create account ion talk PLASMA5sJ5yg8H4sZWN5sdcnUc8dV7JRaTwYuFRrNUmugf9ojSEYLggr

```

You can ensure that the key is in the wallet with the following command.

```
sol wallet keys

```

Deploy contract into the just created account

```
sol set contract talk ./

```

## Creating users and using the contract

Run this in a terminal:
```
sol create account ion bob PLASMA5sJ5yg8H4sZWN5sdcnUc8dV7JRaTwYuFRrNUmugf9ojSEYLggr
sol create account ion jane PLASMA5sJ5yg8H4sZWN5sdcnUc8dV7JRaTwYuFRrNUmugf9ojSEYLggr
sol push action talk post '[1000, 0, bob, "This is a new post"]' -p bob
sol push action talk post '[2000, 0, jane, "This is my first post"]' -p jane
sol push action talk post '[1001, 2000, bob, "Replying to your post"]' -p bob

```

## Listing the messages

Run this in a terminal:
```
sol get table talk '' message

```

## Viewing the front-end decentralized web app (PlasmaJS):

The source code for the React WebApp is at `webapp/src/index.tsx` within the IDE. To preview the WebApp run this in a terminal:

```
gp preview $(gp url 8000)

```

## Resetting the chain

To remove the existing chain and create another:

* Switch to the terminal running `ionode`
* Press `ctrl+c` to stop it
* Run the following

```
rm -rf ~/data/*
ionode --config ~/config.ini --genesis-json ~/genesis.json --data-dir ~/data

```

Note: if the web app is currently open, then it will cause errors like the following. You may ignore them:

```
FC Exception encountered while processing chain.get_table_rows
```

## Contributing

[Contributing Guide](./CONTRIBUTING.md)

[Code of Conduct](./CONTRIBUTING.md#conduct)

## License

[MIT](./LICENSE)

## Important

See [LICENSE](LICENSE) for copyright and license terms.

All repositories and other materials are provided subject to the terms of this [IMPORTANT](important.md) notice and you must familiarize yourself with its terms.  The notice contains important information, limitations and restrictions relating to our software, publications, trademarks, third-party resources, and forward-looking statements.  By accessing any of our repositories and other materials, you accept and agree to the terms of the notice.
