#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <pwmControl.h>


/****************************************************************
 * Constants
 ****************************************************************/

#define SYSFS_PWM_DIR "/sys/class/pwm/pwmchip0"
#define MAX_BUF         64
#define SEC2NANOSEC     1000000000UL

/****************************************************************
 * pwm_export
 ****************************************************************/
int pwm_export(unsigned int pwm_chnl)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_PWM_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("pwm/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", pwm_chnl);
	write(fd, buf, len);
	close(fd);
	return 0;
}

/****************************************************************
 * pwm_unexport
 ****************************************************************/
int pwm_unexport(unsigned int pwm_chnl)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_PWM_DIR "/unexport", O_WRONLY);
	if (fd < 0) {
		perror("pwm/unexport");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", pwm_chnl);
	write(fd, buf, len);
	close(fd);
	return 0;
}

/****************************************************************
 * pwm_set_frequency
 ****************************************************************/
int pwm_set_frequency(unsigned int pwm_chnl, unsigned long freq_Hz)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwm%d/period", pwm_chnl);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("pwm/period");
		return fd;
	}
    unsigned long period = SEC2NANOSEC / freq_Hz;
    
    len = snprintf(buf, sizeof(buf), "%lu", period);
    write(fd, buf, len);
    close(fd);
	return 0;
}

/****************************************************************
 * pwm_set_dutycycle
 ****************************************************************/
int pwm_set_dutycycle(unsigned int pwm_chnl, unsigned long duty_cycle)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwm%d/duty_cycle", pwm_chnl);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("pwm/duty_cycle");
		return fd;
	}
	if (duty_cycle < 0){
        duty_cycle = 0;
    }
	else if (duty_cycle > 100){
		duty_cycle = 100;
    }
    unsigned long duty_cycle_ns = SEC2NANOSEC * duty_cycle/100;

    len = snprintf(buf, sizeof(buf), "%lu", duty_cycle_ns);
    write(fd, buf, len);
    close(fd);
	return 0;
}

/****************************************************************
 * pwm_enable
 ****************************************************************/
int pwm_enable(unsigned int pwm_chnl)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwm%d/enable", pwm_chnl);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("pwm/enable");
		return fd;
	}
    write(fd, "1", 2);
	close(fd);
	return 0;
}

/****************************************************************
 * pwm_disable
 ****************************************************************/
int pwm_disable(unsigned int pwm_chnl)
{
    int fd, len;
    char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwm%d/enable", pwm_chnl);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("pwm/enable");
		return fd;
	}
    write(fd, "0", 2);
	return close(fd);
}
