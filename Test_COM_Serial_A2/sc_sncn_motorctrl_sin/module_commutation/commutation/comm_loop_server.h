
/**
 * \file comm_loop_server.h
 * \brief Commutation Loop based on sinusoidal commutation method
 * \author Ludwig Orgler <lorgler@synapticon.com>
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \author Martin Schwarz <mschwarz@synapticon.com>
 * \version 1.0
 * \date 10/04/2014
 */
/*
 * Copyright (c) 2014, Synapticon GmbH
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Execution of this software or parts of it exclusively takes place on hardware
 *    produced by Synapticon GmbH.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Synapticon GmbH.
 *
 */

#include <bldc_motor_config.h>
#include "comm_loop_client.h"
#include <watchdog.h>

/**
 * \brief Sinusoidal based Commutation Loop
 *
 *  Input
 * \channel c_hall channel to receive position information from hall sensor
 * \channel c_qei channel to receive position information from qei sensor
 * \channel c_signal channel for signaling after initialization of commutation loop
 * \channel c_watchdog channel for controlling the watchdog
 * \channel c_commutation_p1 channel to receive motor voltage input value - priority 1 (highest) 1 ... (lowest) 3
 * \channel c_commutation_p2 channel to receive motor voltage input value - priority 2
 * \channel c_commutation_p3 channel to receive motor voltage input value - priority 3
 * \param hall_params struct defines the pole-pairs and gear ratio
 * \param qei_params the struct defines sensor type and resolution parameters for qei
 * \param commutation_params struct defines the commutation angle parameters
 *
 *  Output
 * \channel c_pwm_ctrl channel to set pwm level output to motor phases
 * \port p_ifm_esf_rstn_pwml_pwmh port to configure motor FET driver
 * \port p_ifm_coastn port to enable motor FET driver
 *
 */
void commutation_sinusoidal(chanend c_hall, chanend c_qei, chanend c_signal, chanend c_watchdog, \
		chanend  c_commutation_p1, chanend  c_commutation_p2, chanend  c_commutation_p3, chanend c_pwm_ctrl,\
		out port p_ifm_esf_rstn_pwml_pwmh, port p_ifm_coastn, port p_ifm_ff1, port p_ifm_ff2,\
		hall_par &hall_params, qei_par &qei_params, commutation_par &commutation_params);

