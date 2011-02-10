// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.

#ifndef SmiScnModel_HPP
#define SmiScnModel_HPP

#if defined(_MSC_VER)
// Turn off compiler warning about long names
#  pragma warning(disable:4786)
#endif

// Include files
#include "SmiDiscreteDistribution.hpp"
#include "SmiScenarioTree.hpp"
#include "SmiScnData.hpp"
#include "OsiSolverInterface.hpp"
#include "CoinPackedVector.hpp"
#include "SmiMessage.hpp"

// STL declarations
#include <map>
#include <vector>
using namespace std;

// forward declaration of SmiScnNode
class SmiScnNode;


//#############################################################################

/** SmiScnModel: COIN-SMI Scenario Model Class

	Concrete class for generating scenario stochastic linear programs.

	This class implements the Scenarios format of the Stochastic MPS
	modeling system (TODO: web pointer).  Core data and Scenarios data
	can be passed using COIN/OSI structures, or can be read from SMPS
	formatted files.

	Typical driver fragment looks like this
	\code
	SmiScnModel smi;
	smi.readSmps("app0110R");
	smi.setOsiSolverHandle(new OsiClpSolverInterface());
	OsiSolverInterface *osiStoch = smi.loadOsiSolverData();
	osiStoch->initialSolve();
	\endcode

	The setOsiSolverHandle method allows the user to pass in any OSI
	compatible solver.

  */
class SmiScnModel
{
	friend void SmiScnModelDiscreteUnitTest();
public:

    /**@name Read SMPS files.

		There should be three files: {name}.[core, time, stoch].
		If you have different extension conventions, then you can
		hack the method yourself.
		The files can be compressed. The object that reads the files is
		derived from CoinMpsIO.

		  The optional argument SmiCoreCombineRule allows user to pass in
		a class to override the default methods to combine core and stochastic data.

	*/
	int readSmps(const char *name,
		SmiCoreCombineRule *r=NULL );

	//SmiCoreData * getCore() {return core_;}

	/**@name Direct methods.

		Direct methods require the user to create instances of
		Core data and Scenario data.
		Currently, the dimension of the core nodes determines the
		dimension of the scenario nodes, but this is something that
		could easily be changed.
	*/

//@{



	/// generate scenarios from discrete distribution
	void processDiscreteDistributionIntoScenarios(SmiDiscreteDistribution *s, bool test=false);

	/** generate scenario with ancestor/branch node identification

		Core argument must be supplied.
		Data values combine with corresponding core values,
		if found, or creates them if not.

		Scenario nodes need to have same dimensions as core nodes.

		Data field arguments can be NULL, or empty.

		branch, anc, arguments must be supplied.  These
		identify the branching node according to the Stochastic MPS
		standard.

	*/
	SmiScenarioIndex generateScenario(SmiCoreData *core,
				CoinPackedMatrix *matrix,
				CoinPackedVector *dclo, CoinPackedVector *dcup,
				CoinPackedVector *dobj,
				CoinPackedVector *drlo, CoinPackedVector *drup,
				SmiStageIndex branch, SmiScenarioIndex anc, double prob,
				SmiCoreCombineRule *r = SmiCoreCombineReplace::Instance());

	/** generate scenario with labels information

		Core argument must be supplied.
		Data values combine with corresponding core values,
		if found, or creates them if not.

		Scenario nodes need to have same dimensions as core nodes.

		Data field arguments can be NULL, or empty.

		Labels are passed as vector<int> array.
		Adds new path using labels to find branching node.
	    The depth (root to leaf) of new path is labels.size().

	*/
	SmiScenarioIndex generateScenario(SmiCoreData *core,
		CoinPackedMatrix *matrix,
		CoinPackedVector *dclo, CoinPackedVector *dcup,
		CoinPackedVector *dobj,
		CoinPackedVector *drlo, CoinPackedVector *drup,
		vector<int>labels, double prob,
		SmiCoreCombineRule *r = SmiCoreCombineReplace::Instance());

	/**@name loadOsiSolverData

		Loads deterministic equivalent model into internal osi data structures
		and return handle.

		Note: this uses a callback class SmiCoreCombineRule to decide how to combine
		the core and stochastic data. The user can override the default
		methods when the scenario is generated (see SmiScnModel::generateScenario)
		or when SMPS files are processed (see SmiScnModel::readSmps).

    */
	OsiSolverInterface * loadOsiSolverData();

//@}

