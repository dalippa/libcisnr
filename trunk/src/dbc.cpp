/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#include "dbc.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
  std::string buildBaseStr(const string& condition, const string& fn, const int& line_no)
  {
    stringstream strm;
    strm << "'" << condition << "' failed in " << fn << "#" << line_no;
    return strm.str();
  }
}

void dbc_assert(const string& condition, const string& function,
                const string& filename, const int line_no, bool do_throw)
{
  stringstream strm(buildBaseStr(condition, filename, line_no));
  strm << " at function " << function << "!" << endl;
  cerr << strm.str();
  if (do_throw) throw logic_error(strm.str());
}

void dbc_assert(const string& condition,
                const string& filename, const int line_no, bool do_throw)
{
  stringstream strm(buildBaseStr(condition, filename, line_no));
  strm << "!" << endl;
  cerr << strm.str();
  if (do_throw) throw logic_error(strm.str());
}
