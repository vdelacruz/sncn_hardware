/*
 * The copyrights, all other intellectual and industrial 
 * property rights are retained by XMOS and/or its licensors. 
 * Terms and conditions covering the use of this code can
 * be found in the Xmos End User License Agreement.
 *
 * Copyright XMOS Ltd 2010
 *
 * In the case where this code is a modification of existing code
 * under a separate license, the separate license terms are shown
 * below. The modifications to the code are still covered by the 
 * copyright notice above.
 *
 */

#ifdef __pwm_config_h_exists__
#include "pwm_config.h"
#endif

#include "pwm_cli_inv.h"

extern inline void calculate_data_out_quick( unsigned value, REFERENCE_PARAM(t_out_data,pwm_out_data) );

#pragma unsafe arrays
void update_pwm_inv( t_pwm_control& ctrl, chanend c, unsigned value[])
{
        unsigned uPwmValueH;
        unsigned uPwmValueL;

	/* update buffer value for next calculation */
	ctrl.pwm_cur_buf = (ctrl.pwm_cur_buf+1)&1;

	/* calculate the required outputs */
#pragma loop unroll
	for (int i = 0; i < PWM_CHAN_COUNT; i++) {

		// Initialise channel number
		ctrl.chan_id_buf[ctrl.pwm_cur_buf][i] = i;

                /* symmetrically insert dead-times
                   high-side: reduce pulse with, low-side: increase pulse width
                   also suppress pulses that are shorter than PWM_DEAD_TIME/2 */
		uPwmValueH = value[i];
		uPwmValueL = value[i];
		if(uPwmValueH <= PWM_DEAD_TIME) {
                        uPwmValueH = 0;
                        uPwmValueL = 0;
#ifndef PWM_CLIPPED_RANGE
        /* clamp to avoid issues with LONG_SINGLE */
		} else if (uPwmValueL >= (PWM_MAX_VALUE - (32+PWM_DEAD_TIME))) {
		    uPwmValueL = PWM_MAX_VALUE - (32+PWM_DEAD_TIME);
		    uPwmValueH = uPwmValueL - PWM_DEAD_TIME;
#endif
		} else {
			uPwmValueH -=  PWM_DEAD_TIME/2;
			uPwmValueL +=  PWM_DEAD_TIME/2;
		}

#ifdef PWM_CLIPPED_RANGE
		calculate_data_out_quick(value[i], ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i]);
#else
		calculate_data_out_ref( uPwmValueH,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].ts0,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].out0,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].ts1,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].out1,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].cat );
		calculate_data_out_ref( uPwmValueL,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].inv_ts0,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].inv_out0,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].inv_ts1,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].inv_out1,
				ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf][i].cat );
#endif
	}

	if (value[0] == -1 && value[1] == -1 && value[2] == -1) {
		ctrl.mode_buf[ctrl.pwm_cur_buf] = -1;
	} else {

		/* now order them and work out the mode */
		order_pwm( ctrl.mode_buf[ctrl.pwm_cur_buf], ctrl.chan_id_buf[ctrl.pwm_cur_buf], ctrl.pwm_out_data_buf[ctrl.pwm_cur_buf] );
	}

	c <: ctrl.pwm_cur_buf;
}

