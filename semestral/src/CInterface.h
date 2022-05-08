//
// Created by tomas on 5/4/22.
//

#ifndef SEMESTRAL_CINTERFACE_H
#define SEMESTRAL_CINTERFACE_H

// todo: rewrite it!!!!!
// it's a copy from D. Bernhauer

class CInterface
{
private:
    std::istream & m_In;
    std::ostream & m_Out;

    CInteractiveBuffer m_Interactive;

    CInterface & Clear ();

    size_t PromptSize ( const char * message, size_t limit = -1 );

public:
    CInterface ( std::istream & in, std::ostream & out );

    CInterface & Redraw ( const CMap & map,
                          const std::vector<std::shared_ptr<CPlayer>> & players,
                          const CPlayer & current,
                          bool hasBomb );

    void Hide(const std::shared_ptr<CObject> obj);

    void Show(const std::shared_ptr<CObject> obj);

    CInterface & PrintLine ( const std::string & line );

    size_t PromptCommand ( const std::function<size_t ( const std::string & )> & valid, size_t commands );

    std::string PromptBuilderName ( const std::function<bool ( const std::string & )> & valid );

    CInterface & BeforeStart ();

    EDirection PromptDirection ( const CControls & controls );

    CInterface & AfterEnd( bool isWinner );

    std::string PromptMapFilename ();

    size_t ScreenWidth ();

    size_t ScreenHeight ();
};

#endif //SEMESTRAL_CINTERFACE_H
