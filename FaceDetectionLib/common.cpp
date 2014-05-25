#include "stdafx.h"
#include "LibInclude.h"

HANDLE	hStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
CRITICAL_SECTION fileCS;
CRITICAL_SECTION faceDetectionCS;

void InitFaceDetectionLib()
{
	InitializeCriticalSection(&faceDetectionCS);
	InitializeCriticalSection(&fileCS);
}

void DeinitFaceDetectionLib()
{
	cvReleaseHaarClassifierCascade(&faceCascades.face);
	cvReleaseHaarClassifierCascade(&faceCascades.eyes);
	cvReleaseHaarClassifierCascade(&faceCascades.nose);
	cvReleaseHaarClassifierCascade(&faceCascades.mouth);
	cvReleaseHaarClassifierCascade(&faceCascades.eye);
	cvReleaseHaarClassifierCascade(&faceCascades.righteye2);
	cvReleaseHaarClassifierCascade(&faceCascades.lefteye2);
	DeleteCriticalSection(&faceDetectionCS);
	DeleteCriticalSection(&fileCS);
}

void FilePrintMessage(char* file, char* expr...)
{
	EnterCriticalSection(&fileCS);
	char message[LOG_MESSAGE_MAX_LENGTH];
	va_list args;

	errno_t err = 0;

	if (expr)
	{
		va_start(args, expr);

		vsprintf(message, expr, args);

		ChooseTextColor(message);

		printf("%s", message);

		RestoreTextColor();

		if (file)
		{
			FILE* fl = NULL;

			if ((fl = fopen(file, "a+")) != NULL)
			{
				if (fl)
				{
					fprintf(fl, "%s", message);
				}
			}
		}
		va_end(args);
	}
	LeaveCriticalSection(&fileCS);
}

void ChooseTextColor(char* msg)
{
	if (memcmp(&msg[0], "[", sizeof(char)) != 0)
		return;

	for (int i = 0; i < 20; i++) // (18 + 2) - max prefix length
	{
		if (memcmp(&msg[i], "]", sizeof(char)) == 0)
		{
			if (memcmp(msg, "[PASS]", i + 1) == 0)
				SetConsoleTextAttribute(hStdHandle, 0x0002 | FOREGROUND_INTENSITY);
			else if (memcmp(msg, "[FAIL]", i + 1) == 0)
				SetConsoleTextAttribute(hStdHandle, 0x0004 | FOREGROUND_INTENSITY);
			else if (memcmp(msg, "[SUCC]", i + 1) == 0)
				SetConsoleTextAttribute(hStdHandle, 0x0007 | FOREGROUND_INTENSITY);
			else if (memcmp(msg, "[WARN]", i + 1) == 0)
				SetConsoleTextAttribute(hStdHandle, 0x0006 | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdHandle, 0x0002 | FOREGROUND_INTENSITY);

			break;
		}
	}
}

void RestoreTextColor()
{
	SetConsoleTextAttribute(hStdHandle, 0x0007);
}