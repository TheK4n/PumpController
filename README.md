<h1 align="center">PumpController</h1>

<p align="center">
  <a href="https://github.com/TheK4n">
    <img src="https://img.shields.io/github/followers/TheK4n?label=Follow&style=social">
  </a>
  <a href="https://github.com/TheK4n/PumpController">
    <img src="https://img.shields.io/github/stars/TheK4n/PumpController?style=social">
  </a>
</p>

## Content
* [Project description](#chapter-0)
* [Usage](#chapter-1)
* [Hardware](#chapter-2)
* [Libraries](#chapter-3)


<a id="chapter-0"></a>
## Project description

Arduino Controller for water pump



<a id="chapter-1"></a>
## Usage

1. Turn to change lower threshold
2. Hold and turn to change upper threshold
3. Hold to save thresholds to EEPROM
4. Click to display current pressure

### Scheme:

[![Scheme](schemes/PumpController.png)](schemes/PumpController.png)


<a id="chapter-2"></a>
## Hardware

| Name                  |  Model                       |
| --------------------- | ---------------------------: |
| Controller            | [Arduino Nano ATmega328]()   |
| Encoder               | [EC11]()                     |
| Display               | [TM1637]()                   |
| Relay                 | [SSR-40DA]()                 |
| Pressure sensor       | [EBOWAN]()                   |


<a id="chapter-3"></a>
## Libraries

* [**GyverTM1637**](https://github.com/GyverLibs/GyverTM1637)
* [**EncButton**](https://github.com/GyverLibs/EncButton)


## ToDO
* create board on easyeda
* LGT8F328P
* average pressure


<h1 align="center"><a href="#top">▲</a></h1>
