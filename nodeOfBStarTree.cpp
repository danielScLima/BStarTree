#include "nodeOfBStarTree.h"
#include <algorithm>
#include <string>

NodeOfBStarTree::NodeOfBStarTree(NodeOfBStarTree* father, int degree):
    degree(degree), father(father)
{

}

void NodeOfBStarTree::dealockSubTree()
{
    NodeOfBStarTree* child = nullptr;
    for (int index = 0; index < vectorOfPointers.size(); ++index)
    {
        child = vectorOfPointers.at(index);
        if (child != nullptr)
        {
            child->dealockSubTree();
            delete child;
            vectorOfPointers[index] = nullptr;
        }
    }

    vectorOfPointers.clear();
    vectorOfEntries.clear();
}

NodeOfBStarTree *NodeOfBStarTree::getFather()
{
    return this->father;
}

void NodeOfBStarTree::setFather(NodeOfBStarTree *father)
{
    this->father = father;
}

void NodeOfBStarTree::removeEntryOfVectorOfEntries(int number)
{
    std::vector<int>::iterator position = std::find
    (
        vectorOfEntries.begin(),
        vectorOfEntries.end(),
        number
    );
    if (position != vectorOfEntries.end())
        vectorOfEntries.erase(position);
}

void NodeOfBStarTree::removePointerOfVectorOfPointers(int index)
{
    vectorOfPointers.erase(vectorOfPointers.begin()+index);
}

int NodeOfBStarTree::removeLastPositionOfVectorOfEntries()
{
    int last = vectorOfEntries.back();
    vectorOfEntries.pop_back();
    return last;
}

int NodeOfBStarTree::removeFirstPositionOfVectorOfEntries()
{
    int first = vectorOfEntries.front();
    vectorOfEntries.erase(vectorOfEntries.begin());
    return first;
}

NodeOfBStarTree* NodeOfBStarTree::removeLastPointer()
{
    NodeOfBStarTree* last = vectorOfPointers.back();
    vectorOfPointers.pop_back();
    return last;
}

NodeOfBStarTree* NodeOfBStarTree::removeFirstPointer()
{
    NodeOfBStarTree* first = vectorOfPointers.front();
    vectorOfPointers.erase(vectorOfPointers.begin());
    return first;
}

void NodeOfBStarTree::insertInFirstPositionOfVectorOfEntries(int number)
{
    vectorOfEntries.insert(vectorOfEntries.begin(), number);
}

void NodeOfBStarTree::insertInFirstPositionOfVectorOfPointers(NodeOfBStarTree* pointer)
{
    vectorOfPointers.insert(vectorOfPointers.begin(), pointer);
}

void NodeOfBStarTree::insertInLastPositionOfVectorOfEntries(int number)
{
    vectorOfEntries.push_back(number);
}

void NodeOfBStarTree::insertInLastPositionOfVectorOfPointers(NodeOfBStarTree* pointer)
{
    vectorOfPointers.push_back(pointer);
}

void NodeOfBStarTree::replaceEntryInVectorOfEntries(int number, int ancestorNumber)
{
    std::replace
    (
        vectorOfEntries.begin(),
        vectorOfEntries.end(),
        number,
        ancestorNumber
    );
}

std::vector<int> NodeOfBStarTree::getVectorOfEntries()
{
    return this->vectorOfEntries;
}

void NodeOfBStarTree::removeByIndexInVectorOfEntries(int index)
{
    if (index < vectorOfEntries.size())
        vectorOfEntries.erase(vectorOfEntries.begin()+index);
    else
        throw std::invalid_argument("Invalid index");
}

int NodeOfBStarTree::entryByIndex(int index)
{
    if (index < vectorOfEntries.size())
        return vectorOfEntries.at(index);
    else
        throw std::invalid_argument("Invalid index");
}

void NodeOfBStarTree::setEntryByIndex(int index, int number)
{
    if (index < vectorOfEntries.size())
        vectorOfEntries[index] = number;
}

NodeOfBStarTree *NodeOfBStarTree::pointerByIndex(int index)
{
    if (index < this->vectorOfPointers.size())
        return this->vectorOfPointers.at(index);
    else
        throw std::invalid_argument("Invalid index");
}

void NodeOfBStarTree::setDegree(int degree)
{
    this->degree = degree;
}

