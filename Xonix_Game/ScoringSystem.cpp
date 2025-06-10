#include "ScoringSystem.h"

// Static power-up thresholds
const int ScoringSystem::powerUpThresholds[] = { 50, 70, 100, 130, 160, 190, 220, 250, 280, 310 };
const int ScoringSystem::thresholdCount = sizeof(ScoringSystem::powerUpThresholds) / sizeof(ScoringSystem::powerUpThresholds[0]);

ScoringSystem::ScoringSystem()
    : totalPoints(0), bonusCounter(0), bonusThreshold(10), powerUps(0), tilesCaptured(0) {
}

void ScoringSystem::tileCaptured(int areaCaptured)
{
    tilesCaptured += areaCaptured;

    int pointsGained = 0;

    if (areaCaptured >= bonusThreshold)
    {
        if (bonusCounter < 100)
            ++bonusCounter;

        if (bonusCounter >= 5)
            pointsGained = areaCaptured * 4;
        else
            pointsGained = areaCaptured * 2;

        if (bonusCounter == 3)
            bonusThreshold = 5; // Shorten threshold after a few bonuses
    }
    else
    {
        pointsGained = areaCaptured;
    }

    totalPoints += pointsGained;

    // Grant power-up if threshold is reached
    if (powerUps < thresholdCount && totalPoints >= powerUpThresholds[powerUps])
        ++powerUps;
}

int ScoringSystem::getScore() const {
    return totalPoints;
}

int ScoringSystem::getPowerUps() const {
    return powerUps;
}

int ScoringSystem::getTilesCaptured() const {
    return tilesCaptured;
}

void ScoringSystem::reset()
{
    totalPoints = 0;
    bonusCounter = 0;
    bonusThreshold = 0;
    powerUps = 0;
    tilesCaptured = 0;
}
