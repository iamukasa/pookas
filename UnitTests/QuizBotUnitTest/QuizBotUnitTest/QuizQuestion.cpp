#include "QuizQuestion.h"

QuizQuestion::QuizQuestion(void)
{
	correctAnswer = 0;
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

void QuizQuestion::setCorrectAnswer( int a )
{
	correctAnswer = a;
}

int QuizQuestion::getCorrectAnswer()
{
	return correctAnswer;
}