/**
* @mainpage OS-Alloc
* This university project is a simulation of how the memory is handled when using "malloc" and "free" functions.<p>
* The app can be run in 4 different ways : 
* <ul>
*	<li><strong>Without argument</strong>, a test program will be launched</li>
*	<li><strong>With the argument "-i"</strong>, the app will be launched in the @subpage InteractiveMode "interactive mode".</li>
*	<li><strong>With the argument "-f"</strong>, the app will be launched and try to @subpage ReadingFile "read a file".</li>
*	<li><strong>With any other argument</strong>, the app will try to parse the @subpage CliBased "command-line arguments" in order to run the program.</li>
* </ul>
*/


/**
* @page InteractiveMode Running the interactive mode
* The interactive mode allows the user to use and see at runtime what happen.<p>
* First, it will be required to enter the number of bytes that the memory will contain.<p>
* Next the program will ask at each turn to enter a number corresponding to an action. Thse actions are : 
* <ol>
*	<li>
*		<strong>Allocate memory</strong> : the program will ask next which number of bytes have to be allocated,
*		and then create the memory zone with the function "myAlloc".
*	</li>
*	<li>
*		<strong>Desallocate memory</strong> : the contrary operation, it will require to specify after the index of the block to remove (index starting from 0).
*		this will use the "myFree" function in order to free this memory block.
*	</li>
*	<li>
*		<strong>Show the memory</strong> : simply show the memory content, with all blocks, their memory address, and the size occupied by the allocated memory.
*	</li>
*	<li>
*		<strong>End the program</strong> : Free the memory and exit the program.
*	</li>
* </ol>
*/

/**
* @page ReadingFile Running with a configuration file
* Running the program with the option <strong>-f <em>[fileName]</em></strong> will allows the program to read a file and execute each command line by line in the order.
* Each command must be on a separate line, and can start with one of this words : 
* <ul>
*	<li><strong>init</strong>, followed by the number of bytes needed, will init the memory.</li>
*	<li><strong>alloc</strong>, followed by the number of bytes needed, will create the memory zone with the function "myAlloc".</li>
*	<li><strong>desalloc</strong>, followed by the index of a block, will free the memory occupied by the block.</li>
*	<li><strong>disp</strong> will display the memory.</li>
*	<li><strong>end (optionnal)</strong> will free the memory previously allocated..</li>
* </ul>
*
* Example of a file content : 
* \code{.unparsed}
* init 25000
* alloc 120
* alloc 50
* disp
* desalloc 0
* disp
* \endcode
*/

/**
* @page CliBased Running only with command-line arguments
* In the CLI-only mode, the program will read each argument in the order and treat them directly. The arguments recognized are :
* <ul>
*	<li><strong>"-init"</strong>, followed by the number of bytes needed, will init the memory.</li>
*	<li><strong>"-alloc"</strong>, followed by the number of bytes needed, will create the memory zone with the function "myAlloc".</li>
*	<li><strong>"-desalloc"</strong>, followed by the index of a block, will free the memory occupied by the block.</li>
*	<li><strong>"-disp"</strong> will display the memory.</li>
*	<li><strong>"-end" (optionnal)</strong> will free the memory previously allocated..</li>
* </ul>
*/