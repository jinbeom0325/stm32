#ifndef ADC_H_
#define ADC_H_

// PA0 핀에서 ADC 값을 읽어오는 함수 선언
uint32_t pa0_adc_read(void);

// ADC 초기화 및 시작 함수 선언
void adc_init_start(void);
void adc_pa0_single_conv_init(void);


#endif /* ADC_H_ */ // ADC_H_ 끝
