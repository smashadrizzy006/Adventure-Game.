#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 10
#define MAX_ITEMS 10
#define MAX_DESC_LEN 256
#define MAX_ITEM_NAME_LEN 50

typedef struct {
    char name[MAX_ITEM_NAME_LEN];
    int is_collected;
} Item;

typedef struct {
    char description[MAX_DESC_LEN];
    int north;
    int south;
    int east;
    int west;
    Item item;
} Room;

Room rooms[MAX_ROOMS];
int current_room = 0;
Item inventory[MAX_ITEMS];
int inventory_count = 0;

void initializeGame() {
    // Room 0
    strcpy(rooms[0].description, "You are in a dark room. There is a door to the north.");
    rooms[0].north = 1;
    rooms[0].south = -1;
    rooms[0].east = -1;
    rooms[0].west = -1;
    strcpy(rooms[0].item.name, "Flashlight");
    rooms[0].item.is_collected = 0;

    // Room 1
    strcpy(rooms[1].description, "You are in a bright room. There is a door to the south and east.");
    rooms[1].north = -1;
    rooms[1].south = 0;
    rooms[1].east = 2;
    rooms[1].west = -1;
    strcpy(rooms[1].item.name, "");
    rooms[1].item.is_collected = 1;

    // Room 2
    strcpy(rooms[2].description, "You are in a mysterious room. There is a door to the west.");
    rooms[2].north = -1;
    rooms[2].south = -1;
    rooms[2].east = -1;
    rooms[2].west = 1;
    strcpy(rooms[2].item.name, "Key");
    rooms[2].item.is_collected = 0;
}

void move(int direction) {
    int next_room = -1;
    switch (direction) {
        case 0: next_room = rooms[current_room].north; break;
        case 1: next_room = rooms[current_room].south; break;
        case 2: next_room = rooms[current_room].east; break;
        case 3: next_room = rooms[current_room].west; break;
    }
    if (next_room != -1) {
        current_room = next_room;
        printf("%s\n", rooms[current_room].description);
    } else {
        printf("You can't go that way.\n");
    }
}

void collectItem() {
    if (strlen(rooms[current_room].item.name) > 0 && !rooms[current_room].item.is_collected) {
        inventory[inventory_count++] = rooms[current_room].item;
        rooms[current_room].item.is_collected = 1;
        printf("You have collected: %s\n", rooms[current_room].item.name);
    } else {
        printf("There is nothing to collect here.\n");
    }
}

void checkInventory() {
    if (inventory_count == 0) {
        printf("Your inventory is empty.\n");
    } else {
        printf("You have the following items:\n");
        for (int i = 0; i < inventory_count; i++) {
            printf("- %s\n", inventory[i].name);
        }
    }
}

void menu() {
    int choice;
    while (1) {
        printf("\n1. Move North\n2. Move South\n3. Move East\n4. Move West\n5. Collect Item\n6. Check Inventory\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: move(0); break;
            case 2: move(1); break;
            case 3: move(2); break;
            case 4: move(3); break;
            case 5: collectItem(); break;
            case 6: checkInventory(); break;
            case 7: exit(0); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    initializeGame();
    printf("Welcome to the Text-Based Adventure Game!\n");
    printf("%s\n", rooms[current_room].description);
    menu();
    return 0;
}
