# Get first available Arduino port
PORT = $(firstword /dev/ttyUSB*)

# Serial baudrate
BAUDRATE = 9600

# Arduino model
MODEL =arduino:avr:uno
#pro:cpu=8MHzatmega328

# Compiler
ACLI = arduino-cli
AFLAGS_C = --output-dir build/ --libraries games --build-property "compiler.cpp.extra_flags=-Isrc/games -Isrc -Isrc/apps -Wall"
AFLAGS_U =

MAIN = ./ArduinoConsole.ino

.PHONY: all compile upload monitor clean

all: clean compile

compile:
	@echo "-- Compiling..."
	$(ACLI) compile $(AFLAGS_C) -b $(MODEL) $(MAIN)

upload: compile
	@echo "-- Flashing..."
	$(ACLI) upload $(AFLAGS_U) -p $(PORT) -b $(MODEL)

monitor:
	@echo "-- Monitoring..."
	$(ACLI) monitor -p $(PORT) --config baudrate=$(BAUDRATE) -b $(MODEL)

clean:
	@echo "-- Cleaning..."
	@rm -rf build
