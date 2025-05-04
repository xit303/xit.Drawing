#include <Drawing/Theme/BrushVisualStateGroup.h>

namespace xit::Drawing
{
    std::map<std::string, BrushVisualStateGroup *> BrushVisualStateGroup::loadedGroups;

    BrushVisualStateGroup::BrushVisualStateGroup() {}
    BrushVisualStateGroup::BrushVisualStateGroup(const std::string &name) : VisualStateGroup(name) {}
    BrushVisualStateGroup::BrushVisualStateGroup(BrushVisualStateGroup &other) : VisualStateGroup(other)
    {
        for (BrushVisualState *state : other.visualStates)
        {
            AddState(new BrushVisualState(*state));
        }
    }

    BrushVisualStateGroup::BrushVisualStateGroup(const BrushVisualStateGroup &other) : VisualStateGroup(other)
    {
        for (const BrushVisualState *state : other.visualStates)
        {
            AddState(new BrushVisualState(*state));
        }
    }

    BrushVisualStateGroup *BrushVisualStateGroup::Load(const std::string &path, const std::string &name, bool isSystemDirectory)
    {
        const std::string fileName = path + "/" + name + ".json";

        if (loadedGroups.contains(fileName))
            return loadedGroups[fileName];

        BrushVisualStateGroup *data = loadedGroups[fileName];
        // XmlFile *xmlFile = XmlFile::Load(fileName);

        // // std::string text = File::ReadAllText(fileName);

        // BrushVisualStateGroup *data = nullptr;

        // if (xmlFile &&
        //     xmlFile->Root.Elements.size() == 1 &&
        //     (xmlFile->Root.Name == "BrushVisualStateGroup"))
        // {
        //     XmlElement *element = xmlFile->Root.Elements[0];

        //     std::list<XmlElement> brushSettingsGroups = element->FindAll("BrushSettingsGroup");

        //     if (brushSettingsGroups.size() > 0)
        //     {
        //         data = new BrushVisualStateGroup();
        //         data->SetName(name);

        //         for (XmlElement brushSettingsGroupElement : brushSettingsGroups)
        //         {
        //             std::string brushGroupName;
        //             XmlAttribute *attribute = brushSettingsGroupElement.FindAttribute("Name");
        //             if (attribute)
        //                 brushGroupName = attribute->Value;

        //             std::list<XmlElement> brushSettingsElements = brushSettingsGroupElement.FindAll("BrushSetting");

        //             if (brushSettingsElements.size() > 0)
        //             {
        //                 BrushVisualState *brushVisualState = new BrushVisualState();
        //                 brushVisualState->SetName(brushGroupName);

        //                 for (XmlElement *brushSetting : *brushSettingsElements)
        //                 {
        //                     std::string brushSettingName;
        //                     XmlAttribute *attribute = brushSetting->FindAttribute("Name");
        //                     if (attribute)
        //                         brushSettingName = attribute->Value;

        //                     XmlElement *valueElement = brushSetting->Find("Value");

        //                     if (valueElement)
        //                     {
        //                         std::string brushType;
        //                         std::string opacityString;
        //                         std::string colorString;
        //                         std::string fileNameString;
        //                         std::string stretchString;

        //                         for (XmlAttribute *attribute : valueElement->Attributes)
        //                         {
        //                             if (attribute->Name == "xsi:type")
        //                             {
        //                                 brushType = attribute->Value;
        //                             }
        //                             else if (attribute->Name == "Opacity")
        //                             {
        //                                 opacityString = attribute->Value;
        //                             }
        //                             else if (attribute->Name == "Color")
        //                             {
        //                                 colorString = attribute->Value;
        //                             }
        //                             else if (attribute->Name == "FileName")
        //                             {
        //                                 fileNameString = attribute->Value;
        //                             }
        //                             else if (attribute->Name == "Stretch")
        //                             {
        //                                 stretchString = attribute->Value;
        //                             }
        //                         }

        //                         BrushBase *brushBase = nullptr;

        //                         if (brushType == "SolidColorBrush")
        //                         {
        //                             SolidColorBrush *solidColorBrush = new SolidColorBrush();

        //                             if (!colorString.empty())
        //                             {
        //                                 solidColorBrush->Argb(colorString);
        //                             }

        //                             brushBase = solidColorBrush;
        //                         }
        //                         else if (brushType == "LinearGradientBrush")
        //                         {
        //                             LinearGradientBrush *linearGradientBrush = new LinearGradientBrush();

        //                             XmlElement *angleElement = valueElement->Find("Angle");
        //                             if (angleElement)
        //                             {
        //                                 double value = atof(angleElement->Value->c_str());
        //                                 if (errno != EINVAL)
        //                                     linearGradientBrush->SetAngle(value);
        //                             }

        //                             std::list<XmlElement> *gradientStops = valueElement->FindAll("GradientStop");

        //                             for (XmlElement *gradientStopElement : *gradientStops)
        //                             {
        //                                 GradientStop *gradientStop = new GradientStop();

        //                                 for (XmlAttribute *attribute : gradientStopElement->Attributes)
        //                                 {
        //                                     if (attribute->Name == "Color")
        //                                     {
        //                                         gradientStop->Argb(attribute->Value);
        //                                     }
        //                                     else if (attribute->Name == "Offset")
        //                                     {
        //                                         double value = atof(attribute->Value->c_str());
        //                                         if (errno != EINVAL)
        //                                             gradientStop->SetOffset((float)value);
        //                                     }
        //                                 }

        //                                 linearGradientBrush->GradientStops().AddChild(gradientStop);
        //                             }

        //                             brushBase = linearGradientBrush;
        //                         }
        //                         else if (brushType == "ImageBrush")
        //                         {
        //                             ImageBrush *imageBrush = new ImageBrush(fileNameString);
        //                             if (!stretchString.empty())
        //                             {
        //                                 imageBrush->SetStretch(StretchHelper::FromString(stretchString));
        //                             }

        //                             brushBase = imageBrush;
        //                         }
        //                         else
        //                         {
        //                             throw InvalidDataException();
        //                         }

        //                         if (brushBase)
        //                         {
        //                             if (!opacityString.empty())
        //                             {
        //                                 double opacity = atof(opacityString.c_str());
        //                                 if (errno != EINVAL)
        //                                     brushBase->SetOpacity(opacity);
        //                             }
        //                         }

        //                         if (brushSettingName == "Background")
        //                         {
        //                             if (isSystemDirectory)
        //                                 brushVisualState->Background.SetDefaultValue(brushBase);
        //                             else
        //                                 brushVisualState->Background.SetLoadedValue(brushBase);
        //                         }
        //                         else if (brushSettingName == "Foreground")
        //                         {
        //                             if (isSystemDirectory)
        //                                 brushVisualState->Foreground.SetDefaultValue(brushBase);
        //                             else
        //                                 brushVisualState->Foreground.SetLoadedValue(brushBase);
        //                         }
        //                         else
        //                         {
        //                             if (isSystemDirectory)
        //                                 brushVisualState->BorderBrush.SetDefaultValue(brushBase);
        //                             else
        //                                 brushVisualState->BorderBrush.SetLoadedValue(brushBase);
        //                         }
        //                     }
        //                 }
        //                 data->AddChild(brushVisualState);
        //             }
        //         }
        //     }

        //     // data->IsSerialized = true;

        //     /*foreach (BrushSettingsGroup visualState in data.Values)
        //     {
        //         visualState.IsSerialized = true;
        //     }*/

        //     Logger::Log(LogLevel::Info, "BrushVisualStateGroup", "Loaded BrushVisualStateGroup " + name + " from " + path);
        // }
        // else
        // {
        //     data = new BrushVisualStateGroup(name);
        //     Logger::Log(LogLevel::Info, "BrushVisualStateGroup", "BrushVisualStateGroup " + name + " did not exist and has been created");
        // }

        // if (data)
        //     data->SetFileName(fileName);

        return data;
    }
}