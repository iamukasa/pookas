/** \class QuizQuestion
Holds data for each quiz question
*/

#ifndef _QUIZQUESTION_H_
#define _QUIZQUESTION_H_

#include <iostream>
#include <vector> 

class QuizQuestion
{
public:
	QuizQuestion(void);
	~QuizQuestion(void);

	void setQuestion( std::string q );
	void addAnswer( std::string a );
	std::string getQuestion();
	std::vector <std::string>* getAnswers();
	
	int getCorrectAnswer();
	void setCorrectAnswer( int a );

private:
	std::string question;
	std::vector <std::string> answers;
	int correctAnswer;
};

#endif