#include "Semestre.h"
#include "Etudiant.h"
Semestre::Semestre(Saison s, unsigned int a):saison(s)
{
    if (a<1972||a>2099)
    {
        throw SemestreException("annee "+std::to_string(a)+" non valide");
    }

    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();

    QString test = ""+s.getNom()+QString::number(a);

   if(!tSemestre.alreadyExist(test))
    {
        code=test;
        annee=a;
        tSemestre.New(*this);
    }
    else
    {
        throw SaisonException("Erreur : le semestre "+test.toStdString()+" existe deja !");
    }

}

void Semestre::destroy()
{
    TemplateManager<Etudiant>& tEtudiant=TemplateManager<Etudiant>::getInstance();
     if(tEtudiant.size()>0)//pour chaque étudiant, on enlève les isncriptions
     {
         for(std::vector<Etudiant>::iterator it = tEtudiant.getIterator();it!=tEtudiant.end();it++)//on supprime toutes les inscriptions ayant ce semestre
         {
             Dossier dos=it->getDossier();
             std::vector<Inscription> inscr = dos.getInscription();
             for(std::vector<Inscription>::iterator it2= inscr.begin();it2 != inscr.end();it2++)
             {
                 if(it2->getSemestre()==*this)
                 {
                     dos.deleteInscription(*it2);
                     it->setDossier(dos);
                 }
             }
         }
     }
}
