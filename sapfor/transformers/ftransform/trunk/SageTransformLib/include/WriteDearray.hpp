#ifndef WRITE_DEARRAY_HPP
#define WRITE_DEARRAY_HPP

#include <vector>
#include <string>
#include "user.h"

using std::vector;
using std::string;

namespace SageTransform {

	/**
	 * Contains logic for Fortran WRITE procedure param scalarization.
	 * Logic is useful to make Fortran program compliant with DVM restrictions.
	 */
	class WriteDearray {
	public:

		//TODO remove space in the beginning
		static string DISTRIBUTED_IO_MARKER;

		/**
		 * Check for applicability of write paraams scalarization.
		 */
		static bool hasIOArrayComment(SgStatement * ioStmt);

		/**
		 * Generic method for removing array access in Fortran I/O procedures.
		 *
		 * @param ioStmt - currently only WRITE statement is supported.
		 * @return new scalar variables, created in the process.
		 */
		static vector<SgSymbol *> removeArrayAccess(SgStatement * ioStmt);

	private:
		/**
		 * Specific inner method for removing array access in Fortran write procedure.
		 *
		 * @param ioStmt statement with WRITE intrinsic procedure call.
		 * @return new scalar variables, created in process.
		 */
		static vector<SgSymbol *> removeArrayAccessInWrite(SgInputOutputStmt * writeStmt);
	};
}
#endif //WRITE_DEARRAY_HPP
