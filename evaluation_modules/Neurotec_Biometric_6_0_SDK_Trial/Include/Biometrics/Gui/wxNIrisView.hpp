#ifndef WX_NIRISVIEW_HPP_INCLUDED
#define WX_NIRISVIEW_HPP_INCLUDED

#include <Images/NImages.hpp>
#include <Gui/wxNView.hpp>

#include <vector>

namespace Neurotec { namespace Biometrics { namespace Gui
{

wxDECLARE_EVENT(wxEVT_IRIS_PROPERTY_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_IRIS_OBJECTS_COLLECTION_CHANGED, wxCommandEvent);

class wxNIrisView: public Neurotec::Gui::wxNView
{
private:
	wxBitmap m_bitmap;
	wxImage m_image;

	int m_outerBoundaryWidth;
	int m_innerBoundaryWidth;
	wxColour m_outerBoundaryColor;
	wxColour m_innerBoundaryColor;

	NIris m_iris;
	::std::vector<NEAttributes> m_attributes;

public:
	wxNIrisView(wxWindow *parent, wxWindowID winid = wxID_ANY)
		: wxNView(parent, winid)
	{
		m_outerBoundaryColor = wxColour(0, 255, 0);
		m_innerBoundaryColor = wxColour(255, 0, 0);
		m_outerBoundaryWidth = 2;
		m_innerBoundaryWidth = 2;

		this->Bind(wxEVT_IRIS_PROPERTY_CHANGED, &wxNIrisView::UpdateIrisView, this);
		this->Bind(wxEVT_IRIS_OBJECTS_COLLECTION_CHANGED, &wxNIrisView::UpdateAttributes, this);

		Clear();
	}

	~wxNIrisView()
	{
	}

	void SetIris(NIris iris)
	{
		if (m_iris.GetHandle() != NULL)
		{
			UnsubscribeFromIrisEvents();
			m_iris = NIris(NULL);
		}

		Clear();

		if (iris.GetHandle() != NULL)
		{
			m_iris = iris;
			SubscribeToIrisEvents();

			::Neurotec::Images::NImage image = m_iris.GetImage();
			if (image.GetHandle())
			{
				wxCommandEvent event(wxEVT_IRIS_PROPERTY_CHANGED);
				event.SetEventObject(new wxImage(image.ToBitmap()));
				wxPostEvent(this, event);
			}
		}
	}

	NIris GetIris()
	{
		return m_iris;
	}

	void SetOuterBoundaryColor(const wxColour & value)
	{
		m_outerBoundaryColor = value;
	}

	const wxColour & GetOuterBoundaryColor()
	{
		return m_outerBoundaryColor;
	}

	void SetOuterBoundaryWidth(int value)
	{
		m_outerBoundaryWidth = value;
	}

	int GetOuterBoundaryWidth()
	{
		return m_outerBoundaryWidth;
	}

	void SetInnerBoundaryWidth(int value)
	{
		m_innerBoundaryWidth = value;
	}

	int GetInnerBoundaryWidth()
	{
		return m_innerBoundaryWidth;
	}

	void SetInnerBoundaryColor(const wxColour & value)
	{
		m_innerBoundaryColor = value;
	}

