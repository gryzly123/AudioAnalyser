#include "PCH.h"
#include "DspPlugin.h"

PrecomputedSin* DspPlugin::PcSin = new PrecomputedSin(65536);
#define HAS_VIZ true
#define Val CurrentValue

NullPlugin::NullPlugin() : DspPlugin(L"(none)") { }
void NullPlugin::ProcessData(float* BufferL, float* BufferR, int Length) { }


SineWaveGenerator::SineWaveGenerator() : DspPlugin(L"Sine Wave")
{
	SineAmp.FloatValueStep = 0.01f;
	SineFrequency.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&SineAmp);
	ParameterRefsForUi.push_back(&SineFrequency);
	ParameterRefsForUi.push_back(&Retrigger);
	ParameterRefsForUi.push_back(&InvertPhase);
}

void SineWaveGenerator::ProcessData(float* BufferL, float* BufferR, int Length)
{
	if (LastFreq != SineFrequency.Val)
	{
		LastFreq = SineFrequency.Val;
		if (Retrigger.Val == 1.0f) SineStatus = 0.0f;
	}

	const float SineInc = SineFrequency.Val / 44100.f;

	for (int i = 0; i < Length; i++)
	{
		SineStatus += SineInc;
		if (SineStatus > 1) SineStatus -= 1;
		float Value = SineAmp.Val * PcSin->GetWithTau(SineStatus);
		BufferL[i] = Value;
		BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * Value : Value;
	}
}

SawWaveGenerator::SawWaveGenerator() : DspPlugin(L"Saw Wave")
{
	Amp.FloatValueStep = 0.01f;
	Frequency.FloatValueStep = 1.0f;
	EquationN.FloatValueStep = 1.0f;

	ParameterRefsForUi.push_back(&Amp);
	ParameterRefsForUi.push_back(&Frequency);
	ParameterRefsForUi.push_back(&Retrigger);
	ParameterRefsForUi.push_back(&InvertPhase);
	ParameterRefsForUi.push_back(&UseEquation);
	ParameterRefsForUi.push_back(&EquationN);
}

void SawWaveGenerator::ProcessData(float* BufferL, float* BufferR, int Length)
{
	TimeIncrementation = Frequency.Val / AUDIO_SAMPLERATE;

	for (int i = 0; i < Length; ++i)
	{
		TimeStatus += TimeIncrementation;
		if (TimeStatus > 1.0f) TimeStatus -= 1.0f;

		if (UseEquation.Val > 0.0f)
		{
			TempValue = 0.0f;
			for (int k = 1; k <= EquationN.Val; ++k)
			{
				float T = PcSin->GetWithTau((float)k * TimeStatus) / (float)k;
				if (k % 2 != 0) T *= -1.0f;
				TempValue += T;
			}
			TempValue = (TempValue * 2.0f * Amp.Val / M_PI);
		}
		else TempValue = Amp.Val * (TimeStatus * 2.0f - 1.0f);

		BufferL[i] = TempValue;
		BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * TempValue : TempValue;
	}
}

SquareWaveGenerator::SquareWaveGenerator() : DspPlugin(L"Square Wave")
{
	Amp.FloatValueStep = 0.01f;
	Frequency.FloatValueStep = 1.0f;
	EquationN.FloatValueStep = 1.0f;

	ParameterRefsForUi.push_back(&Amp);
	ParameterRefsForUi.push_back(&Frequency);
	ParameterRefsForUi.push_back(&Retrigger);
	ParameterRefsForUi.push_back(&InvertPhase);
	ParameterRefsForUi.push_back(&UseEquation);
	ParameterRefsForUi.push_back(&EquationN);
}

void SquareWaveGenerator::ProcessData(float* BufferL, float* BufferR, int Length)
{
	TimeIncrementation = Frequency.Val / AUDIO_SAMPLERATE;

	for (int i = 0; i < Length; ++i)
	{
		TimeStatus += TimeIncrementation;
		if (TimeStatus > 1.0f) TimeStatus -= 1.0f;

		if (UseEquation.Val > 0.0f)
		{
			TempValue = 0.0f;
			int DoubleN = (int)(EquationN.Val * 2.0f);
			for (int x = 1; x <= DoubleN; x += 2)
			{
				// x = (2k - 1)
				TempValue += PcSin->GetWithTau((float)x * TimeStatus) / (float)x;
			}
			TempValue = (TempValue * 4.0f * Amp.Val / M_PI);
		}
		else TempValue = Amp.Val * (TimeStatus >= 0.5f ? 1.0f : -1.0f);

		BufferL[i] = TempValue;
		BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * TempValue : TempValue;
	}
}

WhiteNoiseGenerator::WhiteNoiseGenerator() : DspPlugin(L"White Noise")
{
	Amp.FloatValueStep = 0.01f;
	EquationN.FloatValueStep = 1.0f;

	ParameterRefsForUi.push_back(&Amp);
	ParameterRefsForUi.push_back(&InvertPhase);
	ParameterRefsForUi.push_back(&EquationN);
	RNG = gcroot<Random^>(gcnew Random());
}

