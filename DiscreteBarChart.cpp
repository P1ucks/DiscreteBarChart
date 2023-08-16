#include "pch.h"
#include"DiscreteBarChart.h"


bool compareByY(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second > b.second; }

DiscreteBarChart::DiscreteBarChart()
{
	sortByValue = false;
	drawValueOnTop = true;
	drawYLine = true;
	drawXLine = true;
	// 白色背景
	backgroundColor[0] = 255; backgroundColor[1] = 255; backgroundColor[2] = 255;
	// 蓝色柱子
	barColor[0] = 0; barColor[1] = 0; barColor[2] = 255;
	// 黑色文字
	valueColor[0] = 0; valueColor[1] = 0; valueColor[2] = 0;
	// 黑色表名
	titleColor[0] = 0; titleColor[1] = 0; titleColor[2] = 0;
	// 黑色图例
	axisLegendColor[0] = 0; axisLegendColor[1] = 0; axisLegendColor[2] = 0;

	axisFont.CreateFont(
		16,                     // 字体高度
		0,                      // 字体宽度
		0,                      // 字体倾斜角度
		0,                      // 字体下划线
		FW_NORMAL,              // 字体粗细
		FALSE,                  // 斜体
		FALSE,                  // 下划线
		0,                      // 删除线
		DEFAULT_CHARSET,        // 字符集
		OUT_DEFAULT_PRECIS,     // 输出精度
		CLIP_DEFAULT_PRECIS,    // 剪辑精度
		DEFAULT_QUALITY,        // 字体质量
		DEFAULT_PITCH | FF_DONTCARE, // 字体间距和字体族
		_T("Calibri")             // 字体名称
	);
	valueFont.CreateFont(
		16,                     // 字体高度
		0,                      // 字体宽度
		0,                      // 字体倾斜角度
		0,                      // 字体下划线
		FW_NORMAL,              // 字体粗细
		FALSE,                  // 斜体
		FALSE,                  // 下划线
		0,                      // 删除线
		DEFAULT_CHARSET,        // 字符集
		OUT_DEFAULT_PRECIS,     // 输出精度
		CLIP_DEFAULT_PRECIS,    // 剪辑精度
		DEFAULT_QUALITY,        // 字体质量
		DEFAULT_PITCH | FF_DONTCARE, // 字体间距和字体族
		_T("Arial")             // 字体名称
	);
	titleFont.CreateFont(
		20,                     // 字体高度
		0,                      // 字体宽度
		0,                      // 字体倾斜角度
		TRUE,                      // 字体下划线
		FW_NORMAL,              // 字体粗细
		FALSE,                  // 斜体
		TRUE,                  // 下划线
		0,                      // 删除线
		DEFAULT_CHARSET,        // 字符集
		OUT_DEFAULT_PRECIS,     // 输出精度
		CLIP_DEFAULT_PRECIS,    // 剪辑精度
		DEFAULT_QUALITY,        // 字体质量
		DEFAULT_PITCH | FF_DONTCARE, // 字体间距和字体族
		_T("SimSun")             // 字体名称
	);
	axisLabelFont.CreateFont(
		14,                     // 字体高度
		0,                      // 字体宽度
		0,                      // 字体倾斜角度
		0,                      // 字体下划线
		FW_NORMAL,              // 字体粗细
		FALSE,                  // 斜体
		0,                  // 下划线
		0,                      // 删除线
		DEFAULT_CHARSET,        // 字符集
		OUT_DEFAULT_PRECIS,     // 输出精度
		CLIP_DEFAULT_PRECIS,    // 剪辑精度
		DEFAULT_QUALITY,        // 字体质量
		DEFAULT_PITCH | FF_DONTCARE, // 字体间距和字体族
		_T("SimSun")             // 字体名称
	);
}

DiscreteBarChart::~DiscreteBarChart()
{

}

void DiscreteBarChart::create(CDC* pDC, CRect cr)
{
	DiscreteBarChart::pDC = pDC;
	DiscreteBarChart::backgroundRect = cr;
	cr.top = cr.top + 60;
	cr.bottom = cr.bottom;
	cr.left = cr.left + 10;
	cr.right = cr.right-30;
	DiscreteBarChart::clientRect = cr;
	ComputeYAxisNum();
}

