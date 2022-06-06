# CXXMicroService
A C++ Library that give microservice framework ( Server / Client ) 

[![codecov](https://codecov.io/gh/ZigRazor/CXXMicroService/branch/main/graph/badge.svg?token=773AQ2H9RQ)](https://codecov.io/gh/ZigRazor/CXXMicroService)
[![CodeFactor](https://www.codefactor.io/repository/github/zigrazor/CXXMicroService/badge)](https://www.codefactor.io/repository/github/zigrazor/CXXMicroService)

[![GitHub license](https://img.shields.io/github/license/ZigRazor/CXXMicroService.svg)](https://github.com/ZigRazor/CXXMicroService/blob/master/LICENSE) [![GitHub release](https://img.shields.io/github/release/ZigRazor/CXXMicroService.svg)](https://GitHub.com/ZigRazor/CXXMicroService/releases/)

![LGTM Alerts](https://img.shields.io/lgtm/alerts/github/ZigRazor/CXXMicroService?style=plastic)
![LGTM Grade](https://img.shields.io/lgtm/grade/cpp/github/ZigRazor/CXXMicroService?style=plastic)

[![Generic badge](https://img.shields.io/badge/Required-G++7.3.0-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/required-C++17-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/Required-CMake3.9-Green.svg)](https://shields.io/)

[![Generic badge](https://img.shields.io/badge/Build-Passed-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/UnitTest-Passed-Green.svg)](https://shields.io/)

## Introduction
**CXXMicroService** is a **C++** library, that manages MicroServices, upon different Framework ( actually only 0mq is implemented). 

## We are Looking for...

**We are looking for:**

- **Site Developer** for the development of the CXXMicroService site ( for the moment on GitHub Page );
- **Developers and Committers**, also at *first experience*, we will guide you step by step to the open-source world!

If you are interested, please contact us at zigrazor@gmail.com or contribute to this project. We are waiting for you!

## Roadmap

| Completed | Description | Date of Completition |
| :-------: | :---------- | :-------------------: |
| :heavy_check_mark: | First Commit | May 2, 2022 |
| :heavy_check_mark: | Introduce the basic Framework | May 24, 2022 |
| :memo: | Introduction of more complete Examples | TBD |
| :memo: | Introduction of Orchestrator | TBD |
| :memo: | Introduction of Unit Test Framework | TBD |
| :heavy_check_mark: | Introduction of basic CI/CD | Jun 6, 2022 |
| :memo: | Advanced CI/CD | TBD |
| :memo: | First Beta Release 0.0.1 | TBD |
| :memo: | Introduce HTTP interface | TBD |
| :memo: | Beta Release 0.0.2 | TBD |
| :memo: | Basic Logger Enhancement | TBD |
| :memo: | Beta Release 0.0.3 | TBD |
| :memo: | Packaging on different Operating System | TBD |
| :memo: | Beta Release 0.0.4 | TBD |
| :memo: | Freeze of code for First Release | TBD |
| :memo: | First Stable Release 1.0.0 | TBD |
| :memo: | Multi-Threading Services | TBD |
| :memo: | Beta Release 1.0.1 | TBD |
| :memo: | Thread-Pool for services requests | TBD |
| :memo: | Release 1.1.0 | TBD |
| :memo: | Code Standard Review | TBD |
| :memo: | Beta Release 1.1.1 | TBD |
| :memo: | TBD | TBD |

## Table of Contents

- [CXXMicroService](#cxxmicroservice)
  - [Introduction](#introduction)
  - [We are Looking for...](#we-are-looking-for)
  - [Roadmap](#roadmap)
  - [Table of Contents](#table-of-contents)
  - [Building](#building)
    - [Download the Sources](#download-the-sources)
    - [Building From Sources](#building-from-sources)
  - [Requirements](#requirements)
  - [How to use](#how-to-use)
  - [Example](#example)
  - [How to contribute](#how-to-contribute)
  - [Site](#site)
  - [Contact](#contact)
  - [Support](#support)
  - [References](#references)
  - [Contributors](#contributors)
  - [Other Details](#other-details)
  - [Author](#author)


## Building 

### Download the Sources

You can download the sources with git commands:

``` bash 
git clone https://github.com/ZigRazor/CXXMicroService.git
git submodule init
git submodule update
```

### Building From Sources


You can build from source the library using CMake.
The CMake will compile all the libraries needed to compile the CXXMicroService Library.

You can execute the following command from the project root directory:

``` bash 
mkdir build
cd build
cmake ..
make 
```

## Requirements

The minimun C++ standard required is **C++17** and a G++ compiler version greater than 7.3.0.
Are also required [OpenSSL library](https://www.openssl.org/)## Requerements to build LOG4CXX

To compile **LOG4CXX** are needed the following package:

``` bash 
sudo apt-get install build-essential libapr1-dev libaprutil1-dev gzip zip
```

## How to use

The use of the library is very simple, **just link the generated Dynamic Library to your executable**

## Example

Work in Progess


## How to contribute

[![GitHub contributors](https://img.shields.io/github/contributors/ZigRazor/CXXMicroService.svg)](https://GitHub.com/ZigRazor/CXXMicroService/graphs/contributors/)
If you want give your support you can create a ***pull request***   [![GitHub pull-requests](https://img.shields.io/github/issues-pr/ZigRazor/CXXMicroService.svg)](https://GitHub.com/ZigRazor/CXXMicroService/pull/) or report an ***issue***  [![GitHub issues](https://img.shields.io/github/issues/ZigRazor/CXXMicroService.svg)](https://GitHub.com/ZigRazor/CXXMicroService/issues/).
If you want to change the code, or fix issue, or implement a new feature please read our [CONTRIBUTING Guide](https://github.com/ZigRazor/CXXMicroService/blob/master/CONTRIBUTING.md)

If you want to disscuss new feature or you have any question or suggestion about library please open a [Discussion](https://github.com/ZigRazor/CXXMicroService/discussions) or simply chat on [![Join the chat at https://gitter.im/CXXMicroService-Community/community](https://badges.gitter.im/CXXMicroService-Community/community.svg)](https://gitter.im/CXXMicroService-Community/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Site

[CXXMicroService Site](https://zigrazor.github.io/CXXMicroService/)

## Contact

E-Mail : zigrazor@gmail.com

[![Join the chat at https://gitter.im/CXXMicroService-Community/community](https://badges.gitter.im/CXXMicroService-Community/community.svg)](https://gitter.im/CXXMicroService-Community/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[GitHub Profile](https://github.com/ZigRazor) ![Profile views](https://gpvc.arturio.dev/ZigRazor)

![ZigRazor's github stats](https://github-readme-stats.vercel.app/api?username=ZigRazor&show_icons=true&title_color=fff&icon_color=79ff97&text_color=9f9f9f&bg_color=151515)

## Support

To support me just add ***Star*** the project  [![GitHub stars](https://img.shields.io/github/stars/ZigRazor/CXXMicroService.svg?style=social&label=Star&maxAge=2592000)](https://GitHub.com/ZigRazor/CXXMicroService/stargazers/) or ***follow me***  [![GitHub followers](https://img.shields.io/github/followers/ZigRazor.svg?style=social&label=Follow&maxAge=2592000)](https://github.com/ZigRazor?tab=followers)

To get updated ***watch*** the project  [![GitHub watchers](https://img.shields.io/github/watchers/ZigRazor/CXXMicroService.svg?style=social&label=Watch&maxAge=2592000)](https://GitHub.com/ZigRazor/CXXMicroService/watchers/)

## References

We are referenced by:

- [awesome-cpp](https://github.com/fffaraz/awesome-cpp)

## Contributors

Thank you to all the people who have already contributed to CXXMicroService!

[![Contributors](https://contrib.rocks/image?repo=zigrazor/CXXMicroService)](https://github.com/ZigRazor/CXXMicroService/graphs/contributors) 


## Other Details

View the [Estimated Value of the Project](https://www.openhub.net/p/CXXMicroService/estimated_cost)

## Author

| [<img src="https://avatars0.githubusercontent.com/u/6591180?s=460&v=4" width="100"><br><sub>@ZigRazor</sub>](https://github.com/ZigRazor) |
|:----:|
