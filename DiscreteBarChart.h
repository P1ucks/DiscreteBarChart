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
// 设置成员变量
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
	// 排序
	bool sortByValue;
	// 数据上标
	bool drawValueOnTop;
	// 是否画横/竖线
	bool drawYLine, drawXLine;
	// 背景颜色 
	int backgroundColor[3];
	// 柱子颜色
	int barColor[3];
	// 文字颜色
	int valueColor[3];
	// 轴刻度颜色
	int axisScaleColor[3];
	// 图例颜色
	int axisLegendColor[3];
	// 图表名颜色
	int titleColor[3];
	// y轴刻度数
	int yAxisNum;
};