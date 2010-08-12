/*
 * The information in this file is
 * Copyright(c) David Lippa (dalippa@gmail.com)
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */
#ifndef DBC_H
#define DBC_H

#include <string>

extern void dbc_assert(const std::string& condition, const std::string& function,
                       const std::string& filename, const int line_no, bool do_throw = true);

extern void dbc_assert(const std::string& condition, const std::string& filename, const int line_no,
                       bool do_throw = false);

#ifndef INVARIANT
#define INVARIANT(x) { if (!x) { ASSERT(x, __FILE__, __LINE__); } }
#endif
#ifndef INVARIANTRV
#define INVARIANTRV(x, rv) { if (!x) { ASSERTRV(x, __FILE__, __LINE__); return rv; } }
#endif
#ifndef INVARIANTNRV
#define INVARIANTNRV(x) { if (!x) { ASSERTRV(x, __FILE__, __LINE__); return; } }
#endif

#ifndef DEBUG

#ifdef PRETTY_FUNCTION
#define ASSERT(x, filename, line_no) dbc_assert(#x, PRETTY_FUNCTION, filename, line_no);
#else
#define ASSERT(x, filename, line_no) dbc_assert(#x, filename, line_no);
#endif

#define REQUIRE(x) INVARIANT(x)
#define ENSURE(x) INVARIANT(x)

#else // release mode

#define ASSERT(x, filename, line_no)

#define REQUIRE(x) INVARIANT(x)
#define ENSURE(x) INVARIANT(x)

#endif

#endif
