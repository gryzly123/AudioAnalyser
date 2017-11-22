#pragma once
#include "PCH.h"
#include "AudioProcessor.h"
#include "DspPlugin.h"

#define CURRENT_VER "0.0.2"

namespace AudioAnalyser
{
	using namespace System;
	using namespace System::Xml;
	using namespace System::Windows::Forms;

	public ref class FileSerializer
	{
	public:

		static System::Void SerializeRack(XmlTextWriter^ DW)
		{
			AudioProcessor* Ap = AudioProcessor::GetInstance();
			DW->Formatting = Formatting::Indented;
			DW->Indentation = 4;

			DW->WriteStartDocument();
			DW->WriteStartElement(L"AudioAnalyser");
			DW->WriteAttributeString(L"version", CURRENT_VER);

			DW->WriteStartElement(L"RackItems");
			DW->WriteAttributeString(L"count", GUI_RACKITEMS_COUNT.ToString());

			for (int i = 0; i < GUI_RACKITEMS_COUNT; i++)
			{
				DW->WriteStartElement(L"RackItem");
				DW->WriteAttributeString(L"name", ToClr(Ap->GetPluginName(i)));
				DW->WriteAttributeString(L"bypassed", Ap->IsPluginBypassed(i).ToString());
				DW->WriteAttributeString(L"drywetmix", Ap->GetPluginVolumeMix(i).ToString());

				std::vector<DspPluginParameter*> Parameters = Ap->GetPluginParameters(i);
				int ParametersCount = Parameters.size();
				for (int j = 0; j < ParametersCount; j++)
				{
					DW->WriteStartElement(L"Parameter");
					DW->WriteAttributeString(L"name", ToClr(Parameters[j]->Name));
					DW->WriteAttributeString(L"value", Parameters[j]->CurrentValue.ToString());
					DW->WriteEndElement();
				}

				DW->WriteEndElement();
			}

			DW->WriteEndElement();
			DW->WriteEndElement();
			DW->WriteEndDocument();
			DW->Close();
		}

		static System::Void DeserializeRack(XmlTextReader^ DR)
		{
			AudioProcessor* Ap = AudioProcessor::GetInstance();
			DR->WhitespaceHandling = WhitespaceHandling::None;
			//DR->MoveToContent();
			
			int CurrentRackItem = -1;

			while (DR->Read())
			{
				if (DR->NodeType != XmlNodeType::Element) continue;

				if (DR->LocalName->Equals(L"AudioAnalyser"))
				{
					bool VersionCheckPass = DeserializeRackHelperAudioAnalyser(DR);
				}
				else if (DR->LocalName->Equals(L"RackItem"))
				{
					++CurrentRackItem;
					if (CurrentRackItem > GUI_RACKITEMS_COUNT) continue;
					DeserializeRackHelperRackItem(DR, CurrentRackItem);
				}
				else if (DR->LocalName->Equals(L"Parameter"))
				{
					Ap->UpdatePluginParameterByName(
						CurrentRackItem,
						Utilities::WideFromSystemString(DR->GetAttribute(L"name")),
						Single::Parse(DR->GetAttribute(L"value")));
				}
			}
			{/*
				DW->WriteStartDocument();
				DW->WriteStartElement(L"Audio Analyser");
				DW->WriteAttributeString(L"version", L"0.0.1");

				DW->WriteStartElement(L"RackItems");
				DW->WriteAttributeString(L"count", GUI_RACKITEMS_COUNT.ToString());

				for (int i = 0; i < GUI_RACKITEMS_COUNT; i++)
				{
					DW->WriteStartElement(L"RackItem");
					DW->WriteAttributeString(L"name", ToClr(Ap->GetPluginName(i)));
					DW->WriteAttributeString(L"bypassed", Ap->IsPluginBypassed(i).ToString());
					DW->WriteAttributeString(L"drywetmix", Ap->GetPluginVolumeMix(i).ToString());

					std::vector<DspPluginParameter*> Parameters = Ap->GetPluginParameters(i);
					int ParametersCount = Parameters.size();
					for (int j = 0; j < ParametersCount; j++)
					{
						DW->WriteStartElement(L"Parameter");
						DW->WriteAttributeString(L"name", ToClr(Parameters[j]->Name));
						DW->WriteAttributeString(L"value", Parameters[j]->CurrentValue.ToString());
						DW->WriteEndElement();
					}

					DW->WriteEndElement();
				}

				DW->WriteEndElement();
				DW->WriteEndElement();
				DW->WriteEndDocument();
				DW->Close();
			*/}
		}

	private:

		static System::Boolean DeserializeRackHelperAudioAnalyser(XmlTextReader^ DR)
		{
			bool HasVerifiedVersion = false;
			DR->MoveToFirstAttribute();
			for (int i = 0; i < DR->AttributeCount; ++i)
			{
				if(i) DR->MoveToNextAttribute();
				if (!DR->Name->Equals(L"version")) continue;

				HasVerifiedVersion = true;

				if (!DR->Value->Equals(CURRENT_VER))
				{
					DialogResult Result = MessageBox::Show(
						L"There is a version mismatch between the app and the project file. Do you want to continue reading?",
						L"Version mismatch",
						MessageBoxButtons::YesNo);

					if (Result == DialogResult::No) return false;
				}
			}

			if (!HasVerifiedVersion)
			{
				DialogResult Result = MessageBox::Show(
					L"The data about the app version used to save this project was not found. Do you want to continue reading?",
					L"Missing data",
					MessageBoxButtons::YesNo);

				if (Result == DialogResult::No) return false;
			}

			return true;
		}

		static System::Void DeserializeRackHelperRackItem(XmlTextReader^ DR, int NewIndex)
		{
			AudioProcessor* Ap = AudioProcessor::GetInstance();
			Ap->ChangePlugin(NewIndex, Utilities::WideFromSystemString(DR->GetAttribute(L"name")));
			Ap->SetPluginBypassed(NewIndex, Boolean::Parse(DR->GetAttribute(L"bypassed")));
			Ap->SetPluginVolumeMix(NewIndex, Single::Parse(DR->GetAttribute(L"drywetmix")));
		}
	};
}