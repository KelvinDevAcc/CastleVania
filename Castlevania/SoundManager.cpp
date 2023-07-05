#include "pch.h"
#include "SoundManager.h"
#include <iostream>


    SoundManager::SoundManager()
    {
        // Initialize the audio system
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    }

    SoundManager::~SoundManager()
    {
        // Clean up the audio system
        Mix_CloseAudio();
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
        else
        {
            delete soundEffect;
            return nullptr;
        }
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

    int SoundManager::GetSoundEfferctVolume() const
    {
        for (auto soundEffect : m_soundEffects)
        {
           return soundEffect->GetVolume();
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
        else
        {
            delete soundStream;
            return nullptr;
        }
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
            std::cout << soundEffect->GetVolume();
        }

        if (m_soundStream != nullptr)
        {
            m_soundStream->SetVolume(value);
        }

    }