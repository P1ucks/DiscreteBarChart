#pragma once


#include "pch.h"
#include <unordered_map>
#include <algorithm> // For std::max
#include <string>

class DiscreteBarChart
{
public:
	DiscreteBarChart();
	~DiscreteBarChart();
	void create(CDC* pDC, CRect clientRect);
	void Draw(std::unordered_map<std::string, int>& data);
// ���ó�Ա����
public:
	void setsortByValue(bool b);
	void setDrawValueOnTop(bool b);
	void setDrawYLine(bool b);
	void setDrawXLine(bool b);
	void setBackgroundColor(int r, int g, int b);
	void setBarColor(int r, int g, int b);
	void setValueColor(int r, int g, int b);
	void setaxisScaleColor(int r, int g, int b);
	void setTitleColor(int r, int g, int b);
	void setAxisLegendColor(int r, int g, int b);
	void setValueFont(CFont& font);
	void setAxisFont(CFont& font);
	void setTitleFont(CFont& font);
	void setTitle(char* title);
	void setYAxisNum(int yAxisNum);
	void setYAxisLegend(char* yAxisLabel);
	void setXAxisLegend(char* xAxisLabel);
private:
	void ComputeYAxisNum();
private:
	CDC* pDC;
	CRect backgroundRect,clientRect;
	CFont axisFont, valueFont, titleFont, axisLabelFont;
	CString title, yAxisLegend, xAxisLegend;
	// ����
	bool sortByValue;
	// �����ϱ�
	bool drawValueOnTop;
	// �Ƿ񻭺�/����
	bool drawYLine, drawXLine;
	// ������ɫ 
	int backgroundColor[3];
	// ������ɫ
	int barColor[3];
	// ������ɫ
	int valueColor[3];
	// ��̶���ɫ
	int axisScaleColor[3];
	// ͼ����ɫ
	int axisLegendColor[3];
	// ͼ������ɫ
	int titleColor[3];
	// y��̶���
	int yAxisNum;
};