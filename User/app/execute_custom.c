#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "pid.h"
#include "sys.h"

int16_t football_moto_speed[4];
float football_moto_angle[4];
int16_t football_moto_current[4];

pid_t pid_football_speed[4] = { 0 };
pid_t pid_football_angle[4]  = { 0 };

void football_motor_init() {
    for (int i = 0; i < 4; ++i) {
			  // ������pid�����е����Ŀռ䣬ֻ��͵����
				pid_init(&pid_football_speed[i], 7000, 0, 10, 0, 0);
			  pid_init(&pid_football_angle[i], 7000, 0, 100, 0, 0);
	  }
}

void football_motor_control() {
    football_moto_angle[0] = -rc.ch1 / RC_MAX_VALUE * 160;		// ������Ա
	  //football_moto_angle[0] = -rc.ch1 / RC_MAX_VALUE * 260;	// ����Ա
    football_moto_angle[1] = -(rc.ch2 / RC_MAX_VALUE * 90);
		football_moto_angle[2] = -rc.ch3 / RC_MAX_VALUE * 160;
		football_moto_angle[3] = -(rc.ch4 / RC_MAX_VALUE * 90);
	
		for (int i = 0; i < 4; ++i) {
			  // �Ƕ�pid���������Ϊ�ٶ�pid�������������ڵ�����ٱȣ���total_angle��19.2
				football_moto_speed[i] = pid_calc(&pid_football_angle[i], moto_chassis[i].total_angle/19.2, football_moto_angle[i]);
				football_moto_current[i] = pid_calc(&pid_football_speed[i], moto_chassis[i].speed_rpm, football_moto_speed[i]);
		}			
}