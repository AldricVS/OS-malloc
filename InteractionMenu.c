#include "InteractionMenu.h"

void showMenu() {
	printf("\n\n");
	printf("****************************************************\n");
	printf("* Enter the number for which action you want to do *\n");
	printf("****************************************************\n");
	printf("* 1 - Initialize the Memory \n");
	printf("* 2 - Create a block inside the memory\n");
	printf("* 3 - Free a block from the list of avaible block\n");
	printf("* 4 - Display the memory states\n");
	printf("* 5 - Free the memory, allowing to create another\n");
	printf("* 6 - Exit the program\n");
	printf("****************************************************\n");
}

void interactionLoop() {
    int condition = 0;
    int choice, option = 0;
    // While user want to continue to "play"
    while (condition == 0) {

        showMenu();
        option = 0;
        printf("Make your choice: ");
        scanf("%d", &choice);
        // Flush the std input in order to don't read other characters
        fseek(stdin, 0, SEEK_END);
        printf("\n");

        switch(choice) {
        case 1:
        	printf("Choose the size of the memory to create: ");
			scanf("%d", &option);
			printf("\n");
            initMem(option);
            break;
        case 2:
        	printf("Choose the size of the block to add: ");
			scanf("%d", &option);
			printf("\n");
            allocBlock(option);
            break;
        case 3:
        	printf("Choose which block in the list to remove: ");
			scanf("%d", &option);
			printf("\n");
            desallocBlock(option);
            break;
        case 4:
            displayMem();
            break;
        case 5:
            clearMem();
            break;
		case 6:
			condition = 1;
			break;
        default:
            printf("\nUnknown value, please a number between 1 and 6\n");
        }
        // second flush needed sometimes (when 2 input are needed)
        fseek(stdin, 0, SEEK_END);
    }
}




