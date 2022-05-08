//
// Created by tomas on 5/4/22.
//

#ifndef SEMESTRAL_CAPPLICATION_H
#define SEMESTRAL_CAPPLICATION_H


class CApplication {

    explicit CApplication ( const std::shared_ptr<CInterface> & interface );

    CApplication ( const CApplication & ) = delete;

    CApplication & operator= ( const CApplication & ) = delete;

};


#endif //SEMESTRAL_CAPPLICATION_H