void WhiteNoiseGenerator::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; ++i)
	{
		for (int x = 0; x < EquationN.Val; ++x) TempValue += (Single)RNG->NextDouble();
		TempValue /= EquationN.Val;
		TempValue -= 0.5f;
		TempValue *= Amp.Val;

		BufferL[i] = TempValue;
		BufferR[i] = (InvertPhase.Val > 0.0f) ? -1.0f * TempValue : TempValue;
	}
}

Oscilloscope::Oscilloscope() : DspPlugin(L"Oscilloscope", HAS_VIZ)
{
	std::wstring* ChannelNames = new std::wstring[3];
	ChannelNames[0] = L"Left";
	ChannelNames[1] = L"Right";
	ChannelNames[2] = L"Mixdown";

	Channels.EnumNames = ChannelNames;

	ParameterRefsForUi.push_back(&Channels);
	ParameterRefsForUi.push_back(&CurveDuration);

	Data = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
	Interp = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
	DataPencil = gcroot<Pen^>(gcnew Pen(Color::Black, 1));
	DataBrush = gcroot<SolidBrush^>(gcnew SolidBrush(Color::Black));
	HelperPencil1 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
	HelperPencil2 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
	HelperPencil2->DashStyle = Drawing2D::DashStyle::Dot;
	TextL = gcroot<Font^>(gcnew Font("Microsoft Sans Serif", 8.0f, FontStyle::Regular));
	TextS = gcroot<Font^>(gcnew Font("Microsoft Sans Serif", 5.0f, FontStyle::Regular));
	FormatC = gcroot<StringFormat^>(gcnew StringFormat());
	FormatR = gcroot<StringFormat^>(gcnew StringFormat());
	TextColor = gcroot<Brush^>(gcnew SolidBrush(Color::Black));

	FormatC->Alignment = StringAlignment::Center;
	FormatR->Alignment = StringAlignment::Far;
}

void Oscilloscope::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int CurvePointsSize = (int)((float)AUDIO_SAMPLERATE * (float)CurveDuration.Val / 1000.0f);

	Data->Lock();
	switch ((int)Channels.Val)
	{
	case 0:
		for (int i = 0; i < Length; ++i) Data->PushLast(BufferL[i]);
		break;
	case 1:
		for (int i = 0; i < Length; ++i) Data->PushLast(BufferR[i]);
		break;
	case 2:
		for (int i = 0; i < Length; ++i) Data->PushLast((BufferL[i] + BufferR[i]) / 2.0f);
		break;
	}
	int ExcessData = Data->Size() - CurvePointsSize;
	while (--ExcessData > 0) Data->PopFirst();
	Data->Unlock();
}

void Oscilloscope::UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame)
{
	//Inicjalizacja parametrów rysunku
	const float Padding = 30.0f;
	const float Shift = 13.0f;
	const float LinePadding = 26.0f;
	const float WorkAreaHorizontal = Width - (2 * Padding);
	const float WorkAreaVertical = Height - (2 * Padding);
	const int MaxPoints = Width;
	const int RangeHalved = Height / 2;
	const float HelperLineCount = 10.0f;
	const float SingleHelperLengthMs = CurveDuration.Val / 10.0f;
	Font^ UsedStyle = (Width > 370) ? TextL : TextS;

	//Inicjalizacja rysuku
	Image->Clear(Color::White);

	//Osie
	Image->DrawLine(HelperPencil1, Padding + Shift, Padding - Shift, Padding + Shift, Height - Padding - Shift);
	Image->DrawLine(HelperPencil1, Padding + Shift, Height - Padding - Shift, Width - Padding + Shift, Height - Padding - Shift);

	//Linie pomocnicze i ich podpisy
	for (int i = 0; i < (int)HelperLineCount + 1; i++)
	{
		float HorizontalX = Padding + (WorkAreaHorizontal / HelperLineCount) * (float)i + Shift;
		float VerticalY = Padding + (WorkAreaVertical / HelperLineCount) * (float)i - Shift;

		Image->DrawLine(HelperPencil2,
			HorizontalX,
			Padding - Shift,
			HorizontalX,
			(float)Height - Padding - Shift);

		Image->DrawLine(HelperPencil2,
			Padding + Shift,
			VerticalY,
			(float)Width - Padding + Shift,
			VerticalY);

		Image->DrawString(
			(SingleHelperLengthMs * (i - 5)).ToString("N1"),
			UsedStyle,
			TextColor,
			HorizontalX,
			Height - Padding + 5 - Shift,
			FormatC);

		Image->DrawString(
			(1.0f - (i * 0.2f)).ToString("N1"),
			UsedStyle,
			TextColor,
			Padding - 3 + Shift,
			VerticalY - 6,
			FormatR);
	}

	//Podpisy osi poziomej i pionowej
	Image->DrawString(L"Time [ms]", UsedStyle, TextColor, (float)(Width / 2), (float)(Height - 20), FormatC);

	Drawing::Drawing2D::GraphicsState^ State = Image->Save();
	Image->RotateTransform(-90);
	Image->TranslateTransform(5, Height / 2 - Shift, Drawing2D::MatrixOrder::Append);
	Image->DrawString(L"Signal value", UsedStyle, TextColor, 0, 0, FormatC);
	Image->Restore(State);

	//Interpolacja danych, aby zmieœciæ x próbek w obrazie o szerokoœci y
	Data->Lock();
	Utilities::LinearInterpolate((MonitoredArray<float>^)Data, Interp, (int)WorkAreaHorizontal);
	Data->Unlock();

	//Rysowanie danych
	int PreviousPt = RangeHalved - (int)((Single)WorkAreaVertical / 2.0f * (Single)Interp->Get(0) - Shift) - (int)LinePadding;
	for (int i = 1; i < WorkAreaHorizontal; ++i)
	{
		int HorizontalVal = (int)(i + Padding) + (int)Shift;
		int NewPt = RangeHalved - (int)((Single)WorkAreaVertical / 2.0f * (Single)Interp->Get(i) - Shift) - (int)LinePadding;
		if (PreviousPt != NewPt) PreviousPt = (NewPt < PreviousPt) ? PreviousPt - 1 : PreviousPt + 1;

		if (PreviousPt == NewPt) Image->FillRectangle(DataBrush, HorizontalVal, PreviousPt, 1, 1);
		else                  Image->DrawLine(DataPencil, HorizontalVal, PreviousPt, HorizontalVal, NewPt);

		PreviousPt = NewPt;
	}
}