const std::string NodeOfBStarTree::getNodeName()
{
    std::string name;
    int maxEntries = this->degree - 1;
    for (int index = 0; index < maxEntries; ++index)
    {
        if (index < vectorOfEntries.size())
            name += std::to_string(vectorOfEntries[index]);
        else
            name += "-";

        if (index < maxEntries-1)
            name += "_";
    }
    return name;
}

bool NodeOfBStarTree::insert(int number)
{
    //apenas para ter algo
    bool numberInserted = false;
    bool stopProcessHere = false;

    int maxEntries = this->degree - 1;
    for (int index = 0; index < this->vectorOfEntries.size(); ++index)
    {
        if (number == vectorOfEntries[index])
            return false;
        if (number < vectorOfEntries[index])
        {
            //Existe um ponteiro com posição: index?
            //Se sim, manda inserir neste ponteiro
            if (index < vectorOfPointers.size())
            {
                bool ret = vectorOfPointers[index]->insert(number);
                if (!ret)
                    return false;
                stopProcessHere = true;
                break;
            }
            else //Se não, insere no nó atual, deslocando
            {
                //Verifica se tem espaço nesse nó
                //Deve verificar a quantidade de entradas
                //se é menor que a máxima
                if (this->vectorOfEntries.size() < maxEntries)
                {
                    //A chamada abaixo já desloca as entradas
                    vectorOfEntries.insert(vectorOfEntries.begin()+index, number);
                    numberInserted = true;
                    break;
                }
                else
                {

                }
            }
        }
    }

    if (numberInserted || stopProcessHere)
    {
        //não tem mais nada a fazer
    }
    else
    {
        if (this->vectorOfEntries.size() < maxEntries)
        {
            //Insere depois do último
            //Se esse ponteirofor diferente de null, insere lá
            int sizeEntries = this->vectorOfEntries.size();
            if (sizeEntries < vectorOfPointers.size() &&
                    vectorOfPointers.back() != nullptr)
            {
                bool ret = vectorOfPointers.back()->insert(number);
                if (!ret)
                    return false;
            }
            else
            {
                this->vectorOfEntries.push_back(number);
                numberInserted = true;
            }
        }
        else
        {
            //Neste ponto, antes de inserir, o nó já tem a quantidade máxima
            if
            (
                vectorOfPointers.size() > vectorOfEntries.size() &&
                vectorOfPointers.back() != nullptr
            )
            {
                bool ret = vectorOfPointers.back()->insert(number);
                if (!ret)
                    return false;
            }
            else
            {
                //Deve verificar se o pai é nulo ou não
                //se for nulo (é o root), faz o codigo abaixo
                if (father == nullptr)
                {
                    //caso do root é igual

                    numberInserted = false;
                    int pos = -1;
                    for (int index = 0; index < this->vectorOfEntries.size(); ++index)
                    {
                        if (number == vectorOfEntries[index])
                            return false;
                        if (number < vectorOfEntries[index])
                        {
                            vectorOfEntries.insert(vectorOfEntries.begin()+index, number);
                            numberInserted = true;
                            pos = index;
                            break;
                        }
                    }
                    if (numberInserted == false)
                        vectorOfEntries.push_back(number);

                    //Neste ponto existe uma entrada a mais

                    //Deve quebrar o nó, pois a quantidade de elementos lotou
                    //Deve saber qual a ordem de inserção

                    fixRootNodeThatHasMoreElementsThatAllowed();
                }
                else
                {
                    //insere e verifica
                    numberInserted = false;
                    int pos = -1;
                    for (int index = 0; index < this->vectorOfEntries.size(); ++index)
                    {
                        if (number == vectorOfEntries[index])
                            return false;
                        if (number < vectorOfEntries[index])
                        {
                            vectorOfEntries.insert(vectorOfEntries.begin()+index, number);
                            numberInserted = true;
                            pos = index;
                            break;
                        }
                    }
                    if (numberInserted == false)
                        vectorOfEntries.push_back(number);

                    //Descobrir qual irmão tem menos elementos
                    fixNodeThatIsNotRootThatHasMoreElementsThatAllowed();
                }
            } //else de quando podia usar o ultimo ponteiro
        } //end of else of diference
    }

    return true;
}