	// get scenario problem data
	SmiScenarioIndex getNumScenarios(){ return smiTree_.getNumScenarios();}
	double getScenarioProb(SmiScenarioIndex ns);
	SmiScnNode * getLeafNode(SmiScenarioIndex i){ return smiTree_.getLeaf(i)->getDataPtr(); }
	SmiScnNode * getRootNode(){ return smiTree_.getRoot()->getDataPtr(); }


	// getXXX by scenario
	double getObjectiveValue(SmiScenarioIndex ns);
	double *getColSolution(SmiScenarioIndex ns, int *length);
	double *getRowSolution(SmiScenarioIndex ns, int *length);

	// OsiSolverInterface
	void setOsiSolverHandle(OsiSolverInterface &osi)
	{
		osiStoch_ = osi.clone(false);
	}
	void setOsiSolverHandle(OsiSolverInterface *osi)
	{
		osiStoch_ = osi->clone(false);
	}
	OsiSolverInterface * getOsiSolverInterface();
        // If user wants to delete SmiScnModel but keep OsiSolverInterface
        inline void releaseSolver() {osiStoch_=NULL;}


	// constructor
	SmiScnModel():
		osiStoch_(NULL),
		drlo_(NULL), drup_(NULL), dobj_(NULL), dclo_(NULL), dcup_(NULL), matrix_(NULL),
		solve_synch_(false),totalProb_(0),core_(NULL)
	{ }

	// destructor
	~SmiScnModel();

	void addNode(SmiScnNode *node);
	void deleteNode(SmiScnNode *tnode);
private:
	CoinMessageHandler *handler_;
	SmiMessage *messages_;

	// internal clone of user declared OSI
	OsiSolverInterface * osiStoch_;
	// model statistics useful for predefining size of structures
	int nrow_;
	int ncol_;
	int nels_;
	int nels_max;
	// data pointers used in AddNode
	double *drlo_;
	double *drup_;
	double *dobj_;
	double *dclo_;
	double *dcup_;
	CoinPackedMatrix *matrix_;
	double *dels_;
	int    *indx_;
	int    *rstrt_;
	// number of scenarios
//	int scen_;
	// not sure if this is used
	int minrow_;
	// not sure if this is used
	bool solve_synch_;
	// total probability of added scenarios; used to normalize probability to one
	double totalProb_;
	//core model --- used for discrete distributions
	SmiCoreData * core_;
	// scenario tree pointer
	SmiScenarioTree<SmiScnNode *> smiTree_;
};

class SmiScnNode
{
	friend class SmiScnModel;
public:
	int getCoreColIndex(int i);
	int getCoreRowIndex(int i);
	inline void setScenarioIndex(SmiScenarioIndex i){ scen_=i;}
        inline SmiScenarioIndex getScenarioIndex() {return scen_;}
	inline int  getColStart() {return coffset_;}
	inline int  getRowStart() {return roffset_;}
	inline int getNumCols(){ return node_->getCore()->getNumCols(node_->getStage());}
	inline int getNumRows(){ return node_->getCore()->getNumRows(node_->getStage());}
	inline double getModelProb(){return mdl_prob_;}
	inline SmiScnNode * getParent(){ return parent_;}
        // So can delete root node
        inline void zapNode() {node_=NULL;}

        ~SmiScnNode()
        {
        	if (node_)
        	{
        		delete node_;
        		node_= NULL;
        	}
        }

private:
	inline void setRowOffset(int r) {roffset_ = r;}
	inline void setParent(SmiScnNode * g) {parent_=g;}
	inline void setColOffset(int c) {coffset_ = c;}
	inline double addProb(double prob){ return prob_+=prob;}
	inline double getProb(){return prob_;}
	inline void setProb(double p){prob_=p;}
	inline void setModelProb(double p){mdl_prob_=p;}
	inline SmiNodeData *getNode() {return node_;}
	SmiScnNode(SmiNodeData *&node)	{node_=node;prob_=0;parent_=NULL;scen_=-1;}

private:
	SmiNodeData *node_;
	SmiScnNode *parent_;
	double prob_;
	double mdl_prob_;
	int coffset_;
	int roffset_;
	SmiScenarioIndex scen_;
};

// function object for addnode loop
class SmiScnModelAddNode{
public:
	void operator() (SmiScnNode *node)
	{
		s_->addNode(node);
	}

	SmiScnModelAddNode(SmiScnModel *s) { s_ = s;}
private:
	SmiScnModel *s_;


};

// function object for deleteNode loop
class SmiScnModelDeleteNode{
public:
	void operator() (SmiScnNode *node)
	{
		s_->deleteNode(node);
	}

	SmiScnModelDeleteNode(SmiScnModel *s) { s_ = s;}
private:
	SmiScnModel *s_;


};

#endif //#define SmiScnModel_HPP