	wxColour GetInnerBoundaryColor()
	{
		return m_innerBoundaryColor;
	}

#if wxUSE_GRAPHICS_CONTEXT == 1
	virtual void OnDraw(wxGraphicsContext *gc)
	{
		if (m_bitmap.GetRefData())
		{
			gc->DrawBitmap(m_bitmap, 0, 0, m_bitmap.GetWidth(), m_bitmap.GetHeight());
		}

		if (m_iris.GetHandle() != NULL)
		{
			NIris::ObjectCollection attributes = m_iris.GetObjects();
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				NEAttributes attribute = attributes.Get(i);
				if (attribute.IsInnerBoundaryAvailable())
				{
					wxPen innerBoundaryPen(m_innerBoundaryColor, m_innerBoundaryWidth);
					gc->SetPen(innerBoundaryPen);
					wxGraphicsPath innerBoundaryPath = gc->CreatePath();
					NEAttributes::InnerBoundaryPointCollection innerCollection = attribute.GetInnerBoundaryPoints();
					Neurotec::Geometry::NPoint startPoint = innerCollection.Get(innerCollection.GetCount() - 1);

					innerBoundaryPath.MoveToPoint(startPoint.X, startPoint.Y);
					for (int j = 0; j < innerCollection.GetCount(); j++)
					{
						Neurotec::Geometry::NPoint point = innerCollection.Get(j);
						innerBoundaryPath.AddLineToPoint(point.X, point.Y);
					}

					gc->StrokePath(innerBoundaryPath);
					gc->SetPen(wxNullPen);
				}

				if (attribute.IsOuterBoundaryAvailable())
				{
					wxPen outerBoundaryPen(m_outerBoundaryColor, m_outerBoundaryWidth);
					gc->SetPen(outerBoundaryPen);
					wxGraphicsPath outerBoundaryPath = gc->CreatePath();
					NEAttributes::OuterBoundaryPointCollection outerCollection = attribute.GetOuterBoundaryPoints();
					Neurotec::Geometry::NPoint startPoint = outerCollection.Get(outerCollection.GetCount() - 1);

					outerBoundaryPath.MoveToPoint(startPoint.X, startPoint.Y);
					for (int j = 0; j < outerCollection.GetCount(); j++)
					{
						Neurotec::Geometry::NPoint point = outerCollection.Get(j);
						outerBoundaryPath.AddLineToPoint(point.X, point.Y);
					}

					gc->StrokePath(outerBoundaryPath);
					gc->SetPen(wxNullPen);
				}
			}
		}
	}
#else
	virtual void OnDraw(wxDC &dc)
	{
		if (m_bitmap.GetRefData())
		{
			dc.DrawBitmap(m_bitmap, 0, 0, false);
		}
		if (m_iris.GetHandle() != NULL)
		{
			NIris::ObjectCollection attributes = m_iris.GetObjects();
			for (int i = 0; i < attributes.GetCount(); i++)
			{
				NEAttributes attribute = attributes.Get(i);
				if (attribute.IsInnerBoundaryAvailable())
				{
					wxPen innerBoundaryPen(m_innerBoundaryColor, m_innerBoundaryWidth);
					dc.SetPen(innerBoundaryPen);
					NEAttributes::InnerBoundaryPointCollection innerCollection = attribute.GetInnerBoundaryPoints();

					Neurotec::Geometry::NPoint pointFirst = innerCollection.Get(0);
					Neurotec::Geometry::NPoint pointLast = innerCollection.Get(innerCollection.GetCount() - 1);

					for (int j = 1; j < innerCollection.GetCount(); j++)
					{
						Neurotec::Geometry::NPoint pointA = innerCollection.Get(j - 1);
						Neurotec::Geometry::NPoint pointB = innerCollection.Get(j);

						dc.DrawLine(wxPoint(pointA.X, pointA.Y), wxPoint(pointB.X, pointB.Y));
					}

					dc.DrawLine(wxPoint(pointLast.X, pointLast.Y), wxPoint(pointFirst.X, pointFirst.Y));
					dc.SetPen(wxNullPen);
				}
				if (attribute.IsOuterBoundaryAvailable())
				{
					wxPen outerBoundaryPen(m_outerBoundaryColor, m_outerBoundaryWidth);
					dc.SetPen(outerBoundaryPen);
					NEAttributes::OuterBoundaryPointCollection outerCollection = attribute.GetOuterBoundaryPoints();

					Neurotec::Geometry::NPoint pointFirst = outerCollection.Get(0);
					Neurotec::Geometry::NPoint pointLast = outerCollection.Get(outerCollection.GetCount() - 1);

					for (int j = 1; j < outerCollection.GetCount(); j++)
					{
						Neurotec::Geometry::NPoint pointA = outerCollection.Get(j - 1);
						Neurotec::Geometry::NPoint pointB = outerCollection.Get(j);

						dc.DrawLine(wxPoint(pointA.X, pointA.Y), wxPoint(pointB.X, pointB.Y));
					}

					dc.DrawLine(wxPoint(pointLast.X, pointLast.Y), wxPoint(pointFirst.X, pointFirst.Y));
					dc.SetPen(wxNullPen);
				}
			}
		}
	}
#endif

private:
	void UnsubscribeFromIrisEvents()
	{
		if (m_iris.GetHandle() != NULL)
		{
			m_iris.RemovePropertyChangedCallback(&wxNIrisView::IrisPropertyChangedCallback, this);
			m_iris.GetObjects().RemoveCollectionChangedCallback(&wxNIrisView::IrisObjectsCollectionChangedCallback, this);
		}
	}