Spectrum::Spectrum() : DspPlugin(L"Spectrum", HAS_VIZ)
{
	std::wstring* SampleCounts = new std::wstring[6];
	SampleCounts[0] = L"128";
	SampleCounts[1] = L"256";
	SampleCounts[2] = L"512";
	SampleCounts[3] = L"1024";
	SampleCounts[4] = L"2048";
	SampleCounts[5] = L"4096";
	CurveDuration.EnumNames = SampleCounts;

	std::wstring* ChannelNames = new std::wstring[3];
	ChannelNames[0] = L"Left";
	ChannelNames[1] = L"Right";
	ChannelNames[2] = L"Mixdown";
	Channels.EnumNames = ChannelNames;

	ZoomL.FloatValueStep = 10.f;
	ZoomR.FloatValueStep = 10.f;
	ZoomV.FloatValueStep = 0.01f;

	ParameterRefsForUi.push_back(&Channels);
	ParameterRefsForUi.push_back(&CurveDuration);
	ParameterRefsForUi.push_back(&ZoomL);
	ParameterRefsForUi.push_back(&ZoomR);
	ParameterRefsForUi.push_back(&ZoomV);

	Data = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
	DataPencil = gcroot<Pen^>(gcnew Pen(Color::Black, 1));
	DataBrush = gcroot<SolidBrush^>(gcnew SolidBrush(Color::Black));
	HelperPencil1 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
	HelperPencil2 = gcroot<Pen^>(gcnew Pen(Color::Gray, 1));
	HelperPencil2->DashStyle = Drawing2D::DashStyle::Dot;
	TextL = gcroot<Font^>(gcnew Font("Microsoft Sans Serif", 8.0f, FontStyle::Regular));
	TextS = gcroot<Font^>(gcnew Font("Microsoft Sans Serif", 5.0f, FontStyle::Regular));
	FormatC = gcroot<StringFormat^>(gcnew StringFormat());
	FormatC->Alignment = StringAlignment::Center;
	FormatR = gcroot<StringFormat^>(gcnew StringFormat());
	FormatR->Alignment = StringAlignment::Far;
	TextColor = gcroot<Brush^>(gcnew SolidBrush(Color::Black));
}

void Spectrum::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int CurvePointsSize = pow2((7 + (int)CurveDuration.Val));

	Data->Lock();
	switch ((int)Channels.Val)
	{
	case 0:
		for (int i = 0; i < Length; ++i) Data->PushLast(BufferL[i]);
		break;
	case 1:
		for (int i = 0; i < Length; ++i) Data->PushLast(BufferR[i]);
		break;
	case 2:
		for (int i = 0; i < Length; ++i) Data->PushLast((BufferL[i] + BufferR[i]) / 2.0f);
		break;
	}
	int ExcessData = Data->Size() - CurvePointsSize;
	while (--ExcessData > 0) Data->PopFirst();
	Data->Unlock();
}