void NodeOfBStarTree::fixNodeThatIsNotRootThatHasMoreElementsThatAllowed()
{
    //Descobrir qual irmão tem menos elementos
    if (someBrotherHasLeftSpace())
    {
        //Fazer deslocamento
        if (shouldMoveToRight())
        {
            //move para direita
            moveToRight();
        }
        else
        {
            //move para esquerda
            moveToLeft();
        }
    }
    else //fazer quebra. adaptar código abaixo
    {
        if (hasRightBrother()) //juntar com direita
        {
            std::vector<NodeOfBStarTree*> nodesToBreak;
            std::vector<int> numbersToBreak;
            NodeOfBStarTree * temp = nullptr;
            int n;
            while(getVectorOfEntries().size() > 0)
            {
                n = removeFirstPositionOfVectorOfEntries();
                numbersToBreak.push_back(n);
            }
            while(getVectorOfPointers().size() > 0)
            {
                temp = removeFirstPointer();
                nodesToBreak.push_back(temp);
            }
            //Obter valor de cima
            int top = getTopNumberToRight(); //existe, pois tem rightbrother
            numbersToBreak.push_back(top);

            NodeOfBStarTree* rightBrother = getRightBrother();
            while (rightBrother->getVectorOfEntries().size() > 0)
            {
                n = rightBrother->removeFirstPositionOfVectorOfEntries();
                numbersToBreak.push_back(n);
            }
            while(rightBrother->getVectorOfPointers().size() > 0)
            {
                temp = rightBrother->removeFirstPointer();
                nodesToBreak.push_back(temp);
            }
            int count = numbersToBreak.size()/3;
            for (int index = 0; index < count; ++index)
            {
                int first = numbersToBreak.front();
                numbersToBreak.erase(numbersToBreak.begin());
                insertInLastPositionOfVectorOfEntries(first);
            }
            for (int index = 0; index <= count && nodesToBreak.size()>0; ++index)
            {
                temp = nodesToBreak.front();
                nodesToBreak.erase(nodesToBreak.begin());
                insertInLastPositionOfVectorOfPointers(temp);
                temp->setFather(this);
            }
            int top1 = numbersToBreak.front();
            numbersToBreak.erase(numbersToBreak.begin());
            for (int index = 0; index < count; ++index)
            {
                int first = numbersToBreak.front();
                numbersToBreak.erase(numbersToBreak.begin());
                rightBrother->insertInLastPositionOfVectorOfEntries(first);
            }
            for (int index = 0; index <= count && nodesToBreak.size()>0; ++index)
            {
                temp = nodesToBreak.front();
                nodesToBreak.erase(nodesToBreak.begin());
                rightBrother->insertInLastPositionOfVectorOfPointers(temp);
                temp->setFather(rightBrother);
            }
            int top2 = numbersToBreak.front();
            numbersToBreak.erase(numbersToBreak.begin());
            NodeOfBStarTree* newNode = new NodeOfBStarTree(father, degree);
            while (numbersToBreak.size() > 0)
            {
                int first = numbersToBreak.front();
                numbersToBreak.erase(numbersToBreak.begin());
                newNode->insertInLastPositionOfVectorOfEntries(first);
            }
            while(nodesToBreak.size() > 0)
            {
                temp = nodesToBreak.front();
                nodesToBreak.erase(nodesToBreak.begin());
                newNode->insertInLastPositionOfVectorOfPointers(temp);
                temp->setFather(newNode);
            }

            //Envia para o de cima
            father->sendToUpstairs
            (
                top,
                top1,
                top2,
                this,
                rightBrother,
                newNode,
                true   //isright
            );
        }
        else if (hasLeftBrother()) //juntar com esquerda
        {
            std::vector<int> numbersToBreak;
            std::vector<NodeOfBStarTree*> nodesToBreak;
            int n;
            NodeOfBStarTree *temp = nullptr;
            NodeOfBStarTree* leftBrother = getLeftBrother();
            while (leftBrother->getVectorOfEntries().size() > 0)
            {
                n = leftBrother->removeFirstPositionOfVectorOfEntries();
                numbersToBreak.push_back(n);
            }
            while(leftBrother->getVectorOfPointers().size() > 0)
            {
                temp = leftBrother->removeFirstPointer();
                nodesToBreak.push_back(temp);
            }
            //Obter valor de cima
            int top = getTopNumberToLeft(); //existe, pois tem rightbrother
            numbersToBreak.push_back(top);

            while(getVectorOfEntries().size() > 0)
            {
                n = removeFirstPositionOfVectorOfEntries();
                numbersToBreak.push_back(n);
            }
            while(getVectorOfPointers().size() > 0)
            {
                temp = removeFirstPointer();
                nodesToBreak.push_back(temp);
            }

            int count = numbersToBreak.size()/3;
            for (int index = 0; index < count; ++index)
            {
                int first = numbersToBreak.front();
                numbersToBreak.erase(numbersToBreak.begin());
                leftBrother->insertInLastPositionOfVectorOfEntries(first);
            }
            for (int index = 0; index <= count && nodesToBreak.size()>0; ++index)
            {
                temp = nodesToBreak.front();
                nodesToBreak.erase(nodesToBreak.begin());
                leftBrother->insertInLastPositionOfVectorOfPointers(temp);
                temp->setFather(leftBrother);
            }
            int top1 = numbersToBreak.front();
            numbersToBreak.erase(numbersToBreak.begin());
            for (int index = 0; index < count; ++index)
            {
                int first = numbersToBreak.front();
                numbersToBreak.erase(numbersToBreak.begin());
                insertInLastPositionOfVectorOfEntries(first);
            }
            for (int index = 0; index <= count && nodesToBreak.size()>0; ++index)
            {
                temp = nodesToBreak.front();
                nodesToBreak.erase(nodesToBreak.begin());
                insertInLastPositionOfVectorOfPointers(temp);
                temp->setFather(this);
            }
            int top2 = numbersToBreak.front();
            numbersToBreak.erase(numbersToBreak.begin());
            NodeOfBStarTree* newNode = new NodeOfBStarTree(father, degree);
            while (numbersToBreak.size() > 0)
            {
                int first = numbersToBreak.front();
                numbersToBreak.erase(numbersToBreak.begin());
                newNode->insertInLastPositionOfVectorOfEntries(first);
            }
            while(nodesToBreak.size() > 0)
            {
                temp = nodesToBreak.front();
                nodesToBreak.erase(nodesToBreak.begin());
                newNode->insertInLastPositionOfVectorOfPointers(temp);
                temp->setFather(newNode);
            }

            //Envia para o de cima
            father->sendToUpstairs
            (
                top,
                top1,
                top2,
                leftBrother,
                this,
                newNode,
                false //isfalse
            );
        }
    }
}

