#include "Formation.h"

int Formation::getNbCreditsTotal()const
{
    int sum=0;
    typedef std::map<Categorie, unsigned int>::const_iterator it_type;
    for(it_type iterator = nbCredits.begin(); iterator != nbCredits.end(); iterator++)
    {
        sum += iterator->second;
    }
    return sum;
}

