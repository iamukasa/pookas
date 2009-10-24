#ifndef _QUIZPAGE_H_
#define _QUIZPAGE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "QuizQuestion.h" 

class QuizPage
{
public:
	QuizPage(void);
	~QuizPage(void);

	void loadData( std::string filename );
	QuizQuestion* getNextQuestion();
	void reset(); 
	
private:
	std::vector <QuizQuestion> questions; 
	int counter;
};

#endif