/****************************************************************************
 *
 *   Copyright (c) 2012-2019 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file px4_simple_app.c
 * Minimal application example for PX4 autopilot
 *
 * @author Example User <mail@example.com>
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

