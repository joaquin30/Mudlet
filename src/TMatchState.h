#ifndef MUDLET_TMATCHSTATE_H
#define MUDLET_TMATCHSTATE_H

/***************************************************************************
 *   Copyright (C) 2008-2010 by Heiko Koehn - KoehnHeiko@googlemail.com    *
 *   Copyright (C) 2014 by Ahmed Charles - acharles@outlook.com            *
 *   Copyright (C) 2022 by Stephen Lyons - slysven@virginmedia.com         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

class TMatchState
{
public:
    TMatchState(int numberOfConditions, int delta)
    : mNumberOfConditions(numberOfConditions)
    , mDelta(delta)
    {
    }

    // Copy constructor:
    TMatchState(const TMatchState& ms)
    : mNumberOfConditions(ms.mNumberOfConditions)
    , mNextCondition(ms.mNextCondition)
    , mLineCount(ms.mLineCount)
    , mDelta(ms.mDelta)
    , mSpacer(ms.mSpacer)
    {
    }

    int nextCondition() { return mNextCondition; }
    void conditionMatched() { mNextCondition++; }
    bool isComplete() { return (mNextCondition >= mNumberOfConditions); }
    void newLineArrived() { mLineCount++; }
    bool newLine() { return !(mLineCount > mDelta); }

    bool lineSpacerMatch(int lines)
    {
        if (mSpacer >= lines) {
            mSpacer = 0;
            return true;
        }
        ++mSpacer;
        return false;
    }

    std::list<std::list<std::string>> multiCaptureList;
    std::list<std::list<int>> multiCapturePosList;
    QVector<NameGroupMatches> nameCaptures;
    int mNumberOfConditions = 0;
    // first condition was true when the state was created
    int mNextCondition = 1;
    int mLineCount = 1;
    int mDelta = 0;
    int mSpacer = 0;
};

#endif // MUDLET_TMATCHSTATE_H
