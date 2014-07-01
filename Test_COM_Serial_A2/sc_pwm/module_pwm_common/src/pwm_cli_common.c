/*
 *
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
 **/

#include "pwm_cli_common.h"
#include "pwm_common.h"

void pwm_share_control_buffer_address_with_server(chanend c, t_pwm_control* ctrl)
{
  __asm__ volatile ("outct  res[%0], 0x1;"
	  "chkct  res[%0], 0x1;"
	  "out    res[%0], %1;"
	  "outct  res[%0], 0x1;"
	  "chkct  res[%0], 0x1;"  :: "r"(c),"r"(ctrl));
  return;
}

/*
 * Used by INV and NOINV modes
 */
void order_pwm( unsigned *mode, unsigned *chan_id, t_out_data *pwm_out_data)
{
	unsigned chan_id_tmp;
#ifndef PWM_CLIPPED_RANGE
	unsigned sngle = 0, long_single = 0, dble = 0;
	int e_check = 0;

	for (int i = 0; i < PWM_CHAN_COUNT; i++) {
		switch(pwm_out_data[i].cat) {
		case SINGLE:
			sngle++;
			break;
		case DOUBLE:
			dble++;
			break;
		case LONG_SINGLE:
			long_single++;
			break;
		}
	}

	if (sngle == 3) {
		*mode = 1;
		return;
	}

	else if (long_single == 1 && sngle == 2) {
		*mode = 7;
		/* need to find the long single and put it first */
		for (int i = 0; i < PWM_CHAN_COUNT; i++)
		{
			if (pwm_out_data[i].cat == LONG_SINGLE)
			{
				chan_id_tmp = chan_id[0];
				chan_id[0] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				return;
			}
		}
		e_check = 1;
		asm("ecallt %0" : "=r"(e_check));
	}

	else if (dble == 1 && sngle == 2) {
		*mode = 2;
		/* need to find the double and put it first */
		for (int i = 1; i < PWM_CHAN_COUNT; i++)
		{
			if (pwm_out_data[i].cat == DOUBLE )
			{
				chan_id_tmp = chan_id[0];
				chan_id[0] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				return;
			}
		}
		e_check = 1;
		asm("ecallt %0" : "=r"(e_check));
	}

	else if (dble == 2 && sngle == 1) {
		*mode = 3;

		/* need to find the single and put it last */
		for (int i = 0; i < PWM_CHAN_COUNT; i++)
		{
			if (pwm_out_data[i].cat == SINGLE )
			{
				chan_id_tmp = chan_id[PWM_CHAN_COUNT-1];
				chan_id[PWM_CHAN_COUNT-1] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				break;
			}
		}

		/* now order by length, only go as far as last but one - it is already in the right place */
		for (int i = 0; i < PWM_CHAN_COUNT-2; i++) /* start point loop */
		{
			unsigned max_index = i;
			for (int j = i+1; j < PWM_CHAN_COUNT-1; j++)
			{
				if (pwm_out_data[j].value > pwm_out_data[max_index].value)
					max_index = j;
			}

			/* swap into the correct place */
			chan_id_tmp = chan_id[i];
			chan_id[i] = chan_id[max_index];
			chan_id[max_index] = chan_id_tmp;
		}
		return;
	}

	else if (dble == 3) {
#endif
		*mode = 4;

#if PWM_CHAN_COUNT==3
		if (pwm_out_data[0].value > pwm_out_data[1].value) {
			chan_id_tmp = chan_id[0];
			chan_id[0] = chan_id[1];
			chan_id[1] = chan_id_tmp;
		}
		if (pwm_out_data[1].value > pwm_out_data[2].value) {
			chan_id_tmp = chan_id[1];
			chan_id[1] = chan_id[2];
			chan_id[2] = chan_id_tmp;
		}
		return;
#else
		/* now order by length*/
		for (int i = 0; i < PWM_CHAN_COUNT-1; i++) /* start point loop */
		{
			unsigned max_index = i;
			for (int j = i+1; j < PWM_CHAN_COUNT; j++)
			{
				if (pwm_out_data[j].value > pwm_out_data[max_index].value)
					max_index = j;
			}

			/* swap, even if it is a swap in place */
			chan_id_tmp = chan_id[i];
			chan_id[i] = chan_id[max_index];
			chan_id[max_index] = chan_id_tmp;
		}
		return;
#endif
#ifndef PWM_CLIPPED_RANGE
	}

	else if (long_single == 1 && dble == 1 && sngle == 1) {
		*mode = 5;

		/* need to find the single and put it last */
		for (int i = 0; i < PWM_CHAN_COUNT; i++)
		{
			if (pwm_out_data[i].cat == SINGLE) {
				chan_id_tmp = chan_id[PWM_CHAN_COUNT-1];
				chan_id[PWM_CHAN_COUNT-1] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				break;
			}
		}

		/* need to find the double and put it in the middle */
		for (int i = 0; i < PWM_CHAN_COUNT; i++)
		{
			if (pwm_out_data[i].cat == DOUBLE) {
				chan_id_tmp = chan_id[1];
				chan_id[1] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				break;
			}
		}

		/* long single should be first by definition */
		e_check = (pwm_out_data[0].cat != LONG_SINGLE);
		asm("ecallt %0" : "=r"(e_check));

		return;
	}

	else if (long_single == 1 && dble == 2) {
		*mode = 6;

		/* need to find the long single and put it first */
		for (int i = 0; i < PWM_CHAN_COUNT; i++) {
			if (pwm_out_data[i].cat == LONG_SINGLE) {
				chan_id_tmp = chan_id[0];
				chan_id[0] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				break;
			}
		}

		/* need to find the double and put it in the middle */
		for (int i = 0; i < PWM_CHAN_COUNT; i++) {
			if (pwm_out_data[i].cat == DOUBLE) {
				chan_id_tmp = chan_id[1];
				chan_id[1] = chan_id[i];
				chan_id[i] = chan_id_tmp;
				break;
			}
		}

		/* long single should be first by definition */
		e_check = (pwm_out_data[0].cat != LONG_SINGLE);
		asm("ecallt %0" : "=r"(e_check));

		return;
	}
#endif
}


