/* 
Disk Sector Search is a little software made using the gtk library that make a low level search 
of a single string in all sectors of disk! If the software find the string that the user have 
insert it return the number of sector that contain the string. Otherwise if don't find the string the 
software return an Error String. 

[*] Author 		: Cyberdude
[*] Mailto 		: viromarquantebello(at)libero(dot)it
[*] Date   		: 17/09/2006
[*] Lenguage 		: Assebler for gcc compiler
[*] Operativ System 	: Unix 
[*] How to compile 	: gcc DSS.s `pkg-config --cflags --libs gtk+-2.0` 
[*] How to run 		: sudo /home/.../a.out   
  
*/

info:		.string		"[*] Searching\n -> The string: %s\n -> In device : %s\n"
read:		.string		"r"
errRoot:	.string		"[*] Error: You must be Root\n"
find:		.string		"[*] String find in sector number: %d\n"
errStr:		.string		"[*] Error: String not find in device"
title:		.string		"Disk Sector Search"
strEx1:		.string		"/dev/hda"
strEx2:		.string		"init"
butLab:		.string		"Search"
click:		.string		"clicked"
textLab:	.string		"-- Cyberdude's low level searcher -- \n	- heppy asmcode to all -"

		.comm		window,4,4
		.comm		box,4,4
		.comm		button,4,4
		.comm		entry,4,4
		.comm		entry2,4,4
		.comm		label,4,4

input:
	subl	$40, %esp
	movl	$0, -4(%ebp)				/* create count of sector and put it in -4(%ebp)*/

	movl	$512, (%esp)				/* call malloc to allocate 512 byte of memory */
	call	malloc					/* and put this in -16(%ebp)*/
	movl	%eax, -16(%ebp)

	call	gtk_entry_get_type			/* call gtk_entry_get_type to receiv information */
	movl	%eax, 4(%esp)				/* from main! put it in 4(%esp) becouse after */
	movl	entry, %eax				/* I must call g_type_check_instance_cast with the*/
	movl	%eax, (%esp)				/* entry of gtk method in main */
	call	g_type_check_instance_cast		/* call g_type_check_instance_cast and put the result*/
	movl	%eax, (%esp)				/* in (%esp) to call the next method gtk_entry_get_text*/
	call	gtk_entry_get_text			/* to obtain the text of entryBox. Put this text in */
	movl	%eax, -8(%ebp)				/* -8(%ebp) */

	call	gtk_entry_get_type			/* the same of prev block of istruction*/
	movl	%eax, 4(%esp)				/* in this time i obtain the string that I must*/
	movl	entry2, %eax				/* search in the device that I have obtained */
	movl	%eax, (%esp)				/* in the prev block.*/
	call	g_type_check_instance_cast		/* I put this string in register address -12(%ebp)*/
	movl	%eax, (%esp)
	call	gtk_entry_get_text
	movl	%eax, -12(%ebp)

	movl	-8(%ebp), %eax				/* I take the string to search and the device */
	movl	%eax, 8(%esp)				/* and move they in 4(%esp) and 8(%esp) after */
	movl	-12(%ebp), %eax				/* I take the info string and call the */
	movl	%eax, 4(%esp)				/* printf method to show to the user */
	movl	$info, (%esp)				/* the string and the device that he */
	call	printf					/* have insert in the gtk box*/

	movl	$read, 4(%esp)				/* I move the read char : "r" in 4(%esp)*/
	movl	-8(%ebp), %eax				/* and the device string from the address -8(%ebp)*/
	movl	%eax, (%esp)				/* in (%esp) to call the function fopen that */
	call	fopen					/* try to open the device as a simple file...*/
	movl	%eax, -20(%ebp)				/* I put the return of call to fopen in -20(%ebp)*/

	cmpl	$0, -20(%ebp)				/* I compare the return of call to fopen with */
	jne	isEnd					/* the value 0 if it is different continue*/

	movl	$errRoot, (%esp)			/* else move the errRoot string in (%esp)*/
	call	printf					/* call the method printf end exit from */
	movl	$0, (%esp)				/* the process with a call to method exit*/
	call	exit

isEnd:
	movl	-20(%ebp), %eax				/* if the return of call to the fopen method is */
	movl	%eax, (%esp)				/* different from 0 it is a pointer to the file */
	call	feof					/* (the device) and I call feof method to know if */
	testl	%eax, %eax				/* it is the end of device. If it isn t and of  */
	je	continue				/* file i continue else jump to end block of  */
	jmp	end					/* istruction to exit from the process */

