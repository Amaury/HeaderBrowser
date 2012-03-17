#include <vector>
#include <string>
using namespace std;

#include "styx.hh"
#include "xhb.hh"
#include "head2xhb.hh"
#include "xhb2html.hh"

void	usage()
{
  cout << "Usage:\n" <<  "headerbrowser [-t type] [-o output_directory] files ...\n" << "headerbrowser -h" << endl;
  exit(0);
}

Head2Xhb	*fromHeader(vector<string> files)
{
  Head2Xhb*				parser;
  StyxDom*				dom;
  vector<StyxDomNode*>			l;
  vector<StyxDomNode*>::iterator	it;
  string				id, file, line;

  parser = new Head2Xhb(files);
  dom = parser->getDom();
  l = dom->getFromXpath("/hb:headerbrowser/hb:warning");
  for (it = l.begin(); it != l.end(); it++)
    {
      id = (*(((*it)->getAttributes(XHB_ID_ATTR)).begin()))->getValue();
      file = (*(((*it)->getAttributes(XHB_FILE_ATTR)).begin()))->getValue();
      line = (*(((*it)->getAttributes(XHB_LINE_ATTR)).begin()))->getValue();
      cout << "Warning: " << id << " in file " << file <<
	" at line " << line << endl;
    }
  return (parser);
}

int	main(int ac, char **av)
{
  int			optch;
  char			*optstr = "ht:o:l:";
  string		output;
  string		type;
  string		lang;
  vector<string>	files;
  Head2Xhb*		parser;
  StyxDom*		dom;
  Xhb2Html*		toHtml;
  FILE*			file;
  const char		*tmp, *tmp2;

  while ((optch = getopt(ac, av, optstr)) != -1)
    {
      switch (optch)
	{
	case 'o':
	  output = (string)optarg;
	  break ;
	case 't':
	  type = (string)optarg;
	  break ;
	case 'h':
	  usage();
	  break ;
	case 'l':
	  lang = (string)optarg;
	  break ;
	default:
	  cout << "Unknown option" << endl;
	  exit(1);
	}
    }
  if (lang.size() && lang != "fr" && lang != "eng")
    {
      cout << "Unknown language \"" << lang << "\"" << endl;
      exit(1);
    }
  if (lang.size() == 0)
    lang = "eng";
  if (optind == ac)
    {
      cout << "No header files given" << endl;
      exit(1);
    }
  for (; optind < ac; ++optind)
    files.push_back((string)av[optind]);
  if (!type.size() || type == "h2h")
    {
      parser = fromHeader(files);
      dom = parser->getDom();

      toHtml = new Xhb2Html();
      tmp = output.c_str();
      tmp2 = lang.c_str();
      toHtml->go(dom, tmp, tmp2);
    }
  if (type == "h2x")
    {
      output = (output.size() ? output : ".") + "/hbresult.xhb";
      file = fopen(output.c_str(), "w");
      parser = fromHeader(files);
      dom = parser->getDom();
      dom->writeDom(file);
      fclose(file);
    }
  return (0);
}
