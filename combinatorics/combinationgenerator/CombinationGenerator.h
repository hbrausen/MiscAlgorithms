/***************************************************************************
 *   Copyright (C) 2010 by Henry Brausen                                   *
 *   hbrausen@ualberta.ca                                    		       *
 ***************************************************************************/
#ifndef COMBINATIONGENERATOR_H
#define COMBINATIONGENERATOR_H

#include "config.h"

#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>

/* C++ templatized combination generator based on java source from:
 * http://www.merriampark.com/comb.htm, using algorithm from
 * 'Kenneth H. Rosen, Discrete Mathematics and Its Applications, 2nd edition'.
 * Not safe with numbers that cannot fit into an unsigned long. (r <= 9)
 * Adapted by Henry Brausen <hbrausen@ualberta.ca>
 */
template <typename T>
class CombinationGenerator
{
	public:
		/* Default Constructor */
		CombinationGenerator();
		
		/* Full Constructor */
		CombinationGenerator(const int& inR, const std::vector<T>& inSet) throw (std::out_of_range, std::invalid_argument, std::runtime_error);
		
		/* Destructor */
		~CombinationGenerator();
		
		/* Get next combination (throw out_of_range if no more combinations exist)
		* NOTE -- Reference returned is valid only until next call to getNextCombination!
		*/
		const std::vector<T>& next_combination() throw (std::out_of_range, std::runtime_error);
		
		/* Reset Combination Generator (keep current r and n) */
		void reset() throw (std::runtime_error);
		
		/* Reset Combination Generator with new r and n : to choose new n and r*/
		void reset(const int& inR, const std::vector<T>& inSet) throw (std::out_of_range, std::invalid_argument);
	protected:
		/* Compute factorial of n */
		static const unsigned long long fact(const unsigned long long& n);
		
		/* Build vector subset (combination) from indices in integer array */
		void buildCombination();
		
		/* Disallow pass-by-value */
		CombinationGenerator(const CombinationGenerator& src);
		
		/* Disallow assignment */
		CombinationGenerator& operator=(const CombinationGenerator& rhs);
		
		int mN;
		int mR;
		unsigned long mNumCombs;
		unsigned long mNumLeft;
		std::vector<T> mSet; // entire set of N 
		int* mSelect; // use r indices
		std::vector<T> mCombination; // current combination
};

template <typename T>
CombinationGenerator<T>::CombinationGenerator()
{
	mN = 0;
	mR = 0;
	mNumCombs = 0;
	mNumLeft = 0;
	mSelect = new int[1];	// Workaround
}

template <typename T>
CombinationGenerator<T>::CombinationGenerator(const int& inR, const std::vector<T>& inSet) throw (std::out_of_range, std::invalid_argument, std::runtime_error)
{
	if(inSet.size() <= 0) {
		throw std::out_of_range("Value of n too small: (n <= 0)");
	}
	if(inR > 20) {
		throw std::out_of_range("Value of r too large: (r > 20)");
	}
	if(inR <= 0) {
		throw std::out_of_range("Value of r too small: (r <= 0)");
	}
	if(inR > inSet.size()) {
		throw std::invalid_argument("Value of r cannot be larger than n.");
	}
	mN = inSet.size();
	mR = inR;
	
	mSelect = new int[mR]; //index for new combination
	
	unsigned long long a = 1;
	unsigned long long b = 1;
	
	// numerator
	for(int i = mN; i > (mN-mR); --i) {
		a *= i;
	}
	// denominator
	for(int j = mR; j > 1; --j) {
		b *= j;
	}
	
	/* Calculate # of unique combinations */
	mNumCombs = mNumLeft = (a/b);
	
	mSet.reserve(mN); // give enough memory for entire set
	mCombination.reserve(mR); // give enough memory for the combination
	
	mSet = inSet;
	
	/* Pre-calculate first combination */
	for(int i = 0; i < mR; ++i) {
		mSelect[i] = i;
	}
}

/* Destructor */
template <typename T>
CombinationGenerator<T>::~CombinationGenerator()
{
	//if(mR > 0) {
		delete[] mSelect;
	//}
}

template <typename T>
const std::vector<T>& CombinationGenerator<T>::next_combination() throw (std::out_of_range, std::runtime_error)
{
	if((mN <= 0)||(mR <= 0)) {
		throw std::runtime_error("next_combination(): not initialized");
	}
	
	if(mNumLeft <= 0) {
		throw std::out_of_range("next_combination(): all combinations exhausted");
	}
	
	// For the first combination
	if(mNumLeft == mNumCombs) {
		mNumLeft--;
		buildCombination();
		return mCombination;
	}
	
	int i = mR - 1;
	
	while(mSelect[i] == mN - mR + i) {
		i--;
	}
	++mSelect[i];
	
	for(int j = i + 1; j < mR; ++j) {
		mSelect[j] = mSelect[i] + j - i;
	}
	
	mNumLeft--;
	
	buildCombination();
	return mCombination;
}

template<typename T>
void CombinationGenerator<T>::reset() throw (std::runtime_error)
{
	if((mN <= 0)||(mR <= 0)) {
		throw std::runtime_error("next_combination(): not initialized");
	}
	unsigned long long a = 1;
	unsigned long long b = 1;
	
	// numerator
	for(int i = mN; i > (mN-mR); --i) {
		a *= i;
	}
	// denominator
	for(int j = mR; j > 1; --j) {
		b *= j;
	}
	
	/* Calculate # of unique combinations */
	mNumCombs = mNumLeft = (a/b);

	mCombination.clear();
	for(int i = 0; i < mR; ++i) {
		mSelect[i] = i;
	}
}

template <typename T>
void CombinationGenerator<T>::reset(const int& inR, const std::vector<T>& inSet) throw (std::out_of_range, std::invalid_argument)
{
	if(inSet.size() <= 0) {
		throw std::out_of_range("Value of n too small: (n <= 0)");
	}
	if(inR > 20) {
		throw std::out_of_range("Value of r too large: (r > 20)");
	}
	if(inR <= 0) {
		throw std::out_of_range("Value of r too small: (r <= 0)");
	}
	if(inR > inSet.size()) {
		throw std::invalid_argument("Value of r cannot be larger than n.");
	}
	mN = inSet.size();
	mR = inR;
	
	delete[] mSelect;
	mSelect = new int[mR];
	
	unsigned long long a = 1;
	unsigned long long b = 1;
	
	for(int i = mN; i > (mN-mR); --i) {
		a *= i;
	}
	for(int j = mR; j > 1; --j) {
		b *= j;
	}
	
	/* Calculate # of unique combinations */
	mNumCombs = mNumLeft = (a/b);
	
	mSet.reserve(mN);
	mCombination.reserve(mR);
	
	mSet = inSet;
	
	/* Pre-calculate first combination */
	for(int i = 0; i < mR; ++i) {
		mSelect[i] = i;
	}
}

//actual combinations of x y values
template<typename T>
void CombinationGenerator<T>::buildCombination()
{
	mCombination.clear();
	for(int i = 0; i < mR; ++i) {
		mCombination.push_back(mSet[mSelect[i]]);
	}
}

/* Compute factorial */
template <typename T>
const unsigned long long CombinationGenerator<T>::fact(const unsigned long long& n)
{
	if(n == 0) { return 0; }
	unsigned long long ret = 1;
	for(int i = n; i > 1; --i) {
		ret *= i;
	}
	return ret;
}

#endif	// COMBINATIONGENERATOR_H
