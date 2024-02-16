#include "Input.h"

Input* Input::GetInstance(){

	static Input instance;
	return &instance;
}

void Input::Initialize(){

	HRESULT result{};
	// InputDeviceの作成
	result = DirectInput8Create(WinApp::GetInstance()->GetWc().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&Input::GetInstance()->directInput, nullptr);

	assert(SUCCEEDED(result));
	// キーボードデバイスの作成
	result = Input::GetInstance()->directInput->CreateDevice(GUID_SysKeyboard, &Input::GetInstance()->keyboard, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = Input::GetInstance()->keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	// 排制御レベルのセット
	result = Input::GetInstance()->keyboard->SetCooperativeLevel(
		WinApp::GetInstance()->GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	
}

void Input::Update(){

	memcpy(Input::GetInstance()->preKeys, Input::GetInstance()->keys, 256);
	Input::GetInstance()->keyboard->Acquire();
	Input::GetInstance()->keyboard->GetDeviceState(sizeof(Input::GetInstance()->keys), Input::GetInstance()->keys);
}

bool Input::PushKey(uint8_t keyNum){

	if (Input::GetInstance()->keys[keyNum] == 0x80)
	{
		return true;
	}
	return false;
	
}

bool Input::PushKeyPressed(uint32_t keyNum){
	
	if (Input::GetInstance()->keys[keyNum] == 0x80 && Input::GetInstance()->preKeys[keyNum] == 0x00)
	{
		return true;
	}
	return false;
}