void DiscreteBarChart::Draw(std::unordered_map<std::string, int>& data)
{
	pDC->FillSolidRect(&backgroundRect, RGB(backgroundColor[0], backgroundColor[1], backgroundColor[2])); // Fill background with white color

	// 绘制表名
	CFont* pOldFont = pDC->SelectObject(&titleFont);
	pDC->SetTextColor(RGB(axisScaleColor[0], axisScaleColor[1], axisScaleColor[2]));
	pDC->SetBkMode(TRANSPARENT); // Set background mode to transparent
	CSize titleSize = pDC->GetTextExtent(title);
	pDC->TextOut(backgroundRect.Width()/2-titleSize.cx/2, 10, title); 

	// 还原字体颜色
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(RGB(0, 0, 0));

	// y轴图例
	pOldFont = pDC->SelectObject(&axisLabelFont);
	pDC->SetTextColor(RGB(axisLegendColor[0], axisLegendColor[1], axisLegendColor[2]));
	pDC->SetBkMode(TRANSPARENT); // Set background mode to transparent
	CSize yAxisLabelSize = pDC->GetTextExtent(yAxisLegend);
	int yLabelPos = clientRect.Height() / 2 + 20 - yAxisLabelSize.cx/2;
	yAxisLabelSize.cx = yAxisLabelSize.cx / yAxisLegend.GetLength()+10;

	for (int i = 0; i < yAxisLegend.GetLength(); i++) {
		CString character = yAxisLegend.Mid(i, 1);
		pDC->TextOutW(8, yLabelPos, character);
		yLabelPos += 15; // 增加 Y 坐标，使文字竖向排列
	}
	// x轴图例
	int xLabelPos = clientRect.Width() / 2;
	CSize xAxisLabelSize = pDC->GetTextExtent(yAxisLegend);
	pDC->TextOutW(xLabelPos, clientRect.bottom-xAxisLabelSize.cy-5, xAxisLegend);

	// 还原字体颜色
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(RGB(0, 0, 0));

	int dataCount = data.size();
	if (dataCount > 0)
	{
		// Sort the data by Y values in descending order
		std::vector<std::pair<std::string, int>> sortedData(data.begin(), data.end());
		std::vector<std::pair<std::string, int>> rawData=sortedData;
		std::sort(sortedData.begin(), sortedData.end(), compareByY);

		int maxY = sortedData[0].second; // The largest Y value after sorting
		if (!sortByValue) {
			sortedData = rawData;
		}
		// Calculate the scaling factors for X and Y axis
		double xScale = static_cast<double>(clientRect.Width() - 80) / dataCount; // Leave some margin for Y-axis labels and move X-axis a bit right
		double yScale = maxY != 0 ? static_cast<double>(clientRect.Height() - 25 - (xAxisLabelSize.cy + 5)) / maxY : 0; // Leave some margin for X-axis labels

		CString maxValue;
		maxValue.Format(_T("%d"), maxY);
		CSize xLabelSize = pDC->GetTextExtent(maxValue);

		int xAxisMargin = xLabelSize.cx + 10 + yAxisLabelSize.cx; // Margin for X-axis labels
		int yAxisMargin = 23 + (xAxisLabelSize.cy + 5); // Margin for Y-axis labels

		int maxYLabel = maxY;

		// 绘制坐标轴线
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 创建一个宽度为2的实线画笔，颜色为黑色
		CPen* pOldPen = pDC->SelectObject(&pen); // 选择新画笔，保存旧画笔
		// Draw X-axis
		int xAxisY = clientRect.bottom - yAxisMargin;
		pDC->MoveTo(xAxisMargin, xAxisY);
		pDC->LineTo(clientRect.right, xAxisY);

		// Draw Y-axis
		int yAxisX = xAxisMargin;
		pDC->MoveTo(yAxisX, clientRect.top-20);
		pDC->LineTo(yAxisX, clientRect.bottom - yAxisMargin);

		// 恢复旧画笔
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();

		pDC->MoveTo(clientRect.right, 40);
		pDC->LineTo(clientRect.right, clientRect.bottom - yAxisMargin);

		pDC->MoveTo(xAxisMargin, 40);
		pDC->LineTo(clientRect.right, 40);
		

		// 画Y轴虚线和刻度值
		// Draw Y-axis labels and horizontal dashed lines
		// Y轴刻度数量
		int yLabelStep = maxYLabel / yAxisNum;
		for (int i = 0; i <= yAxisNum; i++)
		{
			CString yLabel;
			yLabel.Format(_T("%d"), i * yLabelStep);

			// 为了防止数据溢出，如果有需要可将long long改为int64_t进一步加大
			long long y2 = clientRect.Height() - yAxisMargin - 2;
			long long y1 = (i * y2 *yLabelStep);
			long long y = clientRect.bottom - yAxisMargin - y1 / maxYLabel;


			// Draw Y-axis label
			// 设置字体颜色
			CFont* pOldFont = pDC->SelectObject(&axisFont);
			pDC->SetTextColor(RGB(axisScaleColor[0], axisScaleColor[1], axisScaleColor[2]));
			pDC->SetBkMode(TRANSPARENT); // Set background mode to transparent
			pDC->TextOut( yAxisLabelSize.cx+7, y - 8, yLabel); // Draw Y-axis label
			// 还原字体颜色
			pDC->SelectObject(pOldFont);
			pDC->SetTextColor(RGB(0, 0, 0));

			// 画坐标刻度线
			pDC->MoveTo(yAxisX, y);
			pDC->LineTo(yAxisX-5, y);

			// Draw horizontal dashed line for each Y-axis label
			// 画Y轴虚线
			if (drawYLine) {
				CPen dashedPen(PS_DOT, 1, RGB(0, 0, 0)); // Create a dashed pen
				CPen* pOldPen = pDC->SelectObject(&dashedPen);
				pDC->MoveTo(yAxisX, y);
				pDC->LineTo(clientRect.right, y);
				pDC->SelectObject(pOldPen);
			}
		}
		
		int maxBarWidth = static_cast<int>(xScale * 0.4); // Maximum width for each bar (40% of the xScale)
		int barSpacing = static_cast<int>(xScale * 0.4); // Spacing between bars (40% of the xScale)

		int validDataCount = 0;
		for (const auto& pair : data)
		{
			if (pair.second != 0) // Check if Y value is not 0
			{
				validDataCount++;
			}
		}

		if (validDataCount > 0)
		{
			double validXScale = static_cast<double>(clientRect.Width() - 60 - (validDataCount - 1) * barSpacing) / validDataCount;
			int validIndex = 0;

			for (const auto& pair : sortedData)
			{
				if (pair.second != 0) // Check if Y value is not 0
				{
					int x = xAxisMargin + static_cast<int>(validIndex * (validXScale + barSpacing)) + 20; // Move X position a bit right
					int y = clientRect.bottom - yAxisMargin - static_cast<int>(pair.second * yScale);

					// Calculate the scaled bar height
					int barHeight = static_cast<int>(pair.second * yScale);

					// Ensure that the bar height does not exceed the control height
					barHeight = min(barHeight, clientRect.Height() - yAxisMargin - 2);

					int barWidth = min(maxBarWidth, static_cast<int>(validXScale) - 2);

					int left = x + 1;
					int right = x + barWidth;
					int bottom = clientRect.bottom - yAxisMargin - 1;
					int top = y==224 ? 222 : y;
					// 画x轴虚线
					if (drawXLine) {
						CPen dashedPen(PS_DOT, 1, RGB(0, 0, 0)); // Create a dashed pen
						CPen* pOldPen = pDC->SelectObject(&dashedPen);
						pDC->MoveTo(x + barWidth / 2, xAxisY);
						pDC->LineTo(x + barWidth / 2, clientRect.top - 20);
						pDC->SelectObject(pOldPen);
					}

					pDC->FillSolidRect(left, top, right - left, bottom - top, RGB(barColor[0], barColor[1], barColor[2])); // Blue bars

					// Draw Y value on the top of each bar
					if (drawValueOnTop)
					{
						CString yValue;
						// 设置字体颜色
						CFont* pOldFont = pDC->SelectObject(&valueFont);
						pDC->SetTextColor(RGB(valueColor[0], valueColor[1], valueColor[2]));
						yValue.Format(_T("%d"), pair.second);
						CSize textSize = pDC->GetTextExtent(yValue);
						pDC->SetBkMode(OPAQUE); // Set background mode to transparent
						pDC->SetBkColor(RGB(255, 255, 255));
						pDC->TextOut((2*x+barWidth)/2-textSize.cx/2, top - textSize.cy-2, yValue); // Draw Y value on top of the bar
						// 还原字体颜色
						pDC->SelectObject(pOldFont);
						pDC->SetTextColor(RGB(0, 0, 0));
					}

					// Draw X-axis label for Y not equal to 0
					CString xLabel;
					// 设置字体颜色
					CFont* pOldFont = pDC->SelectObject(&axisFont);
					pDC->SetTextColor(RGB(axisScaleColor[0], axisScaleColor[1], axisScaleColor[2]));
					//xLabel.Format(_T("%d"), pair.first); // Use data's x value as X-axis label
					xLabel = pair.first.c_str();
					pDC->SetBkMode(TRANSPARENT); // Set background mode to transparent
					CSize textSize = pDC->GetTextExtent(xLabel);
					pDC->TextOut((2 * x + barWidth) / 2 - textSize.cx / 2, clientRect.bottom - yAxisMargin + 5, xLabel); // Draw X-axis label
					// 还原字体颜色
					pDC->SelectObject(pOldFont);
					pDC->SetTextColor(RGB(0, 0, 0));
					validIndex++;
					// 绘制x轴刻度线
					pDC->MoveTo(x+barWidth/2, xAxisY);
					pDC->LineTo(x + barWidth / 2, xAxisY+5);

				}
			}
		}
	}
}