continue:
	movl	-20(%ebp), %eax				/* if the return of testl is 0 it isn t the end */ 
	movl	%eax, 12(%esp)				/* of file and I move the pointer to the device */
	movl	$1, 8(%esp)				/* opened in 12(%esp) the value 1 in 8(%esp) */
	movl	$512, 4(%esp)				/* the value 512 in 4(%esp) and the pointer of */
	movl	-16(%ebp), %eax				/* allocated space addressed in -16(%ebp) in  */
	movl	%eax, (%esp)				/* %eax and in (%esp) so that I can call the  */
	call	fread					/* fread method to read 512 byte from the  */
	leal	-4(%ebp), %eax				/* current position of device opened.After I */
	incl	(%eax)					/* increment the count of sector readed */

	movl	-12(%ebp), %eax				/* Now I move the string that I must search in */
	movl	%eax, 4(%esp)				/* 4(%esp) and the allocated space that now  */
	movl	-16(%ebp), %eax				/* contain the string of 512 byte that I have read */
	movl	%eax, (%esp)				/* from device in (%esp). I call the strstre method */
	call	strstr					/* to control if the string that I want is in the  */
	testl	%eax, %eax				/* allocated space. If the testl is 0 the string  */
	je	isEnd					/* is not present and I must continue to search */

	movl	-4(%ebp), %eax				/* Else if I have find the string that I want */
	movl	%eax, 4(%esp)				/* I move the count of sector in 4(%esp)  */
	movl	$find, (%esp)				/* I move the find string in (%esp) and I call */
	call	printf					/* the method printf  */

	movl	$0, (%esp)				/* I move 0 value in (%eps) and call the exit */
	call	exit					/* to kill the process */

end:
	movl	$errStr, (%esp)				/* if the return of feof is not 0 I stay to  */
	call	printf					/* the end of device and I must exit  */
	movl	$0, (%esp)				/* I move the error string in (%esp) and call */
	call	exit					/* print method and exit method */


