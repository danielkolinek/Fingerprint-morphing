#ifndef WX_NVOICEVIEW_HPP_INCLUDED
#define WX_NVOICEVIEW_HPP_INCLUDED

#include <wx/panel.h>
#include <wx/event.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <Biometrics/NVoice.hpp>

namespace Neurotec { namespace Biometrics { namespace Gui
{

wxDECLARE_EVENT(wxEVT_VOICE_OBJECT_COLLECTION_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_VOICE_PROPERTY_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_NSATTRIBUTES_PROPERTY_CHANGED, wxCommandEvent);

class wxNVoiceView : public wxPanel
{
public:
	wxNVoiceView(wxWindow *parent, wxWindowID winid = wxID_ANY) :
		wxPanel(parent, winid),
		m_voice(NULL),
		m_attributes(0)
	{
		CreateGui();

		this->Bind(wxEVT_VOICE_PROPERTY_CHANGED, &wxNVoiceView::UpdateUIEvent, this);
		this->Bind(wxEVT_NSATTRIBUTES_PROPERTY_CHANGED, &wxNVoiceView::UpdateUIEvent, this);
		this->Bind(wxEVT_VOICE_OBJECT_COLLECTION_CHANGED, &wxNVoiceView::OnAttributeCollectionChanged, this);
	}

	~wxNVoiceView()
	{
		SetVoice(::Neurotec::Biometrics::NVoice(NULL));
		this->Unbind(wxEVT_VOICE_PROPERTY_CHANGED, &wxNVoiceView::UpdateUIEvent, this);
		this->Unbind(wxEVT_NSATTRIBUTES_PROPERTY_CHANGED, &wxNVoiceView::UpdateUIEvent, this);
		this->Unbind(wxEVT_VOICE_OBJECT_COLLECTION_CHANGED, &wxNVoiceView::OnAttributeCollectionChanged, this);
	}

	void SetVoice(::Neurotec::Biometrics::NVoice voice)
	{
		UnsubscribeFromVoiceEvents();
		m_voice = voice;
		m_attributes = NULL;
		SubscribeToVoiceEvents();
		UpdateUI();
		Refresh();
	}

	::Neurotec::Biometrics::NVoice GetVoice()
	{
		return m_voice;
	}

private:
	void CreateGui()
	{
		wxBoxSizer* bSizer1;
		bSizer1 = new wxBoxSizer(wxVERTICAL);

		m_textStatus = new wxStaticText(this, wxID_ANY, wxT("Status: None"), wxDefaultPosition, wxDefaultSize, 0);
		m_textStatus->Wrap(-1);
		bSizer1->Add(m_textStatus, 0, wxALL, 5);

		wxFlexGridSizer* fgSizer1;
		fgSizer1 = new wxFlexGridSizer(2, 3, 0, 0);
		fgSizer1->AddGrowableCol(2);
		fgSizer1->AddGrowableRow(1);
		fgSizer1->SetFlexibleDirection(wxBOTH);
		fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

		m_textVoiceDetected = new wxStaticText(this, wxID_ANY, wxT("Voice detected: No"), wxDefaultPosition, wxDefaultSize, 0);
		m_textVoiceDetected->Wrap(-1);
		fgSizer1->Add(m_textVoiceDetected, 0, wxALL, 5);

		wxStaticText * m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("    Sound level:"), wxDefaultPosition, wxDefaultSize, 0);
		m_staticText3->Wrap(-1);
		fgSizer1->Add(m_staticText3, 0, wxALL, 5);

		m_gaugeSoundLevel = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
		m_gaugeSoundLevel->SetValue(0);
		fgSizer1->Add(m_gaugeSoundLevel, 0, wxALL | wxEXPAND, 5);

		bSizer1->Add(fgSizer1, 1, wxEXPAND, 5);

		this->SetSizer(bSizer1);
		this->Layout();
	}

	void UnsubscribeFromVoiceEvents()
	{
		if (!m_voice.IsNull())
		{
			m_voice.GetObjects().RemoveCollectionChangedCallback(&wxNVoiceView::OnObjectCollectionChanged, this);
			m_voice.RemovePropertyChangedCallback(&wxNVoiceView::OnVoicePropertyChanged, this);
		}
		if (!m_attributes.IsNull())
		{
			m_attributes.RemovePropertyChangedCallback(&wxNVoiceView::OnAttributesPropertyChanged, this);
		}
	}

