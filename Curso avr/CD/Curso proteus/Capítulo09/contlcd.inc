
;********************************************************************************
;CONJUNTO DE SUBRUTINAS QUE PUEDEN INCLUIRSE EN OTROS PROGRAMAS CON LA ORDEN
;			include	"contlcd.inc"
;********************************************************************************

;Estas rutinas permitirán realizar el control de la pantalla visualizadora (LCD).

#define	ACTIVEN	bsf PORTA,2		;Activa señal E.
#define	BORRAEN	bcf PORTA,2		;Desactiva señal E.
#define	LEELCD	bsf PORTA,1		;Lee el módulo.
#define	ESCRLCD	bcf PORTA,1		;Escribe en el módulo.
#define	ORDEN		bcf PORTA,0		;Prepara al módulo para recibir una orden.
#define	DATO		bsf PORTA,0		;Prepara al módulo para recibir un dato

	CBLOCK		0x7E
	TLCD1, TLCD2
	ENDC

;********************************************************************
;						"PROGLCD"
;Realiza la programación de puerto A y puerto B de la manera que 
;necesita el módulo LCD: PORTB como salida y las tres líneas de menos
;peso del PORTA como salidas digitales.
;********************************************************************

PROGLCD:	bsf		STATUS,RP0		;Selecciona banco 1.
			movlw		06					;Configura las patillas del puerto A
			movwf		ADCON1			;como señales digitales.
			movf		TRISA,W			;Lee la programación de TRISA para
			andlw		b'11111000'		;dejar como salidas las tres líneas
			movwf		TRISA				;de menor peso y no tocar las demás.
			clrf		TRISB				;Programa PORTB como salida.
			bcf		STATUS,RP0		;Selecciona banco 0.
			ORDEN							;RS=0.
			BORRAEN						;E=0.
			return

;********************************************************************
;						"INILCD"
;Realiza la inicialización del LCD con interface de 8 bits, 2 líneas 
;de pantalla y caracteres de 5 x 7. La subrutina provocará un retardo
;de 15 ms y un borrado de pantalla.
;********************************************************************

INILCD	call		PROGLCD			;Programación de las líneas de puertos.
			movlw		b'00111100'		;Programación de interface de 8 bits y
			call		ENVC				;pantalla de 2 líneas.
			movlw		b'00001100'		;Programación de pantalla activa, cursor
			call		ENVC				;visible y sin intermitencia.
			movlw		01					;Programación de borrado de pantalla.
			call		ENVC				;			"		
			movlw		06					;Programación de cursor incremental.
			call		ENVC				;			"
			return

;********************************************************************
;						"ENVD"
;Rutina para enviar al visualizador el dato contenido en W.
;********************************************************************

ENVD		DATO							;RS=1: visualizador en modo dato.
			ESCRLCD						;R/-W = 0
			movwf		PORTB				;Saca dato por el puerto B.
			ACTIVEN
			BORRAEN
			call		R1MS
			return

;********************************************************************
;						"ENVC"
;Rutina para enviar al visualizador una orden.
;********************************************************************		

ENVC		ORDEN							;RS=0.
			ESCRLCD						;R/-W = 0
			movwf		PORTB				;Saca en puerto B el valor de W.
			ACTIVEN
			BORRAEN
			call		R1MS
			return

;********************************************************************
;						"LEED"
;Rutina para leer el dato ubicado en la posición del cursor del LCD.
;El dato leído estará disponible en W.
;********************************************************************

LEED		bsf		STATUS,RP0		;Selecciona banco 1.
			movlw		0xFF				;Programa PORTB como entrada.
			movwf		TRISB				;	"
			bcf		STATUS,RP0		;Selecciona banco 0.
			LEELCD						;R/-W= 1: visualizador en modo lectura.
			DATO							;RS=1: visualizador en modo dato.
			ACTIVEN						;E=1: activa Enable.
			movf		PORTB,W			;Lee el dato en posición de cursor.
			BORRAEN						;E=0: desactiva Enable.
			movwf		TLCD2				;Salva dato en registro temporal.
			bsf		STATUS,RP0		;Selecciona el banco 1.
			clrf		TRISB				;Programa PORTB como salida.
			bcf		STATUS,RP0		;Selecciona banco 0.
			call		R1MS
			movf		TLCD2,W			;Recupera valor leído.
			return

;*****************************************************************
;						"LEES"
;Rutina para leer la palabra de Estado del LCD.
;El dato leído estará disponible en W.
;********************************************************************

LEES		bsf		STATUS,RP0		;Selecciona banco 1.
			movlw		0xFF				;Programa PORTB como entrada.
			movwf		TRISB				;	"
			bcf		STATUS,RP0		;Selecciona banco 0.
			LEELCD						;R/-W= 1: visualizador en modo lectura.
			ORDEN							;RS=1: visualizador en modo dato.
			ACTIVEN						;E=1: activa Enable.
			movf		PORTB,W			;Lee el dato en posición de cursor.
			BORRAEN						;E=0: desactiva Enable.
			movwf		TLCD2				;Salva dato en registro temporal.
			bsf		STATUS,RP0		;Selecciona el banco 1.
			clrf		TRISB				;Programa PORTB como salida.
			bcf		STATUS,RP0		;Selecciona banco 0.
			movf		TLCD2,W			;Recupera valor leído.
			call		R1MS
			return
