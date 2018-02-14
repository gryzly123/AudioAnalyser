#pragma once
#include "PCH.h"
#include "AudioProcessor.h"
#include "DspPluginParameter.h"

#define CURRENT_VER "1.0.0"

namespace AudioAnalyser
{
	using namespace System;
	using namespace System::Xml;
	using namespace System::Windows::Forms;

	//Odczyt i zapis plików XML z informacjami o projekcie (.aap)
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
				DW->WriteAttributeString(L"name", Utilities::SystemStringFromWide(Ap->GetPluginName(i)));
				DW->WriteAttributeString(L"bypassed", Ap->IsPluginBypassed(i).ToString());
				DW->WriteAttributeString(L"drywetmix", Ap->GetPluginVolumeMix(i).ToString());

				std::vector<DspPluginParameter*> Parameters = Ap->GetPluginParameters(i);
				int ParametersCount = Parameters.size();
				for (int j = 0; j < ParametersCount; j++)
				{
					DW->WriteStartElement(L"Parameter");
					DW->WriteAttributeString(L"name", Utilities::SystemStringFromWide(Parameters[j]->Name));
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
			bool Success = false;
			
			int CurrentRackItem = -1;
			try
			{
				while (DR->Read())
				{
					if (DR->NodeType != XmlNodeType::Element) continue;

					if (DR->LocalName->Equals(L"AudioAnalyser"))
					{
						bool VersionCheckPass = DeserializeRackHelperAudioAnalyser(DR);
						if (!VersionCheckPass) return;
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

				Success = true;
			}
			catch (System::Exception^) { }
			
			if(!Success) MessageBox::Show(L"File seems to be corrupted and could not be fully loaded.", L"Open failed");
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

					return (Result == DialogResult::Yes);
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