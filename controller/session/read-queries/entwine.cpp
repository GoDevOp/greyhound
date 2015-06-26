#include "read-queries/entwine.hpp"

#include <entwine/reader/query.hpp>
#include <entwine/tree/clipper.hpp>
#include <entwine/types/schema.hpp>

EntwineReadQuery::EntwineReadQuery(
        const entwine::Schema& schema,
        bool compress,
        bool rasterize,
        std::unique_ptr<entwine::Query> query)
    : ReadQuery(schema, compress, rasterize)
    , m_query(std::move(query))
{ }

EntwineReadQuery::~EntwineReadQuery()
{ }

void EntwineReadQuery::readPoint(
        char* pos,
        const entwine::Schema& schema,
        bool rasterize)
{
    m_query->get(index(), pos);
}

bool EntwineReadQuery::eof() const
{
    return index() == numPoints();
}

std::size_t EntwineReadQuery::numPoints() const
{
    return m_query->size();
}