void NodeOfBStarTree::fixRootNodeThatHasMoreElementsThatAllowed()
{
    int maxEntries = this->degree - 1;
    int middle = maxEntries / 2;
    NodeOfBStarTree* left = new NodeOfBStarTree(this, this->degree);
    NodeOfBStarTree* right = new NodeOfBStarTree(this, this->degree);
    for (int index = 0; index < middle; ++index)
    {
        left->insert(vectorOfEntries[index]);
    }
    for (int index = middle+1; index < vectorOfEntries.size(); ++index)
    {
        right->insert(vectorOfEntries[index]);
    }

    int backupNumber = vectorOfEntries[middle];
    vectorOfEntries.clear();

    for (int index = 0;
         index <= middle && getVectorOfPointers().size() > 0;
         ++index)
    {
        NodeOfBStarTree* first = removeFirstPointer();
        left->insertInLastPositionOfVectorOfPointers(first);
        first->setFather(left);
    }
    for (;
         getVectorOfPointers().size() > 0;
         )
    {
        NodeOfBStarTree* first = removeFirstPointer();
        right->insertInLastPositionOfVectorOfPointers(first);
        first->setFather(right);
    }

    vectorOfEntries.push_back(backupNumber);
    vectorOfPointers.push_back(left);
    vectorOfPointers.push_back(right);
}

