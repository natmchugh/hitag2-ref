#include <stdio.h>
#include <string.h>

struct state;
typedef void state_fn(struct state *);

struct state
{
   state_fn * next;
   char input[11]; 
   int i;
};

state_fn un_authed, pre_auth, authed;

void pre_auth(struct state * state)
{
   printf("Mode: %s\n", __func__);
   char start_auth[] = "START_AUTH";
   if (0 == strncmp(start_auth, state->input, 10)) {
      printf("1 1 1 1 1 + serial number\n");
      state->next = un_authed;
   }
     
}

void un_authed(struct state * state)
{
   printf("Mode: %s\n", __func__);
   char password[] = "BDF5E846";
    if (0 == strncmp(password, state->input, 8)) {
      printf("1 1 1 1 1 + page 3\n");
      state->next = authed;
    }
      
}

void authed(struct state * state)
{
   printf("Mode: %s\n", __func__);

}

int main(void)
{
   char  input[11];
   
   struct state state = { pre_auth, 0 };

   while (state.next) {
      printf ("WAITING FOR INPUT: ");
      fgets(input, sizeof(input), stdin);
      strcpy(state.input, input);
      state.next(&state);
   }

}


// mission is to emulate hitag2 tag statemachine in password mode
// reader sends start auth
// respond with start sequence and serial number
// reader sends password
// respond with start sequence and page 3
// then goes into mode where can ask to read pages in any order and with bits inverted
//respond with the correct page


