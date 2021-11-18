#include "HX711.h"


extern long array_weight[45];
extern long offset;
extern long weight_grams;
extern long memory_weight;
extern long weight;
float conversion_rate = 0.035274;

long SCALE;
float weight_of_standard=215.9;
float calibration_value[15];
float calibration_factor=0;

void HX711_init(){
	GPIOB_init_HX711(); // инциализируем пины
	Calibration(); //калибровка весов
}

long HX711_Get_3byte(){
	HX711_work_on(); //запуск на старт - на выход SCK подан низкий сигнал
	int cnt=0;
	while(GPIOB->IDR & GPIO_IDR_9){// ждем, когда АЦП ответит 0, если не ответил выходим, и заново считываем
		cnt++;
		if(cnt>10000){
			SCK_HIGH();
			return 0;
		}
	}
	delay(1);
	long data=0;
	for (int i=0; i<24;i++){//24 bits
		data=data<<1; //сдвигиваем на 1 бит
		//говорим, что готовы принять еще 1 бит (на SCK подаем 1, ждем 1 мкс, подаем 0, ждем 1 мкс)
		SCK_HIGH();
		delay(1);
		SCK_LOW();
		delay(1);
		//считываем данные с IDR
		uint8_t data_bit = ((GPIOB->IDR) & (1<<9))>>9;
		data=(data|data_bit);
	}
	// 1 доп импульс для канала А и коэф 128
	pulse(1);
	power_down(); // сбрасываем
	if(data & 0x800000){ // если старший бит равен 1, то число отрицательное
		data = (data & 0x7fffff)*(-1);
	}
	return data;
}


void HX711_work_on(){ // условие старта
	SCK_LOW();
	delay(100);
}

void pulse(uint8_t time){ // настройка режима для следующего снятия данных с ацп
	for(uint8_t i=0; i<time;i++){
		SCK_HIGH();
		delay(1);
		SCK_LOW();
		delay(1);
	}
}

long HX711_read_average(uint8_t times){ // считываем данные с АЦП times раз
	long data;
	for(int i=0;i<times;i++){
		array_weight[i]=HX711_Get_3byte();
		data+=array_weight[i];
		if(array_weight[i]==0){
			i--;
		}
	}
	power_down();
	data=data/times;
	data = HX711_get_value(data); // вычитаем смещение
	return data;
}

long HX711_get_value(long data){
	return (data - offset);
}

long get_units(uint8_t times){ //получаем данные в унциях
	return HX711_read_average(times)/SCALE;
}

void HX711_get_data(){
	weight = get_units(30);//считываем 30 раз
	weight_grams = weight*conversion_rate; // переводим в граммы
	if (memory_weight!=0) // если кнопка была нажата и вес не ноль
	{
		weight_grams = weight_grams - memory_weight; // вычитаем
	}
	//char str[128];
	//itoa(weight_grams,str,10);
	//Print(&str[0]); // выводим вес на экран
	//delay(2000000);
}

void power_down(){
	SCK_HIGH();
	delay(90);
}

void Calibration(){
	Set_scale(1);
	long data = HX711_read_average(30);
	Set_offset(data);
//	Print("Put the reference weight on the scale"); // просим положить эталлонный вес на весы
	delay(1000000); // ждем 1 с
	//countdown(); обратный отсчет для экрана (10 секунд)
	Set_scale(calibration_array()); // считываем значение с весом и обновляем калибровочный коэф
//	char str[128];
//	itoa(SCALE,str,10);
//	Print(&str[0]); // выводим калибровочный коэффиуиент
}

void Set_offset(long data){
	offset = data;
}

void Set_scale(long scale){
	SCALE = scale;
}

long calibration_array(){
	for (int i = 0; i < 15; i++) {                                                           // запускаем цикл, в котором
	    calibration_value[i] = HX711_read_average(1) / (weight_of_standard / conversion_rate);   // считываем значение с тензодатчика и переводим его в граммы
	    calibration_factor += calibration_value[i];                                           // суммируем все значения
	  }
	calibration_factor = calibration_factor / 15;
	return calibration_factor;
}

void delay(uint32_t tick){
	tick*=(SystemCoreClock/1000000);
	for(int i=0; i<tick;i++);
}

void GPIOB_init_HX711(){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER8_0;//SCK
	GPIOB->MODER &= ~GPIO_MODER_MODER9;//DOUT
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR9_1; //pull down 10
	SCK_HIGH();
	delay(100);
}
