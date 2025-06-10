#pragma once
class ScoringSystem {
private:
    int totalPoints;
    int bonusCounter;
    int bonusThreshold;
    int powerUps;
    int tilesCaptured;

    static const int powerUpThresholds[];
    static const int thresholdCount;

public:
    ScoringSystem();
    void tileCaptured(int areaCaptured);
    int getScore() const;
    int getPowerUps() const;
    int getTilesCaptured() const;
    void reset();
};
