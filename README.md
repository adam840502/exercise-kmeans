# k-means

使用Kmeans演算法作資料分群，並利用GnuPlot視覺化結果  
使用[gnuplot-iostream](https://github.com/dstahlke/gnuplot-iostream)
<br><br><br>
<img src="/images/hierarchy.png" width=640px alt="hierarchy"></img>

需求
---
<ul>
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

syntax
---
    kmeans.exe  data檔名  形心數  kmeans執行次數  兩次繪圖間隔時間(毫秒)

範例
---
    kmeans.exe iris.data.txt 3 20 0
  
上例為讀取iris.data.txt此檔案, 分成三群, 總共執行20次, 兩張圖繪製間	的時間至少隔0毫秒  
可執行範例Example.bat
