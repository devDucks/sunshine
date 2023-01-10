# sunshine

Sunshine is an open source protocol to drive an electronic camera rotator for astrophotography.
You can find here the firmware that can be flashed on Arduino that implements the protocol.

## Protocol spec
TODO

## Development
This firmware has 0 dependencies on external Arduino libraries.
To develop the firmware just clone the repo and use your favorite text editor (arduino ide is probably the best for this code)

## Tests
This repo contains also a test suite that should be used to test the firmware is behaving properly
once flashed.
The tests are writtten in `Python` and `pipenv` is used to manage the virtualenv, to run the tests follow these steps:
 - plug your Arduino into your computer
 - flash the formware via arduino IDE or avrdude
 - run `make tests`

Since these are e2e tests a real Arduino board running the firmware is needed
