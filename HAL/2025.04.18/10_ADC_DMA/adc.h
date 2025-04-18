#ifndef ADC_H_  // 헤더 가드 시작, 이 파일이 여러 번 포함되지 않도록 방지
#define ADC_H_

// PA0 핀에서 ADC 값을 읽어오는 함수 선언
// 이 함수는 PA0 핀에 연결된 아날로그 센서 값을 읽어오는 기능
uint32_t pa0_adc_read(void);

// ADC 초기화 및 시작 함수 선언
// ADC를 초기화하고 변환을 시작하는 함수로, 여러 설정을 통해 ADC를 사용할 수 있도록 설정
void adc_init_start(void);

// PA0 핀에서 단일 변환 모드로 ADC를 초기화하는 함수 선언
// PA0 핀을 단일 변환 모드로 설정하고, 그에 맞는 ADC 설정을 초기화
void adc_pa0_single_conv_init(void);

// PA0 핀에서 인터럽트 모드로 ADC를 초기화하는 함수 선언
// PA0 핀에서 ADC 변환이 완료되었을 때 인터럽트를 발생시키도록 ADC를 설정
void adc_pa0_interrupt_init(void);

// PA0 핀에서 DMA 모드로 ADC를 초기화하는 함수 선언
// PA0 핀에서 DMA를 사용하여 ADC 데이터를 자동으로 전송하도록 설정하는 함수
void adc_pa0_dma_init(void);

#endif /* ADC_H_ */  // 헤더 가드 끝, ADC_H_가 정의된 상태일 때만 이 파일이 포함되도록 설정
