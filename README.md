# Communication Protocol Lab

## Run the Proteus simulation

1. Open the `proteus` folder.
2. Open this Proteus project:

   ```text
   proteus\task.pdsprj
   ```

3. Double-click the **ATmega32** in the schematic.
4. Set its **Program File** to:

   ```text
   atmega32\atmega32\Debug\rebuilt\atmega32-built.elf
   ```

5. Set the ATmega32 clock frequency to:

   ```text
   1 MHz
   ```

6. Start the simulation.

The Arduino sends the date and time through SPI. The ATmega32 receives it and
displays the result through its USART serial terminal at **9600 baud**.

## Important project files

```text
Communication-Protocol-Lab\
├── atmega32\
│   └── atmega32\
│       ├── Debug\rebuilt\atmega32-built.elf  # ATmega32 Proteus program file
│       └── main.c                            # ATmega32 slave application
├── master_main\
│   └── Master-ARDUINO\
│       └── Master-ARDUINO.ino                 # Arduino master application
├── slave_main\
│   └── main.c                                 # Copy of the slave application
└── proteus\
    └── task.pdsprj                            # Proteus project
```

## Serial terminal

Connect the ATmega32 `PD1/TXD` pin to the serial terminal RX pin in Proteus.
Use these serial settings:

```text
Baud rate: 9600
Data:      8 bits
Parity:    None
Stop bits: 1
```

## If the ELF file is missing

Build the ATmega32 project first. The source code and drivers are located in:

```text
atmega32\atmega32\
```

The required MCU is **ATmega32**, and the firmware uses an **F_CPU of 1 MHz**.
