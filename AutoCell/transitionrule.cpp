/*!
 * \file transitionrule.cpp
 * \brief Implémentation des méthodes non inline des classes de < em>"transitionrule.h"< /em>
 * \version 1.0
 * \sa transitionrule.h
 */

#include "transitionrule.h"
using namespace std;

void TransitionRule::EffectuerTransition(const Etat &depart, Etat &arrivee) const
{
    for(int i = 0;i<depart.GetLargeur();i++)
    {
        for(int j=0; j<depart.GetLongueur();j++)
            TransitionCellule(depart.GetCellule(i,j),arrivee.GetCellule(i,j));
    }
}

void ElementaryRule::TransitionCellule(const Cell &depart, Cell &arrivee) const
{
    vector<Cell*> const& voisins = depart.GetVoisins();
    int somme = 0;
    int k = 1;
    for(int i= voisins.size()-1;i>=0;i--)
    {
        if(voisins[i] == nullptr) k *= m_nbEtats;
        else
        {
            somme += voisins[i]->GetEtat()%m_nbEtats*k; //on rajoute un %m_nbEtats au cas où la grille a des cellules qui ont dépassé le plus grand état possible pour une raison inconnue afin de s'assurer de n'avoir aucun bug éventuel
            k *= m_nbEtats;
        }
    }
    if(somme>= m_rule.size()) throw AutomateException("Erreur: la règle de transition de Elementary Rule est trop petite");
    arrivee.SetEtat(m_rule[m_rule.size()-somme-1]-'0');
}

void GameOfLife::TransitionCellule(const Cell &depart, Cell &arrivee) const
{
    //BLANC = MORTE NOIR = VIVANTE
    vector<Cell*> const& voisins = depart.GetVoisins();
    int somme = 0;
    for(int i=0;i<voisins.size();i++)
    {
        if(voisins[i]!= nullptr && voisins[i]!= &depart) //si on est en train de traiter un voisin qui existe et qui est différent de la cellule actuelle (car la cellule est stockée dans son voisinage MAIS on ne veut pas la compter dans la somme des voisins pour un GameOfLife)
           {

            //somme += voisins[i]->GetEtat(); //on ajoute 0 si la cellule voisine = 0 (donc morte) 1 sinon (vivante) /!\ il faut que les etats des cellules soit égaux à 0 ou 1 !!!! (à contrôler à la création du CellularAutomata et de la grille de Depart)
            //ou si on veut pas s'embêter à contrôler :
            if (voisins[i]->GetEtat()!= BLANC) somme++; //on compte le nombre de voisins vivantes
        }

    }
    if(depart.GetEtat()== NOIR) //si la cellule est vivante
    {
        if(somme>=m_minVoisinsVivants && somme<=m_maxVoisinsVivants)
            arrivee.SetEtat(NOIR);
        else
            arrivee.SetEtat(BLANC);
    }
    else if(depart.GetEtat()==BLANC) //si la cellule est morte
    {
        if(somme == m_maxVoisinsVivants)
            arrivee.SetEtat(NOIR);
        else
            arrivee.SetEtat(BLANC);
    }
    else
        throw AutomateException("La cellule prend un état qui n'est pas pris en compte par le GameOfLife");

}

void FeuForet::TransitionCellule(Cell const& depart,Cell& arrivee) const
{
    vector<Cell*> const& voisins = depart.GetVoisins();

    switch(depart.GetEtat())
    {
    case BLANC:
        arrivee.SetEtat(BLANC);
        break;
    case NOIR:
        arrivee.SetEtat(NOIR);
        break;
    case ROUGE:
        arrivee.SetEtat(NOIR);
        break;
    case VERT:
    {
        bool voisinRouge = false;
        int i = 0;
        while(i<voisins.size()&& voisinRouge == false)
        {

            if(voisins[i]!= nullptr && voisins[i]!= &depart && voisins[i]->GetEtat()==ROUGE)
            {
                arrivee.SetEtat(ROUGE);
                voisinRouge = true;

            }
            i++;
        }
        if (voisinRouge == false) arrivee.SetEtat(VERT);
    }
        break;
    default:
        arrivee.SetEtat(BLANC); //si la cellule a un état différent des 4 pris en compte on la remplace par BLANC qui signifie VIDE dans le cas de cet automate
    }

}

std::string ElementaryRule::getTransition() const
{
    return "1D," + m_rule + "," + std::to_string(m_nbEtats);
}

std::string GameOfLife::getTransition() const
{
    return "2D,GameOfLife," + std::to_string(m_minVoisinsVivants) + "," + std::to_string(m_maxVoisinsVivants);
}

std::string FeuForet::getTransition() const
{
    return "2D,FeuForet";
}

