#ifndef WX_NFACE_VIEW_HPP_INCLUDED
#define WX_NFACE_VIEW_HPP_INCLUDED

#include <Gui/wxNView.hpp>
#include <Biometrics/NFace.hpp>

#include <wx/timer.h>

#define MAX_FPS_ENTRIES 30

namespace Neurotec { namespace Biometrics { namespace Gui
{

wxDECLARE_EVENT(wxEVT_FACE_OBJECT_COLLECTION_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_FACE_PROPERTY_CHANGED, wxCommandEvent);

class wxNFaceView : public Neurotec::Gui::wxNView
{
	#define ID_IMAGE_CHANGED          wxID_HIGHEST + 1
	#define ID_PROPERTY_CHANGED       wxID_HIGHEST + 2
	#define ID_COLLECTION_ITEM_ADD    wxID_HIGHEST + 3
	#define ID_COLLECTION_ITEM_REMOVE wxID_HIGHEST + 4
	#define ID_COLLECTION_ITEM_RESET  wxID_HIGHEST + 5
public:
	wxNFaceView(wxWindow *parent, wxWindowID winid = wxID_ANY)
		: wxNView(parent, winid),
		m_faceRectangleColor(wxColour(0, 255, 0)),
		m_livenessItemsColor(wxColour(255, 255, 0)),
		m_faceRectangleWidth(2),
		m_lastTime(0),
		m_firstTime(0),
		m_frameCount(0),
		m_currentFps(0),
		m_showFps(false),
		m_showEyes(true),
		m_showNose(true),
		m_showMouth(true),
		m_showNoseConfidence(false),
		m_showEyesConfidence(false),
		m_showFaceConfidence(true),
		m_showMouthConfidence(false),
		m_showGender(true),
		m_showGenderConfidence(false),
		m_showExpression(true),
		m_showExpressionConfidence(false),
		m_showProperties(true),
		m_showEmotions(true),
		m_showEmotionConfidence(false),
		m_showPropertiesConfidence(false),
		m_showBaseFeaturePoints(true),
		m_mirrorHorizontally(false),
		m_showAge(true),
		m_featureWidth(4),
		m_baseFeatureWidth(2),
		m_face(NULL)
	{
		SetScrollRate(1, 1);
		SetBackgroundColour(wxColour(0, 0, 0));
		this->Bind(wxEVT_FACE_PROPERTY_CHANGED, &wxNFaceView::OnPropertyChanged, this);
		this->Bind(wxEVT_FACE_OBJECT_COLLECTION_CHANGED, &wxNFaceView::OnCollectionChanged, this);
	}

	~wxNFaceView()
	{
		SetFace(NULL);
		this->Unbind(wxEVT_FACE_PROPERTY_CHANGED, &wxNFaceView::OnPropertyChanged, this);
		this->Unbind(wxEVT_FACE_OBJECT_COLLECTION_CHANGED, &wxNFaceView::OnCollectionChanged, this);
	}

private:
		static void OnPropertyChangedCallback(::Neurotec::Biometrics::NFace::PropertyChangedEventArgs args)
		{
			if (args.GetPropertyName() == N_T("Image"))
			{
				::Neurotec::Biometrics::NFace face = args.GetObject< ::Neurotec::Biometrics::NFace>();
				::Neurotec::Images::NImage image = face.GetImage();

				wxNFaceView * faceView = static_cast<wxNFaceView *>(args.GetParam());
				wxCommandEvent ev(wxEVT_FACE_PROPERTY_CHANGED, ID_IMAGE_CHANGED);
				if (!image.IsNull())
					ev.SetEventObject(new wxImage(image.ToBitmap()));
				else
					ev.SetEventObject(new wxImage());
				::wxPostEvent(faceView, ev);
			}
		}

		static void OnCollectionChangedCallback(::Neurotec::Collections::CollectionChangedEventArgs< ::Neurotec::Biometrics::NLAttributes> args)
		{
			wxNFaceView * faceView = static_cast<wxNFaceView*>(args.GetParam());
			wxCommandEvent ev(wxEVT_FACE_OBJECT_COLLECTION_CHANGED);
			if (args.GetAction() == ::Neurotec::Collections::nccaAdd)
			{
				if (args.GetNewItems().GetCount() > 1) NThrowNotImplementedException();
				ev.SetClientData(args.GetNewItems()[0].RefHandle());
				ev.SetId(ID_COLLECTION_ITEM_ADD);
			}
			else if (args.GetAction() == ::Neurotec::Collections::nccaRemove)
			{
				NThrowNotImplementedException();
			}
			else if (args.GetAction() == ::Neurotec::Collections::nccaReset)
			{
				ev.SetId(ID_COLLECTION_ITEM_RESET);
			}
			::wxPostEvent(faceView, ev);
		}

		static void OnAttributesPropertyChangedCallback(::Neurotec::Biometrics::NLAttributes::PropertyChangedEventArgs args)
		{
			wxNFaceView * faceView = static_cast<wxNFaceView*>(args.GetParam());
			wxCommandEvent ev(wxEVT_FACE_PROPERTY_CHANGED, ID_PROPERTY_CHANGED);
			::wxPostEvent(faceView, ev);
		}

		void SubscribeToFaceEvents()
		{
			if (!m_face.IsNull())
			{
				m_face.AddPropertyChangedCallback(&wxNFaceView::OnPropertyChangedCallback, this);
				m_face.GetObjects().AddCollectionChangedCallback(&wxNFaceView::OnCollectionChangedCallback, this);
				OnAttributesAdded(m_face.GetObjects().GetAll());
			}
		}

		void UnsubscribeFromFaceEvents()
		{
			if (!m_face.IsNull())
			{
				m_face.RemovePropertyChangedCallback(&wxNFaceView::OnPropertyChangedCallback, this);
				m_face.GetObjects().RemoveCollectionChangedCallback(&wxNFaceView::OnCollectionChangedCallback, this);
				OnAttributesReset();
			}
		}

		void SetImage(const wxImage & image)
		{
			if (image.IsOk())
			{
				m_bitmap = wxBitmap(image);
				SetViewSize(image.GetWidth(), image.GetHeight());
			}
			else
			{
				m_bitmap = wxBitmap();
				SetViewSize(1, 1);
			}
			Refresh(false);
		}