void calculate_data_out( unsigned value, t_out_data *pwm_out_data )
{
	pwm_out_data->out1 = 0;
	pwm_out_data->ts1 = 0;
	pwm_out_data->inv_out1 = 0;
	pwm_out_data->inv_ts1 = 0;

	// very low values
	if (value <= 31)
	{
		pwm_out_data->cat = SINGLE;
		// compiler work around, bug 8218
		/* pwm_out_data.out0 = ((1 << value)-1);  */
		asm("mkmsk %0, %1"
				: "=r"(pwm_out_data->out0)
				: "r"(value));
		pwm_out_data->out0 <<= (value >> 1); // move it to the middle

		pwm_out_data->ts0 = 16;
		return;
	}

	// close to PWM_MAX_VALUE
	else if (value >= (PWM_MAX_VALUE-31))
	{
		unsigned tmp;
		pwm_out_data->cat = LONG_SINGLE;
		tmp = PWM_MAX_VALUE - value; // number of 0's
		tmp = 32 - tmp; // number of 1's

		// compiler work around, bug 8218
		/* pwm_out_data.out0 = ((1 << value)-1);  */
		asm("mkmsk %0, %1"
				: "=r"(pwm_out_data->out0)
		  	    : "r"(tmp));

		pwm_out_data->out0 <<= (32 - tmp);
		pwm_out_data->ts0 = (PWM_MAX_VALUE >> 1) + ((PWM_MAX_VALUE - value) >> 1); // MAX + (num 0's / 2)
		return;
	}

	// low mid range
	else if (value < 64)
	{
		unsigned tmp;
		pwm_out_data->cat = DOUBLE;

		if (value == 63)
			tmp = 32;
		else
			tmp = value >> 1;

		// compiler work around, bug 8218
		/* pwm_out_data.out0 = ((1 << (value >> 1))-1);  */
		asm("mkmsk %0, %1"
				: "=r"(pwm_out_data->out0)
				: "r"(tmp));


		tmp = value - tmp;

		// compiler work around, bug 8218
		asm("mkmsk %0, %1"
				: "=r"(pwm_out_data->out1)
				: "r"(tmp));
		/* pwm_out_data.out1 = ((1 << (value - (value >> 1)))-1);  */

		pwm_out_data->ts0 = 32;
		pwm_out_data->ts1 = 0;
		return;
	}

	// midrange
	pwm_out_data->cat = DOUBLE;
	pwm_out_data->out0 = 0xFFFFFFFF;
	pwm_out_data->out1 = 0x7FFFFFFF;

	pwm_out_data->ts0 = (value >> 1);
	pwm_out_data->ts1 = (value >> 1)-31;

}


void calculate_data_out_ref( unsigned value, unsigned *ts0, unsigned *out0, unsigned *ts1, unsigned *out1, e_pwm_cat *cat )
{
	*out1 = 0;
	*ts1 = 0;

	// very low values
	if (value < 32)
	{
		*cat = SINGLE;
		// compiler work around, bug 8218
		/* pwm_out_data.out0 = ((1 << value)-1);  */
		asm("mkmsk %0, %1"
				: "=r"(*out0)
				: "r"(value));
		*out0 <<= 16-(value >> 1); // move it to the middle
		*ts0 = 16;

		/* DOUBLE mode safe values */
		*out1 = 0;
		*ts1 = 100;

		return;
	}

	// close to PWM_MAX_VALUE
	/* Its pretty impossible to apply dead time to values this high... so update function should clamp the values to
	 * PWM_MAX - (31+PWM_DEAD_TIME)
	 */
	else if (value >= (PWM_MAX_VALUE-31))
	{
		unsigned tmp;
		*cat = LONG_SINGLE;
		tmp = PWM_MAX_VALUE - value; // number of 0's
		tmp = 32 - tmp; // number of 1's

		// compiler work around, bug 8218
		/* pwm_out_data.out0 = ((1 << value)-1);  */
		asm("mkmsk %0, %1"
				: "=r"(*out0)
		  	    : "r"(tmp));

		*out0 <<= (32 - tmp);
		*ts0 = (PWM_MAX_VALUE >> 1) + ((PWM_MAX_VALUE - value) >> 1); // MAX + (num 0's / 2)
		return;
	}

	// low mid range
	else if (value < 64)
	{
		unsigned tmp;
		*cat = DOUBLE;

		if (value == 63)
			tmp = 32;
		else
			tmp = value >> 1;

		// compiler work around, bug 8218
		/* pwm_out_data.out0 = ((1 << (value >> 1))-1);  */
		asm("mkmsk %0, %1"
				: "=r"(*out0)
				: "r"(tmp));

		/* pwm_out_data.out1 = ((1 << (value - (value >> 1)))-1);  */
		// compiler work around, bug 8218
		tmp = value - tmp;
		asm("mkmsk %0, %1"
				: "=r"(*out1)
				: "r"(tmp));

		*ts0 = 32;
		*ts1 = 0;
		return;
	}
	// midrange
	*cat = DOUBLE;
	*out0 = 0xFFFFFFFF;
	*out1 = 0x7FFFFFFF;

	*ts0 = (value >> 1);
	*ts1 = (value >> 1)-31;

}