void Spectrum::UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame)
{
	const float Padding = 30.f;
	const float Shift = 13.0f;
	const float HelperLineCount = 10.0f;
	const float WorkAreaHorizontal = Width - (2 * Padding);
	const float WorkAreaVertical = Height - (2 * Padding);
	const int MaxPoints = Width;
	const int Range = Height;

	Image->Clear(Color::White);

	if (ZoomL.Val > ZoomR.Val) return;

	Image->DrawLine(HelperPencil1, Padding + Shift, Padding - Shift, Padding + Shift, Height - Padding - Shift);
	Image->DrawLine(HelperPencil1, Padding + Shift, Height - Padding - Shift, Width - Padding + Shift, Height - Padding - Shift);

	float Base = ZoomL.Val;
	float Top = ZoomR.Val;
	float SingleSegmentLen = (Top - Base) / 10.0f;
	Font^ UsedStyle = (Width > 370) ? TextL : TextS;

	for (int i = 0; i < HelperLineCount + 1; i++)
	{
		float HorizontalX = Padding + (WorkAreaHorizontal / HelperLineCount) * (float)i + Shift;
		float VerticalY = Padding + (WorkAreaVertical / HelperLineCount) * (float)i - Shift;

		Image->DrawLine(HelperPencil2,
			HorizontalX,
			Padding - Shift,
			HorizontalX,
			(float)Height - Padding - Shift);

		Image->DrawLine(HelperPencil2,
			Padding + Shift,
			VerticalY,
			(float)Width - Padding + Shift,
			VerticalY);

		Image->DrawString(((int)(Base + i * SingleSegmentLen)).ToString(), UsedStyle, TextColor, HorizontalX, Height - Padding + 5 - Shift, FormatC);
		Image->DrawString((ZoomV.Val - i * 0.1f * ZoomV.Val).ToString("N2"), UsedStyle, TextColor, Padding - 3 + Shift, VerticalY - 6, FormatR);
	}

	Image->DrawString(L"Frequency [Hz]", UsedStyle, TextColor, (float)(Width / 2), (float)(Height - 20), FormatC);

	Drawing::Drawing2D::GraphicsState^ State = Image->Save();
	Image->RotateTransform(-90);
	Image->TranslateTransform(5, Height / 2 - Shift, Drawing2D::MatrixOrder::Append);
	Image->DrawString(L"Signal value", UsedStyle, TextColor, 0, 0, FormatC);
	Image->Restore(State);

	Data->Lock();
	int ArrSize = pow2((7 + (int)CurveDuration.Val));
	if (Data->Size() < ArrSize)
	{
		Data->Unlock();
		return;
	}

	ComplexF* FftResult = new ComplexF[ArrSize];
	for (int i = 0; i < ArrSize; ++i) FftResult[i] = ComplexF(Data->Get(i), 0.0f);
	Data->Unlock();

	Utilities::Fft(FftResult, ArrSize);
	MonitoredArray<float>^ ResultArr = Utilities::FftProcessResult(FftResult, ArrSize);
	MonitoredArray<float>^ ResultArr2 = gcnew MonitoredArray<float>();
	Utilities::CutAndInterpolateSubrange(ResultArr, ResultArr2, ZoomL.Val / (float)(AUDIO_SAMPLERATE / 2), ZoomR.Val / (float)(AUDIO_SAMPLERATE / 2), (int)WorkAreaHorizontal);

	const float ValueMultiplier = 1.0f / ZoomV.Val;
	const int ZeroH = (int)(Height - Padding - Shift);
	int LastVal = ZeroH - (int)(WorkAreaVertical * ValueMultiplier * ResultArr2[0]);
	int InterpolatedArrSize = ResultArr2->Size();
	for (int i = 1; i < InterpolatedArrSize; ++i)
	{
		int HorizontalVal = (int)(i + Padding + Shift);
		int NewPt = ZeroH - (int)(WorkAreaVertical * ValueMultiplier * ResultArr2[i]);
		if (LastVal != NewPt) LastVal = (NewPt < LastVal) ? LastVal - 1 : LastVal + 1;

		if (LastVal == NewPt) Image->FillRectangle(DataBrush, HorizontalVal, LastVal, 1, 1);
		else                  Image->DrawLine(DataPencil, HorizontalVal, LastVal, HorizontalVal, NewPt);

		LastVal = NewPt;
	}

	ResultArr->Empty();
	ResultArr2->Empty();
	delete[] FftResult;
}

Spectrogram::Spectrogram() : DspPlugin(L"Spectrogram", HAS_VIZ)
{
	std::wstring* SampleCounts = new std::wstring[6];
	SampleCounts[0] = L"128";
	SampleCounts[1] = L"256";
	SampleCounts[2] = L"512";
	SampleCounts[3] = L"1024";
	SampleCounts[4] = L"2048";
	SampleCounts[5] = L"4096";
	CurveDuration.EnumNames = SampleCounts;

	std::wstring* ChannelNames = new std::wstring[3];
	ChannelNames[0] = L"Left";
	ChannelNames[1] = L"Right";
	ChannelNames[2] = L"Mixdown";
	Channels.EnumNames = ChannelNames;

	ContrastBump.FloatValueStep = 0.1f;

	ParameterRefsForUi.push_back(&Channels);
	ParameterRefsForUi.push_back(&CurveDuration);
	ParameterRefsForUi.push_back(&ContrastBump);

	Data = gcroot<MonitoredArray<float>^>(gcnew MonitoredArray<float>());
}

void Spectrogram::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int CurvePointsSize = pow2((7 + (int)CurveDuration.Val));

	Data->Lock();
	switch ((int)Channels.Val)
	{
	case 0:
		for (int i = 0; i < Length; ++i) Data->PushLast(BufferL[i]);
		break;
	case 1:
		for (int i = 0; i < Length; ++i) Data->PushLast(BufferR[i]);
		break;
	case 2:
		for (int i = 0; i < Length; ++i) Data->PushLast((BufferL[i] + BufferR[i]) / 2.0f);
		break;
	}
	int ExcessData = Data->Size() - CurvePointsSize;
	while (--ExcessData > 0) Data->PopFirst();
	Data->Unlock();
}

