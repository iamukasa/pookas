#include "QuizQuestion.h"

QuizQuestion::QuizQuestion(void)
{
}

QuizQuestion::~QuizQuestion(void)
{
}

void QuizQuestion::setQuestion( std::string q )
{
	question = q; 

}

void QuizQuestion::addAnswer( std::string a )
{
	answers.push_back( a );
}

std::string QuizQuestion::getQuestion()
{
	return question;
}

std::vector <std::string>* QuizQuestion::getAnswers()
{
	return &answers;
}