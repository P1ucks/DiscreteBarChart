# DisceteBarChart for MFC

Aiming at the issue of inability to discretely display the horizontal axis in High-Speed Charting, a redesigned solution has been implemented to create a customizable bar chart under MFC.

Basic display requirements have been fulfilled, but there are numerous bugs and shortcomings. I will continue to develop and update the application when time permits

If you like this project, don't forget to give it a ⭐!

- Example:

![在这里插入图片描述](https://img-blog.csdnimg.cn/8961600ccec8435a9668d97ecfd642f0.png)

- Sorting by Y-axis Data Magnitude.

![按y数据排序](https://img-blog.csdnimg.cn/296d678a12914b15bc035cec8bf3c91e.png)

## Top News

**`2023-8-16 `**:**Updated the axis legend display.**

<img src="https://img-blog.csdnimg.cn/599e2c0d017a4a96afc7a80dd37d4837.png" alt="在这里插入图片描述"  />

## How To Use

1. First, create a **Picture Control** widget.

![在这里插入图片描述](https://img-blog.csdnimg.cn/491ed22613b84b2e924f44fa24fd9dd6.png)

2. Add the following code to the OnPaint() function of the MFC dialog:

```cpp
void YourDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	// Simulated data
	unordered_map<string, int> testData;
	testData.emplace("apple", 31);
	testData.emplace("B", 123);
	testData.emplace("c", 70);
	testData.emplace("1", 62);
	testData.emplace("99", 79);
	// 1. Get clientRect and pDC
	CRect clientRect;
	GetDlgItem(IDC_STATIC)->GetClientRect(clientRect);
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();
	// 2. Create barchart
	DiscreteBarChart barChart;
	barChart.create(pDC, clientRect);
	// 3. Set some parameters.
	barChart.setTitle("discrete bar chart");
	barChart.setDrawValueOnTop(true);
	// 4. Draw
	barChart.Draw(testData);

	CDialogEx::OnPaint();
	GetDlgItem(IDC_STATIC)->ReleaseDC(mdc);
}
```

Currently, there is only one drawing function.

```cpp
void Draw(std::unordered_map<std::string, int>& data);
```

Use `std::string` for the X-axis data and `int` for the corresponding Y-axis data.

