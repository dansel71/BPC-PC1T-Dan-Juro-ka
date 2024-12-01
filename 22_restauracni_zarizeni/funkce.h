// funkce.h

# pragma once

typedef struct Review;
typedef struct Restaurant;
Restaurant* createRestaurant(char* name);
void addRestaurant(Restaurant** head, char* name, int writeInfo);
Restaurant* findRestaurant(Restaurant* head, char* name);
void deleteRestaurant(Restaurant** head, char* name);
Review* createReview(int rating, char* comment);
void addReview(Restaurant* restaurant, int rating, char* comment, int writeInfo);
void listRestaurants(Restaurant* head);
void saveDatabase(Restaurant** head);
void loadDatabase(Restaurant** head);


// bonus

void sortByRating(Restaurant** head);
void sortRestaurantsAlphabetically(Restaurant** head);


