#include "gerercategorie.h"
#include "ui_gerercategorie.h"

gererCategorie::gererCategorie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gererCategorie)
    //sousCategorie(std::vector);
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->viewport()->setAcceptDrops(true);
    ui->treeWidget->setDropIndicatorShown(true);
    ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
    // Set the number of columns in the tree
    ui->treeWidget->setColumnCount(2);
    QObject::connect(ui->Valider,SIGNAL(clicked()),this,SLOT(validerTree()));
    displayTree();

}

void gererCategorie::displayTree()
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    std::vector<Categorie> rootCats=getOriginCat();

    //ajout des catégories origines
    for(std::vector<Categorie>::iterator it= rootCats.begin();it != rootCats.end() ; it++)
    {
        tree[(*it)]=addTreeRoot(it->getCode(), it->getDescription());
    }

    //ajout des sous catégories
    for(std::vector<Categorie>::iterator it=tCat.getIterator(); it!=tCat.end();it++)
    {
        if(tree.find(*it) == tree.end())//si on ne la pas encore ajoutée
        {
             std::map<Categorie, QTreeWidgetItem *>::iterator parent = tree.find(tCat.getElement(getParentCat(it->getCode())));
            if( parent != tree.end())//si on a ajouté sa catégorie parente
            {
                tree[(*it)]=addTreeChild(parent->second,it->getCode(), it->getDescription());
            }
            else
            {
                std::vector<QString> parentsToAdd;

                QString s = getParentCat(it->getCode());
                QString s2 = it->getCode();

                while(tree.find(tCat.getElement(s))==tree.end())//tant qu'on a pas trouvé un parent dans l'arbre
                {
                    s2=s;
                    s=getParentCat(s);
                    parentsToAdd.push_back(s2);
                }

                for(unsigned int i =0; i<parentsToAdd.size();i++)
                {
                     qDebug()<<"T :"<<parentsToAdd[i];
                }

                while(parentsToAdd.size()>0)
                {
                    qDebug()<<"Taille"<<parentsToAdd.size()<<" S : "<<s<<" S2 :"<<s2;
                    tree[tCat.getElement(s2)]=addTreeChild(tree[tCat.getElement(s)],s2, tCat.getElement(s2).getDescription());

                    s=s2;
                    parentsToAdd.pop_back();
                    if(parentsToAdd.size()>1)
                    {
                        s2=parentsToAdd.back();
                    }

                }
            }
        }
    }
}

void gererCategorie::validerTree()
{
     TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    for(std::map<Categorie, QTreeWidgetItem *>::iterator it = tree.begin(); it!=tree.end();it++)
    {
        QMessageBox* test = new QMessageBox();
        if(it->second->parent()!=0)
        {
            if((getParentCat(it->first.getCode())!=0)&&(getParentCat(it->first.getCode()) != it->second->parent()->text(0)))// si une catégorie a changée de parent
            {
                tCat.getElement(getParentCat(it->first.getCode())).removeSousCategorie(tCat.getElement(it->first.getCode()));
                tCat.getElement(it->second->parent()->text(0)).addSousCategorie(tCat.getElement(it->first.getCode()));
            }
            else if((getParentCat(it->first.getCode())==0)&&(getParentCat(it->first.getCode()) != it->second->parent()->text(0)))
            {
                 tCat.getElement(it->second->parent()->text(0)).addSousCategorie(tCat.getElement(it->first.getCode()));
            }

        }
        else
        {
            if(getParentCat(it->first.getCode()) != "")// si une catégorie n'a plus de parents alors qu'elle en avait un
            {
                tCat.getElement(getParentCat(it->first.getCode())).removeSousCategorie(tCat.getElement(it->first.getCode()));
            }
        }
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


QTreeWidgetItem * gererCategorie::addTreeRoot(QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    return treeItem;
}

QTreeWidgetItem * gererCategorie::addTreeChild(QTreeWidgetItem *parent,QString name, QString description)
{

    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    parent->addChild(treeItem);
    return treeItem;
}
gererCategorie::~gererCategorie()
{
    delete ui;
}
