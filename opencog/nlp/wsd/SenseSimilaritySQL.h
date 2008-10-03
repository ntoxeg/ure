/*
 * SenseSimilaritySQL.h
 *
 * Fetches word-sense similarity measures from an SQL
 * database where a pre-computed set has been previously
 * stored.
 *
 * Copyright (c) 2008 Linas Vepstas <linas@linas.org>
 */

#ifndef _OPENCOG_SENSE_SIMILARITY_SQL_H
#define _OPENCOG_SENSE_SIMILARITY_SQL_H

#ifdef HAVE_SQL_STORAGE

#include <opencog/atomspace/SimpleTruthValue.h>
#include <opencog/nlp/wsd/SenseSimilarity.h>
#include <opencog/persist/odbcxx.h>

namespace opencog {

class SenseSimilaritySQL :
	public SenseSimilarity
{
	private:
		ODBCConnection *db_conn;

		class Response;

	public:
		SenseSimilaritySQL(void);
		virtual ~SenseSimilaritySQL();

		virtual SimpleTruthValue similarity(Handle, Handle);
};

} // namespace opencog

#endif // HAVE_SQL_STORAGE

#endif // _OPENCOG_SENSE_SIMILARITY_SQL_H
