#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>

/*!
 * \brief The NodeOfBStarTree class
 */
class NodeOfBStarTree
{
public:
    /*!
     * \brief NodeOfBStarTree
     * \param father
     * \param degree
     */
    NodeOfBStarTree(NodeOfBStarTree* father, int degree);

    /*!
     * \brief getFather
     * \return
     */
    NodeOfBStarTree* getFather();
    /*!
     * \brief setFather
     * \param father
     */
    void setFather(NodeOfBStarTree* father);

    /*!
     * \brief entryByIndex
     * \param index
     * \return
     */
    int entryByIndex(int index);
    /*!
     * \brief setEntryByIndex
     * \param index
     * \param number
     */
    void setEntryByIndex(int index, int number);

    /*!
     * \brief pointerByIndex
     * \param index
     * \return
     */
    NodeOfBStarTree* pointerByIndex(int index);

    /*!
     * \brief setDegree
     * \param degree
     */
    void setDegree(int degree);

    /*!
     * \brief getDotFileRepresentation
     * \param msg
     */
    void getDotFileRepresentation(std::string &msg);

    /*!
     * \brief getVectorOfPointers
     * \return
     */
    std::vector<NodeOfBStarTree*> getVectorOfPointers();

    /*!
     * \brief getNodeName
     * \return
     */
    const std::string getNodeName();

    /*!
     * \brief insert
     * \param number
     */
    bool insert(int number);

    /*!
     * \brief receiveNodeToInsertFromDownside
     * \param originalNode
     * \param left
     * \param right
     * \param numberToInsert
     */
    void receiveNodeToInsertFromDownside
    (
        NodeOfBStarTree *originalNode,
        NodeOfBStarTree *left,
        NodeOfBStarTree *right,
        int numberToInsert
    );

    /*!
     * \brief getVectorOfEntries
     * \return
     */
    std::vector<int> getVectorOfEntries();
    /*!
     * \brief removeEntryOfVectorOfEntries
     * \param number
     */
    void removeEntryOfVectorOfEntries(int number);

    /*!
     * \brief removeLastPositionOfVectorOfEntries
     * \return
     */
    int removeLastPositionOfVectorOfEntries();
    /*!
     * \brief removeFirstPositionOfVectorOfEntries
     * \return
     */
    int removeFirstPositionOfVectorOfEntries();
    /*!
     * \brief insertInFirstPositionOfVectorOfEntries
     * \param number
     */
    void insertInFirstPositionOfVectorOfEntries(int number);
    /*!
     * \brief insertInLastPositionOfVectorOfEntries
     * \param number
     */
    void insertInLastPositionOfVectorOfEntries(int number);
    /*!
     * \brief replaceEntryInVectorOfEntries
     * \param number
     * \param ancestorNumber
     */
    void replaceEntryInVectorOfEntries(int number, int ancestorNumber);

    /*!
     * \brief removeLastPointer
     * \return
     */
    NodeOfBStarTree *removeLastPointer();
    /*!
     * \brief removeFirstPointer
     * \return
     */
    NodeOfBStarTree *removeFirstPointer();
    /*!
     * \brief insertInFirstPositionOfVectorOfPointers
     * \param pointer
     */
    void insertInFirstPositionOfVectorOfPointers(NodeOfBStarTree *pointer);
    /*!
     * \brief insertInLastPositionOfVectorOfPointers
     * \param pointer
     */
    void insertInLastPositionOfVectorOfPointers(NodeOfBStarTree *pointer);
    /*!
     * \brief removeByIndexInVectorOfEntries
     * \param index
     */
    void removeByIndexInVectorOfEntries(int index);
    /*!
     * \brief removePointerOfVectorOfPointers
     * \param index
     */
    void removePointerOfVectorOfPointers(int index);

    /*!
     * \brief hasRightBrother
     * \return
     */
    int hasRightBrother();
    /*!
     * \brief positionInFather
     * \return
     */
    int positionInFather();
    /*!
     * \brief hasLeftBrother
     * \return
     */
    int hasLeftBrother();
    /*!
     * \brief leftSpaceInRightBrother
     * \return
     */
    int leftSpaceInRightBrother();
    /*!
     * \brief leftSpaceInLeftBrother
     * \return
     */
    int leftSpaceInLeftBrother();
    /*!
     * \brief someBrotherHasLeftSpace
     * \return
     */
    int someBrotherHasLeftSpace();
    /*!
     * \brief shouldMoveToRight
     * \return
     */
    int shouldMoveToRight();
    /*!
     * \brief moveToRight
     */
    void moveToRight();
    /*!
     * \brief moveToLeft
     */
    void moveToLeft();
    /*!
     * \brief getTopNumberToRight
     * \return
     */
    int getTopNumberToRight();
    /*!
     * \brief getRightBrother
     * \return
     */
    NodeOfBStarTree *getRightBrother();
    /*!
     * \brief getLeftBrother
     * \return
     */
    NodeOfBStarTree *getLeftBrother();
    /*!
     * \brief sendToUpstairs
     * \param oldDividionNumber
     * \param newDivisionNumber1
     * \param newDivisionNumber2
     * \param oldRef1
     * \param oldRef2
     * \param newRef
     * \param isRight
     */
    void sendToUpstairs
    (
        int oldDividionNumber,
        int newDivisionNumber1,
        int newDivisionNumber2,
        NodeOfBStarTree *oldRef1,
        NodeOfBStarTree *oldRef2,
        NodeOfBStarTree *newRef,
        bool isRight
    );
    /*!
     * \brief fixRootNodeThatHasMoreElementsThatAllowed
     */
    void fixRootNodeThatHasMoreElementsThatAllowed();
    /*!
     * \brief fixNodeThatIsNotRootThatHasMoreElementsThatAllowed
     */
    void fixNodeThatIsNotRootThatHasMoreElementsThatAllowed();
    /*!
     * \brief getTopNumberToLeft
     * \return
     */
    int getTopNumberToLeft();
    /*!
     * \brief dealockSubTree
     */
    void dealockSubTree();
private:
    int degree = 2;
    NodeOfBStarTree* father = nullptr;

    std::vector<int> vectorOfEntries;
    std::vector<NodeOfBStarTree*> vectorOfPointers;
};

#endif // NODE_H
