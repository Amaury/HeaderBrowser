#ifndef   __HEAD2XHB_H__
#define   __HEAD2XHB_H__

#include <vector>
#include <string>
using namespace std;

#include "styx.hh"
#include "parseheaderfile.hh"

class	Head2Xhb
{
public:
  StyxDom*	getDom(void);
  Head2Xhb(vector<string> files);
  ~Head2Xhb(void);
private:
  StyxDom*	dom;
};

#endif /* __HEAD2XHB._H__ */
