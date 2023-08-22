#pragma once

#include <vector>
#include <string>

#include <SoundEffect.h>
#include <SoundStream.h>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    SoundEffect* LoadSoundEffect(const std::string& path);
    void PlaySoundEffect(SoundEffect* soundEffect, int loops = 0) const;
    void StopAllSoundEffects() const;

    SoundStream* LoadSoundStream(const std::string& path);
    void PlaySoundStream(bool repeat = false) const;
    void StopSoundStream() const;
    void PauseSoundStream() const;
    void ResumeSoundStream() const;
    int GetSoundStreamVolume() const;
    bool IsSoundStreamPlaying() const;


    void SetSoundVolume(int value) const;

private:
    std::vector<SoundEffect*> m_soundEffects;
    SoundStream* m_soundStream;
};

