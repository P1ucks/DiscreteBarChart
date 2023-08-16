# DisceteBarChart for MFC

针对Hight-Speed Charting不能离散显示横坐标的问题，重新设计实现了一款MFC下可以自定义x轴的柱状图。

还有海量bug与不足之处，仅能实现基本的显示需求，后续有空会继续开发更新。

喜欢这个项目别忘了给颗⭐

- 示例

![在这里插入图片描述](https://img-blog.csdnimg.cn/8961600ccec8435a9668d97ecfd642f0.png)

- 按y轴数据大小排序

![按y数据排序](https://img-blog.csdnimg.cn/296d678a12914b15bc035cec8bf3c91e.png)

## Top News

**`2023-8-16 `**:**更新了坐标轴轴例显示**

<img src="https://img-blog.csdnimg.cn/599e2c0d017a4a96afc7a80dd37d4837.png" alt="在这里插入图片描述"  />

## 使用

1. 首先创建一个Picture Control控件
2. 在你的MFC对话框的OnPaint()函数中添加如下代码

```cpp
void YourDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	// 模拟数据
	unordered_map<string, int> testData;
	testData.emplace("apple", 31);
	testData.emplace("B", 123);
	testData.emplace("c", 70);
	testData.emplace("1", 62);
	testData.emplace("99", 79);
	// 1. 获取控件用户区域
	CRect clientRect;
	GetDlgItem(IDC_STATIC)->GetClientRect(clientRect);
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();
	// 2.创建
	DiscreteBarChart barChart;
	barChart.create(pDC, clientRect);
	// 3.设置一些参数
	barChart.setTitle("discrete bar chart");
	barChart.setDrawValueOnTop(true);
	// 4. 绘图
	barChart.Draw(testData);

	CDialogEx::OnPaint();
	GetDlgItem(IDC_STATIC)->ReleaseDC(mdc);
}
```

仅有一个绘图函数

```cpp
void Draw(std::unordered_map<std::string, int>& data);
```

std::string为x轴数据，int为对应的y轴数据。 

