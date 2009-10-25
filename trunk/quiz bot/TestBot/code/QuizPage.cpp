#include "QuizPage.h"

QuizPage::QuizPage(void)
{
	counter = 0; 
}

QuizPage::~QuizPage(void)
{
}

void QuizPage::loadData( std::string filename )
{
	std::string line;
	std::ifstream file (filename.c_str());

	if (file.is_open())
	{
		while (!file.eof() )
		{
			QuizQuestion q;

			std::getline (file, line);
			
			if ( line.size() > 0 )
			{
				if ( line.at(0) == 'Q' ) //it is a question
				{			
					questions.push_back(q); 
					questions.at(questions.size()-1).setQuestion( line.substr(2) );

					std::cout << "Q : " << questions.at(questions.size()-1).getQuestion() << std::endl;
				}

				else if ( line.at(0) == 'A' || line.at(0) == 'C' ) //it is an answer
				{
					questions.at(questions.size()-1).addAnswer( line.substr(2) );
					
					if ( line.at(0) == 'C' ) //if it's a correct answer 
					{
						questions.at(questions.size()-1).setCorrectAnswer( questions.at(questions.size()-1).getAnswers()->size()-1 );
					}
				}
			}
		}

		file.close();
	}


}

QuizQuestion* QuizPage::getNextQuestion()
{
	unsigned int index = counter;
	counter++;
	if ( index < questions.size() )
	{
		return &questions.at(index);
	}
	else
	{
		return NULL;
	}
}

void QuizPage::reset()
{
	counter = 0;
}