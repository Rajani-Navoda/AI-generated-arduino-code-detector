/*
	Пример опроса энкодера через аппаратные прерывания
*/
#include "AccelMotor.h"
AccelMotor motor(DRIVER2WIRE, 4, 3, HIGH);
// подробнее об инициализации смотри в примере motor_demo

void setup() {
  Serial.begin(9600);
  motor.setRunMode(ACCEL_POS);
  attachInterrupt(0, isr, RISING);
}

volatile long encCounter = 0;
void isr() {
  // опрос энкодера
  encCounter += motor.getState();
}

void loop() {
  // потенциометр на А0
  // преобразуем значение в -255.. 255
  static float val;
  val += (255 - analogRead(0) / 2 - val) * 0.3; // фильтор

  // для режима PID_SPEED/ACCEL_SPEED
  //motor.setTargetSpeedDeg(val*3);  // задаём целевую скорость в градусах/сек

  // для режима PID_POS/ACCEL_POS
  motor.setTargetDeg(val * 2);  // задаём новый целевой угол в градусах

  // обязательная функция. Делает все вычисления
  // принимает текущее значение с энкодера или потенциометра
  motor.tick(encCounter);
}