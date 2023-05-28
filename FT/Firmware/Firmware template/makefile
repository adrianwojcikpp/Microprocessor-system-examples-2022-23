default: display

Src = 	Src/hal_gpio.c\
		Src/display_control.c\
		Src/display_control_config.c 

Inc = 	-I Inc

display: main.c $(Src)
	gcc main.c $(Src) $(Inc) -o display.exe -std=c18 -Wall -pedantic
	
clean: 
	rm -f display.exe