void NodeOfBStarTree::sendToUpstairs
(
    int oldDividionNumber,
    int newDivisionNumber1,
    int newDivisionNumber2,
    NodeOfBStarTree* oldRef1,
    NodeOfBStarTree* oldRef2,
    NodeOfBStarTree* newRef,
    bool isRight
)
{
    int foundPos = -1;
    for (int index = 0; index < vectorOfEntries.size(); ++index)
    {
        if (vectorOfEntries[index] == oldDividionNumber)
        {
            foundPos = index;
            break;
        }
    }
    if (foundPos != -1)
    {
        if (isRight)
        {
            vectorOfEntries[foundPos] = newDivisionNumber1;

            if (foundPos < vectorOfEntries.size()-1)
                vectorOfEntries.insert(vectorOfEntries.begin()+foundPos+1, newDivisionNumber2);
            else
                vectorOfEntries.push_back(newDivisionNumber2);
        }
        else
        {
            vectorOfEntries[foundPos] = newDivisionNumber2;

            //Insere antes de newDivisionNumber2
            vectorOfEntries.insert(vectorOfEntries.begin()+foundPos, newDivisionNumber1);
        }
    }
    foundPos = -1;
    for (int index = 0; index < vectorOfPointers.size(); ++index)
    {
        if (vectorOfPointers[index] == oldRef1)
        {
            foundPos = index;
            break;
        }
    }
    if (foundPos != -1)
    {
        if (foundPos+2 < vectorOfPointers.size())
            vectorOfPointers.insert(vectorOfPointers.begin()+foundPos+2, newRef);
        else
            vectorOfPointers.push_back(newRef);
    }

    //Recebeu dados, inseriu, mas talvez tenha mais elementos do que permitido
    int maxEntries = this->degree - 1;
    if (vectorOfEntries.size() > maxEntries)
    {
        if (father == nullptr) //é o root
            fixRootNodeThatHasMoreElementsThatAllowed();
        else
            fixNodeThatIsNotRootThatHasMoreElementsThatAllowed();
    }
}

int NodeOfBStarTree::positionInFather()
{
    int maxEntries = this->degree - 1;
    if (this->getFather() == nullptr)
        return 0; //nenhum

    NodeOfBStarTree* father = this->getFather();
    int myPos = -1;
    std::vector<NodeOfBStarTree *> fatherPointers = father->getVectorOfPointers();
    int countOfFatherPointers = fatherPointers.size();
    for (int index = 0; index < fatherPointers.size(); ++index)
    {
        if (fatherPointers[index] == this)
        {
            myPos = index;
            break;
        }
    }
    return myPos; //pode ser -1: erro
}
int NodeOfBStarTree::hasRightBrother()
{
    int pos = positionInFather();
    if (pos == -1)
        return 0; //não tem

    std::vector<NodeOfBStarTree *> fatherPointers = father->getVectorOfPointers();
    int countOfFatherPointers = fatherPointers.size();

    return pos < countOfFatherPointers-1; //tem irmão direito
}

NodeOfBStarTree* NodeOfBStarTree::getRightBrother()
{
    int pos = positionInFather();
    if (pos == -1)
        return nullptr; //não tem
    std::vector<NodeOfBStarTree *> fatherPointers = father->getVectorOfPointers();
    return fatherPointers.at(pos+1);
}
NodeOfBStarTree* NodeOfBStarTree::getLeftBrother()
{
    int pos = positionInFather();
    if (pos == -1)
        return nullptr; //não tem
    std::vector<NodeOfBStarTree *> fatherPointers = father->getVectorOfPointers();
    return fatherPointers.at(pos-1);
}

int NodeOfBStarTree::hasLeftBrother()
{
    int pos = positionInFather();
    if (pos == -1)
        return 0; //não tem

    return pos > 0; //tem irmão direito
}
int NodeOfBStarTree::leftSpaceInRightBrother()
{
    int maxEntries = this->degree - 1;
    int myPosInFather = positionInFather();
    std::vector<NodeOfBStarTree *> fatherPointers = father->getVectorOfPointers();
    int leftSpaceInRight =
            maxEntries - fatherPointers[myPosInFather+1]->getVectorOfEntries().size();
    return leftSpaceInRight;
}
int NodeOfBStarTree::leftSpaceInLeftBrother()
{
    int maxEntries = this->degree - 1;
    int myPosInFather = positionInFather();
    std::vector<NodeOfBStarTree *> fatherPointers = father->getVectorOfPointers();
    int leftSpaceInLeft =
            maxEntries - fatherPointers[myPosInFather-1]->getVectorOfEntries().size();
    return leftSpaceInLeft;
}

