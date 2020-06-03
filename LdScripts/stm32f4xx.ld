 /******************************************************************************
 * @file	stm32f4xx.ld
 * @author	Малышев Сергей  <onega.malishev@yandex.ru>
 * @version v1.0
 * @date	20/06/2019
 * @brief	stm32f407 Devices linker script
 * 			
 ********************************************************************************
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2019 "KeyPi"
 *********************************************************************************/
 
/* Specify the memory areas */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Aliases */
REGION_ALIAS("CODE_FLASH", FLASH);
REGION_ALIAS("DATA_RAM", RAM);
REGION_ALIAS("BSS_RAM", RAM);

/* Требуемый размер стека, 4 Кбайт*/
_Stack_Size = 0x1000; 

/* Конец RAM на stm32f407VG, отсюда внутрь будет расти стек*/
_estack = ORIGIN(RAM) + LENGTH(RAM); 

/* Entry Point */
ENTRY(Reset_Handler)

/* Define output sections */
SECTIONS
{	
	/* Таблица векторов прерываний располагается первой во FLASH */
	.isr_vector :
  	{
    	KEEP(*(.isr_vector)) /* Таблица векторов прерываний */
    	. = ALIGN(4);
  	} >CODE_FLASH
  	
	.text :
	{
		. = ALIGN(4);
		*(.text) 			/* .text sections (code) */
		*(.text*)			/* .text* sections (code) */
		
		*(.rodata) 		   	/* .rodata sections (constants, strings, etc.) */
		*(.rodata*)			/* .rodata* sections (constants, strings, etc.) */
		
		*(.glue_7)        	/* glue arm to thumb code */
    	*(.glue_7t)        	/* glue thumb to arm code */
    	
    	KEEP(*(.init))
		KEEP(*(.fini))
		
		. = ALIGN(4);
		_etext = .; 		/* указатель на конец кода*/ 			
	} > CODE_FLASH

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > CODE_FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} > CODE_FLASH	

	
	/* .preinit_array - секция для указателей на функции преинициализации,
    *                  вызываемых перед любыми другими функциями
    *                  инициализации (перед выполнением кода из секции
    *                  '.init' и вызовами функций из секции '.init_array').
    *
    * Специальная секция с именем '.preinit_array' и вышеназванным
    * назначением описана в System V gABI. Вызов функций, указатели на
    * которые содержатся в секции '.preinit_array', возлагается на библиотеку
    * времени выполнения (runtime library) -- например, на C runtime. Если в
    * библиотеке не предусмотрен такой вызов, то функции из секции
    * '.preinit_array' не будут вызваны.
    *
    * Секция '.preinit_array' предназначена для пре-инициализации
    * исполняемого файла (executable), выполняемой перед инициализацией
    * динамически скомпонованных с ним разделяемых объектов (shared objects).
    *
    * Символы __preinit_array_start и __preinit_array_end используются
    * библиотекой C времени выполнения (newlib, glibc).
    */
	.preinit_array     :
  	{
    	PROVIDE_HIDDEN (__preinit_array_start = .);
    	KEEP (*(.preinit_array*))
    	PROVIDE_HIDDEN (__preinit_array_end = .);
  	} >CODE_FLASH
  
  
    /* .init_array - секции с указателями на функции инициализации,
    *               выполняющиеся перед вызовом входной точки программы, т.е.
    *               перед вызовом функции main.
    *
    * Специальная секция с именем '.init_array' и вышеназванным назначением
    * описана в System V gABI. Вызов функций, указатели на которые содержатся в
    * секции '.init_array', возлагается на библиотеку времени выполнения
    * (runtime library) -- например, на C runtime. Если в библиотеке не
    * предусмотрен такой вызов, то функции из секции '.init_array' не будут
    * вызваны.
    *
    * GCC использует секцию '.init_array' для обеспечения вызова статических
    * конструкторов: функций, объявленных с __attribute__((constructor)).
    *
	* Для статических конструкторов с объявленным приоритетом PRIORITY,
    * используются секции с именем '.init_array.PRIORITY'
    *
    * Также GCC использует секцию '.init_array' для вызова конструкторов
    * статических объектов C++.
    *
    * Символы __init_array_start и __init_array_end используются библиотекой
    * C времени выполнения (newlib, glibc).
    */
  	.init_array :
  	{
    	PROVIDE_HIDDEN (__init_array_start = .);
    	KEEP (*(SORT(.init_array.*)))
    	KEEP (*(.init_array*))
    	PROVIDE_HIDDEN (__init_array_end = .);
  	} >CODE_FLASH
  	
  	
  	/* .fini_array - секции с указателями на функции терминации,
    *               выполняющиеся по завершению программы (после возврата из
    *               входной точки программы, т.е. из функции main).
	*
    * Специальная секция с именем '.fini_array' и вышеназванным назначением
    * описана в System V gABI. Вызов функций, указатели на которые содержатся в
    * секции '.fini_array', возлагается на библиотеку времени выполнения
    * (runtime library) -- например, на C runtime. Если в библиотеке не
    * предусмотрен такой вызов, то функции из секции '.fini_array' не будут
    * вызваны.
    *
    * GCC использует секцию '.fini_array' для обеспечения вызова статических
    * деструкторов: функций, объявленных с __attribute__((destructor)).
    *
    * Для статических деструкторов с объявленным приоритетом PRIORITY,
    * используются секции с именем '.fini_array.PRIORITY'
    *
    * Символы __fini_array_start и __fini_array_end используются библиотекой
    * C времени выполнения (newlib, glibc).
    */
  	.fini_array :
  	{
    	PROVIDE_HIDDEN (__fini_array_start = .);
    	KEEP (*(.fini_array*))
    	KEEP (*(SORT(.fini_array.*)))
    	PROVIDE_HIDDEN (__fini_array_end = .);
  	} >CODE_FLASH
  
	/* Адрес начала секции данных во Flash. Используется при инициализации data section */
    _sidata = .;
  	
  	/* Выражение _sidata, которое следует за ключевым словом AT, 
    * определяет адрес загрузки секции. По умолчанию, если Вы 
    * не использовали ключевое слово AT, адрес загрузки равен адресу перемещения. 
    * Так как _sidata до этого было равно точке (указатель на текущий адрес),
    * то .data пойдет сразу дальше после неё. Как бы динамическое смещение такое. 
    * 
	*/
	.data : AT ( _sidata )
	{
		. = ALIGN(4);				
		_sdata = .;			/* define a global symbol at data start */  	
   		 
		*(.data)			/* .data sections */
		*(.data*)			/* .data* sections */

		. = ALIGN(4);	
		_edata = .;    		/* define a global symbol at data end */

	} > DATA_RAM

	/* Секция неинициализированных данных (bss) */
	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;		/* define a global symbol at bss start */
		_sbss = __bss_start__;
		
		*(.bss)
		*(.bss*)
		*(COMMON)
		
		. = ALIGN(4);
		__bss_end__ = .;		/* define a global symbol at bss end */
		_ebss = __bss_end__;	
		
	} > BSS_RAM

	/* Функци проверяет, что после всего кода осталось место под стек. 
   	* Стек сделан снизу оперативки!
   	* Не размещайте свои секции после этой функции, только перед!*/
  	._user_heap_stack :
  	{
    	. = ALIGN(4);
    	PROVIDE ( end = . );
    	PROVIDE ( _end = . );
    	. = . + _Stack_Size + 4;
    	. = ALIGN(4);
  	} >RAM
	
	/* Remove information from the standard libraries */
  	/DISCARD/ :
  	{
    	libc.a ( * )
    	libm.a ( * )
    	libgcc.a ( * )
  	}
    .ARM.attributes 0 : { *(.ARM.attributes) }
}

