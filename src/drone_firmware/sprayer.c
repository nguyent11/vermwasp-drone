/**
 * @file sprayer.c
 * Minimal application example for PX4 autopilot
 *
 * @author Tyler Nguyen
 */

#include <px4_platform_common/log.h>
#include <uORB/uORB.h>
#include <uORB/topics/actuator_outputs.h>

#include <string.h>

__EXPORT int sprayer_main(int argc, char *argv[]);

int sprayer_main(int argc, char *argv[]) {
    // Check for the correct number of arguments. The user may only issue command of
    // start or stop from the command line.
    if (argc < 2) {
        PX4_INFO("Error: Usage of sprayer requires arguments of 'start' or 'stop'");
        return 1;
    }

    // Advertise actuator output
    struct actuator_outputs_s actuators = {};
    memset(&actuators, 0, sizeof(actuators));
    orb_advert_t actuator_pub = orb_advertise(ORB_ID(actuator_outputs), &actuators);
    if (actuator_pub == NULL) {
        PX4_INFO("Error: Failed to advertise actuator_outputs");
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        PX4_INFO("Starting sprayer");

        actuators.output[0] = 1.0f;
        orb_publish(ORB_ID(actuator_outputs), actuator_pub, &actuators);

    } else if (strcmp(argv[1], "stop") == 0) {
        PX4_INFO("Stopping sprayer");

        actuators.output[0] = 0.0f;
        orb_publish(ORB_ID(actuator_outputs), actuator_pub, &actuators);
    } else {
        PX4_INFO("Error: Unknown command '%s'\n", argv[1]);
        return 1;
    }


	PX4_INFO("exiting");

	return 0;
}

