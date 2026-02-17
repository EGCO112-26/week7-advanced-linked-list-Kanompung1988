
// self-referential structure (doubly linked list with id and name)
struct Node {
   int id;
   char name[50];
   struct Node *nextPtr; // pointer to next node
   struct Node *prevPtr; // pointer to previous node
}; // end structure Node

typedef struct Node LLnode; // synonym for struct Node
typedef LLnode *LLPtr; // synonym for LLnode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int id, char name[] );
void printList( LLPtr currentPtr );
void instructions( void );
void clearAll( LLPtr *sPtr );


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order by id
void insert( LLPtr *sPtr, int id, char name[] )
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr = (LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = id;
      strcpy( newPtr->name, name );
      newPtr->nextPtr = NULL;
      newPtr->prevPtr = NULL;

      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list (sorted by id)
      while ( currentPtr != NULL && id > currentPtr->id ) {
         previousPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
      } // end while

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
         if ( *sPtr != NULL ) {
            ( *sPtr )->prevPtr = newPtr;
         }
         *sPtr = newPtr;
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->prevPtr = previousPtr;
         newPtr->nextPtr = currentPtr;
         if ( currentPtr != NULL ) {
            currentPtr->prevPtr = newPtr;
         }
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", id );
   } // end else
} // end function insert

// delete a list element by id
int deletes( LLPtr *sPtr, int value )
{
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   currentPtr = *sPtr;

   // loop to find the node with matching id
   while ( currentPtr != NULL && currentPtr->id != value ) {
      currentPtr = currentPtr->nextPtr;
   } // end while

   if ( currentPtr != NULL ) {
      tempPtr = currentPtr;

      // if deleting first node
      if ( currentPtr->prevPtr == NULL ) {
         *sPtr = currentPtr->nextPtr;
      } else {
         currentPtr->prevPtr->nextPtr = currentPtr->nextPtr;
      }

      // if not deleting last node
      if ( currentPtr->nextPtr != NULL ) {
         currentPtr->nextPtr->prevPtr = currentPtr->prevPtr;
      }

      free( tempPtr );
      return value;
   } // end if

   return 0;
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list forward and backward
void printList( LLPtr currentPtr )
{
   LLPtr lastPtr = NULL;

   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "The list is:" );

      // print forward
      while ( currentPtr != NULL ) {
         if ( currentPtr->nextPtr != NULL ) {
            printf( "%d %s --> ", currentPtr->id, currentPtr->name );
         } else {
            printf( "%d %s -->NULL\n", currentPtr->id, currentPtr->name );
            lastPtr = currentPtr;
         }
         currentPtr = currentPtr->nextPtr;
      } // end while

      // print backward
      currentPtr = lastPtr;
      while ( currentPtr != NULL ) {
         if ( currentPtr->prevPtr != NULL ) {
            printf( "%d %s --> ", currentPtr->id, currentPtr->name );
         } else {
            printf( "%d %s -->NULL\n", currentPtr->id, currentPtr->name );
         }
         currentPtr = currentPtr->prevPtr;
      } // end while
   } // end else
} // end function printList

// clear all nodes and free memory
void clearAll( LLPtr *sPtr )
{
   LLPtr tempPtr;
   puts( "Clear all nodes" );
   while ( *sPtr != NULL ) {
      tempPtr = *sPtr;
      printf( "delete %d\n", tempPtr->id );
      *sPtr = ( *sPtr )->nextPtr;
      free( tempPtr );
   }
} // end function clearAll
