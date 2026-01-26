#include<iostream>
#include<iomanip>
#include "data_loader.h"
#include "parser.h"

using namespace std;

int main()
{
    try {
        cout<<"=== HyperTradeX Phase 1 - Data Loader & Parser ==="<<endl;


        //s1 - load the csv file
        cout<<"\n[1] Loading CSV file..."<<endl;
        vector<string>lines = DataLoader::load_file("data/BTCUSDT_1m.csv");
        cout<< "Loaded "<<lines.size() << " lines"<<endl;

        //s2 - parse klines (skip header)
        cout<<"\n[2] Parsing klines..."<<endl;
        vector<Kline>klines;

        for(size_t i = 1; i < lines.size(); i++)
        {
            Kline kline = Parser::parse_kline(lines[i]);
            klines.push_back(kline);
        }

        cout<<" Parsed "<<klines.size()<<" klines"<<endl;

         // Step 3: Print first 5 klines to verify
        cout << "\n[3] First 5 klines:" << endl;
        cout << fixed << setprecision(2);

        cout << left << setw(18) << "Timestamp" 
             << setw(8) << "Symbol" 
             << setw(10) << "Open" 
             << setw(10) << "High" 
             << setw(10) << "Low" 
             << setw(10) << "Close" 
             << setw(10) << "Volume" << endl;
        
        for (size_t i = 0; i < min(size_t(5), klines.size()); ++i) {
            const auto& kline = klines[i];
            cout << left << setw(18) << kline.timestamp_ms 
                 << setw(8) << kline.symbol_id
                 << setw(10) << kline.open 
                 << setw(10) << kline.high 
                 << setw(10) << kline.low 
                 << setw(10) << kline.close 
                 << setw(10) << kline.volume << endl;
        }
        
        cout << "\n✅ Phase 1 Test Complete! Data loader & parser working correctly." << endl;
        
        return 0;
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        return 1;
    }
}
