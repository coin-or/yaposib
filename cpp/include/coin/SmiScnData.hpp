// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.

#ifndef SmiScnData_HPP
#define SmiScnData_HPP

#if defined(_MSC_VER)
// Turn off compiler warning about long names
#  pragma warning(disable:4786)
#endif

#include "OsiSolverInterface.hpp"
#include "CoinPackedVector.hpp"
#include "CoinMpsIO.hpp"
#include "SmiCoreCombineRule.hpp"
#include "SmiLinearData.hpp"

#include <map>
#include <vector>

using namespace std;


typedef int SmiCoreIndex;
typedef int SmiScenarioIndex;
typedef int SmiStageIndex;

class SmiCoreData;

class SmiNodeData
	//: public SmiLinearData
{
public:
	typedef map<int,CoinPackedVector *> SmiRowMap;
	typedef map<int,double *> SmiDenseRowMap;
	void setCoreNode();
	/*
	CoinPackedVector * getRow(int i) {
		SmiRowMap::iterator r=rowMap.find(i);
		if (r!=rowMap.end()) return r->second;
		else return NULL;}
	*/
	double * getDenseRow(int i);

	inline SmiCoreData * getCore() { return core_;}
	inline int getStage() { return stg_;}

	inline void setCoreCombineRule(SmiCoreCombineRule *r){combineRule_=r;}
	inline SmiCoreCombineRule * getCoreCombineRule() { return combineRule_;}

	void copyRowLower(double * drlo);
	void copyRowUpper(double * drup);
	void copyColLower(double * dclo);
	void copyColUpper(double * dcup);
	void copyObjective(double * dobj);

	const int getNumMatrixElements(){
		if (this->has_matrix_)
			return this->strt_[getMatEnd()]-this->strt_[getMatStart()];
		else
			return 0;
	}
	 const int getRowLength(int irow){
		 if (this->has_matrix_)
			 return getLength(this->getMatStart()+irow-this->rowbeg_);
		 else
			return 0;
	 }
	 const int getRowLowerLength()   {return getLength(this->getRloStart());}
	 const int getRowUpperLength()   {return getLength(this->getRupStart());}
	 const int getColLowerLength()   {return getLength(this->getCloStart());}
	 const int getColUpperLength()   {return getLength(this->getCupStart());}
	 const int getObjectiveLength()  {return getLength(this->getObjStart());}

	 const int *getRowIndices(int irow){
		 if (this->has_matrix_)
			 return getIndices(this->getMatStart()+irow-this->rowbeg_);
		 else
			 return NULL;
	 }
	 int *getMutableRowIndices(int irow){
		 // using const_cast to stop warnings about cast-away constness
		 return const_cast<int *>(getRowIndices(irow));
	 }
	 const int *getRowLowerIndices()   {return getIndices(this->getRloStart());}
	 const int *getRowUpperIndices()   {return getIndices(this->getRupStart());}
	 const int *getColLowerIndices()   {return getIndices(this->getCloStart());}
	 const int *getColUpperIndices()   {return getIndices(this->getCupStart());}
	 const int *getObjectiveIndices()  {return getIndices(this->getObjStart());}

	 const double *getRowElements(int irow){
		 if (this->has_matrix_)
			 return getElements(this->getMatStart()+irow-this->rowbeg_);
		 else
			 return NULL;
	 }
	 double *getMutableRowElements(int irow){
		 // using const_cast to stop warnings about cast-away constness
		 return const_cast<double *>(getRowElements(irow));
	 }
	 const double *getRowLowerElements()   {return getElements(this->getRloStart());}
	 const double *getRowUpperElements()   {return getElements(this->getRupStart());}
	 const double *getColLowerElements()   {return getElements(this->getCloStart());}
	 const double *getColUpperElements()   {return getElements(this->getCupStart());}
	 const double *getObjectiveElements()  {return getElements(this->getObjStart());}


	CoinPackedVector * combineWithCoreRow(CoinPackedVector *cr, CoinPackedVector *nr);
	int combineWithDenseCoreRow(double *dr,CoinPackedVector *cpv,double *dels,int *indx);
	int combineWithDenseCoreRow(double *dr,const int nels,const int *inds, const double *dels, double *dest_dels,int *dest_indx);

	SmiNodeData(SmiStageIndex stg, SmiCoreData *core,
				 const CoinPackedMatrix *const matrix,
				 CoinPackedVector *dclo,
				 CoinPackedVector *dcup,
				 CoinPackedVector *dobj,
				 CoinPackedVector *drlo,
				 CoinPackedVector *drup);
	~SmiNodeData();

protected:
	void combineWithCoreDoubleArray(double *d_out, const CoinPackedVector &cpv, int o);
	void combineWithCoreDoubleArray(double *d_out, const int len, const int * inds, const double *dels, int o);
	//Memory assignment/deletion
	void assignMemory();
	void deleteMemory();

	//Covers for starts of arrays
	 const int getMatStart() { return mat_strt_;}
	 const int getMatEnd()   { return mat_strt_+nrow_;}
	 const int getRloStart() { return rlo_strt_;}
	 const int getRupStart() { return rup_strt_;}
	 const int getCloStart() { return clo_strt_;}
	 const int getCupStart() { return cup_strt_;}
	 const int getObjStart() { return obj_strt_;}

	//Access to stored memory
	 const int getLength  (int istart){
		return this->strt_[istart+1] - this->strt_[istart];
	}
	 const int * getIndices (int istart){
		return this->inds_+this->strt_[istart];
	}
	 const double *getElements(int istart){
		return this->dels_+this->strt_[istart];
	}

private:

	SmiStageIndex stg_;
	SmiRowMap rowMap;
	SmiDenseRowMap dRowMap;

	SmiCoreData *core_;
	bool isCoreNode_;
	SmiCoreCombineRule *combineRule_;

	int numarrays_;
	int nels_;
	int nrow_;
	int ncol_;
	int rowbeg_;
	int colbeg_;
	int nstrt_;
	bool has_matrix_;
	int mat_strt_;
	int clo_strt_;
	int cup_strt_;
	int obj_strt_;
	int rlo_strt_;
	int rup_strt_;
	double * dels_;
	int    * inds_;
	int    * strt_;
};


