#include "bStarTree.h"
#include <queue>
#include <algorithm>    // std::find

BTreeStar::BTreeStar(int degree):
    degree(degree)
{

}

BTreeStar::~BTreeStar()
{
    dealockNodeOfBTrees();
}

void BTreeStar::dealockNodeOfBTrees()
{
    if (root != nullptr)
    {
        root->dealockSubTree();
        delete root;
    }
}

NodeOfBStarTree *BTreeStar::getRoot()
{
    return this->root;
}

int BTreeStar::getDegree()
{
    return this->degree;
}

int BTreeStar::entriesSize()
{
    return this->degree - 1;
}

std::string BTreeStar::getDotFileContent()
{
    std::string msg = "digraph g { ";
    msg += "ROOT [shape=none fontcolor=blue];";
    msg += "node [shape=record, height=0.1];";

    std::string msgLinks;

    std::queue<NodeOfBStarTree*> queue;

    if (root != nullptr)
        queue.push(root);
    while(queue.size() > 0)
    {
        NodeOfBStarTree* node = queue.front(); //acessa o primeiro
        queue.pop(); //remove o primeiro

        node->getDotFileRepresentation(msg);
        std::vector<NodeOfBStarTree *> vec = node->getVectorOfPointers();
        for (auto pointer: vec)
        {
            queue.push(pointer);
            msgLinks += "\""+node->getNodeName()+"\"->\""+pointer->getNodeName()+"\";";
        }
    }

    if (root != nullptr)
    {
        std::string rootName = root->getNodeName();
        msg += "ROOT->\""+rootName+"\";";
    }

    msg += msgLinks;

    msg += "}";

    return msg;
}

bool BTreeStar::insert(int number)
{
    if (root == nullptr)
        root = new NodeOfBStarTree(nullptr, this->degree);
    return root->insert(number);
}

NodeOfBStarTree* BTreeStar::search(int number)
{
    NodeOfBStarTree* temp = root;
    bool goToNext = false;
    while (true)
    {
        const std::vector<int> vec = temp->getVectorOfEntries();
        for (int index = 0; index < vec.size(); ++index)
        {
            if (number == vec[index])
                return temp;
            else if (number < vec[index])
            {
                if (index < temp->getVectorOfPointers().size())
                {
                    temp = temp->pointerByIndex(index);
                    goToNext = true;
                    break;
                }
                else
                    return nullptr;
            }
        }
        if (goToNext == false)
        {
            //Verificar no último ponteiro
            if (temp->getVectorOfPointers().size() > 1) //deve ter pelo menos 2 ponteiros
            {
                temp = temp->getVectorOfPointers().back();
            }
            else
                return nullptr;
        }
        else
        {
            goToNext = false;
        }
    }
    return nullptr;
}

bool BTreeStar::remove(int number)
{
    int maxSize = degree-1;
    NodeOfBStarTree* n = search(number);
    if (n == nullptr)
        return false;
    else
    {
        std::vector<NodeOfBStarTree*> removedNodes;

        //Verifica se o nó é uma folha
        if (n->getVectorOfPointers().size() == 0)
        {
            //caso 1: Verifica se tem mais elementos do que a metade
            //do tamanho máximo (antes de remover)
            int size = n->getVectorOfEntries().size();
            if (size > maxSize/3)
            {
                //A função abaixo remove posições internas do vetor tmb
                n->removeEntryOfVectorOfEntries(number);
            }
            else
            {
                //remove
                n->removeEntryOfVectorOfEntries(number);

                //verifica como resolver, se for preciso
                size = n->getVectorOfEntries().size();
                if (size < maxSize/3)
                    fixNodeWithSmallCountOfElements(n, removedNodes);
            }
        }
        else //Não é uma folha
        {
            //caso 2: troca com o seu antecessor
            //isso implica em remover do antecessor um numero (o maior)
            //Pode ter que resolver o problema do antecessor
            NodeOfBStarTree* ancestor = getAncestor(n, number);
            int numberAncestor = ancestor->getVectorOfEntries().back();
            ancestor->removeEntryOfVectorOfEntries(numberAncestor);

            //ancestor é folha, não tem ponteiros filhos

            //Em n, troca o número number por numberAncestor
            n->replaceEntryInVectorOfEntries(number, numberAncestor);

            //Verifica se tem que resolver e resolve, se necessário
            int size = ancestor->getVectorOfEntries().size();
            if (size < maxSize/3)
                fixNodeWithSmallCountOfElements(ancestor, removedNodes);
        }

        for (auto p: removedNodes)
            delete p;

        return true;
    }
}

