#pragma once

namespace baro {
//////////////////////////////////////////////////////////////////////////////////////////
class BN23_CLASS GradientRect final : public CheckPointer
{
public:
	explicit GradientRect(void);
	explicit GradientRect(Gdiplus::Rect rcArea, Gdiplus::Color color = Gdiplus::Color::Transparent);
	~GradientRect();

private :
	Gdiplus::Rect	m_rcArea;
	Gdiplus::Color	m_colorBk;
	
	std::map<int, Gdiplus::Color>	m_mPointColor;

public :
	void Reset(Gdiplus::Rect rcArea, Gdiplus::Color color = Gdiplus::Color::Transparent);
	bool Add(int iPoint, Gdiplus::Color color);
	bool Update(int iPoint, Gdiplus::Color color);
	bool Remove(int iPoint);

	void Draw(Gdiplus::Graphics &g);
	void Draw(Gdiplus::Graphics &g, Gdiplus::Rect rcArea);
};
//////////////////////////////////////////////////////////////////////////////////////////
};
