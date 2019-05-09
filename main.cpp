#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
const int mod = 1000000007;
int ftable [1001];
long long int primes [1000];
long long int recievedMessageHash[1000];
string dictionary [1001];
long long int dictionaryHash[1000];

long long int hasher(int h1, int h2){
    long long int x = recievedMessageHash[h2];
    long long int b = primes[h2-h1]*recievedMessageHash[h1]%mod;
    long long int a = x-b;
    a%=mod;
    a+=mod;
    a%=mod;
    return a;
}

int wordBreak(int textLength,int begin,int dc) {

    int res = 0;
    if (ftable[begin] != 0) {

        res=ftable[begin];
    }else{
        if (begin == textLength) {

            ftable[begin] = 1;
            return 1;
        }
        for (int i = 0; i < dc; i++) {
            if (begin == 0) {

                if ( dictionaryHash[i] == recievedMessageHash[dictionary[i].length() - 1]) {

                    res += wordBreak(textLength, begin + dictionary[i].length(), dc);
                    res%=mod;
                }
            } else {

                if ((dictionaryHash[i]%mod) == hasher(begin - 1, begin + dictionary[i].length() - 1)%mod) {
                    res += wordBreak(textLength, begin + dictionary[i].length(), dc);
                    res%=mod;
                }
            }
        }
        ftable[begin]=res;
    }
    return res;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project5 [input_file] [output_file]" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    for(int i=0;i<1001;i++){
        ftable[i]=0;
    }
    string recievedMessage;
    infile >> recievedMessage;
    int num;
    infile >> num;

    for (int i = 0; i < num; ++i) {
        infile >> dictionary[i];
    }

    int textlength = recievedMessage.length();

    primes[0]=1;
    for (int i = 1; i<textlength; i++)
        primes[i]= (primes[i-1]*11)%mod;

    recievedMessageHash[0]=recievedMessage.at(0);
    for (int i = 1; i < textlength; i++) {
        recievedMessageHash[i] = ((recievedMessage.at(i))+recievedMessageHash[i-1]*primes[1])%mod;
    }

    for (int i = 0; i < num; i++) {
        int wordLength = dictionary[i].length();
        for (int j = 0; j < wordLength; ++j) {
            if (j == 0)
                dictionaryHash[i] = dictionary[i].at(0);
            else
                dictionaryHash[i] = (((dictionaryHash[i]) * primes[1]) + dictionary[i].at(j)) % mod;
        }

    }

    int result = wordBreak(textlength, 0, num);
    result+=mod;
    result%=mod;
    outfile<<result<<endl;
    outfile.close();
    return 0;
}