		void OnPropertyChanged(wxEvent & event)
		{
			int id = event.GetId();
			if (id == ID_IMAGE_CHANGED)
			{
				wxImage * pImage = (wxImage*)event.GetEventObject();
				SetImage(*pImage);
				delete pImage;
			}
			else Refresh();
		}

		void OnCollectionChanged(wxCommandEvent & event)
		{
			int id = event.GetId();
			if (id == ID_COLLECTION_ITEM_ADD)
			{
				::Neurotec::Biometrics::NLAttributes attributes(static_cast< ::Neurotec::Biometrics::HNLAttributes>(event.GetClientData()), true);
				std::vector< ::Neurotec::Biometrics::NLAttributes> attrVector;
				attrVector.push_back(attributes);
				NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attrArray(attrVector.begin(), attrVector.end());
				OnAttributesAdded(attrArray);
			}
			else if (id == ID_COLLECTION_ITEM_RESET)
			{
				OnAttributesReset();
			}
		}

		void OnAttributesAdded(NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attributes)
		{
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				attributes[i].AddPropertyChangedCallback(&wxNFaceView::OnAttributesPropertyChangedCallback, this);
				m_attributes.push_back(attributes[i]);
			}
			Refresh();
		}

		void OnAttributesReset()
		{
			for (std::vector< ::Neurotec::NObject>::iterator it = m_attributes.begin(); it < m_attributes.end(); it++)
			{
				it->RemovePropertyChangedCallback(&wxNFaceView::OnAttributesPropertyChangedCallback, this);
			}
			m_attributes.clear();
			Refresh();
		}
public:
	void Clear()
	{
		m_bitmap = wxBitmap();
		SetFace(NULL);
		m_faceIds.Clear();
		Refresh(false);
	}

	void SetFace(::Neurotec::Biometrics::NFace face)
	{
		if (GetShowFps())
		{
			UpdateFps();
		}

		UnsubscribeFromFaceEvents();

		m_face = face;

		SubscribeToFaceEvents();
		if (!m_face.IsNull())
		{
			::Neurotec::Images::NImage image = m_face.GetImage();
			SetImage(!image.IsNull() ? image.ToBitmap() : wxImage());
		}
		else SetImage(wxImage());
	}

	::Neurotec::Biometrics::NFace GetFace()
	{
		return m_face;
	}
	void SetFaceIds(const wxArrayString &value) { m_faceIds = value; Refresh();}
	const wxArrayString & GetFaceIds() { return m_faceIds; }
	void SetFaceRectangleColor(const wxColour & value){ m_faceRectangleColor = value; }
	const wxColour & GetFaceRectangleColor(){ return m_faceRectangleColor; }

	void SetLivenessItemsColor(const wxColour & value) { m_livenessItemsColor = value; }
	const wxColour & GetLivenessItemsColor() { return m_livenessItemsColor; }

	void SetFaceRectangleWidth(int value){ m_faceRectangleWidth = value; }
	int GetFaceRectangleWidth(){ return m_faceRectangleWidth; }

	void SetShowFps(bool value){ m_showFps = value; }
	bool GetShowFps(){ return m_showFps; }

	bool GetShowEyes(){ return m_showEyes; }
	void SetShowEyes(bool value){ m_showEyes = value; }
	bool GetShowNose(){ return m_showNose; }
	void SetShowNose(bool value){ m_showNose = value; }
	bool GetShowMouth(){ return m_showMouth; }
	void SetShowMouth(bool value){ m_showMouth = value; }
	bool GetShowMouthConfidence(){ return m_showMouthConfidence; }
	void SetShowMouthConfidence(bool value){ m_showMouthConfidence = value; }
	bool GetShowNoseConfidence(){ return m_showNoseConfidence; }
	void SetShowNoseConfidence(bool value){ m_showNoseConfidence = value; }
	bool GetShowEyesConfidence(){ return m_showEyesConfidence; }
	void SetShowEyesConfidence(bool value){ m_showEyesConfidence = value; }
	bool GetShowFaceConfidence(){ return m_showFaceConfidence; }
	void SetShowFaceConfidence(bool value){ m_showFaceConfidence = value; }
	void SetShowGender(bool value){ m_showGender = value; }
	bool GetShowGender(){ return m_showGender; }
	void SetShowGenderConfidence(bool value){ m_showGenderConfidence = value; }
	bool GetShowGenderConfidence(){ return m_showGenderConfidence; }
	bool GetShowExpression() { return m_showExpression; }
	void SetShowExpression(bool value) { m_showExpression = value; }
	bool GetShowExpressionConfidence() { return m_showExpressionConfidence; }
	void SetShowExpressionConfidence(bool value) { m_showExpressionConfidence = value; }
	bool GetShowProperties() { return m_showProperties; }
	void SetShowProperties(bool value) { m_showProperties = value; }
	bool GetShowPropertiesConfidence() { return m_showPropertiesConfidence; }
	void SetShowPropertiesConfidence(bool value) { m_showPropertiesConfidence = value; }
	void SetShowBaseFeaturePoints(bool value){ m_showBaseFeaturePoints = value; }
	bool GetShowBaseFeaturePoints(){ return m_showBaseFeaturePoints; }
	int GetFeatureWidth(){ return m_featureWidth; }
	void SetFeatureWidth(int value){ m_featureWidth = value; }
	int GetBaseFeatureWidth(){ return m_baseFeatureWidth; }
	void SetBaseFeatureWidth(int value){ m_baseFeatureWidth = value; }
	bool GetShowEmotions() { return m_showEmotions; }
	void SetShowEmotions(bool value) { m_showEmotions = value; }
	bool GetShowEmotionsConfidence() { return m_showEmotionConfidence; }
	void SetShowEmotionsConfidence(bool value) { m_showEmotionConfidence = value; }
	bool GetMirrorHorizontally() { return m_mirrorHorizontally; }
	void SetMirrorHorizontally(bool value) { m_mirrorHorizontally = value; }
	bool GetShowAge() { return m_showAge; }
	void SetShowAge(bool value) { m_showAge = value; }
protected:
#if wxUSE_GRAPHICS_CONTEXT == 1
	virtual void OnDraw(wxGraphicsContext *gc)
	{
		if (!m_bitmap.IsOk()) return;
		if (m_bitmap.GetRefData())
		{
			if(m_mirrorHorizontally)
			{
				gc->Translate(m_bitmap.GetWidth(), 0);
				gc->Scale(-1, 1);
			}
			gc->DrawBitmap(m_bitmap, 0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());
		}

		gc->Clip(0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());

		if (!m_face.IsNull())
		{
			NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attributes = m_face.GetObjects().GetAll();
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				wxString faceNumber = wxEmptyString;
				if (!m_faceIds.IsEmpty() && i < (int)m_faceIds.GetCount())
				{
					faceNumber = m_faceIds[i];
				}
				else
				{
					faceNumber = (wxString::Format(wxT("#%d"), i + 1));
				}
				wxString faceConfidence = wxEmptyString;
				::Neurotec::Biometrics::NLAttributes item = attributes[i];
				NByte quality = item.GetQuality();
				if (quality <= 100 && m_showFaceConfidence)
				{
					faceConfidence = wxString::Format(wxT("%d"), quality);
				}
				DrawAttributes(gc, item, faceNumber, faceConfidence);
			}
		}
		gc->ResetClip();

