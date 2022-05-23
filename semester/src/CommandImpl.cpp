/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */



//*    set color <id>;
//    set color <r> <g> <b>;
//
//    set fill <id>;
//    set fill <r> <g> <b>;
//
//    set thickness <int>;
//
//    draw line <pos_start> <pos_end>
//    draw polyline <pos_start> [<pos_i>...]
//
//    draw circle <pos_center> <diameter>
//    draw elipsis todo
//
//    draw rectangle <pos_left_bottom>  <pos_right_top>
//
//    draw square <pos_left_bottom> <pos_right_top>
//
//    draw pa2 <pos_left_bottom> <pos_right_top>
//
//    draw group <group_id> <pos_left_bottom>
//
//    hide shape <id>
//    hide group <id>
//
//    delete group <id>; // force delete group, so it will stop exist
//
//    new group <name> <id> [id...];
//
//    show all // get all ids of objects including their type
//    show <id>

#include "CommandImpl.h"
#include "messages.h"

/*
Command SetCommand() {
    return Command{
            COMMAND_SET,
            HELP_SET,
            [](std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface) {
                std::string commamndName = interface->PromptCommand([]{

                });
                // todo
                return true;
            }
    };
}*/

Command HelpCommand (const std::vector<Command> commands)
{
    return Command {
        COMMAND_HELP,
            HELP_HELP,
            [ &commands ] (std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface ) {
                for ( const auto & c : commands )
                    //if ( c.second.IsActive( game ) )
                        interface->PrintHelp( c.Help() );
                return true;
            }
    };
}

Command QuitCommand ()
{
    return Command {
        COMMAND_QUIT,
            HELP_QUIT,
            [] (std::shared_ptr<Tspaint> tspaint, std::shared_ptr<Interface> interface ) { return false; }
    };
}