void Spectrogram::UpdatePictureBox(System::Drawing::Graphics^ Image, System::Drawing::Bitmap^ ImagePtr, int Width, int Height, bool FirstFrame)
{
	int ArrSize = pow2((7 + (int)CurveDuration.Val));
	ComplexF* FftResult = new ComplexF[ArrSize];

	Data->Lock();
	if (Data->Size() < ArrSize)
	{
		Data->Unlock();
		delete FftResult;
		return;
	}

	for (int i = 0; i < ArrSize; ++i) FftResult[i] = ComplexF(Data->operator[](i), 0.0f);
	Data->Unlock();

	Utilities::Fft(FftResult, ArrSize);
	MonitoredArray<float>^ ResultArr = Utilities::FftProcessResult(FftResult, ArrSize);
	delete[] FftResult;

	int HalfSize = ArrSize / 2;
	Bitmap^ FftLineBitmap = gcnew System::Drawing::Bitmap(1, HalfSize);

	float Buff = ContrastBump.Val + 1.0f;
	for (int i = 0; i < HalfSize; ++i)
	{
		int Val = (int)((ResultArr[i] * 255.0f) * Buff);
		Val = Utilities::Clamp(Val, 0, 255);
		FftLineBitmap->SetPixel(0, HalfSize - i - 1, Color::FromArgb(Val, Val, Val));
	}

	Image->DrawImage(ImagePtr, 1, 0, Width, Height);
	Image->DrawImage(FftLineBitmap, 0, 0, 1, Height);
	ResultArr->Empty();
}

LinearAmplifier::LinearAmplifier() : DspPlugin(L"Gain")
{
	ParameterRefsForUi.push_back(&UniformAmp);
	ParameterRefsForUi.push_back(&LeftChannelAmp);
	ParameterRefsForUi.push_back(&RightChannelAmp);
}

void LinearAmplifier::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; ++i)
	{
		*(BufferL++) *= LeftChannelAmp.Val  * UniformAmp.Val;
		*(BufferR++) *= RightChannelAmp.Val * UniformAmp.Val;
	}
}
Clip::Clip() : DspPlugin(L"Clip")
{
	ParameterRefsForUi.push_back(&PreGain);
	ParameterRefsForUi.push_back(&UniformClip);
	ParameterRefsForUi.push_back(&LeftChannelClip);
	ParameterRefsForUi.push_back(&RightChannelClip);
	ParameterRefsForUi.push_back(&PostGain);

	UniformClip.FloatValueStep = 0.01f;
	LeftChannelClip.FloatValueStep = 0.01f;
	RightChannelClip.FloatValueStep = 0.01f;
}

void Clip::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; ++i)
	{
		BufferL[i] *= PreGain.Val;
		BufferR[i] *= PreGain.Val;

		float LClipVal = min(UniformClip.Val, LeftChannelClip.Val);
		float RClipVal = min(UniformClip.Val, RightChannelClip.Val);

		BufferL[i] = Utilities::Clamp(BufferL[i], -LClipVal, LClipVal);
		BufferR[i] = Utilities::Clamp(BufferR[i], -RClipVal, RClipVal);

		BufferL[i] *= PostGain.Val;
		BufferR[i] *= PostGain.Val;
	}
}
PhaseInverter::PhaseInverter() : DspPlugin(L"Phase Inverter")
{
	std::wstring* InvertChannelNames = new std::wstring[4];
	InvertChannelNames[0] = L"None";
	InvertChannelNames[1] = L"Left only";
	InvertChannelNames[2] = L"Both";
	InvertChannelNames[3] = L"Right only";
	InvertChannel.EnumNames = InvertChannelNames;

	ParameterRefsForUi.push_back(&InvertChannel);
}

void PhaseInverter::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; i++)
	{
		int EnumVal = (int)InvertChannel.Val;
		if (EnumVal == 0) continue;
		BufferL[i] = (EnumVal <= 2) ? -BufferL[i] : BufferL[i];
		BufferR[i] = (EnumVal >= 2) ? -BufferR[i] : BufferR[i];
	}
}

#define MAX_SAMPLE_VALUE_HALVED 32768 //po³owa maksymalnej iloœci próbek w sygnale szesnastobitowym
inline void Bitcrusher::ProcessSample(float& Sample, int Mod)
{
	int S = (int)((Sample + 1.0f) * (float)MAX_SAMPLE_VALUE_HALVED);
	S += Mod / 2;
	S /= Mod;
	S *= Mod;
	Sample = ((float)S / MAX_SAMPLE_VALUE_HALVED) - 1.0f;
}
#undef MAX_SAMPLE_VALUE_HALVED

Bitcrusher::Bitcrusher() : DspPlugin(L"Bitcrusher")
{
	Resolution.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&Resolution);
}