	void SubscribeToIrisEvents()
	{
		if (m_iris.GetHandle() != NULL)
		{
			m_iris.GetObjects().AddCollectionChangedCallback(&wxNIrisView::IrisObjectsCollectionChangedCallback, this);
			m_iris.AddPropertyChangedCallback(&wxNIrisView::IrisPropertyChangedCallback, this);
		}
	}

	void UpdateIrisView(wxCommandEvent &event)
	{
#ifdef N_CPP11
		typedef std::unique_ptr<wxImage> SmartPtrImage;
#else
		typedef std::auto_ptr<wxImage> SmartPtrImage;
#endif
		SmartPtrImage image(dynamic_cast<wxImage*>(event.GetEventObject()));
		if (image.get())
		{
			m_bitmap = wxBitmap(*(image.get()));
			SetViewSize(m_bitmap.GetWidth(), m_bitmap.GetHeight());
		}
		else Clear();

		Refresh(false);
	}

	void UpdateAttributes(wxCommandEvent &event)
	{
#ifdef N_CPP11
		typedef std::unique_ptr<NArrayWrapper<NEAttributes> > SmartPtrAttributes;
#else
		typedef std::auto_ptr<NArrayWrapper<NEAttributes> > SmartPtrAttributes;
#endif
		SmartPtrAttributes attributes((NArrayWrapper<NEAttributes> *)event.GetClientData());
		switch(event.GetInt())
		{
		case ::Neurotec::Collections::nccaAdd:
			OnAttributesAdded(this, *(attributes.get()));
			break;
		case ::Neurotec::Collections::nccaRemove:
			OnAttributesRemoved(this, *(attributes.get()));
			break;
		case ::Neurotec::Collections::nccaReset:
			OnAttributesReset(this);
			break;
		default: break;
		};

		Refresh(false);
	}

private:
	void Clear()
	{
		m_image = wxImage();
		m_bitmap = wxBitmap();
		SetViewSize(1, 1);
		Refresh(false);
	}

	static void OnAttributesAdded(wxNIrisView *view, NArrayWrapper<NEAttributes> attributes)
	{
		for (int i = 0; i < attributes.GetCount(); i++)
		{
			view->m_attributes.push_back(attributes[i]);

			NEAttributes::InnerBoundaryPointCollection innerBoundaryPointCollection =
				attributes[i].GetInnerBoundaryPoints();

			NEAttributes::OuterBoundaryPointCollection outerBoundaryPointCollection =
				attributes[i].GetOuterBoundaryPoints();

			innerBoundaryPointCollection.AddCollectionChangedCallback(&wxNIrisView::OnIrisBoundaryPointsCollectionChanged, view);
			outerBoundaryPointCollection.AddCollectionChangedCallback(&wxNIrisView::OnIrisBoundaryPointsCollectionChanged, view);
		}
	}

