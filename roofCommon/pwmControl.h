#ifndef __PWM_CTRL_H__
#define __PWM_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************
 * Functions
 ****************************************************************/
int pwm_export(unsigned int pwm_chnl);
int pwm_unexport(unsigned int pwm_chnl);
int pwm_set_frequency(unsigned int pwm_chnl, unsigned long freq_Hz);
int pwm_set_duty_cycle(unsigned int pwm_chnl, unsigned long duty_cycle);
int pwm_enable(unsigned int pwm_chnl);
int pwm_disable(unsigned int pwm_chnl);

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CTRL_H__ */