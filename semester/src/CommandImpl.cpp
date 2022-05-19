/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz>
  * @date 19.05.2022
  */

#pragma once



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
#include "FormatterParams.h"

Command SetCommand() {
    return Command{
            COMMAND_HELP,
            HELP_SET,
            [](Tspaint &tspaint, const Interface &interface) {
                Command &command = interface.PromptCommandOption({"color"});
                command.Execute(tspaint, interface);

                Coord coord = interface.PromptColor(PROMPT_MARK, {}, [&tspaint](const CCoord &coord) {
                    return game.IsValid(coord);
                }, ERROR_INVALID_COORD);

                if (game.MarkMine(coord)) {
                    interface.Message(SUCCESS_MARK, FormatterParams{coord});
                    interface.PrintGame(game.Draw());
                } else {
                    interface.Message(ERROR_INVALID_MARK, FormatterParams{coord});
                }

                return true;
            }
    };
}