	static void OnAttributesRemoved(wxNIrisView *view, NArrayWrapper<NEAttributes> attributes)
	{
		for (int i = 0; i < attributes.GetCount(); i++)
		{
			for (unsigned int j = 0; j < view->m_attributes.size(); j++)
			{
				if (view->m_attributes[j].Equals(attributes[i]))
				{
					NEAttributes::InnerBoundaryPointCollection innerBoundaryPointCollection =
						view->m_attributes[j].GetInnerBoundaryPoints();

					NEAttributes::OuterBoundaryPointCollection outerBoundaryPointCollection =
						view->m_attributes[j].GetOuterBoundaryPoints();

					innerBoundaryPointCollection.RemoveCollectionChangedCallback(&wxNIrisView::OnIrisBoundaryPointsCollectionChanged, view);
					outerBoundaryPointCollection.RemoveCollectionChangedCallback(&wxNIrisView::OnIrisBoundaryPointsCollectionChanged, view);

					view->m_attributes.erase(view->m_attributes.begin() + j);
					break;
				}
			}
		}
	}

	static void OnAttributesReset(wxNIrisView *view)
	{
		for (unsigned int i = 0; i < view->m_attributes.size(); i++)
		{
			NEAttributes::InnerBoundaryPointCollection innerBoundaryPointCollection =
				view->m_attributes[i].GetInnerBoundaryPoints();

			NEAttributes::OuterBoundaryPointCollection outerBoundaryPointCollection =
				view->m_attributes[i].GetOuterBoundaryPoints();

			innerBoundaryPointCollection.RemoveCollectionChangedCallback(&wxNIrisView::OnIrisBoundaryPointsCollectionChanged, view);
			outerBoundaryPointCollection.RemoveCollectionChangedCallback(&wxNIrisView::OnIrisBoundaryPointsCollectionChanged, view);
		}

		view->m_attributes.clear();
	}

	static void OnIrisBoundaryPointsCollectionChanged(Neurotec::Collections::CollectionChangedEventArgs<Neurotec::Geometry::NPoint> args)
	{
		wxNIrisView *view = static_cast<wxNIrisView *>(args.GetParam());
		view->Refresh(false);
	}

	static void IrisObjectsCollectionChangedCallback(::Neurotec::Collections::CollectionChangedEventArgs<NEAttributes> args)
	{
		NArrayWrapper<NEAttributes> * pAttributes = NULL;
		NArrayWrapper<NEAttributes> attributes(0);
		NCollectionChangedAction action = args.GetAction();
		NBool postEvent = false;

		switch(action)
		{
		case ::Neurotec::Collections::nccaAdd:
			attributes = args.GetNewItems();
			pAttributes = new NArrayWrapper<NEAttributes>(attributes.begin(), attributes.end());
			postEvent = true;
			break;
		case ::Neurotec::Collections::nccaRemove:
			attributes = args.GetOldItems();
			pAttributes = new NArrayWrapper<NEAttributes>(attributes.begin(), attributes.end());
			postEvent = true;
			break;
		case ::Neurotec::Collections::nccaReset:
			postEvent = true;
			break;
		default: break;
		};

		if (postEvent)
		{
			wxNIrisView * view = static_cast<wxNIrisView *>(args.GetParam());
			wxCommandEvent event(wxEVT_IRIS_OBJECTS_COLLECTION_CHANGED);
			event.SetInt(action);
			event.SetClientData(pAttributes);
			wxPostEvent(view, event);
		}
	}

	static void IrisPropertyChangedCallback(NIris::PropertyChangedEventArgs args)
	{
		wxNIrisView *view = NULL;
		NIris iris = args.GetObject<NIris>();

		wxCommandEvent event(wxEVT_IRIS_PROPERTY_CHANGED);

		if (args.GetPropertyName() == N_T("Image"))
		{
			view = static_cast<wxNIrisView *>(args.GetParam());
			::Neurotec::Images::NImage irisImage = iris.GetImage();
			if (irisImage.GetHandle())
			{
				event.SetEventObject(new wxImage(irisImage.ToBitmap()));
			}
			wxPostEvent(view, event);
		}
	}
};

}}}

#endif // !WX_NIRISVIEW_HPP_INCLUDED