	void SubscribeToVoiceEvents()
	{
		if (!m_voice.IsNull())
		{
			m_voice.GetObjects().AddCollectionChangedCallback(&wxNVoiceView::OnObjectCollectionChanged, this);
			m_voice.AddPropertyChangedCallback(&wxNVoiceView::OnVoicePropertyChanged, this);

			::Neurotec::NArrayWrapper< ::Neurotec::Biometrics::NSAttributes> attributes = m_voice.GetObjects().GetAll();

			if (attributes.GetCount() > 0)
				m_attributes = attributes[0];
			else
				m_attributes = NULL;

			if (!m_attributes.IsNull())
			{
				m_attributes.AddPropertyChangedCallback(&wxNVoiceView::OnAttributesPropertyChanged, this);
			}
		}
	}

	static void OnVoicePropertyChanged(::Neurotec::NObject::PropertyChangedEventArgs args)
	{
		wxString propertyName = args.GetPropertyName();
		if (propertyName == wxT("Status"))
		{
			wxNVoiceView * view = (wxNVoiceView*)args.GetParam();
			wxCommandEvent evt(wxEVT_VOICE_PROPERTY_CHANGED, wxID_ANY);
			wxPostEvent(view, evt);
		}
	}

	static void OnAttributesPropertyChanged(::Neurotec::NObject::PropertyChangedEventArgs args)
	{
		wxString propertyName = args.GetPropertyName();
		if (propertyName == wxT("SoundLevel") || propertyName == wxT("IsVoiceDetected"))
		{
			wxNVoiceView * view = (wxNVoiceView*)args.GetParam();
			wxCommandEvent evt(wxEVT_NSATTRIBUTES_PROPERTY_CHANGED, wxID_ANY);
			wxPostEvent(view, evt);
		}
	}

	static void OnObjectCollectionChanged(::Neurotec::Collections::CollectionChangedEventArgs<NSAttributes> args)
	{
		::Neurotec::Collections::NCollectionChangedAction action = args.GetAction();
		wxNVoiceView * view = (wxNVoiceView*)args.GetParam();
		switch (action)
		{
			case ::Neurotec::Collections::nccaAdd:
				{
					wxCommandEvent evt(wxEVT_VOICE_OBJECT_COLLECTION_CHANGED, wxID_ADD);
					evt.SetClientData(args.GetNewItems()[0].RefHandle());
					wxPostEvent(view, evt);
				}
				break;
			case ::Neurotec::Collections::nccaReset:
				{
					wxCommandEvent evt(wxEVT_VOICE_OBJECT_COLLECTION_CHANGED, wxID_REMOVE);
					evt.SetClientData(args.GetOldItems()[0].RefHandle());
					wxPostEvent(view, evt);
				}
				break;
		default:
			NThrowNotImplementedException();
		}
	}

	void OnAttributeCollectionChanged(wxCommandEvent & event)
	{
		::Neurotec::Biometrics::NSAttributes attributes(static_cast< ::Neurotec::Biometrics::NSAttributes::HandleType>(event.GetClientData()), true);
		int id = event.GetId();
		if (NObject::Equals(m_voice, attributes.GetOwner()))
		{
			if (!m_attributes.IsNull())
			{
				m_attributes.RemovePropertyChangedCallback(&wxNVoiceView::OnAttributesPropertyChanged, this);
				m_attributes = NULL;
			}
			if (id == wxID_ADD)
			{
				m_attributes = attributes;
				m_attributes.AddPropertyChangedCallback(&wxNVoiceView::OnAttributesPropertyChanged, this);
			}
			UpdateUI();
		}
	}

	void UpdateUI()
	{
		if (!m_voice.IsNull())
		{
			wxString statusString = ::Neurotec::NEnum::ToString(::Neurotec::Biometrics::NBiometricTypes::NBiometricStatusNativeTypeOf(), m_voice.GetStatus());
			m_textStatus->SetLabel(wxString::Format(wxT("Status: %s"), statusString.c_str()));
		}
		else
		{
			m_textStatus->SetLabel(wxT("Status: None"));
		}

		if (!m_attributes.IsNull())
		{
			wxString str = wxT("Voice detected: ");
			if (m_attributes.IsVoiceDetected())
				str += wxT("Yes");
			else
				str += wxT("No");
			m_textVoiceDetected->SetLabel(str);
			double value = m_attributes.GetSoundLevel();
			if (value > 1) value = 1;
			if (value < 0) value = 0;
			m_gaugeSoundLevel->SetValue((int)(value * 100));
		}
		else
		{
			m_textVoiceDetected->SetLabel(wxT("Voice detected: No"));
			m_gaugeSoundLevel->SetValue(0);
		}
	}

	void UpdateUIEvent(wxCommandEvent & /*event*/)
	{
		UpdateUI();
	}

private:
	::Neurotec::Biometrics::NVoice m_voice;
	::Neurotec::Biometrics::NSAttributes m_attributes;
	wxStaticText * m_textStatus;
	wxStaticText * m_textVoiceDetected;
	wxGauge * m_gaugeSoundLevel;
};

}}}

#endif // !WX_NVOICEVIEW_HPP_INCLUDED
