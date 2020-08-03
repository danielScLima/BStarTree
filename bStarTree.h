#ifndef BTREE_STAR_H
#define BTREE_STAR_H

#include "nodeOfBStarTree.h"
#include <iostream>

/*!
 * \brief The BTreeStar class
 */
class BTreeStar
{
public:
    /*!
     * \brief BTreeStar
     * \param degree
     */
    BTreeStar(int degree = 4);
    ~BTreeStar();

    /*!
     * \brief getRoot
     * \return
     */
    NodeOfBStarTree* getRoot();

    /*!
     * \brief getDegree
     * \return
     */
    int getDegree();
    /*!
     * \brief entriesSize
     * \return
     */
    int entriesSize();

    /*!
     * \brief getDotFileContent
     * \return
     */
    std::string getDotFileContent();

    /*!
     * \brief insert
     * \param number
     */
    bool insert(int number);
    /*!
     * \brief search
     * \param number
     * \return
     */
    NodeOfBStarTree* search(int number);
    /*!
     * \brief remove
     * \param number
     * \return
     */
    bool remove(int number);

    /*!
     * \brief dealockNodeOfBTrees
     */
    void dealockNodeOfBTrees();

private:
    NodeOfBStarTree* root = nullptr;

    //Is the number of cell's son
    int degree = 2;

    /*!
     * \brief fixNodeWithSmallCountOfElements
     * \param nodeToFix
     * \param removedNodes
     */
    void fixNodeWithSmallCountOfElements
    (
        NodeOfBStarTree *nodeToFix,
        std::vector<NodeOfBStarTree*> &removedNodes
    );
    /*!
     * \brief getAncestor
     * \param node
     * \param number
     * \return
     */
    NodeOfBStarTree *getAncestor(NodeOfBStarTree *node, int number);

};

#endif // BTREE_STAR_H
