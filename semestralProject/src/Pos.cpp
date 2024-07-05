/**
  * @author Tomas Dostal <dostato6@fit.cvut.cz> 
  * @date 08.05.2022
  */

#include "Pos.h"

std::shared_ptr<Pos> Pos::Clone(){
    return std::make_shared<Pos>(x, y);
}