		if (m_showFps
			&& m_currentFps > 0.5f
			&& m_currentFps < 1000.0f)
		{
			wxBrush brush(wxColour(127, 127, 127));
			wxGraphicsBrush graphicsBrush = gc->CreateBrush(brush);
			gc->DrawText(wxString::Format(wxT("%4.1f"), m_currentFps), 5, 5, graphicsBrush);
		}
	}

#else
	virtual void OnDraw(wxDC& dc)
	{
		if (m_bitmap.GetRefData())
		{
			dc.DrawBitmap(m_bitmap, 0, 0, false);
		}

		if (!m_face.IsNull())
		{
			NArrayWrapper< ::Neurotec::Biometrics::NLAttributes> attributes = m_face.GetObjects().GetAll();
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				wxString faceNumber = wxEmptyString;
				if (!m_faceIds.IsEmpty() && i < (int)m_faceIds.GetCount())
				{
					faceNumber = m_faceIds[i];
				}
				else
				{
					faceNumber = (wxString::Format(wxT("#%d"), i + 1));
				}
				wxString faceConfidence = wxEmptyString;
				::Neurotec::Biometrics::NLAttributes item = attributes[i];
				NByte quality = item.GetQuality();
				if (quality <= 100 && m_showFaceConfidence)
				{
					faceConfidence = wxString::Format(wxT("%d"), quality);
				}
				DrawAttributes(dc, item, faceNumber, faceConfidence);
			}
		}
		if (m_showFps
			&& m_currentFps > 0.5f
			&& m_currentFps < 1000.0f)
		{
			dc.SetTextForeground(wxColour(127, 127,127));
			dc.DrawText(wxString::Format(wxT("%4.1f"), m_currentFps), 5, 5);
		}
	}

	static inline void RotatePointAt(double x, double y, double centerX, double centerY, double angle, double *ox, double *oy)
	{
		*ox = centerX + cos(angle) * (x - centerX) - sin(angle) * (y - centerY);
		*oy = centerY + sin(angle) * (x - centerX) + cos(angle) * (y - centerY);
	}

#endif

#if wxUSE_GRAPHICS_CONTEXT == 1
private:
	static wxPoint PreparePath(wxGraphicsContext *gc, wxGraphicsPath& gp, float angle, wxRect playArea, bool invert)
	{
		int border = 2;
		playArea.x += border;
		playArea.y += border;
		playArea.width -= border * 2;
		playArea.height -= border * 2;

		wxRect2DDouble rectd = gp.GetBox();

		float scalex = playArea.height / rectd.m_height;
		float translatey = playArea.y;
		float halfPath = rectd.m_width * scalex / 2;
		float maxYaw = 35;
		float offset = (-angle / maxYaw) * (playArea.width / 2) + halfPath;
		float center = playArea.x + playArea.width / 2;
		float translatex = center - offset;

		wxGraphicsMatrix m = gc->CreateMatrix();
		if (invert)
		{
			m.Translate(rectd.m_width, 0);
			m.Scale(-1, 1);
			gp.Transform(m);
		}

		m = gc->CreateMatrix();
		m.Translate(translatex, translatey);
		m.Scale(scalex, scalex);
		gp.Transform(m);

		rectd = gp.GetBox();
		return wxPoint(rectd.m_x + rectd.m_width / 2, rectd.m_y);
	}

	static wxGraphicsPath CreateArrowPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxPoint2DDouble points[] =
		{
			wxPoint2DDouble(32.380941f, 1022.1241f), wxPoint2DDouble(31.942188f, 1015.7183f), wxPoint2DDouble(29.758001f, 1008.0593f), wxPoint2DDouble(34.975683f, 1002.9847f),
			wxPoint2DDouble(63.530331f, 959.92008f), wxPoint2DDouble(92.084969f, 916.85544f), wxPoint2DDouble(120.6396f, 873.7908f),   wxPoint2DDouble(90.970216f, 829.04496f),
			wxPoint2DDouble(61.300833f, 784.29911f), wxPoint2DDouble(31.631451f, 739.55327f), wxPoint2DDouble(32.4174f, 735.10024f),   wxPoint2DDouble(30.920929f, 728.358f),
			wxPoint2DDouble(33.05677f, 725.25888f),  wxPoint2DDouble(40.037212f, 725.44802f), wxPoint2DDouble(47.596572f, 722.95826f), wxPoint2DDouble(53.587747f, 727.72521f),
			wxPoint2DDouble(145.07152f, 773.61583f), wxPoint2DDouble(236.87685f, 818.88016f), wxPoint2DDouble(327.96427f, 865.54932f), wxPoint2DDouble(337.43478f, 881.9015f),
			wxPoint2DDouble(317.96639f, 887.43366f), wxPoint2DDouble(306.82511f, 892.94892f), wxPoint2DDouble(220.62057f, 936.55761f), wxPoint2DDouble(134.10541f, 979.54806f),
			wxPoint2DDouble(47.717131f, 1022.7908f), wxPoint2DDouble(42.608566f, 1022.6599f), wxPoint2DDouble(37.414432f, 1023.1935f), wxPoint2DDouble(32.380941f, 1022.1241f)
		};