NodeOfBStarTree* BTreeStar::getAncestor(NodeOfBStarTree * node, int number)
{
    int pos = 0;
    std::vector<int> vecOfEntries = node->getVectorOfEntries();
    for (int index = 0; index < vecOfEntries.size(); ++index)
    {
        if (vecOfEntries[index] == number)
            pos = index;
    }

    NodeOfBStarTree* nodePointer = node->getVectorOfPointers().at(pos);
    while (nodePointer->getVectorOfPointers().size() > 0)
    {
        nodePointer = nodePointer->getVectorOfPointers().back();
    }
    return nodePointer;
}

void BTreeStar::fixNodeWithSmallCountOfElements
(
    NodeOfBStarTree *nodeToFix,
    std::vector<NodeOfBStarTree*> &removedNodes
)
{
    int maxSize = degree-1;

    //Verificar a quantidade de filhos
    if (nodeToFix->getVectorOfPointers().size() == 1)
    {
        //nodetofix tem 0 elementos

        //se for o root
        if (nodeToFix->getFather() == nullptr)
        {
            NodeOfBStarTree* backup = root;
            root = nodeToFix->pointerByIndex(0);
            root->setFather(nullptr);
            delete backup;
            if (
                std::find(removedNodes.begin(), removedNodes.end(), backup)
                != removedNodes.end()
            )
            {
                std::remove(removedNodes.begin(), removedNodes.end(), backup);
            }
        }
        else
        {

            //caso contrario, se tiver irmão a direita, junta com ele
            //Verifica se pode obter de algum irmão, um valor excedente
            int indexFound = -1;
            NodeOfBStarTree* father = nodeToFix->getFather();
            std::vector<NodeOfBStarTree *> pointers = father->getVectorOfPointers();
            for (int index = 0; index < pointers.size(); ++index)
            {
                if (nodeToFix == pointers[index])
                {
                    indexFound = index;
                    break;
                }
            }

            //se tiver irmão a esquerda, junta com ele
            if (indexFound > 0)
            {
                NodeOfBStarTree* leftBrother = pointers[indexFound-1];
                int top = father->entryByIndex(indexFound-1); // obtem o numero de cima
                father->removeEntryOfVectorOfEntries(top);
                
                father->removePointerOfVectorOfPointers(indexFound);

                leftBrother->insertInLastPositionOfVectorOfEntries(top);
                NodeOfBStarTree* singleSon = nodeToFix->removeFirstPointer();
                singleSon->setFather(leftBrother);
                leftBrother->insertInLastPositionOfVectorOfPointers(singleSon);

                //verifica pai
                if (father->getVectorOfEntries().size() < maxSize/3)
                    fixNodeWithSmallCountOfElements(father, removedNodes);

                //verifica se left brother esta ok
                if (
                    std::find(removedNodes.begin(), removedNodes.end(), leftBrother)
                    == removedNodes.end() &&
                    leftBrother->getVectorOfEntries().size() > maxSize
                )
                {
                    leftBrother->fixNodeThatIsNotRootThatHasMoreElementsThatAllowed();
                }
                
                delete nodeToFix;
                if (
                    std::find(removedNodes.begin(), removedNodes.end(), nodeToFix)
                    != removedNodes.end()
                )
                {
                    std::remove(removedNodes.begin(), removedNodes.end(), nodeToFix);
                }
            }
            else if (indexFound < pointers.size()-1)
            {
                NodeOfBStarTree* rightBrother = pointers[indexFound+1];
                int top = father->entryByIndex(indexFound); // obtem o numero de cima
                father->removeEntryOfVectorOfEntries(top);
                
                father->removePointerOfVectorOfPointers(indexFound);

                rightBrother->insertInFirstPositionOfVectorOfEntries(top);
                NodeOfBStarTree* singleSon = nodeToFix->removeFirstPointer();
                singleSon->setFather(rightBrother);
                rightBrother->insertInFirstPositionOfVectorOfPointers(singleSon);

                //ou verifica pai
                if (father->getVectorOfEntries().size() < maxSize/3)
                    fixNodeWithSmallCountOfElements(father, removedNodes);

                //verifica se right brother esta ok
                if (
                    std::find(removedNodes.begin(), removedNodes.end(), rightBrother)
                    == removedNodes.end() &&
                    rightBrother->getVectorOfEntries().size() > maxSize)
                {
                    rightBrother->fixNodeThatIsNotRootThatHasMoreElementsThatAllowed();
                }
                
                delete nodeToFix;
                if (
                    std::find(removedNodes.begin(), removedNodes.end(), nodeToFix)
                    != removedNodes.end()
                )
                {
                	std::remove(removedNodes.begin(), removedNodes.end(), nodeToFix);
                }
            }
        }
    }
    else
    {
        if (nodeToFix->getVectorOfEntries().size() >= maxSize/3)
            return; //está resolvido

        if (nodeToFix == root) //o root pode ter menos elementos
        {
            if (nodeToFix->getVectorOfEntries().size() == 0)
            {
                //juntar filhos
                //Tem 2 filhos restantes (pelas propriedades da remoção)
                std::vector<NodeOfBStarTree*> pointers = nodeToFix->getVectorOfPointers();
                for (auto tmp: pointers)
                {
                    while (tmp->getVectorOfEntries().size() > 0)
                    {
                        int first = tmp->removeFirstPositionOfVectorOfEntries();
                        nodeToFix->insertInLastPositionOfVectorOfEntries(first);
                    }
                }
                while (nodeToFix->getVectorOfPointers().size() > 0)
                    nodeToFix->removeLastPointer();

                std::vector<NodeOfBStarTree*> childrens;
                for (auto tmp: pointers)
                {
                    while (tmp->getVectorOfPointers().size() > 0)
                    {
                        NodeOfBStarTree* firstP = tmp->removeFirstPointer();
                        childrens.push_back(firstP);
                    }
                }
                for (auto ptr: childrens)
                {
                    nodeToFix->insertInLastPositionOfVectorOfPointers(ptr);
                    ptr->setFather(nodeToFix);
                }
                
                //aqui sim, deletar
                for (auto tmp : pointers)
                {                   
                    if (
                        std::find(removedNodes.begin(), removedNodes.end(), tmp)
                        == removedNodes.end()
                    )
                    {
                        removedNodes.push_back(tmp);
                    }
                }
            }

            return;
        }

        int indexFound = 0;
        //Verifica se pode obter de algum irmão, um valor excedente
        NodeOfBStarTree* father = nodeToFix->getFather();
        std::vector<NodeOfBStarTree *> pointers = father->getVectorOfPointers();
        for (int index = 0; index < pointers.size(); ++index)
        {
            if (nodeToFix == pointers[index])
            {
                indexFound = index;
                //Verifica o irmão esquerdo, se tiver
                if (index >= 1)
                {
                    NodeOfBStarTree* leftBrother = pointers[index-1];
                    if (leftBrother->getVectorOfEntries().size() > maxSize/3)
                    {
                        //faz e retorna
                        //Este faz não esta considerando ponteiros filhos
                        int last = leftBrother->removeLastPositionOfVectorOfEntries();
                        int top = father->entryByIndex(index-1); // obtem o numero de cima
                        father->setEntryByIndex(index-1, last);
                        //insere número de cima na posição zero de nodeToFix
                        nodeToFix->insertInFirstPositionOfVectorOfEntries(top);

                        //Verificar se tem irmão da direita
                        //Verifica se o irmao tem ponteiro. Se tiver, remove o ultimo
                        if (leftBrother->getVectorOfPointers().size() > 0 &&
                                (index+1) < pointers.size())
                        {
                            NodeOfBStarTree* last = leftBrother->removeLastPointer();
                            NodeOfBStarTree* rightBrother = pointers[index+1];
                            rightBrother->insertInFirstPositionOfVectorOfPointers(last);
                            last->setFather(rightBrother);
                        }

                        return;
                    }
                }

                if (index < pointers.size()-1)
                {
                    NodeOfBStarTree* rightBrother = pointers[index+1];
                    if (rightBrother->getVectorOfEntries().size() > maxSize/3)
                    {
                        //faz e retorna
                        //Este faz não esta considerando ponteiros filhos
                        int first = rightBrother->removeFirstPositionOfVectorOfEntries();
                        int top = father->entryByIndex(index); // obtem o numero de cima
                        father->setEntryByIndex(index, first);
                        nodeToFix->insertInLastPositionOfVectorOfEntries(top);

                        //Verificar se tem irmão da direita
                        //Verifica se o irmao tem ponteiro. Se tiver, remove o ultimo
                        if (rightBrother->getVectorOfPointers().size() > 0 &&
                                (index-1) >= 0)
                        {
                            NodeOfBStarTree* first = rightBrother->removeFirstPointer();
                            NodeOfBStarTree* leftBrother = pointers[index-1];
                            leftBrother->insertInFirstPositionOfVectorOfPointers(first);
                            first->setFather(leftBrother);
                        }

                        return;
                    }
                }

                break; //tratar fora do laço
            }
        }

        //Se chegou aqui, é porque nem o esquerdo, nem o direito, tinham
        //possibilidade de ajudar
        //Junta com o irmão esquerdo (podia ser o direito também)
        if (indexFound > 0) //tem irmão esquerdo
        {
            //Juntar com o esquerdo
            //deletar o esquerdo
            //Remover primeira entrada do pai (valor)
            int top = father->entryByIndex(indexFound-1);
            father->removeByIndexInVectorOfEntries(indexFound-1);
            nodeToFix->insertInFirstPositionOfVectorOfEntries(top);
            NodeOfBStarTree* leftBrother = pointers[indexFound-1];
            while(leftBrother->getVectorOfEntries().size() > 0)
            {
                int last = leftBrother->removeLastPositionOfVectorOfEntries();
                nodeToFix->insertInFirstPositionOfVectorOfEntries(last);
            }
            while(leftBrother->getVectorOfPointers().size() > 0)
            {
                NodeOfBStarTree* pointer = leftBrother->removeLastPointer();
                nodeToFix->insertInFirstPositionOfVectorOfPointers(pointer);
                pointer->setFather(nodeToFix);
            }

            //remover o left do pai
            father->removePointerOfVectorOfPointers(indexFound-1);
            //Deve propagar checagens para cima
            //mas agora não
            //change 2 check
            delete leftBrother;
            if (
                std::find(removedNodes.begin(), removedNodes.end(), leftBrother)
                != removedNodes.end()
            )
            {
                std::remove(removedNodes.begin(), removedNodes.end(), leftBrother);
            }
        }
        else if (indexFound < pointers.size()-1) //tem irmão direito
        {
            //Juntar com o direito
            int top = father->entryByIndex(indexFound);
            father->removeByIndexInVectorOfEntries(indexFound);
            nodeToFix->insertInLastPositionOfVectorOfEntries(top);
            NodeOfBStarTree* rightBrother = pointers[indexFound+1];
            while(rightBrother->getVectorOfEntries().size() > 0)
            {
                int first = rightBrother->removeFirstPositionOfVectorOfEntries();
                nodeToFix->insertInLastPositionOfVectorOfEntries(first);
            }
            while(rightBrother->getVectorOfPointers().size() > 0)
            {
                NodeOfBStarTree* pointer = rightBrother->removeFirstPointer();
                nodeToFix->insertInLastPositionOfVectorOfPointers(pointer);
                pointer->setFather(nodeToFix);
            }

            //remover o right do pai
            father->removePointerOfVectorOfPointers(indexFound+1);
            //Deve propagar checagens para cima
            //mas agora não
            //change 3 check
            delete rightBrother;
            if (
		    std::find(removedNodes.begin(), removedNodes.end(), rightBrother)
		    != removedNodes.end()
		)
		{
			std::remove(removedNodes.begin(), removedNodes.end(), rightBrother);
		}
        }

        if (father->getVectorOfEntries().size() < maxSize/3)
            fixNodeWithSmallCountOfElements(father, removedNodes);

    }
}
