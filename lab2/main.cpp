#include <iostream>
#include <string>

using namespace std;

struct Node {
    string song_title;
    Node* next;
};

void ekleme(Node*& header, string title){
    Node* new_node= new Node();
    new_node->song_title= title;
    new_node->next=header;
    header=new_node;
    cout <<"islem basarili"<< endl;
}


void sarkiara(Node* header, string title){
if(header== nullptr){
    cout<<"sarki yok"<<endl;
    return;
}
Node* durum=header;
while(durum != nullptr){
    if(durum->song_title== title){
        cout<<"sarki bulundu"<<endl;
        return;
    }
    durum= durum->next;
}
cout<<title<<" playlistte yok"<<endl;
}


void display(Node* header){
if(header== nullptr){
    cout<<"sarki yok"<<endl;
    return;
}
int numaralar=1;
Node* durum=header;
cout<<"PLAYLIST\n"<<endl;
while(durum!=nullptr){
    cout<<numaralar<<"_"<<durum->song_title<<endl;
    durum=durum->next;
    numaralar++;
}
}

int main()
{
    string title;
    Node* header= nullptr;
    int choice;
    
    cout<< "1.Add song\n2.Search song\n3.List\n4.Exit\n"<<endl;
    cin>>choice;
    
    switch(choice){
case 1:
cout<<"add a song"<<endl;
getline(cin,title);
ekleme(header,title);
break;
case 2:
cout<<"search a song"<<endl;
getline(cin,title);
sarkiara(header,title);
break;
case 3:
display(header);
break;
case 4:
cout<<"exiting"<<endl;
break;
    }


    return 0;
}