		for (NUInt i = 0; i < sizeof(points)/sizeof(points[0]); i++)
			gp.AddLineToPoint(points[i]);

		gp.CloseSubpath();

		wxRect2DDouble bounds = gp.GetBox();
		wxGraphicsMatrix m = gc->CreateMatrix();
		m.Translate(-bounds.m_x, -bounds.m_y);
		gp.Transform(m);

		return gp;
	}

	static wxGraphicsPath CreateTargetPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxDouble radius[] =
		{
			40, 30, 20, 10
		};

		for (NUInt i = 0; i < sizeof(radius)/sizeof(radius[0]); i++)
			gp.AddArc(wxPoint2DDouble(40, 40), radius[i], 0, 360, false);

		gp.CloseSubpath();

		return gp;
	}

	static wxGraphicsPath CreateBlinkPath(wxGraphicsContext *gc)
	{
		wxGraphicsPath gp = gc->CreatePath();
		wxPoint2DDouble points[] =
		{
			wxPoint2DDouble(435.85713f, 829.28988f), wxPoint2DDouble(435.85713f, 826.14134f), wxPoint2DDouble(435.85713f, 822.99279f), wxPoint2DDouble(435.85713f, 819.84425f),
			wxPoint2DDouble(431.52818f, 819.40493f), wxPoint2DDouble(427.2124f, 818.65847f),  wxPoint2DDouble(422.85713f, 818.61225f), wxPoint2DDouble(420.07381f, 823.2792f),
			wxPoint2DDouble(419.55592f, 829.21363f), wxPoint2DDouble(415.81523f, 833.2958f),  wxPoint2DDouble(411.88195f, 832.96632f), wxPoint2DDouble(402.56019f, 832.2983f),
			wxPoint2DDouble(403.59168f, 826.82747f), wxPoint2DDouble(404.49412f, 822.06959f), wxPoint2DDouble(407.38289f, 817.62303f), wxPoint2DDouble(407.23492f, 812.74024f),
			wxPoint2DDouble(403.97397f, 810.47656f), wxPoint2DDouble(400.43818f, 808.64918f), wxPoint2DDouble(397.01142f, 806.65399f), wxPoint2DDouble(393.40481f, 810.75036f),
			wxPoint2DDouble(390.50368f, 815.74657f), wxPoint2DDouble(385.74505f, 818.59108f), wxPoint2DDouble(381.53086f, 816.45821f), wxPoint2DDouble(371.30273f, 811.69373f),
			wxPoint2DDouble(377.16061f, 806.33105f), wxPoint2DDouble(379.68245f, 802.38916f), wxPoint2DDouble(387.71098f, 797.5141f),  wxPoint2DDouble(381.91398f, 792.84178f),
			wxPoint2DDouble(379.33556f, 788.89088f), wxPoint2DDouble(373.92253f, 785.09903f), wxPoint2DDouble(374.27125f, 780.28926f), wxPoint2DDouble(378.67829f, 776.95361f),
			wxPoint2DDouble(384.55646f, 773.59246f), wxPoint2DDouble(390.26417f, 775.09226f), wxPoint2DDouble(397.24491f, 778.82048f), wxPoint2DDouble(401.76433f, 785.81843f),
			wxPoint2DDouble(408.41041f, 790.09015f), wxPoint2DDouble(424.88655f, 801.96214f), wxPoint2DDouble(447.55374f, 803.93538f), wxPoint2DDouble(466.25184f, 796.46734f),
			wxPoint2DDouble(476.00331f, 792.64778f), wxPoint2DDouble(483.5214f, 785.18173f),  wxPoint2DDouble(491.17644f, 778.33114f), wxPoint2DDouble(495.00098f, 774.23975f),
			wxPoint2DDouble(501.2108f, 773.54521f),  wxPoint2DDouble(505.75694f, 776.89247f), wxPoint2DDouble(510.64456f, 778.33781f), wxPoint2DDouble(513.78144f, 782.54911f),
			wxPoint2DDouble(508.97685f, 786.32591f), wxPoint2DDouble(506.39681f, 789.80997f), wxPoint2DDouble(503.5728f, 793.10166f),  wxPoint2DDouble(500.83072f, 796.45699f),
			wxPoint2DDouble(504.57117f, 801.05482f), wxPoint2DDouble(508.90555f, 805.26143f), wxPoint2DDouble(511.85713f, 810.42573f), wxPoint2DDouble(508.73325f, 813.98587f),
			wxPoint2DDouble(502.37734f, 823.35014f), wxPoint2DDouble(498.04955f, 816.79531f), wxPoint2DDouble(494.57914f, 813.95975f), wxPoint2DDouble(492.73279f, 806.66381f),
			wxPoint2DDouble(487.41682f, 807.78358f), wxPoint2DDouble(482.55765f, 810.13083f), wxPoint2DDouble(475.96485f, 813.63492f), wxPoint2DDouble(480.85493f, 819.58648f),
			wxPoint2DDouble(482.7528f, 823.71135f),  wxPoint2DDouble(486.27353f, 830.95944f), wxPoint2DDouble(479.19952f, 832.07128f), wxPoint2DDouble(475.2306f, 833.59222f),
			wxPoint2DDouble(469.68497f, 836.70712f), wxPoint2DDouble(468.77703f, 830.32197f), wxPoint2DDouble(466.1358f, 826.89057f),  wxPoint2DDouble(466.61264f, 818.27641f),
			wxPoint2DDouble(461.63576f, 818.56925f), wxPoint2DDouble(458.07069f, 819.02156f), wxPoint2DDouble(454.49876f, 819.41691f), wxPoint2DDouble(450.92969f, 819.83583f),
			wxPoint2DDouble(450.73884f, 825.93985f), wxPoint2DDouble(450.54798f, 832.04386f), wxPoint2DDouble(450.35713f, 838.14788f), wxPoint2DDouble(445.5238f, 838.34375f),
			wxPoint2DDouble(440.69046f, 838.53963f), wxPoint2DDouble(435.85713f, 838.7355f),  wxPoint2DDouble(435.85713f, 835.58696f), wxPoint2DDouble(435.85713f, 832.43842f),
			wxPoint2DDouble(435.85713f, 829.28988f)
		};

		for (NUInt i = 0; i < sizeof(points)/sizeof(points[0]); i++)
			gp.AddLineToPoint(points[i]);

		gp.CloseSubpath();

		wxRect2DDouble bounds = gp.GetBox();
		wxGraphicsMatrix m = gc->CreateMatrix();
		m.Scale(0.8f, 1);
		m.Translate(-bounds.m_x, -bounds.m_y);
		gp.Transform(m);

		return gp;
	}
