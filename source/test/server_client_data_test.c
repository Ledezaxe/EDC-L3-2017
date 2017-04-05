#include "server_client_data.h"
int main()
{

  List_Client * t = server_create_list( 5 );
  // Client_Data * test = server_create_void();
  Client_Data * t1 = server_create_client( "niko0" , "001" );

  server_list_add_client( t , t1 );
  debug_list_client_print( t );
  debug_list_client_print( t );
  server_list_rem_client_id( t , "001" );

  debug_list_client_print( t );
  destroy_list_client( t );

  // destroy_client(test);

  // destroy_client(t1);

  // server_client_reset(test,"ouiii","non");

  // Client_Data * t1 = server_create_client("niko0","001");
  // Client_Data * t2 = server_create_client("niko1","002");
  //Client_Data * t3 = server_create_client("niko2","003");
  /*Client_Data * t4 = server_create_client("niko4","004");


  server_list_add_client(t,t1);
  server_list_add_client(t,t2);


  server_list_client_set_word(t,t1->id,50);
  server_list_rem_client(t,t3);
  server_list_add_client(t,t3);
 //
  server_list_rem_client(t,t2);
  server_list_add_client(t,t4);
  server_list_client_reset(t,t1->id);
  //debug_list_client_print(t);
  destroy_list_client(t);
//  destroy_client(test);
*/
  return 0;
}
 