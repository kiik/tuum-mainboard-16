/** @file main.cpp
 *  @brief Mainboard logic entry module.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "mbed.h"
#include "definitions.h"

#include "rtx_protocol.hpp"
#include "rtx_Motor.hpp"

#include "usr_pins.hpp"
#include "usr_ui.hpp"

using namespace rtx;
using namespace usr;

#include "usr_pins.c.hpp"

typedef void (*VoidArray) ();

//DigitalOut led(LED1);
//DigitalOut l(LED2);

Serial pc(USBTX, USBRX);

Ticker motorPidTicker[NUMBER_OF_MOTORS];

char buf[16];
bool serialData = false;
int serialCount = 0;

volatile int16_t motorTicks[NUMBER_OF_MOTORS];
volatile uint8_t motorEncNow[NUMBER_OF_MOTORS];
volatile uint8_t motorEncLast[NUMBER_OF_MOTORS];

Motor motors[NUMBER_OF_MOTORS];

void serialInterrupt();
void parseCommad(char *command);

void motor0EncTick();
void motor1EncTick();
void motor2EncTick();
#if NUMBER_OF_MOTORS == 4
void motor3EncTick();
#endif

void motor0PidTick();
void motor1PidTick();
void motor2PidTick();
#if NUMBER_OF_MOTORS == 4
void motor3PidTick();
#endif

int main() {
  /*
  void (*encTicker[])()  = {
    motor0EncTick,
    motor1EncTick,
    motor2EncTick,
    #if NUMBER_OF_MOTORS == 4
    motor3EncTick
    #endif
  };

  VoidArray pidTicker[] = {
    motor0PidTick,
    motor1PidTick,
    motor2PidTick,
    #if NUMBER_OF_MOTORS == 4
    motor3PidTick
    #endif
  };

  for (int i = 0; i < NUMBER_OF_MOTORS; i++) {
    MotorEncA[i]->mode(PullNone);
    MotorEncB[i]->mode(PullNone);

    motors[i] = Motor(&pc, MotorPwm[i], MotorDir1[i], MotorDir2[i], MotorFault[i]);

    motorTicks[i] = 0;
    motorEncNow[i] = 0;
    motorEncLast[i] = 0;

    MotorEncA[i]->rise(encTicker[i]);
    MotorEncA[i]->fall(encTicker[i]);
    MotorEncB[i]->rise(encTicker[i]);
    MotorEncB[i]->fall(encTicker[i]);

    motorPidTicker[i].attach(pidTicker[i], 0.1);

    motors[i].init();
  }*/

  //pc.printf("Start\n");

  //pc.attach(&serialInterrupt);
  int count = 0;

  usr::UI::setup();
  while(1) {
    /*
    if (count % 20 == 0) {
      for (int i = 0; i < NUMBER_OF_MOTORS; i++) {
        pc.printf("s%d:%d\n", i, motors[i].getSpeed());
      }
    }*/

    /*
    if(serialData) {
      // Consume serial data
      char temp[16];
      memcpy(temp, buf, 16);
      memset(buf, 0, 16);
      serialData = false;

      int res;
      rtx::Protocol::Message msg;
      res = rtx::Protocol::parseCommand(temp, msg);
      if(res >= 0) {
        pc.printf("ACK\n");
      }
    }*/

    //motors[0].pid(motor0Ticks);
    //motor0Ticks = 0;

    usr::UI::process();
  }
}

void serialInterrupt() {
  while(pc.readable()) {
    buf[serialCount] = pc.getc();
    serialCount++;
  }
  if (buf[serialCount - 1] == '\n') {
    serialData = true;
    serialCount = 0;
  }
}

void parseCommad (char *command) {
    if (command[0] == 's' && command[1] == 'd') {
        int16_t speed = atoi(command + 2);
        motors[0].pid_on = 1;
        motors[0].setSpeed(speed);
    }
    if (command[0] == 's') {
        for (int i = 0; i < NUMBER_OF_MOTORS; i++) {
            pc.printf("s%d:%d\n", i, motors[i].getSpeed());
        }
    } else if (command[0] == 'w' && command[1] == 'l') {
        int16_t speed = atoi(command + 2);
        motors[0].pid_on = 0;
        if (speed < 0) motors[0].backward(-1*speed/255.0);
        else motors[0].forward(speed/255.0);
    } else if (command[0] == 'p' && command[1] == 'p') {
        uint8_t pGain = atoi(command + 2);
        motors[0].pgain = pGain;
    } else if (command[0] == 'p' && command[1] == 'i') {
        uint8_t iGain = atoi(command + 2);
        motors[0].igain = iGain;
    } else if (command[0] == 'p' && command[1] == 'd') {
        uint8_t dGain = atoi(command + 2);
        motors[0].dgain = dGain;
    } else if (command[0] == 'p') {
        char gain[20];
        motors[0].getPIDGain(gain);
        pc.printf("%s\n", gain);
    }
}

MOTOR_ENC_TICK(0)
MOTOR_ENC_TICK(1)
MOTOR_ENC_TICK(2)
#if NUMBER_OF_MOTORS == 4
MOTOR_ENC_TICK(3)
#endif

MOTOR_PID_TICK(0)
MOTOR_PID_TICK(1)
MOTOR_PID_TICK(2)
#if NUMBER_OF_MOTORS == 4
MOTOR_PID_TICK(3)
#endif
