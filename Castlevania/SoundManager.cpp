#include "pch.h"
#include "SoundManager.h"
#include <iostream>


SoundManager::SoundManager() :
m_soundStream{nullptr}
{
    // Initialize the audio system
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
}

SoundManager::~SoundManager()
{
    // Clean up the audio system
    Mix_CloseAudio();

    for (size_t i = 0; i < m_soundEffects.size(); ++i)
    {
        delete m_soundEffects[i];
    }
    delete m_soundStream;
}

// SoundEffect management
SoundEffect* SoundManager::LoadSoundEffect(const std::string& path)
{
    SoundEffect* soundEffect = new SoundEffect(path);
    if (soundEffect->IsLoaded())
    {
        m_soundEffects.push_back(soundEffect);
        return soundEffect;
    }

    delete soundEffect;
    return nullptr;
}

void SoundManager::PlaySoundEffect(SoundEffect* soundEffect, const int loops) const
{
    if (soundEffect != nullptr)
    {
        soundEffect->Play(loops);
    }
}

void SoundManager::StopAllSoundEffects() const
{
    for (auto soundEffect : m_soundEffects)
    {
        soundEffect->StopAll();
    }
}


// SoundStream management
SoundStream* SoundManager::LoadSoundStream(const std::string& path)
{
    SoundStream* soundStream = new SoundStream(path);
    if (soundStream->IsLoaded())
    {
        m_soundStream = soundStream;
        return soundStream;
    }

    delete soundStream;
    return nullptr;
}

void SoundManager::PlaySoundStream(bool repeat) const
{
    if (m_soundStream != nullptr)
    {
        m_soundStream->Play(repeat);
    }
}

void SoundManager::StopSoundStream() const
{
    if (m_soundStream != nullptr)
    {
        m_soundStream->Stop();
    }
}

void SoundManager::PauseSoundStream() const
{
    if (m_soundStream != nullptr)
    {
        m_soundStream->Pause();
    }
}

void SoundManager::ResumeSoundStream() const
{
    if (m_soundStream != nullptr)
    {
        m_soundStream->Resume();
    }
}

int SoundManager::GetSoundStreamVolume() const
{
    if (m_soundStream != nullptr)
    {
        return m_soundStream->GetVolume();
    }
    else
    {
        return 0;
    }
}

bool SoundManager::IsSoundStreamPlaying() const
{
    if (m_soundStream != nullptr)
    {
        return m_soundStream->IsPlaying();
    }
    else
    {
        return false;
    }
}

// set volume all
void SoundManager::SetSoundVolume(int value) const
{
    for (auto soundEffect : m_soundEffects)
    {
        soundEffect->SetVolume(value);
    }

    if (m_soundStream != nullptr)
    {
        m_soundStream->SetVolume(value);
    }

}