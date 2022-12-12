#include "Timer.h"

/*
使用方法：

本程式使用<chrono>函式庫
創建Timer class 的物件 my_timer(int total_time)，total_time設定倒數計時的起始時間
Timer my_timer(10000);
此物件包含：_time_elapsed 創建物件以後經過的時間 _time_left 創建物件時開始倒計時剩餘的時間
時間單位為ms

my_timer.timer_update() 更新計時器
get_elapsed_s() 回傳不同的資料(s 或 ms)，回傳值型別為int
get_elapsed_ms()
get_left_s()
get_left_ms()

*/
 

// constructor
Timer:: Timer(int total_time){
    _time_start = chrono::steady_clock::now();

    int j = 1;
    for(int i = 1; i < 100000000; i++){
        j += i;
    }
    cout << j;

    _time_now = chrono::steady_clock::now();

    chrono::milliseconds temp_total(total_time);
    _time_total = temp_total;  // setting total time

    chrono::milliseconds temp_elapsed(chrono::duration_cast<chrono::milliseconds>(_time_now - _time_start).count());
    _time_elapsed = temp_elapsed;  //setting elapsed time

    _time_left = _time_total - _time_elapsed; //setting left time;

    // cout << "Timer Constructed" << endl;
    // cout << "Time total : " << _time_total.count() << endl;
    // cout << "Time elapsed : " << _time_elapsed.count() << endl;
    // cout << "Time left : " << _time_left.count() << endl;

}


bool Timer:: timer_update(){

    _time_now = chrono::steady_clock::now();
    
    chrono::milliseconds temp_elapsed(chrono::duration_cast<chrono::milliseconds>(_time_now - _time_start).count());
    _time_elapsed = temp_elapsed;  //setting elapsed time

    _time_left = _time_total - _time_elapsed; //setting left time;

    if(_time_left.count() <= 0){
        cout << "Time's Up" << endl;
        return false;
    }
    return true;

}

int Timer:: get_elapsed_s(){
    return _time_elapsed.count() / 1000;
}
int Timer:: get_left_s(){
    return ceil(_time_left.count() / 1000.0);
}
int Timer:: get_elapsed_ms(){
    return _time_elapsed.count();
}
int Timer:: get_left_ms(){
    return _time_left.count();
}


// // Example code
// int main()
// {
//     Timer TIMER(10000);
//     while(1){
//         if(TIMER.timer_update()){
//             //cout << TIMER.get_elapsed_s() << endl;
//             cout << TIMER.get_left_ms() << endl;
//         }
//         else{
//             break;
//         }
       
//     }
// }




// // time duration
// // 宣告 chrono:: (milliseconds, minutes, seconds) t
// // 輸出duration cout << t.count()
// // 單位轉換 cout << chrono::duration_cast<chrono::minutes>(t).count() << endl;

// /*
// chrono::minutes t1( 10 );
// chrono::seconds t2( 60 );
// chrono::seconds t3 = t1 - t2;
// chrono::milliseconds t4 = t2;
// cout << t3.count() << " second" << endl;
// cout << t4.count() << "ms" << endl;
// */

// // time_point 
// // 現在時間 auto now = chrono::system_clock::now();
// // time_point 運算後會得到 duration  time_point + duration = time_point
// // auto newtime = now + chrono::hours(10);
// // 單位轉換 time_point_cast<>()

// /*
// chrono::steady_clock::time_point ti = chrono::steady_clock::now();
// int i = 0;
// while(i < 10000000){
//     i++;
// }
// chrono::steady_clock::time_point tf = chrono::steady_clock::now();
// cout << "Took " << chrono::duration_cast<chrono::microseconds>(tf - ti).count() << "us.\n";
// */



// // chrono 碼表與倒數計時器
//     while(true){
//         // 碼表
//         // auto time_now = chrono::steady_clock::now();
//         // chrono::seconds time_elapsed = chrono::duration_cast<chrono::seconds>(time_now - time_start);
//         // cout << time_elapsed.count() << endl;

//         // 倒數計時
//         time_now = chrono::steady_clock::now();
//         chrono::seconds time_left = chrono::duration_cast<chrono::seconds>(timer - (time_now - time_start));
//         cout << time_left.count() << endl;
//         if(time_left.count() == 0){
//             cout << "Time's Up !!!" << endl;
//             break;
//         }
//     }