#define BIT_DEPTH 16
void Bitcrusher::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int Mod = pow2((BIT_DEPTH - (int)Resolution.Val));
	for (int i = 0; i < Length; i++)
	{
		ProcessSample(BufferL[i], Mod);
		ProcessSample(BufferR[i], Mod);
	}
}
#undef BIT_DEPTH


void Decimator::ReallocateMemory(int PointCount)
{
	if (CurrentAllocatedPointsize)
	{
		delete[] LastPointsL;
		delete[] LastPointsR;
	}

	CurrentAllocatedPointsize = PointCount;
	LastPointsL = new float[PointCount];
	LastPointsR = new float[PointCount];
	for (int i = 0; i < PointCount; i++)
	{
		LastPointsL[i] = 0;
		LastPointsR[i] = 0;
	}

	CurrentSample = 0;
}

Decimator::Decimator() : DspPlugin(L"Decimator")
{
	DecimatorPower.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&DecimatorPower);
}


void Decimator::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int TempPointCount = (int)DecimatorPower.Val;
	if (CurrentAllocatedPointsize != TempPointCount) ReallocateMemory(TempPointCount);

	for (int i = 0; i < Length; i++)
	{
		if (++CurrentSample == CurrentAllocatedPointsize)
		{
			CurrentSample = 0;
			PreviousSampleFinalValueL = 0.0f;
			PreviousSampleFinalValueR = 0.0f;
			for (int j = 0; j < CurrentAllocatedPointsize; ++j) PreviousSampleFinalValueL += LastPointsL[j];
			for (int j = 0; j < CurrentAllocatedPointsize; ++j) PreviousSampleFinalValueR += LastPointsR[j];
			PreviousSampleFinalValueL /= CurrentAllocatedPointsize;
			PreviousSampleFinalValueR /= CurrentAllocatedPointsize;
		}

		LastPointsL[CurrentSample] = BufferL[i];
		LastPointsR[CurrentSample] = BufferR[i];
		BufferL[i] = PreviousSampleFinalValueL;
		BufferR[i] = PreviousSampleFinalValueR;
	}
}
Panner::Panner() : DspPlugin(L"Panner")
{
	Balance.FloatValueStep = 0.01f;
	ParameterRefsForUi.push_back(&Balance);
}

void Panner::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; ++i)
	{
		*(BufferL++) *= 2.0f - max(Balance.Val, 1.0f);
		*(BufferR++) *= min(Balance.Val, 1.0f);
	}
}
StereoMerger::StereoMerger() : DspPlugin(L"Stereo Merger")
{
	std::wstring* TypeEnum = new std::wstring[2];
	TypeEnum[0] = L"Merge (cramp)";
	TypeEnum[1] = L"Separate (widen)";
	Type.EnumNames = TypeEnum;

	Type.FloatValueStep = 0.01f;

	ParameterRefsForUi.push_back(&Type);
	ParameterRefsForUi.push_back(&Power);
	ParameterRefsForUi.push_back(&Clip);
}

void StereoMerger::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; i++)
	{
		float Mid = (BufferL[i] + BufferR[i]) / 2.0f;

		//merge
		if (Type.Val == 0.0f)
		{
			BufferL[i] = Utilities::WeightedAvg(BufferL[i], Mid, Power.Val);
			BufferR[i] = Utilities::WeightedAvg(BufferR[i], Mid, Power.Val);
		}
		//separate
		else
		{
			float Side = Mid - BufferL[i];
			BufferL[i] = BufferL[i] - (Side * Power.Val);
			BufferR[i] = BufferR[i] + (Side * Power.Val);
		}
		if (Clip.Val == 1.0f)
		{
			BufferL[i] = Utilities::Clamp(BufferL[i], -1.0f, 1.0f);
			BufferR[i] = Utilities::Clamp(BufferR[i], -1.0f, 1.0f);
		}
	}
}
StereoToMidside::StereoToMidside() : DspPlugin(L"Stereo to Mid-Side")
{
	std::wstring* RerouteEnumL = new std::wstring[4];
	RerouteEnumL[0] = L"Left";
	RerouteEnumL[1] = L"Right";
	RerouteEnumL[2] = L"Mid";
	RerouteEnumL[3] = L"Side";
	RerouteLeft.EnumNames = RerouteEnumL;

	std::wstring* RerouteEnumR = new std::wstring[4];
	RerouteEnumR[0] = L"Left";
	RerouteEnumR[1] = L"Right";
	RerouteEnumR[2] = L"Mid";
	RerouteEnumR[3] = L"Side";
	RerouteRight.EnumNames = RerouteEnumR;

	std::wstring* RerouteEnumIn = new std::wstring[3];
	RerouteEnumIn[0] = L"Left/Right";
	RerouteEnumIn[1] = L"Mid-Side";
	RerouteEnumIn[2] = L"Side-Mid";
	InputType.EnumNames = RerouteEnumIn;

	ParameterRefsForUi.push_back(&InputType);
	ParameterRefsForUi.push_back(&RerouteLeft);
	ParameterRefsForUi.push_back(&RerouteRight);
}

