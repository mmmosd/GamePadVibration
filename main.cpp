#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")
#pragma warning(disable : 4996)

enum Button {
	LT,RT,
	
	LB,RB,
	LTH,RTH,
	A,B,X,Y,
	U,D,L,R,
	
	TLX, TRX,
	TLY, TRY
};

int main(int argc,char **argv) {
	int values[18] = {0};
    char path[1024] = {0};

    printf("Locate your txt file (if you don't have any file, type 'CREATEFILE')\n-- ");
    scanf("%s", path);

    FILE *fp;
        if (fp = fopen(path, "r")) {
            while (feof(fp) == 0) {
				bool b = false;
                char str[1024] = {0}, Bname[5] = {0}, Bvalue[15] = {0};
                fgets(str, 1024, fp);
				if (str[0] != '\n') {
					for (int i = 0; i < 1024; i++) {
						if (str[i] == '/') {
							break;
						}
						
						if (str[i] == '_') {
							b = true;
						}
						else {
							if (b) {
								Bvalue[i-(strlen(Bname)+1)] = str[i];
							}
							else {
								Bname[i] = str[i];
							}
						}
					}
					
					values[LT] = strcmp(Bname, "LT") == 0 ? atoi(Bvalue) : values[LT];
					values[RT] = strcmp(Bname, "RT") == 0 ? atoi(Bvalue) : values[RT];

					values[LB] = strcmp(Bname, "LB") == 0 ? atoi(Bvalue) : values[LB];
					values[RB] = strcmp(Bname, "RB") == 0 ? atoi(Bvalue) : values[RB];

					values[LTH] = strcmp(Bname, "LTH") == 0 ? atoi(Bvalue) : values[LTH];
					values[RTH] = strcmp(Bname, "RTH") == 0 ? atoi(Bvalue) : values[RTH];

					values[A] = strcmp(Bname, "A") == 0 ? atoi(Bvalue) : values[A];
					values[B] = strcmp(Bname, "B") == 0 ? atoi(Bvalue) : values[B];
					values[X] = strcmp(Bname, "X") == 0 ? atoi(Bvalue) : values[X];
					values[Y] = strcmp(Bname, "Y") == 0 ? atoi(Bvalue) : values[Y];

					values[U] = strcmp(Bname, "U") == 0 ? atoi(Bvalue) : values[U];
					values[D] = strcmp(Bname, "D") == 0 ? atoi(Bvalue) : values[D];
					values[L] = strcmp(Bname, "L") == 0 ? atoi(Bvalue) : values[L];
					values[R] = strcmp(Bname, "R") == 0 ? atoi(Bvalue) : values[R];

					values[TLX] = strcmp(Bname, "TLX") == 0 ? atoi(Bvalue) : values[TLX];
					values[TRX] = strcmp(Bname, "TRX") == 0 ? atoi(Bvalue) : values[TRX];
					values[TLY] = strcmp(Bname, "TLY") == 0 ? atoi(Bvalue) : values[TLY];
					values[TRY] = strcmp(Bname, "TRY") == 0 ? atoi(Bvalue) : values[TRY];
					
					printf("%s: %s\n", Bname, Bvalue);
				}
            }
    	fclose(fp);
    }

	while (1) {
		Sleep(10);
		DWORD dwResult;
    	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    	{
     	   	XINPUT_STATE state;
       		ZeroMemory(&state, sizeof(XINPUT_STATE));

        	// Simply get the state of the controller from XInput.
        	dwResult = XInputGetState(i, &state);

        	if (dwResult == ERROR_SUCCESS)
        	{
            	// Controller is connected
	            XINPUT_GAMEPAD pad = state.Gamepad;
	            XINPUT_VIBRATION vibration;
    	        ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
				
				//LT
            	if (vibration.wLeftMotorSpeed <= (WORD)(pad.bLeftTrigger * (values[LT] * 2))
            	&& vibration.wRightMotorSpeed <= (WORD)(pad.bLeftTrigger * (values[LT] * 2))) {
              	  	vibration.wLeftMotorSpeed = (WORD)(pad.bLeftTrigger * (values[LT] * 2));
                	vibration.wRightMotorSpeed = (WORD)(pad.bLeftTrigger * (values[LT] * 2));
            	}
            	
     	       	//RT
            	if (vibration.wLeftMotorSpeed <= (WORD)(pad.bRightTrigger * (values[RT] * 2))
            	&& vibration.wRightMotorSpeed <= (WORD)(pad.bRightTrigger * (values[RT] * 2))) {
            	    vibration.wLeftMotorSpeed = (WORD)(pad.bRightTrigger * (values[RT] * 2));
            	    vibration.wRightMotorSpeed = (WORD)(pad.bRightTrigger * (values[RT] * 2));
            	}

            	//ThumbRX
            	if (vibration.wLeftMotorSpeed <= (WORD)((pad.sThumbRX >= 0 ? pad.sThumbRX : pad.sThumbRX * -1) * (values[TRX] * (2 / 100.0)))
                && vibration.wRightMotorSpeed <= (WORD)((pad.sThumbRX >= 0 ? pad.sThumbRX : pad.sThumbRX * -1) * (values[TRX] * (2 / 100.0)))) {
					vibration.wLeftMotorSpeed = (WORD)((pad.sThumbRX >= 0 ? pad.sThumbRX : pad.sThumbRX * -1) * (values[TRX] * (2 / 100.0)));
                	vibration.wRightMotorSpeed = (WORD)((pad.sThumbRX >= 0 ? pad.sThumbRX : pad.sThumbRX * -1) * (values[TRX] * (2 / 100.0)));
            	}
            	//ThumbLX
            	if (vibration.wLeftMotorSpeed <= (WORD)((pad.sThumbLX >= 0 ? pad.sThumbLX : pad.sThumbLX * -1) * (values[TLX] * (2 / 100.0)))
                && vibration.wRightMotorSpeed <= (WORD)((pad.sThumbLX >= 0 ? pad.sThumbLX : pad.sThumbLX * -1) * (values[TLX] * (2 / 100.0)))) {
                	vibration.wLeftMotorSpeed = (WORD)((pad.sThumbLX >= 0 ? pad.sThumbLX : pad.sThumbLX * -1) * (values[TLX] * (2 / 100.0)));
                	vibration.wRightMotorSpeed = (WORD)((pad.sThumbLX >= 0 ? pad.sThumbLX : pad.sThumbLX * -1) * (values[TLX] * (2 / 100.0)));
            	}

            	//ThumbRY
            	if (vibration.wLeftMotorSpeed <= (WORD)((pad.sThumbRY >= 0 ? pad.sThumbRY : pad.sThumbRY * -1) * (values[TRY] * (2 / 100.0)))
                && vibration.wRightMotorSpeed <= (WORD)((pad.sThumbRY >= 0 ? pad.sThumbRY : pad.sThumbRY * -1) * (values[TRY] * (2 / 100.0)))) {
                	vibration.wLeftMotorSpeed = (WORD)((pad.sThumbRY >= 0 ? pad.sThumbRY : pad.sThumbRY * -1) * (values[TRY] * (2 / 100.0)));
                	vibration.wRightMotorSpeed = (WORD)((pad.sThumbRY >= 0 ? pad.sThumbRY : pad.sThumbRY * -1) * (values[TRY] * (2 / 100.0)));
            	}
            	//ThumbLX
            	if (vibration.wLeftMotorSpeed <= (WORD)((pad.sThumbLY >= 0 ? pad.sThumbLY : pad.sThumbLY * -1) * (values[TLY] * (2 / 100.0)))
                && vibration.wRightMotorSpeed <= (WORD)((pad.sThumbLY >= 0 ? pad.sThumbLY : pad.sThumbLY * -1) * (values[TLY] * (2 / 100.0)))) {
                	vibration.wLeftMotorSpeed = (WORD)((pad.sThumbLY >= 0 ? pad.sThumbLY : pad.sThumbLY * -1) * (values[TLY] * (2 / 100.0)));
                	vibration.wRightMotorSpeed = (WORD)((pad.sThumbLY >= 0 ? pad.sThumbLY : pad.sThumbLY * -1) * (values[TLY] * (2 / 100.0)));
            	}

            	//A,B,X,Y
            	if (pad.wButtons == XINPUT_GAMEPAD_A) {
                	vibration.wLeftMotorSpeed = (WORD)(values[A] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[A] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_B) {
                	vibration.wLeftMotorSpeed = (WORD)(values[B] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[B] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_X) {
                	vibration.wLeftMotorSpeed = (WORD)(values[X] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[X] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_Y) {
                	vibration.wLeftMotorSpeed = (WORD)(values[Y] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[Y] * (65535 / 100));
            	}

				//Dpad
				if (pad.wButtons == XINPUT_GAMEPAD_DPAD_UP) {
                	vibration.wLeftMotorSpeed = (WORD)(values[U] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[U] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN) {
                	vibration.wLeftMotorSpeed = (WORD)(values[D] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[D] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT) {
                	vibration.wLeftMotorSpeed = (WORD)(values[L] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[L] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT) {
                	vibration.wLeftMotorSpeed = (WORD)(values[R] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[R] * (65535 / 100));
            	}

				//LB, RB, LTH, RTH
				if (pad.wButtons == XINPUT_GAMEPAD_LEFT_SHOULDER) {
                	vibration.wLeftMotorSpeed = (WORD)(values[LB] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[LB] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER) {
                	vibration.wLeftMotorSpeed = (WORD)(values[RB] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[RB] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_LEFT_THUMB) {
                	vibration.wLeftMotorSpeed = (WORD)(values[LTH] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[LTH] * (65535 / 100));
            	}
            	if (pad.wButtons == XINPUT_GAMEPAD_RIGHT_THUMB) {
                	vibration.wLeftMotorSpeed = (WORD)(values[RTH] * (65535 / 100));
                	vibration.wRightMotorSpeed = (WORD)(values[RTH] * (65535 / 100));
            	}
            	XInputSetState(i, &vibration);
        	}
        	else
        	{
            	// Controller is not connected
        	}
    }
	}
}
