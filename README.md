# The Solidity Contract-Oriented Programming Language
You can talk to us on [![solidity at https://gitter.im/ethereum/solidity](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/ethereum/solidity?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge). Questions, feedback, and suggestions are welcome!

Solidity is a statically typed, contract-oriented, high-level language for implementing smart contracts on the Ethereum platform.

## Table of Contents

- [Build and Install](#build-and-install)
- [Example](#example)
- [Documentation](#documentation)
- [Development](#development)
- [Maintainers](#maintainers)
- [License](#license)
- [Security](#security)


## Build and Install Manually for Linux

First install Boost lib manually
```bash
 wget https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2
 tar -zxvf boost_1_66_0.tar.bz2 && cd boost_1_66_0.tar.bz2
 ./bootstrap.sh --prefix=/usr/local
 ./b2 install
```

Second, install z3
```bash
apt-get install -y z3
```

Third, install the rest dependencies
```bash
  cd scripts && ./install_deps.sh
```
Finally, build the project. Note: this one will install binaries solc at usr/local/bin
```bash
  mkdir build
  cd scripts && ./build.sh
```

## Example

A "Hello World" program in Solidity is of even less use than in other languages, but still:

```solidity
pragma solidity >=0.6.0 <0.8.0;

contract HelloWorld {
  function helloWorld() external pure returns (string memory) {
    return "Hello, World!";
  }
}
```

To get started with Solidity, you can use [Remix](https://remix.ethereum.org/), which is a
browser-based IDE. Here are some example contracts:

1. [Voting](https://docs.soliditylang.org/en/latest/solidity-by-example.html#voting)
2. [Blind Auction](https://docs.soliditylang.org/en/latest/solidity-by-example.html#blind-auction)
3. [Safe remote purchase](https://docs.soliditylang.org/en/latest/solidity-by-example.html#safe-remote-purchase)
4. [Micropayment Channel](https://docs.soliditylang.org/en/latest/solidity-by-example.html#micropayment-channel)

## Documentation

The Solidity documentation is hosted at [Read the docs](https://docs.soliditylang.org).

## Development

Solidity is still under development. Contributions are always welcome!
Please follow the
[Developers Guide](https://docs.soliditylang.org/en/latest/contributing.html)
if you want to help.

You can find our current feature and bug priorities for forthcoming
releases [in the projects section](https://github.com/ethereum/solidity/projects).

## Maintainers
* [@axic](https://github.com/axic)
* [@chriseth](https://github.com/chriseth)

## License
Solidity is licensed under [GNU General Public License v3.0](LICENSE.txt).

Some third-party code has its [own licensing terms](cmake/templates/license.h.in).

## Security

The security policy may be [found here](SECURITY.md).