#endif

protected:
#if wxUSE_GRAPHICS_CONTEXT == 1
	void DrawAttributes(wxGraphicsContext *gc, const ::Neurotec::Biometrics::NLAttributes & attributes, const wxString& faceNumber, const wxString& faceConfidence)
	{
		::Neurotec::Biometrics::NLFeaturePoint item;

		wxPen pen(m_faceRectangleColor, m_faceRectangleWidth);
		wxBrush solidBrush(m_faceRectangleColor);
		gc->SetPen(pen);

		int half = m_baseFeatureWidth / 2;

		NLivenessAction action = attributes.GetLivenessAction();

		::Neurotec::Geometry::NRect rect = attributes.GetBoundingRect();
		if (rect.Width > 0 && rect.Height > 0)
		{
			wxPen penGreen(m_faceRectangleColor, m_faceRectangleWidth);
			penGreen.SetCap(wxCAP_PROJECTING);
			penGreen.SetJoin(wxJOIN_MITER);
			gc->SetPen(penGreen);

			wxGraphicsMatrix oldTransform = gc->GetTransform();
			wxGraphicsMatrix matrix = gc->CreateMatrix();
			matrix.Translate(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
			matrix.Rotate(attributes.GetRoll() * M_PI / 180.0);
			if(m_mirrorHorizontally) { matrix.Scale(-1, 1); }
			matrix.Translate(-rect.Width / 2, -rect.Height / 2);
			gc->ConcatTransform(matrix);

			wxGraphicsPath path = gc->CreatePath();
			short yaw = attributes.GetYaw();
			path.AddLineToPoint(rect.Width, 0);
			if(yaw < 0)
			{
				path.AddLineToPoint(rect.Width - (rect.Width / 5 * yaw / 45), rect.Height / 2);
			}
			path.AddLineToPoint(rect.Width, rect.Height);
			path.AddLineToPoint(0, rect.Height);
			if(yaw > 0)
			{
				path.AddLineToPoint(-(rect.Width / 5 * yaw / 45), rect.Height / 2);
			}
			path.AddLineToPoint(0, 0);
			path.CloseSubpath();

			gc->StrokePath(path);

			wxBrush brush(m_faceRectangleColor);
			wxGraphicsBrush graphicsBrush = gc->CreateBrush(brush);

			if (action == nlaNone && !faceConfidence.IsEmpty())
			{
				gc->DrawText(faceConfidence, 0, rect.Height + 3, graphicsBrush);
			}

			if (m_showGender || m_showProperties || m_showExpression || m_showEmotions || m_showAge)
			{
				wxString value = GetDetailsString(attributes);
				if (value != wxEmptyString)
				{
					double textWidth, textHeight, descent, externalLeading;
					double faceWidth = rect.Width;
					gc->GetTextExtent(value, &textWidth, &textHeight, &descent, &externalLeading);
					double offset = textWidth > faceWidth ? (textWidth - faceWidth) / 2 : 0;
					gc->DrawText(value, 0 - offset, 0 - textHeight - 1, graphicsBrush);
				}
			}
			if (!faceNumber.IsEmpty())
			{
				double textWidth, textHeight, descent, externalLeading;
				gc->GetTextExtent(faceNumber, &textWidth, &textHeight, &descent, &externalLeading);
				gc->DrawText(faceNumber, rect.Width - textWidth, rect.Height + 3, graphicsBrush);
			}
			gc->SetTransform(oldTransform);
			wxGraphicsMatrix MirroredMatrix = gc->CreateMatrix();

			half = m_featureWidth / 2;
			if (m_showEyes)
			{
				::Neurotec::Biometrics::NLFeaturePoint left = attributes.GetLeftEyeCenter();
				::Neurotec::Biometrics::NLFeaturePoint right = attributes.GetRightEyeCenter();
				if ((IsConfidenceOk(left.Confidence) || IsConfidenceOk(right.Confidence)))
				{
					if(IsConfidenceOk(left.Confidence) && IsConfidenceOk(right.Confidence))
					{
						gc->StrokeLine((NShort)left.X, (NShort)left.Y, (NShort)right.X, (NShort)right.Y);
					}
					gc->SetBrush(solidBrush);
					if(IsConfidenceOk(left.Confidence))
					{
						gc->DrawEllipse((NShort)left.X - half, (NShort)left.Y - half, m_featureWidth, m_featureWidth);
					}
					if(IsConfidenceOk(right.Confidence))
					{
						gc->DrawEllipse((NShort)right.X - half, (NShort)right.Y - half, m_featureWidth, m_featureWidth);
					}
					gc->SetBrush(wxNullBrush);
					if(m_mirrorHorizontally)
					{
						MirroredMatrix = gc->CreateMatrix();
						MirroredMatrix.Translate(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
						MirroredMatrix.Scale(-1, 1);
						MirroredMatrix.Translate(-rect.X -rect.Width / 2, -rect.Y -rect.Height / 2);
						gc->ConcatTransform(MirroredMatrix);
					}
					if(m_showEyesConfidence)
					{
						if(IsConfidenceOk(right.Confidence))
						{
							gc->DrawText(wxString::Format(wxT("%d"), right.Confidence), (NShort)right.X - m_featureWidth, (NShort)right.Y + m_featureWidth);
						}
						if(IsConfidenceOk(left.Confidence))
						{
							gc->DrawText(wxString::Format(wxT("%d"), left.Confidence), (NShort)left.X - m_featureWidth, (NShort)left.Y + m_featureWidth);
						}
					}
				}
			}
			if(m_showNose)
			{
				::Neurotec::Biometrics::NLFeaturePoint nose = attributes.GetNoseTip();
				if (IsConfidenceOk(nose.Confidence))
				{
					gc->SetBrush(solidBrush);
					gc->DrawEllipse((NShort)nose.X - half, (NShort)nose.Y - half, m_featureWidth, m_featureWidth);
				
					if(m_showNoseConfidence)
					{
						gc->DrawText(wxString::Format(wxT("%d"), nose.Confidence), (NShort)nose.X - m_featureWidth, (NShort)nose.Y + m_featureWidth);
					}
					gc->SetBrush(wxNullBrush);
				}
			}
			if(m_showMouth)
			{
				::Neurotec::Biometrics::NLFeaturePoint mouth = attributes.GetMouthCenter();
				if (IsConfidenceOk(mouth.Confidence))
				{
					gc->SetBrush(solidBrush);
					gc->DrawEllipse((NShort)mouth.X - half, (NShort)mouth.Y - half, m_featureWidth, m_featureWidth);
					gc->SetBrush(wxNullBrush);
				
					if(m_showMouthConfidence)
					{
						gc->DrawText(wxString::Format(wxT("%d"), mouth.Confidence), (NShort)mouth.X - m_featureWidth, (NShort)mouth.Y + m_featureWidth);
					}
				}
			}
			if(m_mirrorHorizontally)
			{
				MirroredMatrix = gc->CreateMatrix();
				MirroredMatrix.Translate(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
				MirroredMatrix.Scale(-1, 1);
				MirroredMatrix.Translate(-rect.X -rect.Width / 2, -rect.Y -rect.Height / 2);
				gc->ConcatTransform(MirroredMatrix);
			}
			gc->SetPen(wxNullPen);

			if(m_showBaseFeaturePoints)
			{
				gc->SetBrush(solidBrush);
				NArrayWrapper< ::Neurotec::Biometrics::NLFeaturePoint> points = attributes.GetFeaturePoints().GetAll();
				for(int i = 0; i < points.GetCount(); i++)
				{
					item = points[i];
					if(item.Confidence > 0)
					{
						gc->DrawEllipse((NShort)item.X - half, (NShort)item.Y - half, m_baseFeatureWidth, m_baseFeatureWidth);
					}
				}
			}
		}

		if (action != nlaNone)
		{
			bool rotateYaw = (action & nlaRotateYaw) == nlaRotateYaw;
			bool blink = (action & nlaBlink) == nlaBlink;
			bool keepStill = (action & nlaKeepStill) == nlaKeepStill;

			NByte score = attributes.GetLivenessScore();
			wxString text;
			if (blink) text = wxT("Please blink");
			else if (rotateYaw) text = wxT("Turn face on target");
			else if (keepStill) text = wxT("Please keep still");

			if (!blink && !rotateYaw && score <= 100)
			{
				text += wxString::Format(wxT(", Score: %d"), score);
			}

			wxBrush livenessBrush(m_livenessItemsColor);
			wxPen livenessPen(m_livenessItemsColor);
			gc->SetPen(livenessPen);

			wxGraphicsMatrix oldM = gc->GetTransform();
			wxGraphicsMatrix m = gc->CreateMatrix();
			m.Translate(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
			m.Rotate(attributes.GetRoll() * M_PI / 180.0f);
			if (m_mirrorHorizontally) { m.Scale(-1, 1); }
			m.Translate(-rect.X - rect.Width / 2, -rect.Y - rect.Height / 2);
			gc->ConcatTransform(m);

			if (!text.IsEmpty())
			{
				double textWidth, textHeight, descent, externalLeading;
				gc->GetTextExtent(text, &textWidth, &textHeight, &descent, &externalLeading);
				float fx = rect.X + (rect.Width - textWidth) / 2.0f;
				float fy = rect.Y + rect.Height;
				gc->DrawText(text, fx, fy, gc->CreateBrush(livenessBrush));
			}

			gc->SetTransform(oldM);
			if (m_mirrorHorizontally)
			{
				gc->Translate(m_bitmap.GetWidth(), 0);
				gc->Scale(-1, 1);
			}

			float yaw = attributes.GetYaw();
			float targetYaw = attributes.GetLivenessTargetYaw();
			int imageWidth = m_bitmap.GetWidth();
			float width = (float)imageWidth / 4.0f;
			float height = (float)width / 8.0f;
			float x = m_bitmap.GetHeight() - height * 2.5f;

			if (rotateYaw)
			{
				wxPoint center;
				wxRect playArea(1.5f * width, x, width, height);
				gc->SetBrush(wxNullBrush);
				gc->DrawRectangle(playArea.x, playArea.y, playArea.width, playArea.height);
				gc->SetBrush(livenessBrush);
				if (!blink)
				{
					wxGraphicsPath arrow = CreateArrowPath(gc);
					PreparePath(gc, arrow, yaw, playArea, targetYaw < yaw);
					gc->DrawPath(arrow);

					wxGraphicsPath target = CreateTargetPath(gc);
					center = PreparePath(gc, target, targetYaw, playArea, false);
					gc->DrawPath(target);
				}
				else
				{
					wxGraphicsPath blink = CreateBlinkPath(gc);
					center = PreparePath(gc, blink, yaw, playArea, targetYaw < yaw);
					gc->DrawPath(blink);
				}

				gc->SetBrush(wxNullBrush);
				text = blink ? wxT("Blink") : wxT("Turn here");
				double textWidth, textHeight, descent, externalLeading;
				gc->GetTextExtent(text, &textWidth, &textHeight, &descent, &externalLeading);
				float fx = center.x - textWidth / 2.0f;
				float fy = center.y - textHeight;
				gc->DrawText(text, fx, fy, gc->CreateBrush(livenessBrush));
			}
			gc->SetTransform(oldM);
		}
	}
#else
	void DrawAttributes(wxDC & dc, const ::Neurotec::Biometrics::NLAttributes & attributes, const wxString& faceNumber, const wxString& faceConfidence)
	{
		::Neurotec::Biometrics::NLFeaturePoint item;

		wxPen pen(m_faceRectangleColor, m_faceRectangleWidth);
		wxBrush solidBrush(m_faceRectangleColor);
		dc.SetPen(pen);

		int half = m_baseFeatureWidth / 2;
		if(m_showBaseFeaturePoints)
		{
			dc.SetBrush(solidBrush);
			NArrayWrapper< ::Neurotec::Biometrics::NLFeaturePoint> points = attributes.GetFeaturePoints().GetAll();
			for(int i = 0; i < points.GetCount(); i++)
			{
				item = points[i];
				if(item.Confidence > 0)
				{
					dc.DrawEllipse(item.X - half, item.Y - half, m_baseFeatureWidth, m_baseFeatureWidth);
				}
			}
		}

		half = m_featureWidth / 2;
		if (m_showEyes)
		{
			::Neurotec::Biometrics::NLFeaturePoint left = attributes.GetLeftEyeCenter();
			::Neurotec::Biometrics::NLFeaturePoint right = attributes.GetRightEyeCenter();
			if ((IsConfidenceOk(left.Confidence) || IsConfidenceOk(right.Confidence)))
			{
				if(IsConfidenceOk(left.Confidence) && IsConfidenceOk(right.Confidence))
				{
					dc.DrawLine(left.X, left.Y, right.X, right.Y);
				}
				dc.SetBrush(solidBrush);
				if(IsConfidenceOk(left.Confidence))
				{
					dc.DrawEllipse(left.X - half, left.Y - half, m_featureWidth, m_featureWidth);
				}
				if(IsConfidenceOk(right.Confidence))
				{
					dc.DrawEllipse(right.X - half, right.Y - half, m_featureWidth, m_featureWidth);
				}
				dc.SetBrush(wxNullBrush);

				if(m_showEyesConfidence)
				{
					if(IsConfidenceOk(right.Confidence))
					{
						dc.DrawText(wxString::Format(wxT("%d"), right.Confidence), right.X - m_featureWidth, right.Y + m_featureWidth);
					}
					if(IsConfidenceOk(left.Confidence))
					{
						dc.DrawText(wxString::Format(wxT("%d"), left.Confidence), left.X - m_featureWidth, left.Y + m_featureWidth);
					}
				}
			}
		}
		if(m_showNose)
		{
			::Neurotec::Biometrics::NLFeaturePoint nose = attributes.GetNoseTip();
			if (IsConfidenceOk(nose.Confidence))
			{
				dc.SetBrush(solidBrush);
				dc.DrawEllipse(nose.X - half, nose.Y - half, m_featureWidth, m_featureWidth);

				if(m_showNoseConfidence)
				{
					dc.DrawText(wxString::Format(wxT("%d"), nose.Confidence), nose.X - m_featureWidth, nose.Y + m_featureWidth);
				}
				dc.SetBrush(wxNullBrush);
			}
		}
		if(m_showMouth)
		{
			::Neurotec::Biometrics::NLFeaturePoint mouth = attributes.GetMouthCenter();
			if (IsConfidenceOk(mouth.Confidence))
			{
				dc.SetBrush(solidBrush);
				dc.DrawEllipse(mouth.X - half, mouth.Y - half, m_featureWidth, m_featureWidth);
				dc.SetBrush(wxNullBrush);

				if(m_showMouthConfidence)
				{
					dc.DrawText(wxString::Format(wxT("%d"), mouth.Confidence), mouth.X - m_featureWidth, mouth.Y + m_featureWidth);
				}
			}
		}

		dc.SetPen(wxNullPen);

		::Neurotec::Geometry::NRect rect = attributes.GetBoundingRect();
		if (rect.Width > 0 && rect.Height > 0)
		{
			wxPen penGreen(m_faceRectangleColor, m_faceRectangleWidth);
			penGreen.SetCap(wxCAP_PROJECTING);
			penGreen.SetJoin(wxJOIN_MITER);
			dc.SetPen(penGreen);
			double angle = (double)attributes.GetRoll() * M_PI / 180.0;
			double pt1x, pt1y;
			RotatePointAt(rect.X, rect.Y,
				(rect.X * 2 + rect.Width) / 2,
				(rect.Y * 2 + rect.Height) / 2,
				angle, &pt1x, &pt1y);
			double pt2x, pt2y;
			RotatePointAt(rect.X + rect.Width,
				rect.Y,
				(rect.X * 2 + rect.Width) / 2,
				(rect.Y * 2 + rect.Height) / 2,
				angle, &pt2x, &pt2y);
			double pt3x, pt3y;
			RotatePointAt(rect.X + rect.Width,
				rect.Y + rect.Height,
				(rect.X * 2 + rect.Width) / 2,
				(rect.Y * 2 + rect.Height) / 2,
				angle, &pt3x, &pt3y);
			double pt4x, pt4y;
			RotatePointAt(rect.X,
				rect.Y + rect.Height,
				(rect.X * 2 + rect.Width) / 2,
				(rect.Y * 2 + rect.Height) / 2,
				angle, &pt4x, &pt4y);
			wxPoint points[] ={ wxPoint((int)pt1x, (int)pt1y),
				wxPoint((int)pt2x, (int)pt2y),
				wxPoint((int)pt3x, (int)pt3y),
				wxPoint((int)pt4x, (int)pt4y),
				wxPoint((int)pt1x, (int)pt1y) };
			dc.DrawLines(5, points, 0, 0);
			dc.SetPen(wxNullPen);

			dc.SetTextForeground(m_faceRectangleColor);
			if (!faceConfidence.IsEmpty())
			{
				dc.DrawRotatedText(faceConfidence, (wxCoord)pt4x, (wxCoord)pt4y, (double) -attributes.GetRoll());
			}

			if (m_showGender || m_showExpression || m_showProperties || m_showEmotions)
			{
				wxString value = GetDetailsString(attributes);
				if (value != wxEmptyString)
				{
					wxSize sz = dc.GetTextExtent(value);
					double faceWidth = rect.Width;
					int offset = sz.GetWidth() > faceWidth ? (int)((sz.GetWidth() - faceWidth) / 2) : 0;
					dc.SetTextForeground(m_faceRectangleColor);
					dc.DrawRotatedText(value, (wxCoord)(pt1x - offset), (wxCoord)pt1y - sz.GetHeight() - 1, (double) -attributes.GetRoll());
				}
			}
			if (!faceNumber.IsEmpty())
			{
				wxSize sz = dc.GetTextExtent(faceNumber);
				dc.DrawRotatedText(faceNumber, rect.Width - sz.GetWidth(), rect.Height + 3, (double) -attributes.GetRoll());
			}
		}
	}
#endif

	wxString GetDetailsString( ::Neurotec::Biometrics::NLAttributes attributes)
	{
		wxString value = wxEmptyString;
		if (m_showGender && IsConfidenceOk(attributes.GetGenderConfidence()))
		{
			value = NEnum::ToString(NBiometricTypes::NGenderNativeTypeOf(), attributes.GetGender());
			if(m_showGenderConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetGenderConfidence()));
		}
		if (m_showAge && attributes.GetAge() < 254)
		{
			if (value != wxEmptyString) value.Append(wxT(", "));
			value.Append(wxString::Format(wxT("Age: %d"), attributes.GetAge()));
		}
		if (m_showExpression && IsExpressionOk(attributes.GetExpression()) && IsConfidenceOk(attributes.GetExpressionConfidence()))
		{
			if (value != wxEmptyString) value.Append(wxT(", "));
			value.Append(NEnum::ToString(NBiometricTypes::NLExpressionNativeTypeOf(), attributes.GetExpression()));
			if (m_showExpressionConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetExpressionConfidence()));
		}
		if (m_showProperties)
		{
			if (IsConfidenceOk(attributes.GetGlassesConfidence()) && IsPropertySet(attributes.GetProperties(), nlpGlasses))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.append(wxT("Glasses"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetGlassesConfidence()));
			}
			if (IsConfidenceOk(attributes.GetMouthOpenConfidence()) && IsPropertySet(attributes.GetProperties(), nlpMouthOpen))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.append(wxT("Mouth Open"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetMouthOpenConfidence()));
			}
			if (IsConfidenceOk(attributes.GetBlinkConfidence()) && IsPropertySet(attributes.GetProperties(), nlpBlink))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Blink"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetBlinkConfidence()));
			}
			if (IsConfidenceOk(attributes.GetDarkGlassesConfidence()) && IsPropertySet(attributes.GetProperties(), nlpDarkGlasses))
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(wxT("Dark Glasses"));
				if (m_showPropertiesConfidence) value.Append(wxString::Format(wxT("(%d)"), attributes.GetDarkGlassesConfidence()));
			}
		}
		if (m_showEmotions)
		{
			NByte maxConfidence = 0;
			NByte confidence = 0;
			wxString emotionString = wxEmptyString;

			confidence = attributes.GetEmotionNeutralConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Neutral");
			}
			confidence = attributes.GetEmotionAngerConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Anger");
			}
			confidence = attributes.GetEmotionDisgustConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Disgust");
			}
			confidence = attributes.GetEmotionFearConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Fear");
			}
			confidence = attributes.GetEmotionHappinessConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Happiness");
			}
			confidence = attributes.GetEmotionSadnessConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Sadness");
			}
			confidence = attributes.GetEmotionSurpriseConfidence();
			if (IsConfidenceOk(confidence) && confidence > maxConfidence)
			{
				maxConfidence = confidence;
				emotionString = wxT("Surprise");
			}

			if (emotionString != wxEmptyString)
			{
				if (value != wxEmptyString) value.Append(wxT(", "));
				value.Append(emotionString);
				if (m_showEmotionConfidence) value.Append(wxString::Format(wxT("(%d)"), maxConfidence));
			}
		}
		return value;
	}
	static bool IsExpressionOk(NLExpression expression) { return expression == nleSmile; }
	static bool IsConfidenceOk(NByte confidence) { return confidence > 0 && confidence <= 100; }
	static bool IsPropertySet(NLProperties value, NLProperties flag) { return (value & flag) == flag; }
	void UpdateFps()
	{
		wxLongLong currentTime = ::wxGetLocalTimeMillis();
		float previousFps = m_currentFps;
		m_currentFps = 0.0f;
		if (currentTime - m_lastTime > 5000)
		{
			m_frameCount = 0;
			m_firstTime = currentTime;
		}
		else
		{
			m_frameCount++;
			if (m_frameCount == MAX_FPS_ENTRIES)
			{
				m_currentFps = (float)((m_frameCount.ToDouble() * 1000.0) / (double)(currentTime - m_firstTime).ToDouble());
			}
			else if (m_frameCount > MAX_FPS_ENTRIES)
			{
				float frameFps = (float)(1000.0 / (currentTime - m_lastTime).ToDouble());
				const float newFpsWeight = (float)1.0f / (float)MAX_FPS_ENTRIES;
				m_currentFps = previousFps * (1.0f - newFpsWeight) + frameFps * newFpsWeight;
			}
		}
		m_lastTime = currentTime;
	}
protected:
	wxBitmap m_bitmap;
	wxArrayString m_faceIds;
	wxColour m_faceRectangleColor;
	wxColour m_livenessItemsColor;
	int m_faceRectangleWidth;
	wxLongLong m_lastTime;
	wxLongLong m_firstTime;
	wxLongLong m_frameCount;
	float m_currentFps;
	bool m_showFps;
	bool m_showEyes;
	bool m_showNose;
	bool m_showMouth;
	bool m_showNoseConfidence;
	bool m_showEyesConfidence;
	bool m_showFaceConfidence;
	bool m_showMouthConfidence;
	bool m_showGender;
	bool m_showGenderConfidence;
	bool m_showExpression;
	bool m_showExpressionConfidence;
	bool m_showProperties;
	bool m_showEmotions;
	bool m_showEmotionConfidence;
	bool m_showPropertiesConfidence;
	bool m_showBaseFeaturePoints;
	bool m_mirrorHorizontally;
	bool m_showAge;
	int m_featureWidth;
	int m_baseFeatureWidth;
	::Neurotec::Biometrics::NFace m_face;
	std::vector< ::Neurotec::NObject> m_attributes;
};

}}}

#endif // !WX_NFACE_VIEW_HPP_INCLUDED