int NodeOfBStarTree::someBrotherHasLeftSpace()
{
    if (hasRightBrother() == 1 && leftSpaceInRightBrother() > 0)
        return 1;

    if (hasLeftBrother() == 1 && leftSpaceInLeftBrother() > 0)
        return 1;

    return 0;
}

int NodeOfBStarTree::shouldMoveToRight()
{
    //Quando essa função é chamada, garantiu que um dos filhos
    //tem espaço sobrando

    //se não tem irmão direito, o esquerdo é quem tem sobrando
    if (hasRightBrother() == false)
        return false;
    if (hasLeftBrother() == false)
        return true;
    //Tem os dois irmãos

    return leftSpaceInRightBrother() >= leftSpaceInLeftBrother();
}

int NodeOfBStarTree::getTopNumberToRight()
{
    int maxSize = this->degree - 1;
    int indexFound = 0;
    //Verifica se pode obter de algum irmão, um valor excedente
    std::vector<NodeOfBStarTree *> pointers = father->getVectorOfPointers();
    for (int index = 0; index < pointers.size(); ++index)
    {
        if (this == pointers[index])
        {
            if (index < pointers.size()-1)
            {
                int top = father->entryByIndex(index); // obtem o numero de cima
                return top;
            }
            break;
        }
    }
    return -1;
}

int NodeOfBStarTree::getTopNumberToLeft()
{
    int maxSize = this->degree - 1;
    int indexFound = 0;
    //Verifica se pode obter de algum irmão, um valor excedente
    std::vector<NodeOfBStarTree *> pointers = father->getVectorOfPointers();
    for (int index = 1; index < pointers.size(); ++index)
    {
        if (this == pointers[index])
        {
            if (index > 0)
            {
                int top = father->entryByIndex(index-1); // obtem o numero de cima
                return top;
            }
            break;
        }
    }
    return -1;
}

void NodeOfBStarTree::moveToRight()
{
    int maxSize = this->degree - 1;
    int indexFound = 0;
    //Verifica se pode obter de algum irmão, um valor excedente
    std::vector<NodeOfBStarTree *> pointers = father->getVectorOfPointers();
    for (int index = 0; index < pointers.size(); ++index)
    {
        if (this == pointers[index])
        {
            indexFound = index;

            if (index < pointers.size()-1)
            {
                NodeOfBStarTree* rightBrother = pointers[index+1];
                if (rightBrother->getVectorOfEntries().size() < maxSize)
                {
                    //faz e retorna
                    //Este faz não esta considerando ponteiros filhos
                    int lastData = removeLastPositionOfVectorOfEntries();
                    int top = father->entryByIndex(index); // obtem o numero de cima
                    father->setEntryByIndex(index, lastData);
                    rightBrother->insertInFirstPositionOfVectorOfEntries(top);

                    //Mover 1 ponteiro
                    if (getVectorOfPointers().size() > 0)
                    {
                        NodeOfBStarTree* last = removeLastPointer();
                        rightBrother->insertInFirstPositionOfVectorOfPointers(last);
                        last->setFather(rightBrother);
                    }

                    return;
                }
            }
        }
    }
}

void NodeOfBStarTree::moveToLeft()
{
    int maxSize = this->degree - 1;
    int indexFound = 0;
    //Verifica se pode obter de algum irmão, um valor excedente
    std::vector<NodeOfBStarTree *> pointers = father->getVectorOfPointers();
    for (int index = 0; index < pointers.size(); ++index)
    {
        if (this == pointers[index])
        {
            indexFound = index;
            //Verifica o irmão esquerdo, se tiver
            if (index >= 1)
            {
                NodeOfBStarTree* leftBrother = pointers[index-1];
                if (leftBrother->getVectorOfEntries().size() < maxSize)
                {
                    //faz e retorna
                    //Este faz não esta considerando ponteiros filhos
                    int myFirst = removeFirstPositionOfVectorOfEntries();
                    int top = father->entryByIndex(index-1); // obtem o numero de cima
                    father->setEntryByIndex(index-1, myFirst);
                    //insere número de cima na posição zero de nodeToFix
                    leftBrother->insertInLastPositionOfVectorOfEntries(top);

                    if (getVectorOfPointers().size() > 0)
                    {
                        NodeOfBStarTree* firstP = removeFirstPointer();
                        leftBrother->insertInLastPositionOfVectorOfPointers(firstP);
                        firstP->setFather(leftBrother);
                    }

                    return;
                }
            }
        }
    }
}

