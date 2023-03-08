#include <model/Model.h>
#include <cstdlib>
#include <ctime>

namespace SSw
{

using std::rand;

Model::Model()
    : m_width(0),
      m_height(0),
      m_totalMineNr(0),
      m_discoveredFieldsNr(0),
      m_data()
{
}

void Model::reset(int32_t width, int32_t height, int32_t mineNumber)
{
    m_width         = width;
    m_height        = height;
    m_totalMineNr  = mineNumber;
    m_discoveredFieldsNr = 0;
    m_data.clear();

    const int64_t fieldsNr = size();
    m_data.reserve(fieldsNr);
    m_data.insert(m_data.begin(), fieldsNr, SField());

    srand(std::time(0));
}

void Model::populate(int32_t xToSkip, int32_t yToSkip)
{
    populateMineCrew(xToSkip, yToSkip);
    populateNeighbourhood();
}

void Model::populateMineCrew(int32_t xToSkip, int32_t yToSkip)
{
    Q_ASSERT(m_totalMineNr < size());
    const uint64_t noMineFieldId = yToSkip * m_width + xToSkip;
    int64_t mineMade             = 0;

    while (mineMade < m_totalMineNr)
    {
        const uint64_t fieldId = rand() % size();
        Q_ASSERT(fieldId < m_data.size());

        if ((0 == m_data[fieldId].mine) && (fieldId != noMineFieldId))
        {
            m_data[fieldId].mine = 1;
            mineMade++;
        }
    }
}

bool Model::checkWinCondition() const
{
    const int32_t fieldsToDiscover = size() - m_discoveredFieldsNr - m_totalMineNr;
    return fieldsToDiscover == 0;
}

void Model::populateNeighbourhood()
{
    for (int32_t x = 0; x < m_width; ++x)
    {
        for (int32_t y = 0; y < m_height; ++y)
        {
            const uint8_t mineValue =
                    getMine   (x-1,   y-1)
                    + getMine (x,     y-1)
                    + getMine (x+1,   y-1)
                    + getMine (x-1,   y)
                    + getMine (x,     y)
                    + getMine (x+1,   y)
                    + getMine (x-1,   y+1)
                    + getMine (x,     y+1)
                    + getMine (x+1,   y+1);

            field(x,y).neighbours = mineValue;
        }
    }
}

uint8_t Model::getFlag(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).disarmed == 1 ? 1 : 0;
    }
    else
    {
        return 0;
    }
}

uint8_t Model::countFlagsAround(int32_t x, int32_t y) const
{
    return getFlag    (x-1,   y-1) // up
            + getFlag (x,     y-1)
            + getFlag (x+1,   y-1)
            + getFlag (x-1,   y)   // mid
            + getFlag (x,     y)
            + getFlag (x+1,   y)
            + getFlag (x-1,   y+1) // down
            + getFlag (x,     y+1)
            + getFlag (x+1,   y+1);
}

uint8_t Model::getNeighbours(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).neighbours;
    }
    else
    {
        return 0;
    }
}

uint8_t Model::getMine(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).mine;
    }
    else
    {
        return 0;
    }
}

bool Model::getDiscovered(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).discovered != 0;
    }
    else
    {
        return true;
    }
}

void Model::discover(int32_t x, int32_t y)
{
    if (field(x, y).discovered == 0 && field(x,y).disarmed == 0)
    {
        field(x, y).discovered = 1;
        m_discoveredFieldsNr++;
    }
}

void Model::disarm(int32_t x, int32_t y)
{
    if (field(x, y).disarmed < 2)
    {
        field(x, y).disarmed++;
    }
    else if (field(x, y).disarmed == 2)
    {
        field(x, y).disarmed = 0;
    }
}

bool Model::isValidIndex(int32_t x, int32_t y) const
{
    return (x >= 0 && x < m_width && y >= 0 && y < m_height);
}

const SField& Model::field(int32_t x, int32_t y) const
{
    const int32_t id = y * m_width + x;
    Q_ASSERT(id >= 0 && id < size());
    return m_data.at(id);
}

SField& Model::field(int32_t x, int32_t y)
{
    const int32_t id = y * m_width + x;
    Q_ASSERT(id >= 0 && id < size());
    return m_data[id];
}

} // namespace SSw
