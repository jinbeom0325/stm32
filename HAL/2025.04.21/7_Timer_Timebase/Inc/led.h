#ifndef LED_H_
#define LED_H_

#define LED_PORT GPIOA                   // LED가 연결된 포트 정의
#define LED_PIN GPIO_PIN_5               // LED가 연결된 핀 정의 (PA5)

void pa5_led_init(void);

#endif /* LED_H_ */