void NodeOfBStarTree::receiveNodeToInsertFromDownside
(
    NodeOfBStarTree* originalNode,
    NodeOfBStarTree* left,
    NodeOfBStarTree* right,
    int numberToInsert
)
{
    left->father = this;
    right->father = this;

    int maxEntries = this->degree - 1;

    //caso no qual o nó não está full, assim ele não se divide
    int insertionPosition = 0;

    for (int index = 0; index < this->vectorOfPointers.size(); ++index)
    {
        if (vectorOfPointers[index] == originalNode)
        {
            insertionPosition = index;
        }
    }

    if (insertionPosition == vectorOfEntries.size())
    {
        vectorOfEntries.push_back(numberToInsert);
    }
    else //é menor
    {
        vectorOfEntries.insert
        (
            vectorOfEntries.begin()+insertionPosition,
            numberToInsert
        );
    }

    if (vectorOfPointers.size() == 0)
    {
        vectorOfPointers.push_back(left);
        vectorOfPointers.push_back(right);
    }
    else
    {
        vectorOfPointers[insertionPosition] = left;
        vectorOfPointers.insert(vectorOfPointers.begin()+insertionPosition+1, right);
    }

    if (vectorOfEntries.size() > maxEntries)
    {
        if (father == nullptr)
        {
            int middle = vectorOfEntries.size() / 2;

            NodeOfBStarTree* leftMe = new NodeOfBStarTree(this, this->degree);
            NodeOfBStarTree* rightMe = new NodeOfBStarTree(this, this->degree);
            for (int index = 0; index < middle; ++index)
            {
                leftMe->insert(vectorOfEntries[index]);
            }
            for (int index = middle+1; index < vectorOfEntries.size(); ++index)
            {
                rightMe->insert(vectorOfEntries[index]);
            }
            int backupNumber = vectorOfEntries[middle];

            for (int index = 0; index <= middle; ++index)
            {
                vectorOfPointers[index]->father = leftMe;
                leftMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }
            for (int index = middle+1; index < vectorOfPointers.size(); ++index)
            {
                vectorOfPointers[index]->father = rightMe;
                rightMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }

            vectorOfEntries.clear();
            vectorOfPointers.clear();
            vectorOfEntries.push_back(backupNumber);
            vectorOfPointers.push_back(leftMe);
            vectorOfPointers.push_back(rightMe);
        } //fim de root
        else //quando não é root o full
        {
            int middle = vectorOfEntries.size() / 2;

            NodeOfBStarTree* leftMe = new NodeOfBStarTree(this, this->degree);
            NodeOfBStarTree* rightMe = new NodeOfBStarTree(this, this->degree);
            for (int index = 0; index < middle; ++index)
            {
                leftMe->insert(vectorOfEntries[index]);
            }
            for (int index = middle+1; index < vectorOfEntries.size(); ++index)
            {
                rightMe->insert(vectorOfEntries[index]);
            }
            int backupNumber = vectorOfEntries[middle];

            for (int index = 0; index <= middle; ++index)
            {
                vectorOfPointers[index]->father = leftMe;
                leftMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }
            for (int index = middle+1; index < vectorOfPointers.size(); ++index)
            {
                vectorOfPointers[index]->father = right;
                rightMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }

            vectorOfEntries.clear();
            vectorOfPointers.clear();

            //faz chamada para o pai receber tudo
            father->receiveNodeToInsertFromDownside
            (
                this,
                leftMe,
                rightMe,
                backupNumber
            );
        }
    }
}

void NodeOfBStarTree::getDotFileRepresentation(std::string & msg)
{
    int maxEntries = this->degree - 1;
    std::string name = getNodeName();

    msg += "\""+name+"\" [label = \"";

    //Inserir as partes internas
    for (int index = 0; index < maxEntries; ++index)
    {
        msg += "<"+std::to_string(index)+"> ";

        if (index < vectorOfEntries.size())
        {
            msg += std::to_string(vectorOfEntries[index])+" ";
        }

        if (index < maxEntries-1)
            msg += "| ";
    }

    msg += "\"];";
}

std::vector<NodeOfBStarTree *> NodeOfBStarTree::getVectorOfPointers()
{
    return this->vectorOfPointers;
}
