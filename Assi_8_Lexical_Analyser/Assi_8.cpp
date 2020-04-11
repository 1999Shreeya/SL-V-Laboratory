//============================================================================
// Name        : Assi_8
// Author      : Shreeya Thigale
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef struct usd{
	string symbol;
	string sym_type;
	int index;
}usd_tbl;

//search in vector
int searchIt (vector<string> v,string s) {
    vector<string> :: iterator it;
    it = find (v.begin(), v.end(), s);
    return  (it-v.begin())+1;
}

void printUST(vector<usd_tbl> ust) {
	cout << "+----------+--------+---------+" << endl;
    cout << "|  Symbol  |  TYPE  |  INDEX  |" << endl;
    cout << "+----------+--------+---------+" << endl;
    for(vector<usd_tbl>::iterator i = ust.begin(); i != ust.end(); ++i) {
        cout << "|" << setw(10) << (*i).symbol << "|" << setw(8) << (*i).sym_type << "|" << setw(9) << (*i).index << "|" << endl;
    }
    cout << "+----------+--------+---------+" << endl;
}

int main() {
	FILE *fp,*fp1,*fp2;
	int i=1;
	char str[1000];
	char data[1000];
	int multi_cmt=0;//for multi line comment
	vector<string>trm;
    vector<string> lit;
    vector<string>ident;
    vector<usd_tbl> ust;
	vector< string >::iterator it;
	char operators[] = "<>+-*/!=";
	
	cout<<"\nINPUT PROGRAM :: \n\n";
	fp2 = fopen("input.c","r+");
		while(fgets(data, 1000, (FILE*) fp2)!=NULL)
			cout<<data;
		cout<<endl;
	fclose(fp2);

	fp = fopen("keywords.txt","r+");
	fp1 = fopen("input.c","r+");
	//Create TRM table
	while(fgets(data, 1000, (FILE*) fp)!=NULL) {
		strcpy(str,data);
		char* token = strtok(str, " ");
        while (token != NULL) {
            trm.push_back(token); i++;
            token = strtok(NULL, " ");
        }
	}

	//tokenize by \n
    char delim[]="\n";
    while(fgets(data, 1000, (FILE*) fp1)!=NULL) {
        strcpy(str,data);
        char* token = strtok(str,delim);
        while (token != NULL){
        	if(multi_cmt==1) i++;  //for ignoring multi line cmt
        	//if token is present in TRM
            it = find(trm.begin(),trm.end(),token);
            if (it != trm.end()) {
                usd_tbl temp;
                temp.symbol = token;
                temp.sym_type = "TRM";
                temp.index = it - trm.begin() + 1;
                ust.push_back(temp);
            }

            //character check
            else{
                int len=strlen(token);int i=0;
                while(i!=len){
                string temp_word,temp_no,temp;

                	//multi line comment start
					if(token[i]=='/' && token[i+1]=='*'){
						multi_cmt=1;
						i+=2; continue;
					}

                	//multi line cmt end
					else if(token[i]=='*' && token[i+1]=='/'){
                		multi_cmt=0;
                		i+=2; continue;
                	}
					//ignore tokens between multi line comment symbols
                	else if(multi_cmt==1)
                	{ i++; continue;}

					//single line comment
					if(token[i]=='/' && token[i+1]=='/'){
						break;
					}

                	temp.push_back(token[i]);
                    //check if char present in TRM
                    it = find (trm.begin(), trm.end(), temp ); //search in TRM
                    if (it != trm.end() && temp!="\"" && !(strchr(operators,token[i]) && strchr(operators,token[i+1]))  ){
                        usd_tbl temp;
                        temp.symbol = token[i];
                        temp.sym_type = "TRM";
                        temp.index = it - trm.begin() + 1;
                        ust.push_back(temp);
                    }


                    else if(isalpha(token[i])){ //alphabet
                        string temp_header;
                        temp_word.push_back(token[i]);
                        while(isalnum(token[i+1]) || token[i+1]=='_'){
                            i++;
                            temp_word.push_back(token[i]);
                        }
                        vector<string> :: iterator it = find(trm.begin(),trm.end(),temp_word);
                        //if WORD is present in TRM, insert into UST
                        if( it != trm.end() ) {
                            usd_tbl temp;
                            temp.symbol = temp_word;
                            temp.sym_type = "TRM";
                            temp.index = it - trm.begin() + 1;
                            ust.push_back(temp);
                        }
                        //if not present in TRM check in IDENT
                        else {
                            int ind = searchIt(ident,temp_word);
                            if( ind <= ident.size() ) { //if present in IDENT,insert in UST
                                usd_tbl temp;
                                temp.symbol = temp_word;
                                temp.sym_type = "IDN";
                                temp.index = ind;
                                ust.push_back(temp);
                            }
                            else {//if not in IDENT,insert in IDENT and UST
                                ident.push_back(temp_word);
                                usd_tbl temp;
                                temp.symbol = temp_word;
                                temp.sym_type = "IDN";
                                temp.index = ident.size();
                                ust.push_back(temp);
                            }
                        }

                        //for header files
					   if(temp_word=="include"){
							i+=2;
							while(1){
								temp_header.push_back(token[i]); i++;
								if(token[i]=='>'){//Push literal into LIT table and USD table
									ident.push_back(temp_header);
									usd_tbl new_header;
									new_header.symbol = temp_header;
									new_header.sym_type = "IDN";
									new_header.index = ident.size();
									ust.push_back(new_header);
									break;
								}
							}
					   }
                    }


                    else if(isdigit(token[i])){ //number
                    	temp_no.push_back(token[i]);
                        while(isdigit(token[i+1])){
                                i++;
                                temp_no.push_back(token[i]);
                        }
                        //insert in LIT and UST;
                        lit.push_back(temp_no);
                        usd_tbl temp;
                        temp.symbol = temp_no;
                        temp.sym_type = "LIT";
                        temp.index = lit.size();
                        ust.push_back(temp);
                    }

                    else if(temp=="\""){ //Quotes
                    	//Push first quotesymbol in USD
                    	it = find (trm.begin(), trm.end(), temp ); //search in TRM
                    	usd_tbl temp;
                    	temp.symbol = token[i];
                    	temp.sym_type = "TRM";
						temp.index = it - trm.begin() + 1;
						ust.push_back(temp);
						i++;
						//make literal
						string temp_lit;
						while(1){
							temp_lit.push_back(token[i]); i++;
							if(token[i]==34){
								//Push literal into LIT table and USD table
								lit.push_back(temp_lit);
								usd_tbl new_lit;
								new_lit.symbol = temp_lit;
								new_lit.sym_type = "LIT";
								new_lit.index = lit.size();
								ust.push_back(new_lit);
								break;
							}
						}

						//Push second quote symbol in USD
						ust.push_back(temp);
                    }
                    else if(strchr(operators,token[i]) && strchr(operators,token[i+1])){   //binary operators
                    	string temp_op;
                    	temp_op.push_back(token[i]); temp_op.push_back(token[i+1]); i++;
                    	//Push binary operators in usd
                    	it = find (trm.begin(), trm.end(), temp_op ); //search in TRM
                    	if(it!=trm.end()){
                    		usd_tbl new_op;
                    		new_op.symbol = temp_op;
							new_op.sym_type = "TRM";
							new_op.index =  it - trm.begin() + 1;
							ust.push_back(new_op);
                    	}
                    }
                    i++;
                }
            }
            token = strtok(NULL," ");
        }
    }
    //print trm
    cout<<"\nTERMINAL TABLE :: \n";
    cout << "\n|-------+---------+" << endl;
	cout << "| Index |  Symbol |" << endl;
	cout << "+-------+---------+" << endl;
	for(int i=0;i<trm.size();i++){
		cout<< "|" << setw(7)<<i+1<< "|" << setw(8)<<trm[i]<<" | "<<endl;
	}
	cout << "+-------+---------+" << endl;
    printUST(ust);

    //print idn
    cout<<"\nIDENTIFIER TABLE :: \n";
    cout << "\n|-------+---------+" << endl;
	cout << "| Index |  Symbol |" << endl;
	cout << "+-------+---------+" << endl;
	for(int i=0;i<ident.size();i++){
		cout<< "|" << setw(7)<<i+1<< "|" << setw(8)<<ident[i]<<" | "<<endl;
	}
	cout << "+-------+---------+" << endl;

     //print lit
    cout<<"\nLITERAL TABLE :: \n";
	cout << "\n|-------+---------+" << endl;
	cout << "| Index |  Symbol |" << endl;
	cout << "+-------+---------+" << endl;
	for(int i=0;i<lit.size();i++){
		cout<< "|" << setw(7)<<i+1<< "|" << setw(8)<<lit[i]<<" | "<<endl;
	}
	cout << "+-------+---------+" << endl;
	fclose(fp1);
	fclose(fp);
	return 0;
}