void DiscreteBarChart::setsortByValue(bool b)
{
	sortByValue = b;
}

void DiscreteBarChart::setDrawValueOnTop(bool b)
{
	drawValueOnTop = b;
}

void DiscreteBarChart::setDrawYLine(bool b)
{
	drawYLine = b;
}

void DiscreteBarChart::setDrawXLine(bool b)
{
	drawXLine = b;
}

void DiscreteBarChart::setBackgroundColor(int r, int g, int b)
{
	backgroundColor[0] = r;
	backgroundColor[1] = g;
	backgroundColor[2] = b;
}

void DiscreteBarChart::setBarColor(int r, int g, int b)
{
	barColor[0] = r;
	barColor[1] = g;
	barColor[2] = b;
}

void DiscreteBarChart::setValueColor(int r, int g, int b)
{
	valueColor[0] = r;
	valueColor[1] = g;
	valueColor[2] = b;
}

void DiscreteBarChart::setValueFont(CFont& font)
{
	valueFont.DeleteObject();
	LOGFONT lf;
	font.GetLogFont(&lf);
	valueFont.CreateFontIndirectW(&lf);
}

void DiscreteBarChart::setAxisFont(CFont& font)
{
	axisFont.DeleteObject();
	LOGFONT lf;
	font.GetLogFont(&lf);
	axisFont.CreateFontIndirectW(&lf);
}

