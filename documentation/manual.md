# Verminator Wasp Drone Manual

## Setting Up a Development Environment
To configure your system for development purposes, traverse to the desired directory to store this projet. Then clone the repository:
```
    cd path/to/desired/location
    git clone git@github.com:nguyent11/verm-wasp-drone.git
    cd verm-wasp-drone
```

This project links other repositories as submodules. To clone the submodules, run the following command:
```
    git submodule update --init --recursive
```

## Hardware
This manual mainly covers instructions regarding the operation of the hardware. For more information on hardware implementations, take a look at the [Detailed Design Specification](https://github.com/nguyent11/verm-wasp-drone/blob/main/documentation/detailed_design_specification_r2.pdf) document for design and implementation details.

### Connecting the Drone to Ground Station Software
The drone's flight controller is loaded with PX4 Autopilot Firmware. QGroundControl (QGC) is a ground station software that is fully compatible with PX4 drones. To connect the drone to QGC, simply turn power on the drone. The connection should occur automatically.

If the connection is not automatic, calibrating the telemetry radios will be necessary. Refer to RFDesign RFD 900x-US [documentation](https://files.rfdesign.com.au/docs/) on how to calibrate a pair of telemetry modems.

### Uploading Custom Firmware to the Drone's Flight Controller
PX4 Autopilot makes it simple to compile new firmware modifications. This drone uses the CubePilot Cube Orange+ flight controller. To target this platform, use:
```
    make cubepilot_cubeorangeplus
```

After compiling the new firmware, firmware can be uploaded to the drone through QGroundControl. Connect the flight controller to the ground station computer using a Micro USB to USB cable. Under vehicle settings and under firmware, a custom install can be selected. When performing a custom install, select the modified firmware desired, then flash the firmware. Refer to [PX4 developer's documentation](https://docs.px4.io/main/en/development/development.html) on how to build PX4 software or setup a development environment for more information.

If you are not developing for the drone, but for whatever reason, lost the firmware for the flight controller, the firmware can be rebuilt from this repository. Traverse starting from the root of the repository and going to src/drone_firmware/ and enter the following command:
```
    bash build.sh
```

### Preparing for Flight
Before flight can begin, a preflight check is required. QGroundControl will notify the user of required tests before the drone can be armed. Refer to [PX4](https://docs.px4.io/main/en/advanced_config/prearm_arm_disarm.html) and [QGC](https://docs.qgroundcontrol.com/Stable_V4.3/en/qgc-user-guide/fly_view/fly_view.html) documentation on information regarding pre-flight checks and ground control software.

It may also be useful for the user to set up their RC transmitter and controller with predefiend switch assignments. Instructions on how to do this vary by manufacturer. Refer to your RC controller's manual on more information on how to do this. To bind RC switches in QGroundControl, they can be found on the radio and actuator sections of Vehicle Setup. The Vermiantor Team recommends setting a switch for arming/disarming the drone and second switch for toggling the sprayer.

Before flying, attaching the drones propellers are necessary. The motors spin in one of two directions, so ensuring that the propellers are located in the correct orientation is required. The propellers will have a lock symbol with an arrow pointed in a certain direction. The silver nut motors spin CCW. The black nut motors spin CW. Ensure that the propellers are attached to the correct motor. To do so, make sure that the nut to lock the propeller spins in the same diretion that the propeller is labelled with.

If this is the first time flying, calibrating the electronic speed controllers (ESCs) and battery is required. Refer to [PX4 documentation](https://docs.px4.io/main/en/config/actuators.html) to calibrate ESCs and motors.

### Flying the Drone
To arm the drone, ensure that the throttle is placed at the lowest positon. If RC switches are configured, flip the switch to arm the drone. If RC switches are not configured, click arm and slide the arm slider in QGroundControl.

When the drone is armed, the motors and propellers should be spinning at a low speed. Increase thrust by pushing the throttle upwards. The following table lists flight controls for the drone:
| Rotation Type | Stick Control          |
| ------------- | ---------------------- |
| Pitch         | Right stick up/down    |
| Yaw           | Left stick left/right  |
| Roll          | Right stick left/right |

### Controlling the Sprayer
Because the sprayer is defined as a motor, controlling it requires the drone to be armed. If the drone is flying, it is already armed. If the drone is not flying, arm the drone.

There are two methods of toggling the sprayer:
1. If the RC switch for the sprayer is configured, flip the switch and the sprayer will turn on through hardware. Return the switch to the normal position to stop spraying.
2. If the RC switch for the sprayer is not configured, enter the drone's shell in QGroundControl. It is under Analytical Tools. Enter command `sprayer start` to toggle the sprayer on. Enter command `sprayer stop` to toggle the sprayer off.

### Filling the Insecticide Tank
The tank uses a standard 12V liquid pump. Do not toggle the pump without liquid. Liquid is used to cool the pump's internals.

To fill the liquid insectide tank, unscrew the tank from the cap and silicone tube assembly. Fill the tank with liquid insecticide. Screw the tank back onto the cap and silicone tube assembly. Ensure that the straw is rotated downwards by turning the insecticide tank in its mount. Once the tank is in positon, tighten the straps to secure the tank in place.

## Software
For software, we currently only support building from source. The verm-wasp-drone repository contains a link to a submodule called rjc. In the rjc repository, the README contains instructions on how to build from source.

### RJCamera (rjc)
Build rjc from source with the following commands:
```
    bash configure.sh
    qmake6
    make
    ./rjc
```
