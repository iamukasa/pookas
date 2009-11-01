#include "QuizPage.h"

QuizPage::QuizPage(void)
{
	counter = 0; 
}

QuizPage::~QuizPage(void)
{
}

/** 
\fn void QuizPage::loadData( std::string filename )
\brief Loads data from a text file and populates the questions vector with it
\param filename File name of the file that contains HTML data
*/
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

void QuizPage::loadHTMLDataFromFile( std::string filename )
{
	std::string line;
	std::ifstream file (filename.c_str());
	std::string c;
	bool ignore = false;
	std::vector <std::string> stringslist; 
	if (file.is_open())
	{
		while (!file.eof() )
		{
			QuizQuestion q;

			c = file.get();
			if ( c == "<" )
			{
				ignore = true; 
			}

			else if ( c == ">" )
			{
				ignore = false;
				stringslist.push_back(std::string(""));
			}

			else if (!ignore && c!= "\n") //not a < or > and not ignoring
			{
				stringslist.at(stringslist.size()-1).append(std::string(c));
			}
			
		}

		file.close();
	}
		
	//remove all the ones which are spaces only 
	for (unsigned int j = 0; j < stringslist.size(); j++ )
	{	
		
		if ( stringslist.at(j).find('.') != std::string::npos ) //it's a question 
		{
			//std::cout << "Q" << stringslist.at(j) << "\n";
			QuizQuestion q;			
			q.setQuestion(stringslist.at(j)); 
			questions.push_back(q);			
		}

		else if ( stringslist.at(j).find(':') != std::string::npos ) //an answer
		{
			//std::cout << "A" << stringslist.at(j) << "\n";			
			int asterixIndex = stringslist.at(j).find('*');
			if ( asterixIndex != std::string::npos ) //it's a correct answer
			{
				int lastAnswer = questions.at(questions.size()-1).getAnswers()->size();
				questions.at(questions.size()-1).setCorrectAnswer(lastAnswer);
				stringslist.at(j).erase(stringslist.at(j).begin()+asterixIndex);
			}
			
			questions.at(questions.size()-1).addAnswer(stringslist.at(j));			
		}

	}		
}

/** 
\fn void QuizPage::loadHTMLData( std::string data )
\brief Reads HTML data from a string and populates the questions list with it
\param data String containing HTML data for quiz
*/
void QuizPage::loadHTMLData( std::string data )
{
	std::string c;
	bool ignore = false;
	std::vector <std::string> stringslist; 
	
	for ( unsigned int i = 0; i < data.length(); i++ )
	{
		QuizQuestion q;

		c = data.at(i);
		if ( c == "<" )
		{
			ignore = true; 
		}

		else if ( c == ">" )
		{
			ignore = false;
			stringslist.push_back(std::string(""));
		}

		else if (!ignore && c!= "\n") //not a < or > and not ignoring
		{
			stringslist.at(stringslist.size()-1).append(std::string(c));
		}
	}
		
		
	//remove all the ones which are spaces only 
	for (unsigned int j = 0; j < stringslist.size(); j++ )
	{	
		
		if ( stringslist.at(j).find('.') != std::string::npos ) //it's a question 
		{
			//std::cout << "Q" << stringslist.at(j) << "\n";
			QuizQuestion q;			
			q.setQuestion(stringslist.at(j)); 
			questions.push_back(q);			
		}

		else if ( stringslist.at(j).find(':') != std::string::npos ) //an answer
		{
			//std::cout << "A" << stringslist.at(j) << "\n";			
			int asterixIndex = stringslist.at(j).find('*');
			if ( asterixIndex != std::string::npos ) //it's a correct answer
			{
				int lastAnswer = questions.at(questions.size()-1).getAnswers()->size();
				questions.at(questions.size()-1).setCorrectAnswer(lastAnswer);
				stringslist.at(j).erase(stringslist.at(j).begin()+asterixIndex);
			}
			
			questions.at(questions.size()-1).addAnswer(stringslist.at(j));			
		}

	}	
	
	//print out stringslist
	for (unsigned int i = 0; i < questions.size(); i++ )
	{
		std::cout << "Q:" << questions.at(i).getQuestion() << "\n";
		std::cout << "Correct answer: " << questions.at(i).getCorrectAnswer() << "\n";
		for ( unsigned int y = 0; y < questions.at(i).getAnswers()->size(); y++ )
		{
			std::cout << "A: " << questions.at(i).getAnswers()->at(y) << "\n";
		}
	}

	
}

/** 
\fn QuizQuestion* QuizPage::getNextQuestion()
\brief Gets the next question in the quiz
\return Next question 
*/
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

/** 
\fn void QuizPage::reset()
\brief Resets the index into the quiz vector
*/
void QuizPage::reset()
{
	counter = 0;
}