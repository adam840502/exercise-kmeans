# k-means

使用Kmeans演算法作資料分群，並利用GnuPlot視覺化結果
<br><br>

使用資源
---
* [gnuplot-iostream](https://github.com/dstahlke/gnuplot-iostream)
* [Boost C++ Libraries](http://www.boost.org/)
<br>
<img src="/images/hierarchy.png" width="640" alt="hierarchy" />  
圖1.  程式架構示意圖
<br><br>

需求
---
<ul>
  <li>Windows 作業系統</li>
  <li>Boost C++ Libraries</li>
  <li>gnuplot程式</li>
  <li>資料 (現成資料:iris.data.txt) 
  <ul>
    <li>格式</li> 
    <ul>
      <li>以LF結尾</li> 
      <li>以逗號隔開各變數</li> 
      <li>每一行為一樣本</li> 
    </ul>
    <li>範例<br>
        5.1,3.5,1.4,0.2,Iris-setosa<br>
        4.9,3.0,1.4,0.2,Iris-setosa<br>
        4.7,3.2,1.3,0.2,Iris-setosa<br>
        4.6,3.1,1.5,0.2,Iris-setosa ...
        
    </li>
  </ul>
</ul>
<br><br>

syntax
---
    kmeans.exe  data檔名  形心數  kmeans執行次數  兩次繪圖間隔時間(毫秒)
<br><br>

範例
---
    kmeans.exe iris.data.txt 3 20 0
    
上例為讀取iris.data.txt此檔案, 分成三群, 總共執行20次, 兩張圖繪製間	的時間至少隔0毫秒  
可執行範例Example.bat
<br>

<img src="/images/kmeans2.png" alt="kmeans2" width="640" />  
圖2.  執行程式後會先進行數入參數對應項目的確認。<br><br>

<img src="/images/kmeans3.png" alt="kmeans3" width="640" />  
圖3.  確認後，程式將計算數值變數量與類別變數量，並逐列(一列為一樣本)進行變數的解析。<br><br>

<img src="/images/kmeans4.png" alt="kmeans4" width="640" />  
圖4.  接著，程式將於每次運算開始時隨機產生形心，並將K-means演算法過程視覺化後呈現至銀幕上。此視窗為範例樣本Iris中，第一、第二變數之二維圖。<br><br>

<img src="/images/kmeans4-1.png" alt="kmeans4-1" width="640" />  
圖5.  圖中視窗為範例樣本Iris中之第三、第四變數之二維圖。<br><br>

<img src="/images/kmeans4-2.png" alt="kmeans4-2" width="640" />  
圖6.  結束運算後，cmd視窗將列出各次運算結果之SSE值，並列出最低SSE與平均SSE之值。
