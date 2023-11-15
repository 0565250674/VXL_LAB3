/*
 * fsm_traffic_light.c
 *
 *  Created on: Nov 15, 2023
 *      Author: 84565
 */


#include "fsm_traffic_light.h"

void fsm_traffic_light() {
	switch(status){

//----------------------------------------------------------------------------------------------
// MODE INIT
	case INIT:
		// Chuyen ve trang thai mode 1
		status = MODE1;
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 1
	case MODE1:
		// Chuyen ve trang thai period AUTO_REDL_GREENP
		status = AUTO_REDL_GREENP;

		// Setup cho den Landscape_RED va Portrait_GREEN sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);

		// Setup ban dau va cap nhat gia tri, hien thi ra LED 7 doan
		counterL = 1;
		counterP = 1;
		index_led = 0;
		updateClockBufferMode1();
		update7SEG(index_led);

		// Set Timer
		setTimer(0, GREEN * 1000);	// Timer cho truong hop AUTO_REDL_GREENP
		setTimer(1, 1000);			// Timer updateClockBufferMode1
		setTimer(2, 250);			// Timer quet LED 7-SEG
		clearTimer(3);				// O mode 1 khong su dung Timer cho blinking LED

		break;

	case AUTO_REDL_GREENP:
		// Setup cho den Landscape_RED va Portrait_GREEN sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDL_AMBERP dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDL_AMBERP;
			setTimer(0, AMBER * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDL_AMBERP:
		// Setup cho den Landscape_RED va Portrait_AMBER sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDP_GREENL dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDP_GREENL;
			setTimer(0, GREEN * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDP_GREENL:
		// Setup cho den Portrait_RED va Landscape_GREEN sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDP_AMBERL dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDP_AMBERL;
			setTimer(0, AMBER * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDP_AMBERL:
		// Setup cho den Portrait_RED va Landscape_AMBER sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDL_GREENP dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDL_GREENP;
			setTimer(0, GREEN * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 2
	case MODE2:
		// Setup cho tat ca cac den RED sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		// Update lai gia tri hien thi ra LED 7 doan
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer de quet LED 7 doan dong thoi update lai buffer
		setTimer(3, 500);	// Timer blinking LED-RED
		clearTimer(0);		// O mode nay khong su dung timer de hien thi den o che do normal-mode
		clearTimer(1);		// Khong can su dung timer de update buffer moi giay
		// Chuyen ve trang thai AUTO_RED
		status = AUTO_RED;

		break;

	case AUTO_RED:
		// Neu timer_flag[3] == 1, toggle tat ca cac den RED va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian RED, dong thoi chuyen sang trang thai INC_RED
		if (isButtonPressed(1) == 1) {
			status = INC_RED;
			if (RED >= 99) RED = AMBER + 1;
			else RED++;
		}
		break;

	case INC_RED:
		// Neu timer_flag[3] == 1, toggle tat ca cac den RED va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian RED
		if (isButtonPressed(1) == 1) {
			if (RED >= 99) RED = AMBER + 1;
			else RED++;
		}
		// Neu nhan nut SET, co dinh gia tri thoi gian RED, quay tro ve trang thai AUTO_RED, dong thoi cap nhat lai bo ba gia tri thoi gian RED, AMBER va GREEN
		if (isButtonPressed(2) == 1) {
			status = AUTO_RED;
			GREEN = RED - AMBER;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 3
	case MODE3:
		// Setup cho tat ca cac den AMBER sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		// Update lai gia tri hien thi ra LED 7 doan
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer de quet LED 7 doan dong thoi update lai buffer
		setTimer(3, 500);	// Timer blinking LED-AMBER
		clearTimer(0);		// O mode nay khong su dung timer de hien thi den o che do normal-mode
		clearTimer(1);		// Khong can su dung timer de update buffer moi giay
		// Chuyen ve trang thai AUTO_AMBER
		status = AUTO_AMBER;
		break;

	case AUTO_AMBER:
		// Neu timer_flag[3] == 1, toggle tat ca cac den AMBER va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 4
		if (isButtonPressed(0) == 1) {
			status = MODE4;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian AMBER, dong thoi chuyen sang trang thai INC_AMBER
		if (isButtonPressed(1) == 1) {
			status = INC_AMBER;
			if (AMBER >= 5) AMBER = 1;
			else AMBER++;
		}
		break;

	case INC_AMBER:
		// Neu timer_flag[3] == 1, toggle tat ca cac den AMBER va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian AMBER, dong thoi chuyen sang trang thai INC_AMBER
		if (isButtonPressed(1) == 1) {
			if (AMBER >= 5) AMBER = 1;
			else AMBER++;
		}
		// Neu nhan nut SET, co dinh gia tri thoi gian AMBER, quay tro ve trang thai AUTO_AMBER, dong thoi cap nhat lai bo ba gia tri thoi gian RED, AMBER va GREEN
		if (isButtonPressed(2) == 1) {
			status = AUTO_AMBER;
			if (RED <= AMBER) RED = AMBER + 1;
			GREEN = RED - AMBER;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 4
	case MODE4:
		// Setup cho tat ca cac den GREEN sang
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		// Update lai gia tri hien thi ra LED 7 doan
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer de quet LED 7 doan dong thoi update lai buffer
		setTimer(3, 500);	// Timer blinking LED-GREEN
		clearTimer(0);		// O mode nay khong su dung timer de hien thi den o che do normal-mode
		clearTimer(1);		// Khong can su dung timer de update buffer moi giay
		// Chuyen ve trang thai AUTO_GREEN
		status = AUTO_GREEN;
		break;

	case AUTO_GREEN:
		// Neu timer_flag[3] == 1, toggle tat ca cac den GREEN va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 1
		if (isButtonPressed(0) == 1) {
			status = MODE1;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian GREEN, dong thoi chuyen sang trang thai INC_GREEN
		if (isButtonPressed(1) == 1) {
			status = INC_GREEN;
			if (GREEN >= RED - AMBER) GREEN = 1;
			else GREEN++;
		}
		break;

	case INC_GREEN:
		// Neu timer_flag[3] == 1, toggle tat ca cac den GREEN va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian GREEN, dong thoi chuyen sang trang thai INC_GREEN
		if (isButtonPressed(1) == 1) {
			if (GREEN >= RED - AMBER) GREEN = 1;
			else GREEN++;
		}
		// Neu nhan nut SET, co dinh gia tri thoi gian GREEN, quay tro ve trang thai AUTO_GREEN, dong thoi cap nhat lai bo ba gia tri thoi gian RED, AMBER va GREEN
		if (isButtonPressed(2) == 1) {
			status = AUTO_GREEN;
			RED = GREEN + AMBER;
		}
		break;
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// DEFAULT
	default:
		break;
	}
}
