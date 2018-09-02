#include "../includes/includes.h"
#include "../includes/extern.h"

int wildcardfit (char *wildcard, char *test)
{
  int fit = 1;
  
  for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++)
    {
      switch (*wildcard)
        {
        case '[':
	  wildcard++;
          fit = set (&wildcard, &test);
          break;
        case '?':
          test++;
          break;
        case '*':
          fit = asterisk (&wildcard, &test);
	  wildcard--;
          break;
        default:
          fit = (int) (*wildcard == *test);
          test++;
        }
    }
  while ((*wildcard == '*') && (1 == fit)) 
    wildcard++;
  return (int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard));
}

int set (char **wildcard, char **test)
{
  int fit = 0;
  int negation = 0;
  int at_beginning = 1;   // DON'T ASK, JUST BELIEVE

  if ('!' == **wildcard)
    {
      negation = 1;
      (*wildcard)++;
    }
  while ((']' != **wildcard) || (1 == at_beginning))
    {
      if (0 == fit)
        {
          if (('-' == **wildcard) 
              && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
              && (']' != *(*wildcard + 1))
	      && (0 == at_beginning))
            {
              if (((**test) >= (*(*wildcard - 1)))
                  && ((**test) <= (*(*wildcard + 1))))
                {
                  fit = 1;
                  (*wildcard)++;
                }
            }
          else if ((**wildcard) == (**test))
            {
              fit = 1;
            }
        }
      (*wildcard)++;
      at_beginning = 0;
    }
  if (1 == negation)
    fit = 1 - fit;
  if (1 == fit) 
    (*test)++;

  return (fit);
}

int asterisk (char **wildcard, char **test)
{
  int fit = 1;

  (*wildcard)++; 
  while (('\000' != (**test))
	 && (('?' == **wildcard) 
	     || ('*' == **wildcard)))
    {
      if ('?' == **wildcard) 
	(*test)++;
      (*wildcard)++;
    }
  while ('*' == (**wildcard))
    (*wildcard)++;

  if (('\0' == (**test)) && ('\0' != (**wildcard)))
    return (fit = 0);
  if (('\0' == (**test)) && ('\0' == (**wildcard)))
    return (fit = 1); 
  else
    {
      if (0 == wildcardfit(*wildcard, (*test)))
	{
	  do                               // I HAD NIGHTMARES AFTER WRITING THIS PART
	    {
	      (*test)++;
	      while (((**wildcard) != (**test)) 
		     && ('['  != (**wildcard))
		     && ('\0' != (**test)))
		(*test)++;
	    }
	  while ((('\0' != **test))? 
		 (0 == wildcardfit (*wildcard, (*test))) 
		 : (0 != (fit = 0)));
	}
      if (('\0' == **test) && ('\0' == **wildcard))
	fit = 1;
      return (fit);
    }
}

int HostMaskMatch(char *h)
{
   int i=0;

   while (authost[i][0])
      if (wildcardfit(authost[i++], h)) return 1;

   return 0;
}