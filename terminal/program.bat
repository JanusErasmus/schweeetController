::start /D "C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\" avrdude -C "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -c arduino -p m2560 -P COM7 -b 19200
::timeout /T 1
::taskkill /im "avrdude.exe" /f
::ping -n 1 -w 500 1.0.0.0 > nul
"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude" -C "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -c arduino -p m2560 -P COM7 -b 19200 -U flash:w:%1