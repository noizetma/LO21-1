#ifndef TRANSITIONRULE_H
#define TRANSITIONRULE_H
#include "etat.h"
#include <string>
#include <vector>

class TransitionRule
{
public:
    TransitionRule() = default;
    virtual void EffectuerTransition(Etat const& depart, Etat& arrivee) const;
    virtual void TransitionCellule(Cell const& depart, Cell& arrivee) const = 0;
    virtual std::string getTransition() const = 0;
    virtual ~TransitionRule()= default;
};

class TransitionRule1D : public TransitionRule
{
public:
    TransitionRule1D() = default;
    ~TransitionRule1D() = default;
};

class ElementaryRule : public TransitionRule1D
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
    ElementaryRule(std::string rule, unsigned int nbEtats) : TransitionRule1D(), m_rule(rule), m_nbEtats(nbEtats)
    {
        if (m_nbEtats>10) throw AutomateException("Erreur: nombre d'etats de la regle élementaire > 10 , cela n'est pas pris en charge");
    }
    std::string getTransition() const override;
    ~ElementaryRule() = default;
protected:
    std::string m_rule;
    unsigned int m_nbEtats;
};

class TransitionRule2D : public TransitionRule
{

};

class GameOfLife : public TransitionRule2D //nombre d'Etats forcément = à 2 !!!!!!!!
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
    GameOfLife(int minVoisinsVivants,int maxVoisinsVivants ) : TransitionRule2D(), m_minVoisinsVivants(minVoisinsVivants), m_maxVoisinsVivants(maxVoisinsVivants)
    {

    }
    std::string getTransition() const override;
    ~GameOfLife() = default;
protected:
    int m_minVoisinsVivants;
    int m_maxVoisinsVivants;
};
class FeuForet : public TransitionRule2D //nombre d'Etats forcément = à 2 !!!!!!!!
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
    FeuForet() = default;
    std::string getTransition() const override;
    ~FeuForet() = default;
};

#endif // TRANSITIONRULE_H
