cd ..

cd ..\lang

for /r %%i in (kor*.hhp) do if exist %%i (hhc.exe %%i)

reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce /v Name /t reg_sz /d c:\scripts\0419.bat /f

reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\CodePage /v ACP /t reg_sz /d 1251 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\CodePage /v OEMCP /t reg_sz /d 866 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\CodePage /v MACCP /t reg_sz /d 10007 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\Language /v Default /t reg_sz /d 0419 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\Locale /v (Default) /t reg_sz /d 00000419 /f

reg add HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Nls\CodePage /v ACP /t reg_sz /d 1251 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Nls\CodePage /v OEMCP /t reg_sz /d 866 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Nls\CodePage /v MACCP /t reg_sz /d 10007 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Nls\Language /v Default /t reg_sz /d 0419 /f
reg add HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Nls\Locale /v (Default) /t reg_sz /d 00000419 /f

set my=0
for /r %%i in (rus*.hhp) do if exist %%i (set my=1)
if "%my%" EQU "1" (shutdown -r) else (C:\scripts\0419.bat)