void StereoToMidside::ProcessData(float* BufferL, float* BufferR, int Length)
{
	for (int i = 0; i < Length; i++)
	{
		float L, R, Mid, Side;

		switch ((int)InputType.Val)
		{
		case 0: //Left/Right
			L = BufferL[i];
			R = BufferR[i];
			Mid = (L + R) / 2.0f;
			Side = Mid - L;
			break;

		case 1: //Mid-side
			Mid = BufferL[i];
			Side = BufferR[i];
			L = Mid + Side;
			R = Mid - Side;
			break;

		case 2: //Mid-side
			Mid = BufferR[i];
			Side = BufferL[i];
			L = Mid + Side;
			R = Mid - Side;
			break;
		}

		switch ((int)RerouteLeft.Val)
		{
		case 0: BufferL[i] = L; break;
		case 1: BufferL[i] = R; break;
		case 2: BufferL[i] = Mid; break;
		case 3: BufferL[i] = Side; break;
		}

		switch ((int)RerouteRight.Val)
		{
		case 0: BufferR[i] = L; break;
		case 1: BufferR[i] = R; break;
		case 2: BufferR[i] = Mid; break;
		case 3: BufferR[i] = Side; break;
		}

	}
}

#define SINC_LEN 255
SincFilter::SincFilter(std::wstring ChildFilterName) : DspPlugin(ChildFilterName)
{
	CutoffFrequency.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&CutoffFrequency);

	LastPointsL = new float[SINC_LEN];
	LastPointsR = new float[SINC_LEN];
	Response = new float[SINC_LEN];

	for (int i = 0; i < SINC_LEN; ++i)
	{
		LastPointsL[i] = 0.0f;
		LastPointsR[i] = 0.0f;
	}
}

void SincFilter::SaveLastPoints(float* BufferL, float* BufferR, int Length)
{
	int i1 = 0;
	for (int i2 = Length - SINC_LEN; i2 < Length; ++i2)
	{
		LastPointsL[i1] = BufferL[i2];
		LastPointsR[i1++] = BufferR[i2];
	}
}

inline float SincFilter::GetPoint(int Index, float* SubzeroBufferPtr, float* BufferPtr)
{
	return (Index >= 0) ? BufferPtr[Index] : SubzeroBufferPtr[Index + SINC_LEN];
}

void SincFilter::ProcessData(float* BufferL, float* BufferR, int Length)
{
	float* OutL = new float[Length];
	float* OutR = new float[Length];
	for (int i = 0; i < Length; i++)
	{
		OutL[i] = 0.0f;
		OutR[i] = 0.0f;
	}

	//Aktualizacja sinc
	if (LastKnownCutoffFrequency != CutoffFrequency.Val)
	{
		LastKnownCutoffFrequency = CutoffFrequency.Val;
		GenerateSincFunction();
	}

	//Aplikacja splotu
	for (int i = 0; i < Length; ++i)
	{
		for (int j = 0; j < SINC_LEN; ++j)
		{
			OutL[i] += GetPoint(i - j, LastPointsL, BufferL) * Response[j];
			OutR[i] += GetPoint(i - j, LastPointsR, BufferR) * Response[j];
		}
	}

	SaveLastPoints(BufferL, BufferR, Length);

	//Post-amp
	for (int i = 0; i < Length; ++i)
	{
		BufferL[i] = OutL[i];
		BufferR[i] = OutR[i];
	}

	delete[] OutL;
	delete[] OutR;
}

LowPassFilterSinc::LowPassFilterSinc() : SincFilter(L"Low Pass Filter (sinc)")
{
	CutoffFrequency.Val = CutoffFrequency.MaximumValue;
}

void LowPassFilterSinc::GenerateSincFunction()
{
	const float CutoffFreq = (LastKnownCutoffFrequency / 22100.0f) / 2.0f;
	const int FilterHalfLength = SINC_LEN / 2;
	float ResponseSum = 0.0f;

	for (int i = 0; i < SINC_LEN; ++i)
	{
		int Condition = i - FilterHalfLength;

		if (Condition == 0) Response[i] = M_TAU * CutoffFreq;
		else Response[i] = PcSin->GetWithTau(CutoffFreq * (float)Condition) / (float)Condition;
		Response[i] *= 0.54f - (0.46f * cos(M_TAU * (float)i / (float)SINC_LEN));
		ResponseSum += Response[i];
	}

	for (int i = 0; i < SINC_LEN; ++i) Response[i] /= ResponseSum;
}

void LowpassFilterAvg::ReallocateMemory(int CutoffFrequency)
{
	if (CurrentAllocatedPointsize)
	{
		delete[] LastPointsL;
		delete[] LastPointsR;
	}

	CurrentAllocatedPointsize = CutoffFrequency;
	LastPointsL = new float[CutoffFrequency];
	LastPointsR = new float[CutoffFrequency];
	for (int i = 0; i < CutoffFrequency; i++)
	{
		LastPointsL[i] = 0;
		LastPointsR[i] = 0;
	}
}

LowpassFilterAvg::LowpassFilterAvg() : DspPlugin(L"Low Pass Filter (avg)")
{
	CutoffFrequency.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&CutoffFrequency);
}