class SmiCoreData
{
public:
	inline int getNumCols(){ return ncol_;}
	inline int getNumRows(){ return nrow_;}
	inline int getNumStages(){ return nstag_;}
	inline int getNumCols(SmiStageIndex t){ return nColInStage_[t];}
	inline int getNumRows(SmiStageIndex t){ return nRowInStage_[t];}
	inline int getColStart(SmiStageIndex t){ return stageColPtr_[t];}
	inline int getRowStart(SmiStageIndex t){ return stageRowPtr_[t];}
	inline int getColStage(int i){ return colStage_[i];}
	inline int getRowStage(int i){ return rowStage_[i];}
	inline int getRowInternalIndex(int i){ return rowEx2In_[i];}
	inline int getColInternalIndex(int i){ return colEx2In_[i];}
	inline int getRowExternalIndex(int i){ return rowIn2Ex_[i];}
	inline int getColExternalIndex(int i){ return colIn2Ex_[i];}
	/*
	inline CoinPackedVector * getMatrixRow(SmiStageIndex t, int i){ return nodes_[t]->getRow(i);}
	*/
	inline const double * getDenseRowLower(SmiStageIndex t){return cdrlo_[t];}
	inline const double * getDenseRowUpper(SmiStageIndex t){return cdrup_[t];}
	inline const double * getDenseColLower(SmiStageIndex t){return cdclo_[t];}
	inline const double * getDenseColUpper(SmiStageIndex t){return cdcup_[t];}
	inline const double * getDenseObjCoefficients(SmiStageIndex t){return cdobj_[t];}

	void copyRowLower(double * drlo,SmiStageIndex t );
	void copyRowUpper(double * drup,SmiStageIndex t);
	void copyColLower(double * dclo,SmiStageIndex t);
	void copyColUpper(double * dcup,SmiStageIndex t);
	void copyObjective(double * dobj,SmiStageIndex t);

	inline SmiNodeData * getNode(SmiStageIndex t){return nodes_[t];}
	SmiCoreData(OsiSolverInterface *osi, int nstag, int *cstag, int *rstag);
	SmiCoreData(CoinMpsIO *cMps, int nstag, int *cstag, int *rstag);
	~SmiCoreData();

private:
	void gutsOfConstructor(int nrow,int ncol,int nstag,
							   int *cstag,int *rstag,
							   CoinPackedMatrix *matrix,
							   CoinPackedVector *dclo,
							   CoinPackedVector *dcup,
							   CoinPackedVector *dobj,
							   CoinPackedVector *drlo,
							   CoinPackedVector *drup);
private:
	int nrow_;
	int ncol_;
	SmiStageIndex nstag_;
	int *nColInStage_;
	int *nRowInStage_;
	int *stageColPtr_;
	int *stageRowPtr_;
	int *colStage_;
	int *rowStage_;
	int *colEx2In_;
	int *rowEx2In_;
	int *colIn2Ex_;
	int *rowIn2Ex_;
	double **cdrlo_;
	double **cdrup_;
	double **cdobj_;
	double **cdclo_;
	double **cdcup_;
	vector<SmiNodeData*> nodes_;
	vector<double *> pDenseRow_;
};

#endif //#define SmiScnData_HPP