void DiscreteBarChart::setTitleFont(CFont& font)
{
	titleFont.DeleteObject();
	LOGFONT lf;
	font.GetLogFont(&lf);
	titleFont.CreateFontIndirectW(&lf);
}

void DiscreteBarChart::setTitle(char* s)
{
	title = s;
}

void DiscreteBarChart::setYAxisNum(int i)
{
	yAxisNum = i;
}

void DiscreteBarChart::setYAxisLegend(char* y)
{
	yAxisLegend = y;
}

void DiscreteBarChart::setXAxisLegend(char* x)
{
	xAxisLegend = x;
}

void DiscreteBarChart::ComputeYAxisNum()
{
	if (clientRect.Height() < 50) {
		yAxisNum = 1;
	}
	else if (50 < clientRect.Height() && clientRect.Height() < 120) {
		yAxisNum = 2;
	}
	else if (120 < clientRect.Height() && clientRect.Height() < 250) {
		yAxisNum = 3;
	}
	else {
		yAxisNum = 4;
	}
}

void DiscreteBarChart::setaxisScaleColor(int r, int g, int b)
{
	axisScaleColor[0] = r;
	axisScaleColor[1] = g;
	axisScaleColor[2] = b;
}

void DiscreteBarChart::setTitleColor(int r, int g, int b)
{
	titleColor[0] = r;
	titleColor[1] = g;
	titleColor[2] = b;
}

void DiscreteBarChart::setAxisLegendColor(int r, int g, int b)
{
	axisLegendColor[0] = r;
	axisLegendColor[1] = g;
	axisLegendColor[2] = b;
}