void LowpassFilterAvg::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int TempMuxPointCount = (int)CutoffFrequency.Val;

	if (CurrentAllocatedPointsize != TempMuxPointCount) ReallocateMemory(TempMuxPointCount);

	float* LCopy = new float[Length + TempMuxPointCount];
	float* RCopy = new float[Length + TempMuxPointCount];

	for (int i = 0; i < TempMuxPointCount; i++)
	{
		LCopy[i] = LastPointsL[i];
		RCopy[i] = LastPointsR[i];
	}

	for (int i = 0; i < Length; i++)
	{
		LCopy[i + TempMuxPointCount] = BufferL[i];
		RCopy[i + TempMuxPointCount] = BufferR[i];
	}

	for (int i = 0; i < Length; i++)
	{
		BufferL[i] = 0;
		BufferR[i] = 0;

		for (int j = i; j < i + TempMuxPointCount; j++)
		{
			BufferL[i] += LCopy[j];
			BufferR[i] += RCopy[j];
		}

		BufferL[i] /= (float)TempMuxPointCount;
		BufferR[i] /= (float)TempMuxPointCount;
	}

	for (int i = 0; i < TempMuxPointCount; i++)
	{
		LastPointsL[i] = LCopy[Length + i];
		LastPointsR[i] = RCopy[Length + i];
	}

	delete[] LCopy;
	delete[] RCopy;
}

RetriggerSimple::RetriggerSimple() : DspPlugin(L"Retrigger (Simple)")
{
	Modulo.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&Modulo);
}

void RetriggerSimple::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int ModuloVal = (int)((float)Length / (float)pow2((int)Modulo.Val));

	for (int i = 0; i < Length; i++)
	{
		BufferL[i] = BufferL[i % ModuloVal];
		BufferR[i] = BufferR[i % ModuloVal];
	}
}
Retrigger::Retrigger() : DspPlugin(L"Retrigger")
{
	Modulo.FloatValueStep = 1.0f;
	ParameterRefsForUi.push_back(&SampleLength);
	ParameterRefsForUi.push_back(&Modulo);
}

void Retrigger::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int PointsSize = (int)((float)AUDIO_SAMPLERATE * (float)SampleLength.Val / 1000.0f);
	int ArrSize = DataL.size();
	for (int i = 0; i < Length; ++i)
	{
		if (Modulo.Val == 1.0f)
		{
			DataL.clear();
			DataR.clear();
			break;
		}

		if (ArrSize < PointsSize)
		{
			DataL.push_back(BufferL[i]);
			DataR.push_back(BufferR[i]);
			++ArrSize;
			continue;
		}

		BufferL[i] = DataL[RepeatSample];
		BufferR[i] = DataR[RepeatSample];
		++RepeatSample;
		if (RepeatSample < PointsSize) continue;

		RepeatSample = 0;
		++RepeatState;
		if (RepeatState < Modulo.Val) continue;

		RepeatState = 1;
		DataL.clear();
		DataR.clear();
		ArrSize = 0;
	}
}
ReverserSimple::ReverserSimple() : DspPlugin(L"Reverser (Simple)") { }

void ReverserSimple::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int HalfLength = Length / 2;
	for (int i = 0; i < HalfLength; i++)
	{
		Utilities::Swap(BufferL[i], BufferL[Length - i - 1]);
		Utilities::Swap(BufferR[i], BufferR[Length - i - 1]);
	}
}

inline void Reverser::NextState()
{
	switch (State)
	{
	case 1:
		State = 2;
		DataL1.clear();
		DataR1.clear();
		break;

	case 0:
	case 2:
		State = 1;
		DataL2.clear();
		DataR2.clear();
		break;
	}
}
Reverser::Reverser() : DspPlugin(L"Reverser")
{
	ParameterRefsForUi.push_back(&SampleLength);
}

void Reverser::ProcessData(float* BufferL, float* BufferR, int Length)
{
	int PointsSize = (int)((float)AUDIO_SAMPLERATE * (float)SampleLength.Val / 1000.0f);
	if (OldPointsize != PointsSize)
	{
		DataL1.clear();
		DataR1.clear();
		DataL2.clear();
		DataR2.clear();
		State = 0;
	}
	OldPointsize = PointsSize;

	for (int i = 0; i < Length; ++i)
	{
		int ArrSize = (State != 1) ? DataL1.size() : DataL2.size();
		switch (State)
		{
		case 0:
			DataL1.push_back(BufferL[i]);
			DataR1.push_back(BufferR[i]);
			BufferL[i] = 0.0f;
			BufferR[i] = 0.0f;
			break;

		case 1:
			DataL2.push_back(BufferL[i]);
			DataR2.push_back(BufferR[i]);
			BufferL[i] = DataL1[PointsSize - ArrSize];
			BufferR[i] = DataR1[PointsSize - ArrSize];
			break;

		case 2:
			DataL1.push_back(BufferL[i]);
			DataR1.push_back(BufferR[i]);
			BufferL[i] = DataL2[PointsSize - ArrSize];
			BufferR[i] = DataR2[PointsSize - ArrSize];
			break;
		}

		if (ArrSize < PointsSize) continue;
		NextState();
	}
}

#undef Val
#undef HAS_VIZ 