.globl main
main:
	movl	%esp, %ebp 
	subl	$24, %esp
	andl	$-16, %esp 
	movl	$0, %eax
	subl	%eax, %esp

	leal	12(%ebp), %eax				/* I leal 12(%ebp) and 8(%ebp) becouse they are */
	movl	%eax, 4(%esp)				/* the address of register that contain the */
	leal	8(%ebp), %eax				/* int argc, char *argv[] that I must give in input */
	movl	%eax, (%esp)				/* to the gtk_init method and I move this in (%esp) end */
	call	gtk_init				/* 4(%esp) so I call the gtk_init  */

	movl	$0, (%esp)				/* after move the value 0 in (%esp) and call the*/
	call	gtk_window_new				/* gtk_window_new method to crete new window*/
	movl	%eax, window				/* and assign the return to the window object */

	call	gtk_window_get_type			/* After I obtain the type of object called the method */
	movl	%eax, 4(%esp)				/* gtk_window_get_type and move this in 4(%esp) after */
	movl	window, %eax				/* move the object window in (%esp) so that I can call */
	movl	%eax, (%esp)				/* the method g_type_check_instance_cast that I use to */
	call	g_type_check_instance_cast		/* assign the title to the window created in the first */
	movl	$title, 4(%esp)				/* moment. I move the title string in 4(%esp) and the */
	movl	%eax, (%esp)				/* typecast in the (%esp) and call the gtk_window_set_title*/
	call	gtk_window_set_title			/* method! in C this is: */
							/* gtk_window_set_title(GTK_WINDOW (window),"Disk Sector Search");*/

	call	gtk_container_get_type			/* Now I must repeat the same opeation to obtain the */
	movl	%eax, 4(%esp)				/* typecast of the container and i move this in 4(%esp) */	
	movl	window, %eax				/* after move the object window in (%esp) and call the */
	movl	%eax, (%esp)				/* g_type_check_instance_cast method. After move the */
	call	g_type_check_instance_cast		/* value 50 in 4(%esp) and the typecast returned from the */
	movl	$50, 4(%esp)				/* call of g_type_check_instance_cast in (%esp) and now */
	movl	%eax, (%esp)				/* I can call the method gtk_container_set_vorder_width */
	call	gtk_container_set_border_width		/* to set the width and height of object window to 50 */ 	

	movl	$0, 4(%esp)				/* Now I must take 0 value in (%esp) and 4(%esp) to call */ 
	movl	$0, (%esp)				/* the method gtk_vbox_new to create a new box */
	call	gtk_vbox_new				/* I call the method gtk_vbox_new and assign the return */
	movl	%eax, box				/* to object named box */

	call	gtk_container_get_type			/* After I must call the method gtk_container_get_type to */
	movl	%eax, 4(%esp)				/* obtain the type of the container and I move it in */
	movl	window, %eax				/* 4(%esp) after i move the object window in the address */
	movl	%eax, (%esp)				/* registry (%esp). After I call the g_type_check_instance_cast */
	call	g_type_check_instance_cast		/* method so I have created this GTK_CONTAINER (window) */
	movl	%eax, %edx				/* Now I move this in %edx becouse I must use it after. */
	movl	box, %eax				/* Noi I move the object box in 4(%esp) and the typecast of */
	movl	%eax, 4(%esp)				/* object window that is in %edx in (%esp) so I have obtened */
	movl	%edx, (%esp)				/* this (GTK_CONTAINER (window), box) and I can call the */
	call	gtk_container_add			/* gtk_container_add method to insert the window in the box */

	movl	box, %eax				/* Now I move the box object in (%esp) and I call the */
	movl	%eax, (%esp)				/* gtk_widget_show method to insert the box in the */
	call	gtk_widget_show				/* principal form */

	call	gtk_entry_new				/* After that I can call the gtk_entry_new to create an entry */
	movl	%eax, entry				/* and assign the returnament of this call in object entry */

	call	gtk_entry_get_type			/* With gtk_entry_get_type I can obtain the type of */
	movl	%eax, 4(%esp)				/* entry and I move it in 4(%esp) */
	movl	entry, %eax				/* Now move the entry object in (%esp) and call the */
	movl	%eax, (%esp)				/* g_type_check_instance_cast method to obtain */
	call	g_type_check_instance_cast		/* this GTK_ENTRY (entry) */
	movl	$50, 4(%esp)				/* After I move the value 50 in 4(%esp) and */
	movl	%eax, (%esp)				/* the typecast in (%esp) and call the */
	call	gtk_entry_set_max_length		/* gtk_entry_set_max_lenght method to set the max */	
							/* number of char that the entry can contain */

	call	gtk_entry_get_type			/* Now I repeat the same operation to obtain the */			
	movl	%eax, 4(%esp)				/* GTK_ENTRY (entry) */
	movl	entry, %eax
	movl	%eax, (%esp)
	call	g_type_check_instance_cast 

	movl	$strEx1, 4(%esp)			/* After I move the string to insert in the entry */
	movl	%eax, (%esp)				/* in 4(%esp) and the typecast in (%esp) */
	call	gtk_entry_set_text			/* and call the gtk_entry_set_text method to set the text */

	call	gtk_box_get_type			/* Now I call the gtk_box_get_type to obtain the type of*/
	movl	%eax, 4(%esp)				/* box and I move this in 4(%esp)*/
	movl	box, %eax				/* After I move the box object in (%esp) and call the */
	movl	%eax, (%esp)				/* g_type_check_instance_cast method to obtain this */
	call	g_type_check_instance_cast		/* GTK_BOX (box)*/	
	movl	%eax, %edx				/* Move this in %edx to mantein this*/

	movl	$0, 16(%esp)				/* Now move che value 0 in 16(%esp) the value */
	movl	$1, 12(%esp)				/* 1 in 12(%esp) and the value 1 in 8(%esp) */
	movl	$1, 8(%esp)				/* After I move the object entry in 4(%esp) */
	movl	entry, %eax				/* and the typecast obtened in the first moment */
	movl	%eax, 4(%esp)				/* int the registry address (%esp) */
	movl	%edx, (%esp)				/* Now I can call the gtk_box_pack_start method as */
	call	gtk_box_pack_start			/* gtk_box_pack_start (GTK_BOX (box), entry, TRUE, TRUE, 0);*/

	movl	entry, %eax				/* Now I move the entry in (%esp) and call */
	movl	%eax, (%esp)				/* che gtk_widget_show method so now the entry is */
	call	gtk_widget_show				/* visible in the box created first*/

	call	gtk_entry_new				/* Now I repeat the same operation of first */
	movl	%eax, entry2				/* for the entry2 with the same caracteristics */

	call	gtk_entry_get_type
	movl	%eax, 4(%esp)
	movl	entry2, %eax
	movl	%eax, (%esp)
	call	g_type_check_instance_cast
	movl	$50, 4(%esp)
	movl	%eax, (%esp)
	call	gtk_entry_set_max_length

	call	gtk_entry_get_type
	movl	%eax, 4(%esp)
	movl	entry2, %eax
	movl	%eax, (%esp)
	call	g_type_check_instance_cast

	movl	$strEx2, 4(%esp)			/* The difference between entry and entry2 is that*/
	movl	%eax, (%esp)				/* only the text */
	call	gtk_entry_set_text

	call	gtk_box_get_type
	movl	%eax, 4(%esp)
	movl	box, %eax
	movl	%eax, (%esp)
	call	g_type_check_instance_cast
	movl	%eax, %edx

	movl	$0, 16(%esp)
	movl	$1, 12(%esp)
	movl	$1, 8(%esp)
	movl	entry2, %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	gtk_box_pack_start

	movl	entry2, %eax
	movl	%eax, (%esp)
	call	gtk_widget_show				/* Now entry2 too is visible in the principal form */


	movl	$butLab, (%esp)				/* Now I must creat a button so I move the label of */
	call	gtk_button_new_with_label		/* button in (%esp) and I call the gtk_button_new_with_label */
	movl	%eax, button				/* method and assign the return to the button object */

	movl	$80, 4(%esp)				/* Now move the value 80 in 4(%esp) and the button */
	movl	button, %eax				/* created in the prev block of code in (%esp) */
	movl	%eax, (%esp)				/* and call the g_type_check_instance_cast */
	call	g_type_check_instance_cast		/* method to obtain this G_OBJECT (button) */
	movl	$0, 20(%esp)				/* After move the 0 value in the registry address */
	movl	$0, 16(%esp)				/* 20(%esp) 16(%esp) and 12(%esp) after move the */
	movl	$0, 12(%esp)				/* call of method input in 8(%esp), the text clicked in */
	movl	$input, 8(%esp)				/* 4(%esp) after move the button with cast created in the */
	movl	$click, 4(%esp)				/* prev block of code in (%esp) and so that I have created */
	movl	%eax, (%esp)				/* this C strin : (G_OBJECT (button), "clicked", G_CALLBACK (input), NULL)*/
	call	g_signal_connect_data			/* and now I can call g_signal_connect_data to assign */
							/* a method to the pression of the button*/

	movl	button, %eax				/* After I move the object button in (%esp) */
	movl	%eax, (%esp)				/* and I can call the gtk_widget_show to */
	call	gtk_widget_show				/* see the button in the principal form */

	call	gtk_box_get_type			/* Now I must insert in the box and so that */
	movl	%eax, 4(%esp)				/* I must call the gtk_box_get_type and move this */
	movl	box, %eax				/* in the 4(%esp) so I move the object box in (%esp) */
	movl	%eax, (%esp)				/* and call the g_type_check_instance_cast to obtein */
	call	g_type_check_instance_cast		/* this GTK_BOX (box) and move this in registry address*/
	movl	%eax, %edx				/* %edx becouse I must use it in the second time */

	movl	$0, 16(%esp)				/* Now I move the 0 value in 16(%esp) and 1 in */
	movl	$1, 12(%esp)				/* 12(%esp) and 8(%esp) after I move button */
	movl	$1, 8(%esp)				/* object in 4(%esp) and the returnament of */
	movl	button, %eax				/* prev block of code in (%esp) to obtain this: */
	movl	%eax, 4(%esp)				/* (GTK_BOX (box), button, TRUE, TRUE, 0) */
	movl	%edx, (%esp)				/* Now I can call the gtk_box_pack_start method */
	call	gtk_box_pack_start			/* To insert the box in my box*/

	movl	$textLab, (%esp)			/* Now move the text of label in (%esp) */
	call	gtk_label_new				/* and creat the label with the method gtk_label_new */
	movl	%eax, label				/* and assign the returnament to the label object */

	movl	label, %eax				/* Now move this label in (%esp) and I call the */
	movl	%eax, (%esp)				/* gtk_widget_show method */
	call	gtk_widget_show

	call	gtk_box_get_type			/* Now I call the gtk_box_get_type to obtein the */
	movl	%eax, 4(%esp)				/* typecast of the box and move this in 4(%esp) */
	movl	box, %eax				/* I move the box object in (%esp) and call the */
	movl	%eax, (%esp)				/* g_type_check_instance_cast method... */
	call	g_type_check_instance_cast		/* all is the same of the several block of prev code */
	movl	%eax, %edx
	movl	$0, 16(%esp)		
	movl	$1, 12(%esp)
	movl	$1, 8(%esp)
	movl	label, %eax				/* Now I move the label object in 4(%esp) */
	movl	%eax, 4(%esp)				/* and the typecast in (%esp) */
	movl	%edx, (%esp)
	call	gtk_box_pack_start			/* After call the gtk_box_pack_start */

	movl	window, %eax				/* Now I move the window object in (%esp)*/
	movl	%eax, (%esp)				/* and I can call the gtk_widget_show method */
	call	gtk_widget_show				/* to see the window */
	call	gtk_main				/* Now call gtk_main and the game started :p */
