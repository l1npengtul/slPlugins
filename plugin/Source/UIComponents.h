/*
  ==============================================================================

    UIComponents.h
    Created: 5 Jul 2019 11:45:25am
    Author:  Roland Rabien

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"

//==============================================================================
class HSelect : public gin::Select
{
public:
    HSelect (gin::Parameter* p) : gin::Select (p) {}

    void resized() override
    {
        juce::Rectangle<int> r = getLocalBounds().reduced (4);

        name.setBounds (r.removeFromLeft (90));
        comboBox.setBounds (r.reduced (2));
    }
};
//==============================================================================

class LockComponent : public gin::PluginButton
{
public:
    LockComponent (gin::Parameter* p)
        : PluginButton (p)
    {
        static const unsigned char pathData[] = { 110,109,0,0,32,68,0,0,64,68,108,0,0,144,68,0,0,64,68,108,0,0,144,68,0,0,16,68,113,0,0,144,68,0,0,235,67,0,160,134,68,0,128,197,67,113,0,128,122,68,0,0,160,67,0,0,96,68,0,0,160,67,113,0,128,69,68,0,0,160,67,0,192,50,68,0,128,197,67,113,0,0,32,68,0,0,235,
            67,0,0,32,68,0,0,16,68,108,0,0,32,68,0,0,64,68,99,109,0,0,184,68,0,0,88,68,108,0,0,184,68,0,0,180,68,113,0,0,184,68,0,0,185,68,0,128,180,68,0,128,188,68,113,0,0,177,68,0,0,192,68,0,0,172,68,0,0,192,68,108,0,0,208,67,0,0,192,68,113,0,0,188,67,0,0,192,
            68,0,0,174,67,0,128,188,68,113,0,0,160,67,0,0,185,68,0,0,160,67,0,0,180,68,108,0,0,160,67,0,0,88,68,113,0,0,160,67,0,0,78,68,0,0,174,67,0,0,71,68,113,0,0,188,67,0,0,64,68,0,0,208,67,0,0,64,68,108,0,0,224,67,0,0,64,68,108,0,0,224,67,0,0,16,68,113,0,0,
            224,67,0,0,196,67,0,0,17,68,0,0,130,67,113,0,0,50,68,0,0,0,67,0,0,96,68,0,0,0,67,113,0,0,135,68,0,0,0,67,0,128,151,68,0,0,130,67,113,0,0,168,68,0,0,196,67,0,0,168,68,0,0,16,68,108,0,0,168,68,0,0,64,68,108,0,0,172,68,0,0,64,68,113,0,0,177,68,0,0,64,68,
            0,128,180,68,0,0,71,68,113,0,0,184,68,0,0,78,68,0,0,184,68,0,0,88,68,99,101,0,0 };

        path.loadPathFromData (pathData, sizeof (pathData));

        setTooltip ("Lock parameter during mutation");
    }

private:
    void paint (juce::Graphics& g) override
    {
        bool on = parameter->getUserValue() > 0.0f;
        auto rc = getLocalBounds().toFloat();

        g.setColour (findColour (gin::PluginLookAndFeel::grey90ColourId).withAlpha (on ? 0.8f : 0.3f));
        g.fillPath (path, path.getTransformToScaleToFit (rc.reduced (2), true));
    }

    juce::Path path;
};

//==============================================================================
class MenuButton : public juce::TextButton
{
public:
    MenuButton()
    {
        static const unsigned char pathData[] = { 110,109,0,0,208,68,0,0,168,68,108,0,0,208,68,0,0,184,68,113,0,0,208,68,0,64,187,68,0,160,205,68,0,160,189,68,113,0,64,203,68,0,0,192,68,0,0,200,68,0,0,192,68,108,0,0,64,67,0,0,192,68,113,0,0,38,67,0,0,192,68,0,0,19,67,0,160,189,68,113,0,0,0,67,0,64,187,
            68,0,0,0,67,0,0,184,68,108,0,0,0,67,0,0,168,68,113,0,0,0,67,0,192,164,68,0,0,19,67,0,96,162,68,113,0,0,38,67,0,0,160,68,0,0,64,67,0,0,160,68,108,0,0,200,68,0,0,160,68,113,0,64,203,68,0,0,160,68,0,160,205,68,0,96,162,68,113,0,0,208,68,0,192,164,68,0,0,
            208,68,0,0,168,68,99,109,0,0,208,68,0,0,80,68,108,0,0,208,68,0,0,112,68,113,0,0,208,68,0,128,118,68,0,160,205,68,0,64,123,68,113,0,64,203,68,0,0,128,68,0,0,200,68,0,0,128,68,108,0,0,64,67,0,0,128,68,113,0,0,38,67,0,0,128,68,0,0,19,67,0,64,123,68,113,
            0,0,0,67,0,128,118,68,0,0,0,67,0,0,112,68,108,0,0,0,67,0,0,80,68,113,0,0,0,67,0,128,73,68,0,0,19,67,0,192,68,68,113,0,0,38,67,0,0,64,68,0,0,64,67,0,0,64,68,108,0,0,200,68,0,0,64,68,113,0,64,203,68,0,0,64,68,0,160,205,68,0,192,68,68,113,0,0,208,68,0,128,
            73,68,0,0,208,68,0,0,80,68,99,109,0,0,208,68,0,0,160,67,108,0,0,208,68,0,0,224,67,113,0,0,208,68,0,0,237,67,0,160,205,68,0,128,246,67,113,0,64,203,68,0,0,0,68,0,0,200,68,0,0,0,68,108,0,0,64,67,0,0,0,68,113,0,0,38,67,0,0,0,68,0,0,19,67,0,128,246,67,113,
            0,0,0,67,0,0,237,67,0,0,0,67,0,0,224,67,108,0,0,0,67,0,0,160,67,113,0,0,0,67,0,0,147,67,0,0,19,67,0,128,137,67,113,0,0,38,67,0,0,128,67,0,0,64,67,0,0,128,67,108,0,0,200,68,0,0,128,67,113,0,64,203,68,0,0,128,67,0,160,205,68,0,128,137,67,113,0,0,208,68,
            0,0,147,67,0,0,208,68,0,0,160,67,99,101,0,0 };

        path.loadPathFromData (pathData, sizeof (pathData));
    }

private:
    void paint (juce::Graphics& g) override
    {
        auto rc = getLocalBounds().toFloat();

        g.setColour (findColour (gin::PluginLookAndFeel::grey90ColourId));
        g.fillPath (path, path.getTransformToScaleToFit (rc.reduced (2), true));
    }

    juce::Path path;
};

//==============================================================================
class PadComponent : public juce::Component,
private juce::Timer
{
public:
    PadComponent (SFXAudioProcessor& pc, Pad& p)
        : processor (pc), pad (p)
    {
        startTimerHz (30);
        setRepaintsOnMouseActivity (true);
    }

    std::function<void ()> onDown, onUp;

private:
    void timerCallback() override
    {
        bool newBright = processor.isMidiNoteDown (pad.note);
        if (newBright != bright || lastCurrentPad != processor.getCurrentPad())
        {
            lastCurrentPad = processor.getCurrentPad();
            bright = newBright;
            repaint();
        }
    }

    void mouseDown (const juce::MouseEvent&) override
    {
        if (onDown)
            onDown();
    }

    void mouseUp (const juce::MouseEvent&) override
    {
        if (onUp)
            onUp();
    }

    void paint (juce::Graphics& g) override
    {
        auto rc = getLocalBounds().reduced (4);

        if (processor.getCurrentPad() == pad.index)
        {
            g.setColour (findColour (gin::PluginLookAndFeel::grey90ColourId).withAlpha (0.25f));
            g.fillRect (rc);
        }

        if (isMouseOver())
        {
            g.setColour (findColour (gin::PluginLookAndFeel::grey90ColourId).withAlpha (0.2f));
            g.fillRect (rc);
        }

        if (bright)
        {
            g.setColour (findColour (gin::PluginLookAndFeel::grey90ColourId).withAlpha (0.3f));
            g.fillRect (rc);
        }

        g.setColour (findColour (gin::PluginLookAndFeel::grey90ColourId));
        g.drawRect (rc);

        rc = rc.reduced (2);

        g.drawText (pad.name, rc, juce::Justification::centredBottom);
    }

    SFXAudioProcessor& processor;
    Pad& pad;
    int lastCurrentPad = -1;

    bool bright = false;
};

//==============================================================================
class PadGridComponent : public juce::Component
{
public:
    PadGridComponent (SFXAudioProcessor& pr)
        : processor (pr)
    {
        for (auto p : processor.getPads())
        {
            auto pc = new PadComponent (processor, *p);
            addAndMakeVisible (pc);
            pads.add (pc);
        }

        listener.onValueTreePropertyChanged = [this] (const juce::ValueTree&, const juce::Identifier& i)
        {
            if (i.toString().startsWith ("name"))
                repaint();
        };
    }

    const juce::OwnedArray<PadComponent>& getPads() { return pads; }

private:
    void resized() override
    {
        auto rc = getLocalBounds();

        int w = getWidth() / 4;
        int h = getHeight() / 4;

        for (int y = 0; y < 4; y++)
        {
            auto row = rc.removeFromTop (h);
            for (int x = 0; x < 4; x++)
            {
                pads[y * 4 + x]->setBounds (row.removeFromLeft (w));
            }
        }
    }

    SFXAudioProcessor& processor;

    juce::OwnedArray<PadComponent> pads;
    gin::AsyncLambdaValueTreeListener listener {processor.state};
};

//==============================================================================
class ParamPageComponent : public juce::Component
{
public:
    ParamPageComponent (SFXAudioProcessor& pr, Pad& p)
        : processor (pr), pad (p)
    {
        addAndMakeVisible (name);
        addAndMakeVisible (note);
        addAndMakeVisible (menu);

        addAndMakeVisible (coin);
        addAndMakeVisible (laser);
        addAndMakeVisible (explosion);
        addAndMakeVisible (powerup);
        addAndMakeVisible (hit);
        addAndMakeVisible (jump);
        addAndMakeVisible (blip);
        addAndMakeVisible (random);
        addAndMakeVisible (mutate);

        name.setText (pad.name, juce::dontSendNotification);
        name.onTextChange = [this]
        {
            pad.name = name.getText();
        };

        note.setText (juce::String (pad.note), juce::dontSendNotification);
        note.onTextChange = [this]
        {
            pad.note = juce::jlimit (0, 127, note.getText().getIntValue());
        };

        listener.onValueTreePropertyChanged = [this] (const juce::ValueTree&, const juce::Identifier& i)
        {
            if (i.toString() == juce::String ("name") + juce::String (pad.index))
            {
                if (pad.name != name.getText())
                    name.setText (pad.name, juce::dontSendNotification);
            }
            if (i.toString() == juce::String ("note") + juce::String (pad.index))
            {
                note.setText (juce::String (pad.note), juce::dontSendNotification);
            }
        };

        menu.onClick = [this]
        {
            showMenu();
        };
        coin.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generatePickupCoin();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Coin");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        laser.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generateLaserShoot();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Laser");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        explosion.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generateExplosion();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Explosion");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        powerup.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generatePowerup();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Powerup");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        hit.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generateHitHurt();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Hit");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        jump.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generateJump();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Jump");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        blip.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.generateBlipSelect();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Blip");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        random.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.randomize();
            pad.toPluginParams();
            pad.name = processor.uniqueName ("Random");
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };
        mutate.onClick = [this]
        {
            pad.fromPluginParams();
            pad.params.mutate();
            pad.toPluginParams();
            processor.midiNoteOn (pad.note);
            processor.midiNoteOff (pad.note);
        };

        int i = 0;
        for (auto pp : pad.pluginParams)
        {
            gin::ParamComponent* pc = nullptr;
            if (pp->getUid().startsWith ("wave"))
                pc = new HSelect (pp);
            else
                pc = new gin::HorizontalFader (pp, false);

            pc->setTooltip (pad.params.getDescription (pad.params.getParams()[size_t (i)]));
            addAndMakeVisible (pc);
            controls.add (pc);

            i++;
        }

        for (auto lp : pad.pluginLockParams)
        {
            auto pc = new LockComponent (lp);
            addAndMakeVisible (pc);
            locks.add (pc);
        }
    }

private:
    void parentHierarchyChanged() override
    {
        if (getLookAndFeel().isColourSpecified (gin::PluginLookAndFeel::grey90ColourId))
        {
            name.applyColourToAllText (findColour (gin::PluginLookAndFeel::grey90ColourId, true));
            note.applyColourToAllText (findColour (gin::PluginLookAndFeel::grey90ColourId, true));
        }
    }

    void resized() override
    {
        auto r = getLocalBounds();

        // top
        {
            auto rc = r.removeFromTop (30);
            name.setBounds (juce::Rectangle<int> (rc).withSizeKeepingCentre (150, 20));
            menu.setBounds (rc.removeFromLeft (20).reduced (0, 5));
            note.setBounds (rc.removeFromRight (40).reduced (0, 5));
            r.removeFromTop (10);
        }

        // faders
        auto rc1 = r;
        auto rc2 = rc1.removeFromRight (rc1.getWidth() / 2);
        auto h = (rc1.getHeight() - 25) / (controls.size() / 2);

        int i = 0;
        for (auto c : controls)
        {
            auto rc = (i < controls.size() / 2) ? rc1.removeFromTop (h) : rc2.removeFromTop (h);
            locks[i]->setBounds (rc.removeFromLeft (rc.getHeight()));
            c->setBounds (rc);

            i++;
        }

        // bottom
        {
            auto rc = getLocalBounds().withTrimmedBottom (4).removeFromBottom (20);
            int w = (rc.getWidth() - 7 * 4) / 9;

            coin.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            laser.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            explosion.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            powerup.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            hit.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            jump.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            blip.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            random.setBounds (rc.removeFromLeft (w));
            rc.removeFromLeft (4);
            mutate.setBounds (rc.removeFromLeft (w));
        }
    }

    void showMenu()
    {
        juce::PopupMenu m;
        m.setLookAndFeel (&getLookAndFeel());

        m.addItem (juce::PopupMenu::Item ("MIDI Learn").setTicked (processor.getMidiLearn()).setAction ([this] { toggleMidiLearn(); }));
        m.addSeparator();
        m.addItem (juce::PopupMenu::Item ("Import Sound...").setAction ([this] { importSound(); }));
        m.addItem (juce::PopupMenu::Item ("Export Sound...").setAction ([this] { exportSound(); }));
        m.addItem (juce::PopupMenu::Item ("Export .WAV...").setAction ([this] { exportWav(); }));

        m.showMenuAsync ({}, {});
    }

    void toggleMidiLearn()
    {
        processor.setMidiLearn (! processor.getMidiLearn());
    }

    void importSound()
    {
        juce::FileChooser fc ("Load", {}, "*.sfx8sound");
        if (fc.browseForFileToOpen())
        {
            auto json = juce::JSON::parse (fc.getResult().loadFileAsString());
            if (auto obj = json.getDynamicObject())
            {
                for (auto nv : obj->getProperties())
                {
                    auto uid = nv.name.toString();
                    if (uid == "name")
                        pad.name = nv.value.toString();
                    else
                        pad.params.setParam (uid.toRawUTF8(), (float) nv.value);
                }
            }

            pad.toPluginParams();
        }
    }

    void exportSound()
    {
        juce::FileChooser fc ("Save", {}, "*.sfx8sound");
        if (fc.browseForFileToSave (true))
        {
            auto obj = new juce::DynamicObject();

            for (auto pid : pad.params.getParams())
                obj->setProperty (juce::String (pid.c_str()), pad.params.getParam (pid));
            obj->setProperty ("name", pad.name.get());

            auto text = juce::JSON::toString (juce::var (obj));
            fc.getResult().replaceWithText (text);
        }
    }

    void exportWav()
    {
        juce::FileChooser fc ("Save", {}, "*.wav");
        if (fc.browseForFileToSave (true))
        {
            SfxrSynth sfxr (44100.0f);
            pad.fromPluginParams();
            sfxr.setParams (pad.params);
            sfxr.reset (true);

            juce::AudioSampleBuffer buffer (1, 128);
            buffer.clear();

            if (auto os = fc.getResult().createOutputStream())
            {
                std::unique_ptr<juce::AudioFormatWriter> writer (juce::WavAudioFormat().createWriterFor (os.release(), 44100, 1, 16, {}, 0));

                if (writer != nullptr)
                {
                    while (! sfxr.synthWave (buffer.getWritePointer (0), 0, 128))
                    {
                        writer->writeFromAudioSampleBuffer (buffer, 0, 128);
                        buffer.clear();
                    }
                }
            }
        }
    }

    SFXAudioProcessor& processor;
    Pad& pad;
    gin::AsyncLambdaValueTreeListener listener {processor.state};

    MenuButton menu;
    juce::TextEditor name, note;
    juce::OwnedArray<gin::ParamComponent> controls;
    juce::OwnedArray<LockComponent> locks;

    juce::TextButton coin {"Coin"}, laser {"Laser"}, explosion {"Explosion"}, powerup {"Powerup"}, hit {"Hit"},
                     jump {"Jump"}, blip {"Blip"}, random {"Random"}, mutate {"Mutate"};
};

//==============================================================================
class ParamComponent : public juce::Component
{
public:
    ParamComponent (SFXAudioProcessor& pr)
        : processor (pr)
    {
        for (auto p : processor.getPads())
        {
            auto ppc = new ParamPageComponent (processor, *p);
            addChildComponent (ppc);

            pages.add (ppc);
        }

        setPage (processor.getCurrentPad());

        processor.onCurrentPageChanged = [this] ()
        {
            for (auto p : pages)
                p->setVisible (false);

            pages[processor.getCurrentPad()]->setVisible (true);
        };
    }

    ~ParamComponent() override
    {
        processor.onCurrentPageChanged = nullptr;
    }

    void setPage (int num)
    {
        for (auto p : pages)
            p->setVisible (false);

        pages[num]->setVisible (true);

        processor.setCurrentPad (num);
    }

private:
    void resized() override
    {
        for (auto p : pages)
            p->setBounds (getLocalBounds());
    }

    SFXAudioProcessor& processor;
    juce::OwnedArray<ParamPageComponent> pages;
};
